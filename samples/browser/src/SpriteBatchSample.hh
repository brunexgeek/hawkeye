#ifndef SPRITEBATCHSAMPLE_H_
#define SPRITEBATCHSAMPLE_H_

#include <hawkeye/gameplay.hh>
#include "Sample.hh"

using namespace hawkeye;

/**
 * Sample drawing many quad sprites with SpriteBatch.
 */
class SpriteBatchSample : public Sample
{
public:

    SpriteBatchSample();

    void touchEvent(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex);

protected:

    void initialize();

    void finalize();

    void update(float elapsedTime);

    void render(float elapsedTime);

private:

    Font* _font;
    SpriteBatch* _spriteBatch;
    Matrix _worldViewProjectionMatrix;
};

#endif