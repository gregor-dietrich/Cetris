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
			for (auto& [v_key, on_cooldown] : keys)
			{
				if (!GetAsyncKeyState(v_key) || on_cooldown)
					continue;

				input_queue.emplace(v_key);
				on_cooldown = true;

				thread reset([&] {
					sleep(TICK_RATE);
					on_cooldown = false;
				});
				reset.detach();
			}
	});
}

auto Input::handle() -> thread
{
	return thread([&] {
		while (!game->exit_flag)
		{
			if (input_queue.empty())
				continue;

			switch(input_queue.front())
			{
			case VK_SPACE:
				game->level->active_block->rotate(false);
				break;
			case VK_UP:
				game->level->active_block->rotate();
				break;
			case VK_LEFT:
				game->level->active_block->move(-1);
				break;
			case VK_RIGHT:
				game->level->active_block->move(1);
				break;
			case VK_DOWN:
				game->level->active_block->move();
				break;
			case VK_ESCAPE:
				game->exit_flag = true;
				break;
			default:
				break;
			}

			input_queue.pop();
		}
	});	
}
