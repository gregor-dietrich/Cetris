#pragma once
#include <array>
#include <deque>

#include "globals.h"

namespace cetris
{
	using grid_row = std::array<hulk::console::color, LEVEL_WIDTH>;

	struct Level final
	{
		std::deque<grid_row> grid{};
		std::deque<grid_row> buffer{};
				
		Level();		
		auto tick() -> void;
		auto draw() const -> void;
		auto draw_row(const grid_row&) const -> void;
		static auto draw_h_border(const bool& = true) -> void;
	};
}
