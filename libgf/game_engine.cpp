#include "game_engine.h"

#include "config.h"
#include "window.h"
#include "physics.h"
#include "render.h"

game_engine::game_engine() {}

game_engine::~game_engine()
{
	terminate();
}

int game_engine::init()
{
	int err_lvl = 0;

	config cfg;
	cfg.read();

	err_lvl = window::get()->create(
		cfg.window.left,
		cfg.window.top,
		cfg.window.size_x,
		cfg.window.size_y,
		cfg.window.title,
		cfg.window.show,
		cfg.window.foreground
	);

	if (!err_lvl)
	{
		err_lvl = physics::get()->init();
	}

	if (!err_lvl)
	{
		err_lvl = render::get()->init(
			cfg.render.fullscreen,
			cfg.render.vsync
		);
	}

	return err_lvl;
}

void game_engine::terminate()
{
	render::get()->terminate();
	physics::get()->terminate();
	window::get()->destroy();
}

int game_engine::loop()
{
	int err_lvl = 0;

	while (!err_lvl)
	{
		err_lvl = window::get()->proc();

		if (!err_lvl)
		{
			err_lvl = physics::get()->simulate();
		}

		if (!err_lvl)
		{
			err_lvl = render::get()->draw();
		}
	}

	return err_lvl;
}
