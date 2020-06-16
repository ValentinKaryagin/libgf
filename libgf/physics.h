#pragma once

#include "commons.h"

class physics_component;

class physics
{
public:
	btDefaultCollisionConfiguration		bt_configuration;
	btCollisionDispatcher				bt_dispatcher;
	btDbvtBroadphase					bt_pair_cache;
	btSequentialImpulseConstraintSolver	bt_solver;
	btDiscreteDynamicsWorld				bt_world;

protected:
	physics();

public:
	virtual ~physics();

public:
	int init();
	void terminate();
	void set_gravity(const btVector3 &value);
	void insert_component(physics_component *ptr);
	void remove_component(physics_component *ptr);
	int simulate();

public:
	__forceinline static physics *get()
	{
		static physics physics_instance;
		return &physics_instance;
	}
};
