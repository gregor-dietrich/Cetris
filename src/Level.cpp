#include "Game.h"
#include "Level.h"

using namespace cetris;
using namespace hulk;

Level::Level(Game& game): game(&game)
{
	grid.resize(LEVEL_HEIGHT + BUFFER_HEIGHT);
}

auto Level::draw() const -> void
{
	console::clear();

	draw_h_border();

	for (u8 i = BUFFER_HEIGHT; i < LEVEL_HEIGHT; i++)
		this->draw_row(i);

	draw_h_border(false);

	sleep(TICK_RATE);
}

auto Level::draw_row(const u8& row_index) const -> void
{
	print(U_VERTICAL);

	for (u8 col_index = 0; col_index < LEVEL_WIDTH; col_index++)
	{
		bool is_block = false;

		const auto block = game->active_block;
		const auto x = block->pos.first;
		const auto y = block->pos.second;

		if (row_index < y && row_index >= y - block->height()
			&& (col_index >= x && col_index < x + block->width())
			&& block->shape[row_index - y + block->height()][col_index - x])
			is_block = true;

		console::color cell;
		if (is_block)
		{
			cell = block->color;
		}
		else
			cell = grid[row_index][col_index];

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
