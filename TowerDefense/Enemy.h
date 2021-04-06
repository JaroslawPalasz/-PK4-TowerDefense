#pragma once
#include "MovableObject.h"

class Enemy : public MovableObject
{
public:
	Enemy(const TEXTURES &id, const sf::Vector2i _coordinates, const sf::Vector2f __coordinates)
		: MovableObject(id, _coordinates)
	{
		this->type = id;
		switch (this->type)
		{
		case(ENEMY_FAST):
			this->speed = 2.;
			this->hitpoints = 6.;
			this->damage = 2;
			break;
		case(ENEMY_HEAVY):
			this->speed = 1.2;
			this->hitpoints = 10.;
			this->damage = 3;
			break;
		case(ENEMY_BOSS):
			this->speed = 0.9;
			this->hitpoints = 20.;
			this->damage = 6;
			break;
		}
		set_sprite_position(_coordinates, 54., 54.);
		circle.setRadius(1);
		circle.setOutlineColor(sf::Color::Red);
		circle.setOutlineThickness(1);
		circle.setOrigin(circle.getRadius(), circle.getRadius());
		circle.setPosition(__coordinates.x+54./2, __coordinates.y + 54. / 2);
	}

	void update(std::vector<DIRECTIONS>& path);

	sf::CircleShape circle;
	sf::Vector2i coordinates;
	sf::Time slow_time;
	sf::Time freeze_time;
	sf::Time poison_time;
	sf::Time poison_each_second;
	TEXTURES type;
	int it_path = 0;
	bool is_frozen = false;
	bool is_poisoned = false;
	bool is_slowed = false;
	bool is_alive = true;
	bool end = false;
	float speed;
	float hitpoints;
	int damage;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(this->get_sprite());
	}
};