#include "Game.h"

using namespace cetris;
using namespace hulk;

Game::Game(): input(new Input(*this)), level(new Level(*this))
{	
	threads.emplace_back(input->handle());
	threads.emplace_back(input->listen());
}

Game::~Game()
{
	for (auto& t: threads)
		t.join();
	delete this->input;
	delete this->level;
}

auto Game::main_loop() -> void
{
	if (exit_flag)
		return;

	level->draw();

	main_loop();
}
