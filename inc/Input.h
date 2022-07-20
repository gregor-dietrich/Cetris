#pragma once

#include "globals.h"

namespace cetris
{
	struct Game;

	struct Input final
	{
		Game* game = nullptr;
		hulk::i32 v_key = -1;
		const std::vector<hulk::i32> keys = { VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT, VK_ESCAPE };
		
		explicit Input(Game&);
		auto listen() -> hulk::thread;
		auto handle() -> hulk::thread;
	};	
}
