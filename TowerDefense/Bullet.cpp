#include "Bullet.h"

/*shoots a bullet - moves it with rotation, if rocket then hit all enemies in radius, sets enemies hitpoints*/
void Bullet::shoot(std::vector<std::shared_ptr<Enemy>>& enemies)
{
	tower_center = circle.getPosition();
	enemy_center = enemy->circle.getPosition();
	aimdir = enemy_center - tower_center;
	//aimdir_normalized = aimdir / sqrt(pow(aimdir.x, 2) + pow(aimdir.y, 2));
	aimdir_normalized.x = aimdir.x / sqrt(pow(aimdir.x, 2) + pow(aimdir.y, 2));
	aimdir_normalized.y = aimdir.y / sqrt(pow(aimdir.x, 2) + pow(aimdir.y, 2));
	velocity = aimdir_normalized * speed;

	//rotating bullet, converting to degrees from rads
	float angle = atan2((circle.getPosition().y - enemy->circle.getPosition().y),
		(enemy->circle.getPosition().x - circle.getPosition().x));
	float degrees = angle * 57.2957795f;
	circle.setRotation(degrees);

	if (sqrt(pow(aimdir.x, 2) + pow(aimdir.y, 2)) > 20)	// 20 - hitbox
	{
		circle.setPosition(circle.getPosition() + velocity);
	}
	else
	{
		std::cout << "enemy hit" << std::endl;
		switch (type)
		{
		case(BULLET_MG_1):
		case(BULLET_MG_2):
			enemy->hitpoints -= damage;
			break;
		case(BULLET_POISON_1):
			enemy->is_poisoned = true;
			enemy->hitpoints -= damage;
			break;
		case(BULLET_SLOW_1):
			enemy->is_slowed = true;
			enemy->hitpoints -= damage;
			break;
		case(BULLET_ROCKET_1):
		case(BULLET_ROCKET_2):
			//search other enemies in radius
			for (auto const& value : enemies)
			{
				if (circle.getGlobalBounds().intersects(value->circle.getGlobalBounds()))
				{
					std::cout << "Rocket goes boom" << std::endl;
					value->hitpoints -= damage;
				}
			}
			break;
		}

		hit_target = true;
		if (enemy->hitpoints <= 0.)
			enemy->is_alive = false;
	}
}
