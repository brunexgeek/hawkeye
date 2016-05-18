#ifndef HAWKEYE_PAL_AUDIOSOURCE_HH
#define HAWKEYE_PAL_AUDIOSOURCE_HH

#include <hawkeye/Vector3.h>
#include <hawkeye/Ref.h>
#include <hawkeye/Transform.h>
#include <hawkeye/openal.h>
#include <hawkeye/AudioSource.h>
#include "OpenAudioBuffer.hh"

namespace hawkeye {

class Node;
class NodeCloneContext;

namespace pal {


using hawkeye::AudioSource;


/**
 * Defines an audio source in 3D space.
 *
 * This can be attached to a Node for applying its 3D transformation.
 *
 * @see http://gameplay3d.github.io/GamePlay/docs/file-formats.html#wiki-Audio
 */
class OpenAudioSource : public hawkeye::AudioSource
{
public:

    friend class hawkeye::Node;
    friend class OpenAudioController;

    /**
     * Create an audio source. This is used to instantiate an Audio Source. Currently only wav, au, and raw files are supported.
     * Alternately, a URL specifying a Properties object that defines an audio source can be used (where the URL is of the format
     * "<file-path>.<extension>#<namespace-id>/<namespace-id>/.../<namespace-id>" and "#<namespace-id>/<namespace-id>/.../<namespace-id>" is optional).
     *
     * @param url The relative location on disk of the sound file or a URL specifying a Properties object defining an audio source.
     * @param streamed Don't read the entire audio buffer first before playing, instead play immediately from a stream that is read on demand.
     * @return The newly created audio source, or NULL if an audio source cannot be created.
     * @script{create}
     */
    static OpenAudioSource* create(const char* url, bool streamed = false);

    /**
     * Create an audio source from the given properties object.
     *
     * @param properties The properties object defining the audio source (must have namespace equal to 'audio').
     * @return The newly created audio source, or <code>NULL</code> if the audio source failed to load.
     * @script{create}
     */
    static OpenAudioSource* create(Properties* properties);

    /**
     * Plays the audio source.
     */
    void play();

    /**
     * Pauses the playing of the audio source.
     */
    void pause();

    /**
     * Resumes playing of the audio source.
     */
    void resume();

    /**
     * Stops the playing of the audio source.
     */
    void stop();

    /**
     * Rewinds the audio source to the beginning.
     */
    void rewind();

    /**
     * Gets the current state of the audio source.
     *
     * @return PLAYING if the source is playing, STOPPED if the source is stopped, PAUSED if the source is paused and INITIAL otherwise.
     */
    AudioSource::State getState() const;

    /**
     * Determines whether the audio source is streaming or not.
     *
     * @return true if the audio source is streaming, false if not.
     */
    bool isStreamed() const;

    /**
     * Determines whether the audio source is looped or not.
     *
     * @return true if the audio source is looped, false if not.
     */
    bool isLooped() const;

    /**
     * Sets the state of the audio source to be looping or not.
     *
     * @param looped true to loop the sound, false to not loop it.
     */
    void setLooped(bool looped);

    /**
     * Returns the gain of the audio source.
     *
     * @return The gain.
     */
    float getGain() const;

    /**
     * Sets the gain/volume of the audio source.
     *
     * @param gain The gain/volume of the source.
     */
    void setGain(float gain);

    /**
     * Returns the pitch of the audio source.
     *
     * @return The pitch.
     */
    float getPitch() const;

    /**
     * Sets the pitch of the audio source.
     *
     * @param pitch The pitch of the source.
     */
    void setPitch(float pitch);

    /**
     * Gets the velocity of the audio source.
     *
     * @return The velocity as a vector.
     */
    const Vector3& getVelocity() const;

    /**
     * Sets the velocity of the audio source.
     *
     * @param velocity A vector representing the velocity.
     */
    void setVelocity(const Vector3& velocity);

    /**
     * Sets the velocity of the audio source.
     *
     * @param x The x coordinate of the velocity.
     * @param y The y coordinate of the velocity.
     * @param z The z coordinate of the velocity.
     */
    void setVelocity(float x, float y, float z);

protected:

    /**
     * Constructor that takes an AudioBuffer.
     */
    OpenAudioSource(OpenAudioBuffer* buffer, ALuint source);

    /**
     * Destructor.
     */
    virtual ~OpenAudioSource();

    /**
     * Hidden copy assignment operator.
     */
    AudioSource& operator=(const AudioSource&);

    /**
     * @see Transform::Listener::transformChanged
     */
    void transformChanged(Transform* transform, long cookie);

    /**
     * Clones the audio source and returns a new audio source.
     *
     * @param context The clone context.
     * @return The newly created audio source.
     */
    AudioSource* clone(NodeCloneContext& context);

    bool streamDataIfNeeded();

    ALuint _alSource;
    OpenAudioBuffer* _buffer;
    bool _looped;
    float _gain;
    float _pitch;
    Vector3 _velocity;
};

}}

#endif // HAWKEYE_PAL_AUDIOSOURCE_HH
