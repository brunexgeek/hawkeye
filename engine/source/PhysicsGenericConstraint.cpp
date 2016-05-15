#include "Base.h"
#include "PhysicsGenericConstraint.h"
#include "Node.h"
#include "PhysicsRigidBody.h"

namespace hawkeye
{

PhysicsGenericConstraint::PhysicsGenericConstraint()
    : PhysicsConstraint(NULL, NULL), _rotationOffsetA(NULL), _rotationOffsetB(NULL),
    _translationOffsetA(NULL), _translationOffsetB(NULL)
{
    // Not used.
}

PhysicsGenericConstraint::PhysicsGenericConstraint(PhysicsRigidBody* a, PhysicsRigidBody* b)
    : PhysicsConstraint(a, b), _rotationOffsetA(NULL), _rotationOffsetB(NULL),
    _translationOffsetA(NULL), _translationOffsetB(NULL)
{
    GP_ASSERT(a && a->_body && a->getNode());

    if (b)
    {
        GP_ASSERT(b->_body && b->getNode());
        Vector3 origin = centerOfMassMidpoint(a->getNode(), b->getNode());
        _constraint = bullet_new<btGeneric6DofConstraint>(*a->_body, *b->_body, getTransformOffset(a->getNode(), origin), getTransformOffset(b->getNode(), origin), true);
    }
    else
    {
        _constraint = bullet_new<btGeneric6DofConstraint>(*a->_body, btTransform::getIdentity(), true);
    }
}

PhysicsGenericConstraint::PhysicsGenericConstraint(PhysicsRigidBody* a, const Quaternion& rotationOffsetA, const Vector3& translationOffsetA,
    PhysicsRigidBody* b, const Quaternion& rotationOffsetB, const Vector3& translationOffsetB)
    : PhysicsConstraint(a, b), _rotationOffsetA(NULL), _rotationOffsetB(NULL), _translationOffsetA(NULL), _translationOffsetB(NULL)
{
    GP_ASSERT(a && a->_body && a->getNode());

    // Take scale into account for the first node's translation offset.
    Vector3 sA;
    a->getNode()->getWorldMatrix().getScale(&sA);
    Vector3 tA(translationOffsetA.x * sA.x, translationOffsetA.y * sA.y, translationOffsetA.z * sA.z);

    if (b)
    {
        GP_ASSERT(b->_body && b->getNode());

        // Take scale into account for the second node's translation offset.
        Vector3 sB;
        b->getNode()->getWorldMatrix().getScale(&sB);
        Vector3 tB(translationOffsetB.x * sB.x, translationOffsetB.y * sB.y, translationOffsetB.z * sB.z);

        btTransform frameInA(BQ(rotationOffsetA), BV(tA));
        btTransform frameInB(BQ(rotationOffsetB), BV(tB));
        _constraint = bullet_new<btGeneric6DofConstraint>(*a->_body, *b->_body, frameInA, frameInB, true);
    }
    else
    {
        btTransform frameInA(BQ(rotationOffsetA), BV(tA));
        _constraint = bullet_new<btGeneric6DofConstraint>(*a->_body, frameInA, true);
    }
}

PhysicsGenericConstraint::~PhysicsGenericConstraint()
{
    SAFE_DELETE(_rotationOffsetA);
    SAFE_DELETE(_rotationOffsetB);
    SAFE_DELETE(_translationOffsetA);
    SAFE_DELETE(_translationOffsetB);
}


const Quaternion& PhysicsGenericConstraint::getRotationOffsetA() const
{
    if (!_rotationOffsetA)
        _rotationOffsetA = new Quaternion();

    GP_ASSERT(_constraint);
    btQuaternion ro = static_cast<btGeneric6DofConstraint*>(_constraint)->getFrameOffsetA().getRotation();
    _rotationOffsetA->set(ro.x(), ro.y(), ro.z(), ro.w());
    return *_rotationOffsetA;
}

const Quaternion& PhysicsGenericConstraint::getRotationOffsetB() const
{
    if (!_rotationOffsetB)
        _rotationOffsetB = new Quaternion();

    GP_ASSERT(_constraint);
    btQuaternion ro = static_cast<btGeneric6DofConstraint*>(_constraint)->getFrameOffsetB().getRotation();
    _rotationOffsetB->set(ro.x(), ro.y(), ro.z(), ro.w());
    return *_rotationOffsetB;
}

const Vector3& PhysicsGenericConstraint::getTranslationOffsetA() const
{
    if (!_translationOffsetA)
        _translationOffsetA = new Vector3();

    GP_ASSERT(_constraint);
    btVector3 to = static_cast<btGeneric6DofConstraint*>(_constraint)->getFrameOffsetA().getOrigin();
    _translationOffsetA->set(to.x(), to.y(), to.z());
    return *_translationOffsetA;
}

const Vector3& PhysicsGenericConstraint::getTranslationOffsetB() const
{
    if (!_translationOffsetB)
        _translationOffsetB = new Vector3();

    GP_ASSERT(_constraint);
    btVector3 to = static_cast<btGeneric6DofConstraint*>(_constraint)->getFrameOffsetB().getOrigin();
    _translationOffsetB->set(to.x(), to.y(), to.z());
    return *_translationOffsetB;
}

void PhysicsGenericConstraint::setAngularLowerLimit(const Vector3& limits)
{
    GP_ASSERT(_constraint);
    ((btGeneric6DofConstraint*)_constraint)->setAngularLowerLimit(BV(limits));
}

void PhysicsGenericConstraint::setAngularUpperLimit(const Vector3& limits)
{
    GP_ASSERT(_constraint);
    ((btGeneric6DofConstraint*)_constraint)->setAngularUpperLimit(BV(limits));
}

void PhysicsGenericConstraint::setLinearLowerLimit(const Vector3& limits)
{
    GP_ASSERT(_constraint);
    ((btGeneric6DofConstraint*)_constraint)->setLinearLowerLimit(BV(limits));
}

void PhysicsGenericConstraint::setLinearUpperLimit(const Vector3& limits)
{
    GP_ASSERT(_constraint);
    ((btGeneric6DofConstraint*)_constraint)->setLinearUpperLimit(BV(limits));
}

void PhysicsGenericConstraint::setRotationOffsetA(const Quaternion& rotationOffset)
{
    GP_ASSERT(_constraint);
    static_cast<btGeneric6DofConstraint*>(_constraint)->getFrameOffsetA().setRotation(BQ(rotationOffset));
}

void PhysicsGenericConstraint::setRotationOffsetB(const Quaternion& rotationOffset)
{
    GP_ASSERT(_constraint);
    static_cast<btGeneric6DofConstraint*>(_constraint)->getFrameOffsetB().setRotation(BQ(rotationOffset));
}

void PhysicsGenericConstraint::setTranslationOffsetA(const Vector3& translationOffset)
{
    GP_ASSERT(_constraint);
    static_cast<btGeneric6DofConstraint*>(_constraint)->getFrameOffsetA().setOrigin(BV(translationOffset));
}

void PhysicsGenericConstraint::setTranslationOffsetB(const Vector3& translationOffset)
{
    GP_ASSERT(_constraint);
    static_cast<btGeneric6DofConstraint*>(_constraint)->getFrameOffsetB().setOrigin(BV(translationOffset));
}


}
