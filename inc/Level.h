#pragma once
#include <array>
#include <deque>

#include "globals.h"

namespace cetris
{
	struct Game;

	constexpr hulk::u8 LEVEL_WIDTH = 10;
	constexpr hulk::u8 LEVEL_HEIGHT = 20;
	constexpr hulk::u8 BUFFER_HEIGHT = 4;

	using grid_row = std::array<hulk::console::color, LEVEL_WIDTH>;

	struct Level final
	{
		Game* game = nullptr;
		Block* active_block;
		Block* next_block;
		std::deque<grid_row> grid{};
				
		explicit Level(Game&);
		~Level();
		Level(const Level&) = delete;
		Level(const Level&&) = delete;
		auto operator=(const Level&) -> Level& = delete;
		auto operator=(const Level&&) -> Level&& = delete;
				
		auto draw() const -> void;
		auto draw_row(const hulk::i8&) const -> void;
		static auto draw_h_border(const bool& = true) -> void;

		auto lock_block() -> void;
	};
}
