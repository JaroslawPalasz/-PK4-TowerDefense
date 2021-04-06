#pragma once
#include "Object.h"
#include "TowerPanel.h"
#include "PowerPanel.h"
#include "Power.h"

class Player : public sf::Drawable
{
public:
	Player()
	{

	}
	/*sets heart, gold, text textures and position*/
	Player(int lives, int money, int waves, TextureHolder * textures, sf::Font & font)
		:lives(lives),
		money(money),
		waves(0, waves),
		textures(textures)
	{

		//panels - always displaying
		hearts_panel.setSize(sf::Vector2f(142.f, 64.f));
		hearts_panel.setOutlineColor(sf::Color::Black);
		hearts_panel.setTexture(&textures->get(PANEL));
		hearts_panel.setPosition(0.f,0.f);

		sf::Vector2f vec(hearts_panel.getSize().x + 48.f, hearts_panel.getSize().y);
		gold_panel.setSize(vec);
		gold_panel.setOutlineColor(sf::Color::Black);
		gold_panel.setTexture(&textures->get(PANEL));
		gold_panel.setPosition(hearts_panel.getPosition().x + hearts_panel.getSize().x, 
			hearts_panel.getPosition().y);
		vec = sf::Vector2f(hearts_panel.getSize().x + 66.f, hearts_panel.getSize().y);
		wave_panel.setSize(vec);
		wave_panel.setOutlineColor(sf::Color::Black);
		wave_panel.setTexture(&textures->get(PANEL));
		wave_panel.setPosition(gold_panel.getPosition().x + gold_panel.getSize().x,
			hearts_panel.getPosition().y);

		//hearts, gold sprites
		heart.setSize(sf::Vector2f(64.f, 64.f));
		heart.setTexture(&textures->get(HEART));
		heart.setPosition(hearts_panel.getPosition().x,
			hearts_panel.getPosition().y);

		gold.setSize(heart.getSize());
		gold.setTexture(&textures->get(GOLD));
		gold.setPosition(gold_panel.getPosition().x + 12.f,
			gold_panel.getPosition().y);

		text_lives.setFont(font);
		text_money.setFont(font);
		text_waves.setFont(font);

		text_lives.setString(std::to_string(this->lives));
		text_money.setString(std::to_string(this->money));
		s_waves = "wave " + std::to_string(this->waves.x) + "/" + std::to_string(this->waves.y);
		text_waves.setString(s_waves);

		text_lives.setCharacterSize(64);
		text_money.setCharacterSize(48);
		text_waves.setCharacterSize(48);

		text_lives.setFillColor(sf::Color::Black);
		text_money.setFillColor(sf::Color::Black);
		text_waves.setFillColor(sf::Color::Black);

		text_lives.setPosition(hearts_panel.getPosition().x + 64.f, hearts_panel.getPosition().y - 10.f);
		text_money.setPosition(gold_panel.getPosition().x + 74.f, gold_panel.getPosition().y);
		text_waves.setPosition(wave_panel.getPosition().x+ 10.f, wave_panel.getPosition().y);

		TOWER_MG.setFont(font);
		TOWER_ROCKET.setFont(font);
		TOWER_SLOW.setFont(font);
		TOWER_POISON.setFont(font);

		TOWER_MG.setLineSpacing(0.7);
		TOWER_ROCKET.setLineSpacing(0.7);
		TOWER_SLOW.setLineSpacing(0.7);
		TOWER_POISON.setLineSpacing(0.7);

		TOWER_MG.setString("damage: 2\nrange: 100\nspeed: 1.5s\nprice: 200");
		TOWER_ROCKET.setString("damage: 4\nrange: 200\nspeed: 3s\nprice: 300");
		TOWER_SLOW.setString("damage: 0\nrange: 150\nspeed: 1.4s\nprice: 150");
		TOWER_POISON.setString("dps: 0.6\nrange: 100\nprice: 260");

		TOWER_MG.setCharacterSize(20);
		TOWER_ROCKET.setCharacterSize(20);
		TOWER_SLOW.setCharacterSize(20);
		TOWER_POISON.setCharacterSize(20);
		
		TOWER_MG.setFillColor(sf::Color::Black);
		TOWER_ROCKET.setFillColor(sf::Color::Black);
		TOWER_SLOW.setFillColor(sf::Color::Black);
		TOWER_POISON.setFillColor(sf::Color::Black);
		

		TOWER_MG.setPosition(920.f, 155.f);
		TOWER_ROCKET.setPosition(TOWER_MG.getPosition().x, TOWER_MG.getPosition().y + 105.f);
		TOWER_SLOW.setPosition(TOWER_ROCKET.getPosition().x, TOWER_ROCKET.getPosition().y + 105.f);
		TOWER_POISON.setPosition(TOWER_SLOW.getPosition().x, TOWER_SLOW.getPosition().y + 120.f);

		explosion_cooldown.setFont(font);
		explosion_cooldown.setString("0");
		explosion_cooldown.setCharacterSize(40);
		explosion_cooldown.setFillColor(sf::Color::Black);
		explosion_cooldown.setPosition(280.f, 920.f);

		freeze_cooldown.setFont(font);
		freeze_cooldown.setString("0");
		freeze_cooldown.setCharacterSize(40);
		freeze_cooldown.setFillColor(sf::Color::Black);
		freeze_cooldown.setPosition(explosion_cooldown.getPosition().x + 100.f, explosion_cooldown.getPosition().y);

		slow_cooldown.setFont(font);
		slow_cooldown.setString("0");
		slow_cooldown.setCharacterSize(40);
		slow_cooldown.setFillColor(sf::Color::Black);
		slow_cooldown.setPosition(freeze_cooldown.getPosition().x + 100.f, freeze_cooldown.getPosition().y);
	}

