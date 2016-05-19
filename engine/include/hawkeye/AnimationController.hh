#ifndef ANIMATIONCONTROLLER_H_
#define ANIMATIONCONTROLLER_H_

#include <hawkeye/AnimationClip.hh>
#include <hawkeye/Animation.hh>
#include <hawkeye/AnimationTarget.hh>
#include <hawkeye/Properties.hh>

namespace hawkeye {

/**
 * Defines a class for controlling game animation.
 */
class AnimationController
{
    friend class Game;
    friend class Animation;
    friend class AnimationClip;
    friend class SceneLoader;

public:

    /**
     * Stops all AnimationClips currently playing on the AnimationController.
     */
    void stopAllAnimations();

private:

    /**
     * The states that the AnimationController may be in.
     */
    enum State
    {
        RUNNING,
        IDLE,
        PAUSED,
        STOPPED
    };

    /**
     * Constructor.
     */
    AnimationController();

    /**
     * Constructor.
     */
    AnimationController(const AnimationController& copy);

    /**
     * Destructor.
     */
    ~AnimationController();

    /**
     * Gets the controller's state.
     *
     * @return The current state.
     */
    State getState() const;

    /**
     * Callback for when the controller is initialized.
     */
    void initialize();

    /*
     * Callback for when the controller is finalized.
     */
    void finalize();

    /**
     * Resumes the AnimationController.
     */
    void resume();

    /**
     * Pauses the AnimationController.
     */
    void pause();

    /**
     * Schedules an AnimationClip to run.
     */
    void schedule(AnimationClip* clip);

    /**
     * Unschedules an AnimationClip.
     */
    void unschedule(AnimationClip* clip);

    /**
     * Callback for when the controller receives a frame update event.
     */
    void update(float elapsedTime);

    State _state;                                 // The current state of the AnimationController.
    std::list<AnimationClip*> _runningClips;      // A list of running AnimationClips.
};

}

#endif

