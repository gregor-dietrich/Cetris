#include "Block.h"

using namespace cetris;
using namespace hulk;

Block::Block() : Block(static_cast<shape_t>(rand_int(6)))
{
}

Block::Block(const shape_t& variant):
	color(static_cast<console::color>(rand_int(1, console::color::white))),
	type(variant)
{
	switch (variant)
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

	if (this->type != O)
	{
		for (u8 i = 0; i < rand_int(3); i++)
			this->rotate();
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

auto Block::move(const i32& direction) -> bool
{
	switch (direction)
	{
	case VK_LEFT:
		this->pos.col--;
		break;
	case VK_RIGHT:
		this->pos.col++;
		break;
	case VK_DOWN:
		this->pos.row++;
		break;
	default:
		break;
	}
	return true;
}

auto Block::rotate() -> void
{
	if (this->type == O)
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
