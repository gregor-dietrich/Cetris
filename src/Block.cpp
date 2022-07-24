#include "Game.h"
#include "Block.h"

using namespace cetris;
using namespace hulk;

Block::Block(Game& game) : Block(game, static_cast<shape_t>(rand_int(6)))
{
}

Block::Block(Game& game, const shape_t& type): game(&game), type(type), pos({0, BUFFER_HEIGHT - 1}),
	color(static_cast<console::color>(rand_int(1, console::color::white)))	
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

auto Block::move(const i8& direction) -> bool
{
	switch (direction)
	{
	case -1:
		if (pos.first > 0)
			pos.first--;
		break;
	case 0:
		if (pos.second < LEVEL_HEIGHT)
			pos.second++;
		break;
	case 1:
		if (pos.first + width() < LEVEL_WIDTH)
			pos.first++;
		break;
	default:
		break;
	}
	return true;
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
			temp[i].push_back(shape[j - 1][i]);
	}
	shape = temp;
}

auto Block::launch() -> thread
{
	return thread([&] {		
		while (!game->exit_flag && pos.second < LEVEL_HEIGHT)
		{
			move();
			sleep(TICK_RATE * 5);
		}		
		game->level->lock_block();
		delete this;
	});
}
