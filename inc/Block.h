#pragma once

#include "globals.h"

namespace cetris
{
	struct Game;

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
		explicit Block(Game&);
		Block(Game&, const shape_t&);
		auto display() const -> void;

		Game* game;
		const shape_t type;
		std::pair<hulk::i8, hulk::i8> pos;
		hulk::console::color color;
		std::vector<std::vector<bool>> shape = {};

		[[nodiscard]] auto width() const -> hulk::u64;
		[[nodiscard]] auto height() const -> hulk::u64;
		
		auto launch() -> hulk::thread;
		auto move(const hulk::i8& = 0) -> bool;
		auto rotate(const bool& = true) -> void;
	};
}
