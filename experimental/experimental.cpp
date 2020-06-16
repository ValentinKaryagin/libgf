#include "..\\libgf\\libgf.h"

int main()
{
	int err_lvl = 0;
	
	err_lvl = game_engine::get()->init();

	if (!err_lvl)
	{
		err_lvl = game_engine::get()->loop();
	}	

	return err_lvl;
}
