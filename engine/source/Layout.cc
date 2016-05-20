#include <hawkeye/Base.hh>
#include <hawkeye/Layout.hh>
#include <hawkeye/Control.hh>
#include <hawkeye/Container.hh>
#include <hawkeye/Game.hh>

namespace hawkeye
{

bool Layout::touchEvent(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex)
{
    return false;
}

}