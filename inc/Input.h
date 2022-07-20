#pragma once

#include <queue>

#include "globals.h"

namespace cetris
{
	struct Game;

	struct Input final
	{
		Game* game = nullptr;
		const std::vector<hulk::i32> keys = { VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT, VK_ESCAPE };
		std::queue<hulk::i32> input_queue;
		
		explicit Input(Game&);
		auto listen() -> hulk::thread;
		auto handle() -> hulk::thread;
	};	
}
