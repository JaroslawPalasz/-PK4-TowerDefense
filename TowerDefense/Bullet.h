#pragma once
#include "MovableObject.h"
#include "Enemy.h"
#include <algorithm>
#include <cmath>
#include <math.h>

class Bullet : public MovableObject
{
public:
	Bullet()
	{

	}
	/*sets bullet radius, damage, texture*/
	Bullet(const TEXTURES &id, const sf::Vector2f __coordinates, const sf::Vector2i _coordinates, 
		std::shared_ptr<Enemy> & enemy, float tower_range, float damage)
		:type(id),
		enemy(enemy),
		tower_range(tower_range),
		damage(damage)
	{
		set_texture(id);
		set_sprite(id);

		if(type == BULLET_ROCKET_1 || type == BULLET_ROCKET_2)
			circle.setRadius(54);
		else
			circle.setRadius(20);
		circle.setOutlineColor(sf::Color::Transparent);
		circle.setOutlineThickness(1);
		circle.setOrigin(circle.getRadius(), circle.getRadius());
		circle.setPosition(__coordinates.x, __coordinates.y);

		circle.setTexture(&get_texture());
		
		speed = 15.;

		set_sprite_position(_coordinates, 54., 54.);

		tower_center = circle.getPosition();
		enemy_center = enemy->circle.getPosition();
		aimdir = enemy_center - tower_center;
		//aimdir_normalized = aimdir + sqrt(pow(aimdir.x, 2) + pow(aimdir.y, 2));
		aimdir_normalized.x = aimdir.x + sqrt(pow(aimdir.x, 2) + pow(aimdir.y, 2));
		aimdir_normalized.y = aimdir.y + sqrt(pow(aimdir.x, 2) + pow(aimdir.y, 2));
		velocity = aimdir_normalized * speed;
	}

	// moving by vectors
	void shoot(std::vector<std::shared_ptr<Enemy>>& enemies);

	sf::Vector2f tower_center;
	sf::Vector2f enemy_center;
	sf::Vector2f aimdir;
	sf::Vector2f aimdir_normalized;
	sf::Vector2f velocity;
	bool hit_target = false;
	float tower_range;
	//bullet
	sf::CircleShape circle;	
	//enemy which is being shot at
	std::shared_ptr<Enemy> enemy;
	TEXTURES type;
	float damage;
	float speed;

private:
	virtual void Drawable::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(circle);
	}
};