#pragma once

#include "physics_component.h"

class rigidbody_component
	: public physics_component
{
public:
	btRigidBody bt_rigidbody;

public:
	rigidbody_component(
		float mass,
		btCollisionShape *ptr,
		btCollisionObject::CollisionFlags flags = btCollisionObject::CollisionFlags::CF_STATIC_OBJECT,
		const TCHAR *name = TEXT("rigidbody_component")
	);

	virtual ~rigidbody_component();

public:

};
