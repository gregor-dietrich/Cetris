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
			for (auto& key : keys)
			{
				if (!GetAsyncKeyState(key.first) || key.second)
					continue;

				input_queue.emplace(key.first);
				key.second = true;

				thread reset([&] {
					sleep(TICK_RATE);
					key.second = false;
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
				game->active_block->rotate(false);
				break;
			case VK_UP:
				game->active_block->rotate();
				break;
			case VK_LEFT:
				game->active_block->move(-1);
				break;
			case VK_RIGHT:
				game->active_block->move(1);
				break;
			case VK_DOWN:
				game->active_block->move();
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
