#include "Game.h"
#include "Level.h"

using namespace cetris;
using namespace hulk;

Level::Level(Game& game): game(&game), active_block(new Block(game)), next_block(new Block(game))
{
	grid.resize(LEVEL_HEIGHT + BUFFER_HEIGHT);
	active_block->launch().detach();
}

Level::~Level()
{
	delete this->next_block;
	delete this->active_block;
}

auto Level::lock_block() -> void
{
	const auto x = active_block->pos.first;
	const auto y = active_block->pos.second;

	for (u64 i = 0; i < active_block->height(); i++)
		for (u64 j = 0; j < active_block->width(); j++)
			if (active_block->shape[i][j])
				grid[i + y - active_block->height()][j + x] = active_block->color;

	active_block = next_block;
	next_block = new Block(*game);
	active_block->launch().detach();
}

auto Level::draw() const -> void
{
	console::clear();

	draw_h_border();

	for (u8 i = BUFFER_HEIGHT; i < LEVEL_HEIGHT; i++)
		draw_row(i);

	draw_h_border(false);

	sleep(TICK_RATE);
}

auto Level::draw_row(const i8& row_index) const -> void
{
	print(U_VERTICAL);

	for (i8 col_index = 0; col_index < LEVEL_WIDTH; col_index++)
	{
		bool is_block = false;
		const auto x = active_block->pos.first;
		if (const auto y = active_block->pos.second; row_index < y && row_index >= y - active_block->height()
			&& (col_index >= x && col_index < x + active_block->width())
			&& active_block->shape[row_index - y + active_block->height()][col_index - x])
			is_block = true;

		const auto cell = is_block ? active_block->color : grid[row_index][col_index];
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
