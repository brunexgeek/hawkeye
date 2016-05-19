#include <hawkeye/Base.hh>
#include <hawkeye/Node.hh>
#include <hawkeye/AudioBuffer.hh>
#include <hawkeye/AudioController.hh>
#include <hawkeye/AudioSource.hh>
#include <hawkeye/Game.hh>
#include <hawkeye/Node.hh>
#include "pal/OpenAudioSource.hh"

namespace hawkeye {


AudioSource::AudioSource() : node(NULL)
{

}


AudioSource::~AudioSource()
{

}

AudioSource* AudioSource::create(const char* url, bool streamed)
{
    return pal::OpenAudioSource::create(url, streamed);
}

AudioSource* AudioSource::create(Properties* properties)
{
    return pal::OpenAudioSource::create(properties);
}

Node* AudioSource::getNode() const
{
    return this->node;
}

void AudioSource::setNode(Node* node)
{
    if (this->node != node)
    {
        // Disconnect our current transform.
        if (this->node)
        {
            this->node->removeListener(this);
        }

        // Connect the new node.
        this->node = node;

        if (this->node)
        {
            this->node->addListener(this);
            // Update the audio source position.
            transformChanged(this->node, 0);
        }
    }
}

}
