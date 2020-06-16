#include "rigidbody_component.h"

btVector3 get_local_inertia(float mass, btCollisionShape *ptr)
{
	btVector3 result(0.0f, 0.0f, 0.0f);
	ptr->calculateLocalInertia(mass, result);
	return result;
}

rigidbody_component::rigidbody_component(
	float mass,
	btCollisionShape *ptr,
	btCollisionObject::CollisionFlags flags,
	const TCHAR *name
)
	: physics_component(name)
	, bt_rigidbody(
		mass,
		&bt_motion_state,
		ptr,
		flags == btCollisionObject::CollisionFlags::CF_KINEMATIC_OBJECT ? get_local_inertia(mass, ptr) : btVector3(0.0f, 0.0f, 0.0f)
	)
{
	bt_rigidbody.setFlags(flags);
}

rigidbody_component::~rigidbody_component() {}