	void update_text(std::vector<std::shared_ptr<Object>>& panels, sf::Time &cooldown_time, std::vector<std::shared_ptr<Power>>& powers
		, bool paused, std::vector<std::shared_ptr<Tower>>& towers, bool explosion_used, bool freeze_used, bool slow_used);

	void update_money(int amount, bool buy);
	
	TextureHolder * textures;

	int lives;
	int money;
	sf::Vector2i waves;	//x - current wave, y - waves in level
	
	bool turret_pressed = false;
	bool power_pressed = false;

	bool is_pressed = false;

	bool can_draw_towers = false;
	bool can_draw_powers = false;
	TEXTURES id_pressed = NONE;
	sf::RectangleShape hearts_panel;
	sf::RectangleShape gold_panel;
	sf::RectangleShape wave_panel;

	sf::RectangleShape heart;
	sf::RectangleShape gold;

	sf::Font font;
	sf::Text text_lives;
	sf::Text text_money;
	sf::Text text_waves;

	//tower texts
	sf::Text TOWER_MG;
	sf::Text TOWER_ROCKET;
	sf::Text TOWER_SLOW;
	sf::Text TOWER_POISON;

	//cooldowns
	sf::Text explosion_cooldown;
	sf::Text freeze_cooldown;
	sf::Text slow_cooldown;

	sf::Time explosion_time = sf::seconds(20);
	sf::Time freeze_time = sf::seconds(20);
	sf::Time slow_time = sf::seconds(20);

	std::string s_waves;

private:
	virtual void Drawable::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		//drawing panel for hearts
		target.draw(hearts_panel);
		target.draw(gold_panel);
		target.draw(wave_panel);

		//drawing heart and gold
		//TODO: changing heart texture every 2 life lost
		target.draw(heart);
		target.draw(gold);
		//displaying amount of lives and gold	(heart/gold: amount)
		//displaying waves x/y
		target.draw(text_lives);
		target.draw(text_money);
		target.draw(text_waves);
		//displaying cooldown of powers
		if (can_draw_powers)
		{
			target.draw(explosion_cooldown);
			target.draw(freeze_cooldown);
			target.draw(slow_cooldown);
		}
		//displaying properties of towers from tower panel (IF)
		if (can_draw_towers)
		{
			target.draw(TOWER_MG);
			target.draw(TOWER_ROCKET);
			target.draw(TOWER_SLOW);
			target.draw(TOWER_POISON);
		}
	}
};