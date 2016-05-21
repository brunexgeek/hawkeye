#ifndef HAWKEYE_PAL_AUDIOCONTROLLER_HH
#define HAWKEYE_PAL_AUDIOCONTROLLER_HH

#include <set>
#include <memory>
#include <thread>
#include <mutex>

#include <hawkeye/AudioController.hh>
#include <hawkeye/AudioSource.hh>
#include <hawkeye/openal.hh>
#include "OpenAudioSource.hh"

namespace hawkeye {

	class AudioListener;

namespace pal {


	/**
	 * Defines a class for controlling game audio.
	 */
	class OpenAudioController : public hawkeye::AudioController
	{
		public:
			friend class OpenAudioSource;

			/**
			 * Constructor.
			 */
			OpenAudioController();

			/**
			 * Destructor.
			 */
			virtual ~OpenAudioController();

		protected:

			/**
			 * Controller initialize.
			 */
			void initialize();

			/**
			 * Controller finalize.
			 */
			void finalize();

			/**
			 * Controller pause.
			 */
			void pause();

			/**
			 * Controller resume.
			 */
			void resume();

			/**
			 * Controller update.
			 */
			void update(float elapsedTime);

			void addPlayingSource(hawkeye::AudioSource* source);

			void removePlayingSource(hawkeye::AudioSource* source);

			static void streamingThreadProc(void* arg);

			ALCdevice* _alcDevice;
			ALCcontext* _alcContext;
			std::set<AudioSource*> _playingSources;
			std::set<AudioSource*> _streamingSources;
			AudioSource* _pausingSource;

			bool _streamingThreadActive;
			std::unique_ptr<std::thread> _streamingThread;
			std::unique_ptr<std::mutex> _streamingMutex;
	};


}}

#endif // HAWKEYE_PAL_AUDIOCONTROLLER_HH
