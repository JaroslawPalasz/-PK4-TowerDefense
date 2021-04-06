#include "Tower.h"

/*checks if tower can be upgraded - is not at max level*/
bool Tower::can_upgrade()
{
	int max_level;
	switch (tower_type)
	{
	case(TOWER_MG_1):
		max_level = 3;
		break;
	case(TOWER_POISON_1):
	case(TOWER_SLOW_1):
	case(TOWER_ROCKET_1):
		max_level = 2;
		break;
	}
	if (level < max_level)
		return true;
	return false;
}

/*upgrades twoer - changes it properties and textures*/
void Tower::upgrade_tower()
{
	switch (get_id())
	{
	case(TOWER_MG_1):
		set_sprite(TOWER_MG_2);
		bullet_type = BULLET_MG_2;
		upgrade_to_level.setTexture(&textureMap->get(UPGRADE_2));
		circle.setRadius(120);
		cooldown_seconds = 1.3;
		upgrade_cost = 300;
		damage = 3.;
		break;
	case(TOWER_MG_2):
		set_sprite(TOWER_MG_3);
		upgrade_to_level.setTexture(&textureMap->get(UPGRADE_3));
		circle.setRadius(130);
		cooldown_seconds = 1.1;
		upgrade_cost = 420;
		damage = 3.5;
		break;
	case(TOWER_ROCKET_1):
		set_sprite(TOWER_ROCKET_2);
		bullet_type = BULLET_ROCKET_2;
		upgrade_to_level.setTexture(&textureMap->get(UPGRADE_2));
		circle.setRadius(230);
		cooldown_seconds = 2.2;
		upgrade_cost = 500;
		damage = 5;
		break;
	case(TOWER_SLOW_1):
		set_sprite(TOWER_SLOW_2);
		upgrade_to_level.setTexture(&textureMap->get(UPGRADE_2));
		circle.setRadius(160);
		cooldown_seconds = 1.2;
		upgrade_cost = 180;
		damage = 1.;
		break;
	case(TOWER_POISON_1):
		set_sprite(TOWER_POISON_2);
		upgrade_to_level.setTexture(&textureMap->get(UPGRADE_2));
		circle.setRadius(120);
		cooldown_seconds = 1.5;
		upgrade_cost = 320;
		this->damage = 1.5;
		break;
	}
	circle.setOrigin(circle.getRadius(), circle.getRadius());
	circle.setPosition(get_sprite().getPosition().x + 54. / 2, get_sprite().getPosition().y + 54. / 2);
	level++;
	value = upgrade_cost / 2;
	range = circle.getRadius();
}

/*checks if an enemy is in range and time interval, creates bullet object*/
void Tower::shoot(std::vector<std::shared_ptr<Enemy>>& enemies, std::vector<std::shared_ptr<Bullet>>& bullets, sf::Vector2f end_position, sf::Time & time)
{
	if (enemies.size() > 0)
	{
		bool found = false;
		//find shortest distance
		int j = 0;
		for (int i = 0; i < enemies.size(); i++)
		{
			if (enemies[i]->circle.getGlobalBounds().intersects(circle.getGlobalBounds()))
			{
				j = i;
				found = true;
				break;
			}
		}
		if (found)
		{
			//different cooldowns for different types of towers
			if (cooldown.asSeconds() > cooldown_seconds)
			{
				bullets.push_back(std::make_shared<Bullet>(bullet_type, circle.getPosition(),
					get_coordinates(), enemies[j], circle.getRadius(), damage));
				std::cout << "bullet spawned" << std::endl;
				cooldown = sf::Time();
			}
			else
				cooldown += time;
		}
	}
}