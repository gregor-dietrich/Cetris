#include "Game.h"
#include "Block.h"

using namespace cetris;
using namespace hulk;

Block::Block(Game& game) : Block(game, static_cast<shape_t>(rand_int(Z)))
{
}

Block::Block(Game& game, const shape_t& type): game(&game),
	color(static_cast<console::color>(rand_int(1, console::color::white))), type(type)
{
	switch (type)
	{
	case I:
		shape = {{true}, {true}, {true}, {true}};
		break;
	case J:
		shape = {{true, false, false}, {true, true, true}};
		break;
	case L:
		shape = {{false, false, true}, {true, true, true}};
		break;
	case O:
		shape = {{true, true}, {true, true}};
		break;
	case S:
		shape = {{false, true, true}, {true, true, false}};
		break;
	case T:
		shape = {{false, true, false}, {true, true, true}};
		break;
	case Z:
		shape = {{true, true, false}, {false, true, true}};
		break;
	}
	
	if (type != O)
	{
		for (u8 i = 0; i < rand_int(3); i++)
			rotate();
	}

	pos = {(LEVEL_WIDTH - width()) / 2, BUFFER_HEIGHT - 1};
}

auto Block::display() const -> void
{
	text_color(this->color);
	for (auto& i : shape)
	{
		for (auto&& j : i)
			print(j ? U_SQUARE : U_EMPTY);
		println(L"");
	}
}

auto Block::width() const -> u64
{
	return shape[0].size();
}

auto Block::height() const -> u64
{
	return shape.size();
}

auto Block::can_move(const i8& direction) const -> bool
{
	switch (direction)
	{
	case -1:
		if (pos.first <= 0)
			return false;
		break;
	case 0:
		if (pos.second >= LEVEL_HEIGHT)
			return false;
		break;
	case 1:
		if (pos.first + width() >= LEVEL_WIDTH)
			return false;
		break;
	default:
		break;
	}
	return true;
}

auto Block::move(const i8& direction) -> void
{
	if (!can_move(direction))
		return;

	switch (direction)
	{
	case -1:
		pos.first--;
		break;
	case 0:
		pos.second++;
		break;
	case 1:
		pos.first++;
		break;
	default:
		break;
	}
}

auto Block::rotate(const bool& clockwise) -> void
{
	if (type == O)
		return;
	std::vector<std::vector<bool>> temp;
	for (u64 i = 0; i < shape[0].size(); i++)
	{
		temp.emplace_back();
		for (u64 j = shape.size(); j > 0; j--)
			temp[i].emplace_back(shape[j - 1][i]);
	}
	shape = temp;
}

auto Block::launch() -> thread
{
	return thread([&] {		
		while (!game->exit_flag && can_move())
		{
			move();
			sleep(TICK_RATE * 5);
		}
		game->level->lock_block();
		delete this;
	});
}
