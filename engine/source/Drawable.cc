#include <hawkeye/Base.hh>
#include <hawkeye/Drawable.hh>
#include <hawkeye/Node.hh>


namespace hawkeye
{

Drawable::Drawable()
    : _node(NULL)
{
}

Drawable::~Drawable()
{
}

Node* Drawable::getNode() const
{
    return _node;
}

void Drawable::setNode(Node* node)
{
    _node = node;
}

}
