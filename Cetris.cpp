#include "Game.h"

using namespace cetris;
using namespace hulk;

i32 main()
{
	console::enable_unicode();

	const auto game = new Game();
	game->main_loop();

	delete game;
	return !console::text_color();
}
