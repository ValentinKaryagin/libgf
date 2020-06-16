#pragma once

#include "commons.h"

class game_engine
{
protected:
	game_engine();

public:
	virtual ~game_engine();

protected:
	int init();

public:
	void terminate();

public:
	int loop();

public:
	__forceinline static game_engine *get()
	{
		static game_engine game_engine_instance;
		return &game_engine_instance;
	}
};
