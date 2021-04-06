#pragma once
#include "enums.h"
#include "TextureHolder.h"

class Menu
{

public:
	Menu(TextureHolder * textures)
		:Window(sf::VideoMode(1016, 1080), "Menu"),
		textures(textures),
		background(textures->get(BACKGROUND)),
		test(textures->get(BUTTON)),
		level1(textures->get(BUTTON)),
		level2(textures->get(BUTTON))
	{
		if (!font.loadFromFile("fonts/arial.ttf"))
		{
			throw std::runtime_error("failed to load font");
		}

		level_test.setFont(font);
		level_1.setFont(font);
		level_2.setFont(font);

		level_test.setString("Test");
		level_1.setString("level 1");
		level_2.setString("level 2");
		level_test.setCharacterSize(76);
		level_1.setCharacterSize(76);
		level_2.setCharacterSize(76);
		level_test.setFillColor(sf::Color::Red);
		level_1.setFillColor(sf::Color::Red);
		level_2.setFillColor(sf::Color::Red);

		level_test.setOrigin(level_test.getLocalBounds().width / 2, level_test.getLocalBounds().height / 2);
		level_test.setPosition(Window.getSize().x / 2.0f + 150.f, Window.getSize().y / 2.0f - 320.f);

		level_1.setOrigin(level_1.getLocalBounds().width / 2, level_1.getLocalBounds().height / 2);
		level_1.setPosition(level_test.getPosition().x + 40.f , level_test.getPosition().y + 300.f);

		level_2.setOrigin(level_2.getLocalBounds().width / 2, level_2.getLocalBounds().height / 2);
		level_2.setPosition(level_1.getPosition().x, level_1.getPosition().y + 300.f);

		test.setOrigin(test.getLocalBounds().width / 2, test.getLocalBounds().height / 2);
		test.setPosition(Window.getSize().x / 2.0f - 100.f, Window.getSize().y / 2.0f - 300.f );

		level1.setOrigin(level1.getLocalBounds().width / 2, level1.getLocalBounds().height / 2);
		level1.setPosition(test.getPosition().x, test.getPosition().y + 300.f);

		level2.setOrigin(level2.getLocalBounds().width / 2, level2.getLocalBounds().height / 2);
		level2.setPosition(level1.getPosition().x, level1.getPosition().y + 300.f);
	}

	int get_level()
	{
		return level;
	}

	void loop()
	{
		while (Window.isOpen())
		{
			while (Window.pollEvent(evnt))
			{
				process();
				
					
			}
			render();
			check_if_chosen();
		}
	}

	void process()
	{
		if (evnt.type == sf::Event::Closed)
		{
			Window.close();
			level = 3;
		}
		if (evnt.type == sf::Event::KeyPressed)
			if (evnt.key.code == sf::Keyboard::Escape)
			{
				Window.close();
				level = 3;
			}
		if ((evnt.type == sf::Event::MouseButtonPressed) && (evnt.key.code == sf::Mouse::Left))
		{
			auto mousePos = sf::Mouse::getPosition(Window);	//Vector2i
			auto translatedPos = Window.mapPixelToCoords(mousePos);	//Vector2f

			if (test.getGlobalBounds().contains(translatedPos))
			{
				level = 0;
				level_chosen = true;
			}
			else if (level1.getGlobalBounds().contains(translatedPos))
			{
				level = 1;
				level_chosen = true;
			}
			else if (level2.getGlobalBounds().contains(translatedPos))
			{
				level = 2;
				level_chosen = true;
			}
		}
	}

	void render()
	{
		Window.clear();

		Window.draw(background);
		Window.draw(test);
		Window.draw(level1);
		Window.draw(level2);
		Window.draw(level_test);
		Window.draw(level_1);
		Window.draw(level_2);

		Window.display();
	}

	void check_if_chosen()
	{
		if (level_chosen)
			Window.close();
	}

private:
	TextureHolder * textures;
	sf::RenderWindow Window;
	sf::Event evnt;
	sf::Font font;
	sf::Text level_test;
	sf::Text level_1;
	sf::Text level_2;

	sf::Sprite background;
	sf::Sprite test;
	sf::Sprite level1;
	sf::Sprite level2;

	int level = 99;
	bool level_chosen = false;

};