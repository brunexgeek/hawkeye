#include <hawkeye/DebugNew.hh>
#include <hawkeye/Base.hh>
#include <hawkeye/PhysicsSpringConstraint.hh>
#include <hawkeye/Node.hh>
#include <hawkeye/PhysicsRigidBody.hh>

namespace hawkeye
{

PhysicsSpringConstraint::PhysicsSpringConstraint(PhysicsRigidBody* a, PhysicsRigidBody* b)
{
    GP_ASSERT(a && a->_body);
    GP_ASSERT(b && b->_body);

    // Initialize the physics rigid body references since we don't call the PhysicsConstraint constructor that does it properly automatically.
    _a = a;
    _b = b;

    Vector3 origin = centerOfMassMidpoint(a->getNode(), b->getNode());
    _constraint = bullet_new<btGeneric6DofSpringConstraint>(*a->_body, *b->_body, getTransformOffset(a->getNode(), origin), getTransformOffset(b->getNode(), origin), true);
}

PhysicsSpringConstraint::PhysicsSpringConstraint(PhysicsRigidBody* a, const Quaternion& rotationOffsetA, const Vector3& translationOffsetA,
                                                 PhysicsRigidBody* b, const Quaternion& rotationOffsetB, const Vector3& translationOffsetB)
{
    GP_ASSERT(a && a->_body && a->getNode());
    GP_ASSERT(b && b->_body && b->getNode());

    // Initialize the physics rigid body references since we don't call the PhysicsConstraint constructor that does it properly automatically.
    _a = a;
    _b = b;

    // Take scale into account for the translation offsets.
    Vector3 sA;
    a->getNode()->getWorldMatrix().getScale(&sA);
    Vector3 tA(translationOffsetA.x * sA.x, translationOffsetA.y * sA.y, translationOffsetA.z * sA.z);

    Vector3 sB;
    b->getNode()->getWorldMatrix().getScale(&sB);
    Vector3 tB(translationOffsetB.x * sB.x, translationOffsetB.y * sB.y, translationOffsetB.z * sB.z);

    btTransform frameInA(BQ(rotationOffsetA), BV(tA));
    btTransform frameInB(BQ(rotationOffsetB), BV(tB));
    _constraint = bullet_new<btGeneric6DofSpringConstraint>(*a->_body, *b->_body, frameInA, frameInB, true);
}

PhysicsSpringConstraint::~PhysicsSpringConstraint()
{
    // Used
}

void PhysicsSpringConstraint::setStrength(SpringProperty property, float strength)
{
    GP_ASSERT(_constraint);
    if (strength < MATH_EPSILON)
        ((btGeneric6DofSpringConstraint*)_constraint)->enableSpring(property, false);
    else
    {
        ((btGeneric6DofSpringConstraint*)_constraint)->enableSpring(property, true);
        ((btGeneric6DofSpringConstraint*)_constraint)->setStiffness(property, strength);
        ((btGeneric6DofSpringConstraint*)_constraint)->setEquilibriumPoint(property);
    }
}

void PhysicsSpringConstraint::setDamping(SpringProperty property, float damping)
{
    GP_ASSERT(_constraint);
    ((btGeneric6DofSpringConstraint*)_constraint)->setDamping(property, damping);
    ((btGeneric6DofSpringConstraint*)_constraint)->setEquilibriumPoint(property);
}


void PhysicsSpringConstraint::setAngularDampingX(float damping)
{
    setDamping(ANGULAR_X, damping);
}

void PhysicsSpringConstraint::setAngularDampingY(float damping)
{
    setDamping(ANGULAR_Y, damping);
}

void PhysicsSpringConstraint::setAngularDampingZ(float damping)
{
    setDamping(ANGULAR_Z, damping);
}

void PhysicsSpringConstraint::setAngularStrengthX(float strength)
{
    setStrength(ANGULAR_X, strength);
}

void PhysicsSpringConstraint::setAngularStrengthY(float strength)
{
    setStrength(ANGULAR_Y, strength);
}

void PhysicsSpringConstraint::setAngularStrengthZ(float strength)
{
    setStrength(ANGULAR_Z, strength);
}

void PhysicsSpringConstraint::setLinearDampingX(float damping)
{
    setDamping(LINEAR_X, damping);
}

void PhysicsSpringConstraint::setLinearDampingY(float damping)
{
    setDamping(LINEAR_Y, damping);
}

void PhysicsSpringConstraint::setLinearDampingZ(float damping)
{
    setDamping(LINEAR_Z, damping);
}

void PhysicsSpringConstraint::setLinearStrengthX(float strength)
{
    setStrength(LINEAR_X, strength);
}

void PhysicsSpringConstraint::setLinearStrengthY(float strength)
{
    setStrength(LINEAR_Y, strength);
}

void PhysicsSpringConstraint::setLinearStrengthZ(float strength)
{
    setStrength(LINEAR_Z, strength);
}


}
