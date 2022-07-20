#include "Game.h"
#include "Input.h"

using namespace cetris;
using namespace hulk;

Input::Input(Game& game): game(&game)
{
}

auto Input::listen() -> thread
{
	return thread([&] {
		while (!game->exit_flag)
		{
			for (const auto& key : keys)
				if (GetAsyncKeyState(key))
					this->v_key = key;
		}
	});
}

auto Input::handle() -> thread
{
	return thread([&]
	{
		while (!game->exit_flag)
		{
			switch(v_key)
			{
			case VK_ESCAPE:
				game->exit_flag = true;
				break;
			case VK_UP:
				game->active_block->rotate();
				break;
			default:
				game->active_block->move(v_key);
				break;
			}

			if (v_key == -1)
				continue;
			
			v_key = -1;
			sleep(100);
		}
	});	
}
