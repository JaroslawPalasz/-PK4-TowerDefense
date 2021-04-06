#pragma once
#include "enums.h"
#include "TextureHolder.h"
#include "SceneManager.h"
#include "Object.h"


class Game
{
public:
	Game(TextureHolder * textures, int level)
		: Window(sf::VideoMode(1080, 1080), "Tower Defense", sf::Style::Default)	//simple window
		, texture_holder(textures)	
		, background(textures->get(BACKGROUND))
		, scene_manager(textures)	//initializing texture holder, then game scene class with it
	{
		background.setScale(1.2, 1.2);
		text.setFont(font);
		text.setString("-");
		text.setCharacterSize(48);
		text.setFillColor(sf::Color::Red);
		text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
		text.setPosition(Window.getSize().x / 2.0f, Window.getSize().y / 2.0f);

		Window.setFramerateLimit(60);
		Object::textureMap = texture_holder;
		scene_manager.load_level(level);
	}

	void game_loop();	//main game loop

	int checkendgame();

	void end_game(std::string s);

private:
	//processing user input
	void process(sf::Clock &clock);

	void process_pause(sf::Clock & clock, sf::Time time);

	//drawing all objects on screen
	void render();

private:
	sf::Font font;
	sf::Sprite background;
	sf::Text text;
	sf::Time pause_time;
	bool paused = false;
	TextureHolder * texture_holder;
	SceneManager scene_manager;
	sf::RenderWindow Window;
};