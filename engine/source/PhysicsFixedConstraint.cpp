#include "Base.h"
#include "PhysicsFixedConstraint.h"

namespace gameplay
{

PhysicsFixedConstraint::PhysicsFixedConstraint(PhysicsRigidBody* a, PhysicsRigidBody* b)
    : PhysicsGenericConstraint(a, b)
{
    PhysicsGenericConstraint::setAngularLowerLimit(Vector3(0.0f, 0.0f, 0.0f));
    PhysicsGenericConstraint::setAngularUpperLimit(Vector3(0.0f, 0.0f, 0.0f));
    PhysicsGenericConstraint::setLinearLowerLimit(Vector3(0.0f, 0.0f, 0.0f));
    PhysicsGenericConstraint::setLinearUpperLimit(Vector3(0.0f, 0.0f, 0.0f));
}

PhysicsFixedConstraint::~PhysicsFixedConstraint()
{
    // Not used.
}


inline void PhysicsFixedConstraint::setAngularLowerLimit(const Vector3& limit)
{
    PhysicsGenericConstraint::setAngularLowerLimit(limit);
}

inline void PhysicsFixedConstraint::setAngularUpperLimit(const Vector3& limit)
{
    PhysicsGenericConstraint::setAngularUpperLimit(limit);
}

inline void PhysicsFixedConstraint::setLinearLowerLimit(const Vector3& limit)
{
    PhysicsGenericConstraint::setLinearLowerLimit(limit);
}

inline void PhysicsFixedConstraint::setLinearUpperLimit(const Vector3& limit)
{
    PhysicsGenericConstraint::setLinearUpperLimit(limit);
}



}
