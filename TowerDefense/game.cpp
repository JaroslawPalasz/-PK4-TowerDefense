#include "game.h"

/*main game loop*/
void Game::game_loop()
{
	sf::Clock clock;
	while (Window.isOpen())
	{
		process(clock);
		render();
		if (checkendgame() == 0)
		{
			end_game("You've lost");
		}
		else if (checkendgame() == 1)
		{
			end_game("You've won");
		}
	}
}

/*processes all events*/
void Game::process(sf::Clock & clock)
{
	sf::Time time = clock.getElapsedTime();
	clock.restart();
	sf::Event evnt;
	while (Window.pollEvent(evnt))
	{
		if (evnt.type == sf::Event::Closed)
			Window.close();
		if (evnt.type == sf::Event::KeyPressed)
			if (evnt.key.code == sf::Keyboard::Escape)
				Window.close();

		scene_manager.process_click(evnt, Window, time, time);
		scene_manager.update_cursor(evnt, Window);
	}
	scene_manager.update_text(time);
	scene_manager.update_texture_enemies();
	scene_manager.update_towers();

	process_pause(clock, time);
}

/*handles time calculation depending of state of the game (paused or not)*/
void Game::process_pause(sf::Clock & clock, sf::Time time)
{
	if (scene_manager.paused)
	{
		if (!paused)
		{
			//writing only once
			pause_time = clock.getElapsedTime();
			paused = true;
		}
	}
	else
	{
		if (pause_time.asSeconds() != 0)
		{
			time = pause_time;
			pause_time = sf::Time();
		}
		scene_manager.update_powers(time, time);
		scene_manager.process_enemies(Window, time, time, time,
			time, time);
		scene_manager.update_text(time);
	}
}

/*checks if level ended - lost all of lives or finished all waves*/
int Game::checkendgame()
{
	//losing
	if (scene_manager.getLives() <= 0)
		return 0;
	//winning
	if (scene_manager.isfinished() && scene_manager.get_enemies() == 0)
		return 1;
	return 2;
}

/*shows screen after finishing the game*/
void Game::end_game(std::string s)
{
	text.setString(s);
	Window.clear();
	Window.draw(background);
	Window.draw(text);
	Window.display();
	while (Window.isOpen())
	{
		sf::Event evnt;
		while (Window.pollEvent(evnt))
		{
			if ((evnt.type == sf::Event::Closed) || (evnt.type == sf::Event::KeyPressed && evnt.key.code == sf::Keyboard::Escape) ||
				(evnt.type == sf::Event::MouseButtonPressed))
				Window.close();
		}
	}
}

/*renders all of sprites*/
void Game::render()
{
	Window.clear();
	Window.draw(scene_manager);
	Window.display();
}