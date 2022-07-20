#include "Level.h"

using namespace cetris;
using namespace hulk;

Level::Level()
{
	grid.resize(LEVEL_HEIGHT);
	buffer.resize(BUFFER_HEIGHT);
}

auto Level::tick() -> void
{
	
}

auto Level::draw() const -> void
{
	draw_h_border();

	for (u8 i = BUFFER_HEIGHT; i < LEVEL_HEIGHT; i++)
		this->draw_row(grid[static_cast<std::deque<grid_row,
		                                std::allocator<grid_row>>::size_type>(LEVEL_HEIGHT) - i]);

	draw_h_border(false);
}

auto Level::draw_row(const grid_row& row) const -> void
{
	print(U_VERTICAL);

	for (const auto& cell : row)
	{
		if (cell)
			text_color(cell);
		print(cell ? U_SQUARE : U_EMPTY);
	}

	console::text_color();
	println(U_VERTICAL);
}

auto Level::draw_h_border(const bool& top) -> void
{
	print(top ? U_CORNER_TOP_LEFT : U_CORNER_BOTTOM_LEFT);

	print(U_HORIZONTAL, LEVEL_WIDTH);

	println(top ? U_CORNER_TOP_RIGHT : U_CORNER_BOTTOM_RIGHT);
}
