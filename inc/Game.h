#pragma once

#include "Block.h"
#include "Input.h"
#include "Level.h"

namespace cetris
{	
	struct Game final
	{
		std::vector<std::thread> threads;
		bool exit_flag = false;
		Input* input;
		Level* level;

		Game();
		~Game();
		auto main_loop() -> void;

		Game(const Game&) = delete;
		Game(const Game&&) = delete;
		auto operator=(const Game&) -> Game& = delete;
		auto operator=(const Game&&) -> Game&& = delete;
	};
}
