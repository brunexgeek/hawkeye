#ifndef HAWKEYE_AUDIOSOURCE_HH
#define HAWKEYE_AUDIOSOURCE_HH

#include <hawkeye/Vector3.hh>
#include <hawkeye/Ref.hh>
#include <hawkeye/Transform.hh>

namespace hawkeye {


	class Node;
	class NodeCloneContext;

	/**
	 * Defines an audio source in 3D space.
	 *
	 * This can be attached to a Node for applying its 3D transformation.
	 *
	 * @see http://gameplay3d.github.io/GamePlay/docs/file-formats.html#wiki-Audio
	 */
	class AudioSource : public Ref, public Transform::Listener
	{
		public:

			friend class Node;
			friend class AudioController;

			/**
			 * The audio source's audio state.
			 */
			enum State
			{
				INITIAL,
				PLAYING,
				PAUSED,
				STOPPED
			};

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
			static AudioSource* create(const char* url, bool streamed = false);

			/**
			 * Create an audio source from the given properties object.
			 *
			 * @param properties The properties object defining the audio source (must have namespace equal to 'audio').
			 * @return The newly created audio source, or <code>NULL</code> if the audio source failed to load.
			 * @script{create}
			 */
			static AudioSource* create(Properties* properties);

			/**
			 * Plays the audio source.
			 */
			virtual void play() = 0;

			/**
			 * Pauses the playing of the audio source.
			 */
			virtual void pause() = 0;

			/**
			 * Resumes playing of the audio source.
			 */
			virtual void resume() = 0;

			/**
			 * Stops the playing of the audio source.
			 */
			virtual void stop() = 0;

			/**
			 * Rewinds the audio source to the beginning.
			 */
			virtual void rewind() = 0;

			/**
			 * Gets the current state of the audio source.
			 *
			 * @return PLAYING if the source is playing, STOPPED if the source is stopped, PAUSED if the source is paused and INITIAL otherwise.
			 */
			virtual AudioSource::State getState() const = 0;

			/**
			 * Determines whether the audio source is streaming or not.
			 *
			 * @return true if the audio source is streaming, false if not.
			 */
			virtual bool isStreamed() const = 0;

			/**
			 * Determines whether the audio source is looped or not.
			 *
			 * @return true if the audio source is looped, false if not.
			 */
			virtual bool isLooped() const = 0;

			/**
			 * Sets the state of the audio source to be looping or not.
			 *
			 * @param looped true to loop the sound, false to not loop it.
			 */
			virtual void setLooped(bool looped) = 0;

			/**
			 * Returns the gain of the audio source.
			 *
			 * @return The gain.
			 */
			virtual float getGain() const = 0;

			/**
			 * Sets the gain/volume of the audio source.
			 *
			 * @param gain The gain/volume of the source.
			 */
			virtual void setGain(float gain) = 0;

			/**
			 * Returns the pitch of the audio source.
			 *
			 * @return The pitch.
			 */
			virtual float getPitch() const = 0;

			/**
			 * Sets the pitch of the audio source.
			 *
			 * @param pitch The pitch of the source.
			 */
			virtual void setPitch(float pitch) = 0;

			/**
			 * Gets the velocity of the audio source.
			 *
			 * @return The velocity as a vector.
			 */
			virtual const Vector3& getVelocity() const = 0;

			/**
			 * Sets the velocity of the audio source.
			 *
			 * @param velocity A vector representing the velocity.
			 */
			virtual void setVelocity(const Vector3& velocity) = 0;

			/**
			 * Sets the velocity of the audio source.
			 *
			 * @param x The x coordinate of the velocity.
			 * @param y The y coordinate of the velocity.
			 * @param z The z coordinate of the velocity.
			 */
			virtual void setVelocity(float x, float y, float z) = 0;

			/**
			 * Gets the node that this source is attached to.
			 *
			 * @return The node that this audio source is attached to.
			 */
			Node* getNode() const;

		protected:
			Node* node;

			/**
			 * Constructor that takes an AudioBuffer.
			 */
			AudioSource();

			/**
			 * Destructor.
			 */
			virtual ~AudioSource();

			/**
			 * Hidden copy assignment operator.
			 */
			AudioSource& operator=(const AudioSource&);

			/**
			 * Sets the node for this audio source.
			 */
			void setNode(Node* node);

			/**
			 * @see Transform::Listener::transformChanged
			 */
			virtual void transformChanged(Transform* transform, long cookie) = 0;

			/**
			 * Clones the audio source and returns a new audio source.
			 *
			 * @param context The clone context.
			 * @return The newly created audio source.
			 */
			 virtual AudioSource* clone(NodeCloneContext& context) = 0;
	};

}

#endif // HAWKEYE_AUDIOSOURCE_HH
