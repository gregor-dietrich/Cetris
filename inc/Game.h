#pragma once

#include "Block.h"
#include "Input.h"
#include "Level.h"

namespace cetris
{	
	struct Game final
	{
		bool exit_flag = false;
		Input* input;
		Level* level;
		Block* active_block;
		Block* next_block;
		hulk::thread listen_thread;
		hulk::thread input_thread;

		Game();
		~Game();
		auto main_loop() -> void;

		Game(const Game&) = delete;
		Game(const Game&&) = delete;
		auto operator=(const Game&) -> Game& = delete;
		auto operator=(const Game&&) -> Game&& = delete;
	};
}
