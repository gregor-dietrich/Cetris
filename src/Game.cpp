#include "Game.h"

using namespace cetris;
using namespace hulk;

Game::Game()
{
	this->input = new Input(*this);
	this->level = new Level(*this);

	this->active_block = new Block(*this);
	this->next_block = new Block(*this);
	
	threads.emplace_back(input->handle());
	threads.emplace_back(input->listen());

	auto t = active_block->launch();
	t.detach();
}

Game::~Game()
{
	for (auto& t: threads)
		t.join();
	delete this->input;
	delete this->level;
	delete this->next_block;
	delete this->active_block;
}

auto Game::main_loop() -> void
{
	if (exit_flag)
		return;

	level->draw();

	main_loop();
}
