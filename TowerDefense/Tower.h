#pragma once
#include <algorithm>
#include <cmath>
#include "Object.h"
#include "Enemy.h"
#include "Tile.h"
#include "Bullet.h"

//when clicked can be sold/upgraded and shows range
class Tower : public Object
{
public:
	Tower(const TEXTURES &id, const sf::Vector2i _coordinates, bool is_buyable)
		: Object(id, _coordinates)
	{
		set_sprite_position(_coordinates, tower_size, tower_size);
		this->is_buyable = is_buyable;
		if (!is_buyable)
		{
			level = 1;
			switch (id)
			{
			case TOWER_MG_1:
				damage = 2.;
				circle.setRadius(100);
				this->cooldown_seconds = 1.5;
				this->upgrade_cost = 200;
				bullet_type = BULLET_MG_1;
				circle.setOutlineColor(sf::Color::Black);
				break;
			case TOWER_ROCKET_1:
				damage = 4;
				circle.setRadius(200);
				cooldown_seconds = 3.;
				bullet_type = BULLET_ROCKET_1;
				circle.setOutlineColor(sf::Color::Red);
				this->upgrade_cost = 300;
				break;
			case TOWER_SLOW_1:
				damage = 0.;
				circle.setRadius(150);
				cooldown_seconds = 1.4;
				bullet_type = BULLET_SLOW_1;
				circle.setOutlineColor(sf::Color::White);
				this->upgrade_cost = 150;
				break;
			case TOWER_POISON_1:
				this->damage = 1.;
				circle.setRadius(100);
				cooldown_seconds = 1.7;
				bullet_type = BULLET_POISON_1;
				circle.setOutlineColor(sf::Color::Green);
				this->upgrade_cost = 260;
				break;
			}
			circle.setOutlineThickness(1);
			circle.setFillColor(sf::Color::Transparent);
			circle.setOrigin(circle.getRadius(), circle.getRadius());
			circle.setPosition(get_sprite().getPosition().x + 54. / 2, get_sprite().getPosition().y + 54. / 2);
			range = circle.getRadius();

			sell.setSize(sf::Vector2f(22, 22));
			sell.setOutlineColor(sf::Color::Black);
			sell.setTexture(&textureMap->get(SELL));
			sell.setPosition(get_sprite().getPosition().x + 32., get_sprite().getPosition().y);

			upgrade_to_level.setSize(sf::Vector2f(22, 22));
			upgrade_to_level.setOutlineColor(sf::Color::Black);
			upgrade_to_level.setTexture(&textureMap->get(UPGRADE_1));
			upgrade_to_level.setPosition(get_sprite().getPosition().x, get_sprite().getPosition().y);

			//can shoot when spawned
			value = upgrade_cost / 2;
			cooldown = sf::seconds(cooldown_seconds);
			tower_type = id;
		}
	}

	bool can_upgrade();

	void upgrade_tower();

	//shooting nearest enemy
	void shoot(std::vector<std::shared_ptr<Enemy>>& enemies, std::vector<std::shared_ptr<Bullet>>& bullets,
		sf::Vector2f end_position, sf::Time& time);

	sf::CircleShape circle;
	sf::RectangleShape upgrade_to_level;
	sf::RectangleShape sell;
	TEXTURES bullet_type;
	TEXTURES tower_type;
	const float tower_size = 54.;
	float damage;
	int level;	//3 upgrade levels
	int upgrade_cost;
	int value;
	float range;
	bool is_pressed = false;
	bool is_buyable = false;
	bool sold = false;
	sf::Time cooldown;
	int cooldown_seconds;
	sf::Text buy_sell;

private:
	/*draws tower, its range and buttons to upgrade/sell if tower is clicked*/
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(this->get_sprite());
		if (is_pressed && !is_buyable)
		{
			target.draw(circle);
			target.draw(upgrade_to_level);
			target.draw(sell);
			target.draw(buy_sell);
		}
	}
};