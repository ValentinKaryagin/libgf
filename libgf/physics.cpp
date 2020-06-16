#include "physics.h"

#include "physics_component.h"
#include "rigidbody_component.h"

physics::physics()
	: bt_dispatcher(&bt_configuration)
	, bt_world(&bt_dispatcher, &bt_pair_cache, &bt_solver, &bt_configuration)
{}

physics::~physics() {}

int physics::init()
{
	int err_lvl = 0;

	bt_world.stepSimulation(1.0f / 60.0f);

	return err_lvl;
}

void physics::terminate()
{
	
}

void physics::set_gravity(const btVector3 &value)
{
	bt_world.setGravity(value);
}

void physics::insert_component(physics_component *ptr)
{

}

void physics::remove_component(physics_component *ptr)
{

}

int physics::simulate()
{
	int err_lvl = 0;

	bt_world.stepSimulation(1.0f / 60.0f);

	return err_lvl;
}
