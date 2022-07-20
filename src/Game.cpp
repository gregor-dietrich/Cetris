#include "Game.h"

using namespace cetris;
using namespace hulk;

Game::Game()
{
	this->level = new Level();

	this->active_block = new Block();
	this->next_block = new Block();

	this->input = new Input(*this);
	listen_thread = input->listen();
	input_thread = input->handle();
}

Game::~Game()
{
	if (listen_thread.joinable())
		listen_thread.join();
	if (input_thread.joinable())
		input_thread.join();
	delete this->input;
	delete this->level;
}

auto Game::main_loop() -> void
{
	if (exit_flag)
		return;
	
	console::clear();
	level->draw();

	sleep(1000);
	main_loop();
}
 