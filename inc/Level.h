#pragma once
#include <array>
#include <deque>

#include "globals.h"

namespace cetris
{
	struct Game;

	using grid_row = std::array<hulk::console::color, LEVEL_WIDTH>;

	struct Level final
	{
		Game* game = nullptr;
		Block* active_block;
		Block* next_block;
		std::deque<grid_row> grid{};
				
		explicit Level(Game&);
		~Level();
				
		auto lock_block() -> void;

		auto draw() const -> void;
		auto draw_row(const hulk::i8&) const -> void;
		static auto draw_h_border(const bool& = true) -> void;
	};
}
