#include "Player.h"

/*updates text to draw on screen - lives, money, properties of towers to buy, cooldown of powers*/
void Player::update_text(std::vector<std::shared_ptr<Object>>& panels, sf::Time & cooldown_time, std::vector<std::shared_ptr<Power>>& powers, bool paused, std::vector<std::shared_ptr<Tower>>& towers, bool explosion_used, bool freeze_used, bool slow_used)
{
	//lives, money, waves
	text_lives.setString(std::to_string(this->lives));
	text_money.setString(std::to_string(this->money));
	s_waves = "wave " + std::to_string(this->waves.x) + "/" + std::to_string(this->waves.y);
	text_waves.setString(s_waves);

	//towerpower panel
	if (std::shared_ptr<TowerPanel> towerpanel = std::dynamic_pointer_cast<TowerPanel>(panels[0]))
	{
		if (towerpanel->can_draw)
			can_draw_towers = true;
		else
			can_draw_towers = false;
	}
	if (std::shared_ptr<PowerPanel> powerpanel = std::dynamic_pointer_cast<PowerPanel>(panels[1]))
	{
		if (powerpanel->can_draw)
			can_draw_powers = true;
		else
			can_draw_powers = false;
	}
	//update cooldowns
	if(!paused)
	{
		for (auto const& value : powers)
		{
			if (value->on_cooldown)
			{
				switch (value->get_id())
				{
				case(POWERUP_EXPLOSION):
					explosion_time -= cooldown_time;
					break;
				case(POWERUP_FREEZE):
					freeze_time -= cooldown_time;
					break;
				case(POWERUP_SLOW):
					slow_time -= cooldown_time;
					break;
				}
			}
			else
			{
				switch (value->get_id())
				{
				case(POWERUP_EXPLOSION):
					explosion_time = sf::seconds(20);
					explosion_cooldown.setString("0");
					break;
				case(POWERUP_FREEZE):
					freeze_time = sf::seconds(20);
					freeze_cooldown.setString("0");
					break;
				case(POWERUP_SLOW):
					slow_time = sf::seconds(20);
					slow_cooldown.setString("0");
					break;
				}
			}
		}
		explosion_cooldown.setString(std::to_string(static_cast<unsigned int>(explosion_time.asSeconds())));
		freeze_cooldown.setString(std::to_string(static_cast<unsigned int>(freeze_time.asSeconds())));
		slow_cooldown.setString(std::to_string(static_cast<unsigned int>(slow_time.asSeconds())));
	}

	//update buy/sell price
	for (auto const& value : towers)
	{
		if (value->is_pressed)
		{
			value->buy_sell.setFont(font);
			std::string text = std::to_string(value->upgrade_cost) /*+ "    " + value->value*/;
			value->buy_sell.setString("elo");
			value->buy_sell.setCharacterSize(40);
			value->buy_sell.setFillColor(sf::Color::Black);
			value->buy_sell.setPosition(value->upgrade_to_level.getPosition());
		}
	}
}

/*updates player money*/
void Player::update_money(int amount, bool buy)
{
	//buying tower
	if (buy)
	{
		money -= amount;
		if (money < 0)
			money = 0;
	}
	//selling tower for 1/2 of its value or killing enemy
	else
		money += amount;
}