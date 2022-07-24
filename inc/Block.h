#pragma once

#include "globals.h"

namespace cetris
{
	struct Game;
	struct Level;

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
		Game* game;
		std::vector<std::vector<bool>> shape = {};
		std::pair<hulk::i8, hulk::i8> pos;
		hulk::console::color color;
		const shape_t type;

		explicit Block(Game&);
		Block(Game&, const shape_t&);

		[[nodiscard]] auto width() const -> hulk::u64;
		[[nodiscard]] auto height() const -> hulk::u64;

		[[nodiscard]] auto can_move(const hulk::i8& = 0) const -> bool;
		auto move(const hulk::i8& = 0) -> void;
		auto rotate(const bool& = true) -> void;
		
		auto display() const -> void;
		auto launch() -> hulk::thread;
	};
}
