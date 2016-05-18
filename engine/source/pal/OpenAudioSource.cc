#include <hawkeye/Base.h>
#include <hawkeye/Node.h>
#include <hawkeye/AudioController.h>
#include <hawkeye/AudioSource.h>
#include <hawkeye/Game.h>
#include <hawkeye/Node.h>
#include "OpenAudioSource.hh"
#include "OpenAudioController.hh"

namespace hawkeye {
namespace pal {


using hawkeye::AudioSource;


OpenAudioSource::OpenAudioSource(
	OpenAudioBuffer* buffer,
	ALuint source) : AudioSource(), _alSource(source), _buffer(buffer), _looped(false), _gain(1.0f),
		_pitch(1.0f)
{
    GP_ASSERT(buffer);

    if (isStreamed())
        AL_CHECK(alSourceQueueBuffers(_alSource, 1, &buffer->_alBufferQueue[0]));
    else
        AL_CHECK(alSourcei(_alSource, AL_BUFFER, buffer->_alBufferQueue[0]));

    AL_CHECK(alSourcei(_alSource, AL_LOOPING, _looped && !isStreamed()));

    AL_CHECK( alSourcef(_alSource, AL_PITCH, _pitch) );
    AL_CHECK( alSourcef(_alSource, AL_GAIN, _gain) );
    AL_CHECK( alSourcefv(_alSource, AL_VELOCITY, (const ALfloat*)&_velocity) );
}

OpenAudioSource::~OpenAudioSource()
{
    if (_alSource)
    {
        // Remove the source from the controller's set of currently playing sources
        // regardless of the source's state. E.g. when the AudioController::pause is called
        // all sources are paused but still remain in controller's set of currently
        // playing sources. When the source is deleted afterwards, it should be removed
        // from controller's set regardless of its playing state.
        OpenAudioController* audioController = dynamic_cast<OpenAudioController*>(Game::getInstance()->getAudioController());
        GP_ASSERT(audioController);
        audioController->removePlayingSource(this);

        AL_CHECK(alDeleteSources(1, &_alSource));
        _alSource = 0;
    }
    SAFE_RELEASE(_buffer);
}

OpenAudioSource* OpenAudioSource::create(const char* url, bool streamed)
{
    // Load from a .audio file.
    std::string pathStr = url;
    if (pathStr.find(".audio") != std::string::npos)
    {
        Properties* properties = Properties::create(url);
        if (properties == NULL)
        {
            GP_ERROR("Failed to create audio source from .audio file.");
            return NULL;
        }

        OpenAudioSource* audioSource = create((strlen(properties->getNamespace()) > 0) ? properties : properties->getNextNamespace());
        SAFE_DELETE(properties);
        return audioSource;
    }

    // Create an audio buffer from this URL.
    OpenAudioBuffer* buffer = OpenAudioBuffer::create(url, streamed);
    if (buffer == NULL)
        return NULL;

    // Load the audio source.
    ALuint alSource = 0;

    AL_CHECK( alGenSources(1, &alSource) );
    if (AL_LAST_ERROR())
    {
        SAFE_RELEASE(buffer);
        GP_ERROR("Error generating audio source.");
        return NULL;
    }

    return new OpenAudioSource(buffer, alSource);
}

OpenAudioSource* OpenAudioSource::create(Properties* properties)
{
    // Check if the properties is valid and has a valid namespace.
    GP_ASSERT(properties);
    if (!properties || !(strcmp(properties->getNamespace(), "audio") == 0))
    {
        GP_ERROR("Failed to load audio source from properties object: must be non-null object and have namespace equal to 'audio'.");
        return NULL;
    }

    std::string path;
    if (!properties->getPath("path", &path))
    {
        GP_ERROR("Audio file failed to load; the file path was not specified.");
        return NULL;
    }

    bool streamed = false;
    if (properties->exists("streamed"))
    {
        streamed = properties->getBool("streamed");
    }

    // Create the audio source.
    OpenAudioSource* audio = OpenAudioSource::create(path.c_str(), streamed);
    if (audio == NULL)
    {
        GP_ERROR("Audio file '%s' failed to load properly.", path.c_str());
        return NULL;
    }

    // Set any properties that the user specified in the .audio file.
    if (properties->exists("looped"))
    {
        audio->setLooped(properties->getBool("looped"));
    }
    if (properties->exists("gain"))
    {
        audio->setGain(properties->getFloat("gain"));
    }
    if (properties->exists("pitch"))
    {
        audio->setPitch(properties->getFloat("pitch"));
    }
    Vector3 v;
    if (properties->getVector3("velocity", &v))
    {
        audio->setVelocity(v);
    }

    return audio;
}

OpenAudioSource::State OpenAudioSource::getState() const
{
    ALint state;
    AL_CHECK( alGetSourcei(_alSource, AL_SOURCE_STATE, &state) );

    switch (state)
    {
        case AL_PLAYING:
            return PLAYING;
        case AL_PAUSED:
            return PAUSED;
        case AL_STOPPED:
            return STOPPED;
        default:
            return INITIAL;
    }
    return INITIAL;
}

bool OpenAudioSource::isStreamed() const
{
    GP_ASSERT(_buffer);
    return _buffer->_streamed;
}

void OpenAudioSource::play()
{
    AL_CHECK( alSourcePlay(_alSource) );

    // Add the source to the controller's list of currently playing sources.
    OpenAudioController* audioController = dynamic_cast<OpenAudioController*>(Game::getInstance()->getAudioController());
    GP_ASSERT(audioController);
    audioController->addPlayingSource(this);
}

void OpenAudioSource::pause()
{
    AL_CHECK( alSourcePause(_alSource) );

    // Remove the source from the controller's set of currently playing sources
    // if the source is being paused by the user and not the controller itself.
    OpenAudioController* audioController = dynamic_cast<OpenAudioController*>(Game::getInstance()->getAudioController());
    GP_ASSERT(audioController);
    audioController->removePlayingSource(this);
}

void OpenAudioSource::resume()
{
    if (getState() == PAUSED)
    {
        play();
    }
}

void OpenAudioSource::stop()
{
    AL_CHECK( alSourceStop(_alSource) );

    // Remove the source from the controller's set of currently playing sources.
    OpenAudioController* audioController = dynamic_cast<OpenAudioController*>(Game::getInstance()->getAudioController());
    GP_ASSERT(audioController);
    audioController->removePlayingSource(this);
}

void OpenAudioSource::rewind()
{
    AL_CHECK( alSourceRewind(_alSource) );
}

bool OpenAudioSource::isLooped() const
{
    return _looped;
}

void OpenAudioSource::setLooped(bool looped)
{
    AL_CHECK(alSourcei(_alSource, AL_LOOPING, (looped && !isStreamed()) ? AL_TRUE : AL_FALSE));
    if (AL_LAST_ERROR())
    {
        GP_ERROR("Failed to set audio source's looped attribute with error: %d", AL_LAST_ERROR());
    }
    _looped = looped;
}

float OpenAudioSource::getGain() const
{
    return _gain;
}

void OpenAudioSource::setGain(float gain)
{
    AL_CHECK( alSourcef(_alSource, AL_GAIN, gain) );
    _gain = gain;
}

float OpenAudioSource::getPitch() const
{
    return _pitch;
}

void OpenAudioSource::setPitch(float pitch)
{
    AL_CHECK( alSourcef(_alSource, AL_PITCH, pitch) );
    _pitch = pitch;
}

const Vector3& OpenAudioSource::getVelocity() const
{
    return _velocity;
}

void OpenAudioSource::setVelocity(const Vector3& velocity)
{
    AL_CHECK( alSourcefv(_alSource, AL_VELOCITY, (ALfloat*)&velocity) );
    _velocity = velocity;
}

void OpenAudioSource::setVelocity(float x, float y, float z)
{
    setVelocity(Vector3(x, y, z));
}


void OpenAudioSource::transformChanged(Transform* transform, long cookie)
{
    if (node)
    {
        Vector3 translation = node->getTranslationWorld();
        AL_CHECK( alSourcefv(_alSource, AL_POSITION, (const ALfloat*)&translation.x) );
    }
}

AudioSource* OpenAudioSource::clone(NodeCloneContext& context)
{
    GP_ASSERT(_buffer);

    ALuint alSource = 0;
    AL_CHECK( alGenSources(1, &alSource) );
    if (AL_LAST_ERROR())
    {
        GP_ERROR("Unable to cloning audio.");
        return NULL;
    }
    OpenAudioSource* audioClone = new OpenAudioSource(_buffer, alSource);

    _buffer->addRef();
    audioClone->setLooped(isLooped());
    audioClone->setGain(getGain());
    audioClone->setPitch(getPitch());
    audioClone->setVelocity(getVelocity());
    if (Node* node = getNode())
    {
        Node* clonedNode = context.findClonedNode(node);
        if (clonedNode)
        {
            audioClone->setNode(clonedNode);
        }
    }
    return audioClone;
}

bool OpenAudioSource::streamDataIfNeeded()
{
    GP_ASSERT( isStreamed() );
    if( getState() != PLAYING )
        return false;

    int queuedBuffers;
    alGetSourcei(_alSource, AL_BUFFERS_QUEUED, &queuedBuffers);

    int buffersNeeded = std::min<int>(_buffer->_buffersNeededCount, OpenAudioBuffer::STREAMING_BUFFER_QUEUE_SIZE);
    if (queuedBuffers < buffersNeeded)
    {
        while (queuedBuffers < buffersNeeded)
        {
            if (!_buffer->streamData(_buffer->_alBufferQueue[queuedBuffers], _looped))
                return false;

            AL_CHECK( alSourceQueueBuffers(_alSource, 1, &_buffer->_alBufferQueue[queuedBuffers]) );
            queuedBuffers++;
        }
    }
    else
    {
        int processedBuffers;
        alGetSourcei(_alSource, AL_BUFFERS_PROCESSED, &processedBuffers);

        while (processedBuffers-- > 0)
        {
            ALuint bufferID;
            AL_CHECK( alSourceUnqueueBuffers(_alSource, 1, &bufferID) );
            if (!_buffer->streamData(bufferID, _looped))
                return false;

            AL_CHECK( alSourceQueueBuffers(_alSource, 1, &bufferID) );
        }
    }
    return true;
}

}}
