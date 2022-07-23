#pragma once

#include <queue>
#include <unordered_map>

#include "globals.h"

namespace cetris
{
	struct Game;

	struct Input final
	{
		Game* game = nullptr;
		std::queue<hulk::i32> input_queue;
		std::unordered_map<hulk::i32, bool> keys = {
			{VK_UP, false},
			{VK_SPACE, false},
			{VK_LEFT, false},
			{VK_RIGHT, false},
			{VK_DOWN, false},
			{VK_ESCAPE, false}
		};
		
		explicit Input(Game&);
		auto listen() -> hulk::thread;
		auto handle() -> hulk::thread;
	};	
}
