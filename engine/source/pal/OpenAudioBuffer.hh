#ifndef HAWKEYE_PAL_AUDIOBUFFER_HH
#define HAWKEYE_PAL_AUDIOBUFFER_HH

#include <hawkeye/Ref.h>
#include <hawkeye/Stream.h>
#include <hawkeye/AudioBuffer.h>
#include <vorbis/vorbisfile.h>
#include <hawkeye/openal.h>
#include "OpenAudioBuffer.hh"

namespace hawkeye {
namespace pal {


class OpenAudioSource;

/**
 * Defines the actual audio buffer data.
 *
 * Currently only supports supported formats: .ogg, .wav, .au and .raw files.
 */
class OpenAudioBuffer : public Ref
{
    friend class OpenAudioSource;

protected:

    /**
     * Constructor.
     */
    OpenAudioBuffer(
		const char* path,
		ALuint* buffers,
		bool streamed );

    /**
     * Destructor.
     */
    virtual ~OpenAudioBuffer();

    /**
     * Hidden copy assignment operator.
     */
    OpenAudioBuffer& operator=(const OpenAudioBuffer&);

    /**
     * Creates an audio buffer from a file.
     *
     * @param path The path to the audio buffer on the filesystem.
     *
     * @return The buffer from a file.
     */
    static OpenAudioBuffer* create(const char* path, bool streamed);

    struct AudioStreamStateWav
    {
        long dataStart;
        unsigned int dataSize;
        ALuint format;
        ALuint frequency;
    };

    struct AudioStreamStateOgg
    {
        long dataStart;
        unsigned int dataSize;
        ALuint format;
        ALuint frequency;
        OggVorbis_File oggFile;
    };

    enum { STREAMING_BUFFER_QUEUE_SIZE = 3 };
    enum { STREAMING_BUFFER_SIZE = 48000 };

    static bool loadWav(Stream* stream, ALuint buffer, bool streamed, AudioStreamStateWav* streamState);

    static bool loadOgg(Stream* stream, ALuint buffer, bool streamed, AudioStreamStateOgg* streamState);

    bool streamData(ALuint buffer, bool looped);

    ALuint _alBufferQueue[STREAMING_BUFFER_QUEUE_SIZE];
    std::string _filePath;
    bool _streamed;
    std::unique_ptr<Stream> _fileStream;
    std::unique_ptr<AudioStreamStateWav> _streamStateWav;
    std::unique_ptr<AudioStreamStateOgg> _streamStateOgg;
    int _buffersNeededCount;
};

}}

#endif // HAWKEYE_PAL_AUDIOBUFFER_HH
