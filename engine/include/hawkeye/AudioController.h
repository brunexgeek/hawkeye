#ifndef HAWKEYE_AUDIOCONTROLLER_HH
#define HAWKEYE_AUDIOCONTROLLER_HH


namespace hawkeye
{

	class AudioListener;
	class AudioSource;

	/**
	 * Defines a class for controlling game audio.
	 */
	class AudioController
	{
		friend class Game;
		friend class AudioSource;

	public:

		/**
		 * Destructor.
		 */
		virtual ~AudioController();

	protected:

		/**
		 * Constructor.
		 */
		AudioController();

		/**
		 * Controller initialize.
		 */
		virtual void initialize() = 0;

		/**
		 * Controller finalize.
		 */
		virtual void finalize() = 0;

		/**
		 * Controller pause.
		 */
		virtual void pause() = 0;

		/**
		 * Controller resume.
		 */
		virtual void resume() = 0;

		/**
		 * Controller update.
		 */
		virtual void update(
			float elapsedTime ) = 0;

		virtual void addPlayingSource(
			AudioSource* source ) = 0;

		virtual void removePlayingSource(
			AudioSource* source ) = 0;

	};

}

#endif  // HAWKEYE_AUDIOCONTROLLER_HH
