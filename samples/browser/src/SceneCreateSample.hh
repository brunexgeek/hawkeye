#ifndef SCENECREATESAMPLE_H_
#define SCENECREATESAMPLE_H_

#include <hawkeye/gameplay.hh>
#include "Sample.hh"

using namespace hawkeye;

/**
 * Samples programattically contructing a scene.
 */
class SceneCreateSample : public Sample
{
public:

    SceneCreateSample();

    void touchEvent(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex);

protected:

    void initialize();

    void finalize();

    void update(float elapsedTime);

    void render(float elapsedTime);

private:

    bool drawScene(Node* node);

    Font* _font;
    Scene* _scene;
    Node* _cubeNode;
};

#endif
