#pragma once

#include "globals.h"

namespace cetris
{
	struct Pos final {
		hulk::i8 col = 8;
		hulk::i8 row = -BUFFER_HEIGHT;
	};

	enum shape_t
	{
		I,
		J,
		L,
		O,
		S,
		T,
		Z
	};
	
	struct Block final
	{
		std::vector<std::vector<bool>> shape = {};
		hulk::console::color color;
		const shape_t type;
		Pos pos;

		Block();
		explicit Block(const shape_t&);
		auto width() const -> hulk::u64;
		auto height() const -> hulk::u64;
		auto move(const hulk::i8&) -> bool;
		auto rotate() -> void;
		auto display() const -> void;
	};
}
