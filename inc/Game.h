#pragma once

#include "Block.h"
#include "Input.h"
#include "Level.h"

namespace cetris
{
	constexpr hulk::u64 TICK_RATE = 200;

	struct Game final
	{
		Input* input;
		Level* level;
		std::vector<std::thread> threads;
		bool exit_flag = false;

		Game();
		~Game();
		Game(const Game&) = delete;
		Game(const Game&&) = delete;
		auto operator=(const Game&) -> Game& = delete;
		auto operator=(const Game&&) -> Game&& = delete;

		auto main_loop() -> void;
	};
}
