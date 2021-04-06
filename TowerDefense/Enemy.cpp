#include "Enemy.h"

/*sets enemy texture dependning on its position*/
void Enemy::update(std::vector<DIRECTIONS>& path)
{
	if (is_frozen && is_poisoned)
	{
		switch (type)
		{
		case(ENEMY_FAST):
			switch (path[it_path])
			{
			case(RIGHT):
				set_sprite(ENEMY_FAST_FREEZED_POISONED_RIGHT);
				break;
			case(LEFT):
				set_sprite(ENEMY_FAST_FREEZED_POISONED_LEFT);
				break;
			case(UP):
				set_sprite(ENEMY_FAST_FREEZED_POISONED_UP);
				break;
			case(DOWN):
				set_sprite(ENEMY_FAST_FREEZED_POISONED_DOWN);
				break;
			}
			break;
		case(ENEMY_BOSS):
			switch (path[it_path])
			{
			case(RIGHT):
				set_sprite(ENEMY_BOSS_FREEZED_POISONED_RIGHT);
				break;
			case(LEFT):
				set_sprite(ENEMY_BOSS_FREEZED_POISONED_LEFT);
				break;
			case(UP):
				set_sprite(ENEMY_BOSS_FREEZED_POISONED_UP);
				break;
			case(DOWN):
				set_sprite(ENEMY_BOSS_FREEZED_POISONED_DOWN);
				break;
			}
			break;
		case(ENEMY_HEAVY):
			switch (path[it_path])
			{
			case(RIGHT):
				set_sprite(ENEMY_HEAVY_FREEZED_POISONED_RIGHT);
				break;
			case(LEFT):
				set_sprite(ENEMY_HEAVY_FREEZED_POISONED_LEFT);
				break;
			case(UP):
				set_sprite(ENEMY_HEAVY_FREEZED_POISONED_UP);
				break;
			case(DOWN):
				set_sprite(ENEMY_HEAVY_FREEZED_POISONED_DOWN);
				break;
			}
			break;
		}
	}
	else if (is_frozen)
	{
		switch (type)
		{
		case(ENEMY_FAST):
			switch (path[it_path])
			{
			case(RIGHT):
				set_sprite(ENEMY_FAST_FREEZED_RIGHT);
				break;
			case(LEFT):
				set_sprite(ENEMY_FAST_FREEZED_LEFT);
				break;
			case(UP):
				set_sprite(ENEMY_FAST_FREEZED_UP);
				break;
			case(DOWN):
				set_sprite(ENEMY_FAST_FREEZED_DOWN);
				break;
			}
			break;
		case(ENEMY_BOSS):
			switch (path[it_path])
			{
			case(RIGHT):
				set_sprite(ENEMY_BOSS_FREEZED_RIGHT);
				break;
			case(LEFT):
				set_sprite(ENEMY_BOSS_FREEZED_LEFT);
				break;
			case(UP):
				set_sprite(ENEMY_BOSS_FREEZED_UP);
				break;
			case(DOWN):
				set_sprite(ENEMY_BOSS_FREEZED_DOWN);
				break;
			}
			break;
		case(ENEMY_HEAVY):
			switch (path[it_path])
			{
			case(RIGHT):
				set_sprite(ENEMY_HEAVY_FREEZED_RIGHT);
				break;
			case(LEFT):
				set_sprite(ENEMY_HEAVY_FREEZED_LEFT);
				break;
			case(UP):
				set_sprite(ENEMY_HEAVY_FREEZED_UP);
				break;
			case(DOWN):
				set_sprite(ENEMY_HEAVY_FREEZED_DOWN);
				break;
			}
			break;
		
		}
	}
	else if (is_poisoned)
	{
		switch (type)
		{
		case(ENEMY_FAST):
			switch (path[it_path])
			{
			case(RIGHT):
				set_sprite(ENEMY_FAST_POISONED_RIGHT);
				break;
			case(LEFT):
				set_sprite(ENEMY_FAST_POISONED_LEFT);
				break;
			case(UP):
				set_sprite(ENEMY_FAST_POISONED_UP);
				break;
			case(DOWN):
				set_sprite(ENEMY_FAST_POISONED_DOWN);
				break;
			}
			break;
		case(ENEMY_BOSS):
			switch (path[it_path])
			{
			case(RIGHT):
				set_sprite(ENEMY_BOSS_POISONED_RIGHT);
				break;
			case(LEFT):
				set_sprite(ENEMY_BOSS_POISONED_LEFT);
				break;
			case(UP):
				set_sprite(ENEMY_BOSS_POISONED_UP);
				break;
			case(DOWN):
				set_sprite(ENEMY_BOSS_POISONED_DOWN);
				break;
			}
			break;
		case(ENEMY_HEAVY):
			switch (path[it_path])
			{
			case(RIGHT):
				set_sprite(ENEMY_HEAVY_POISONED_RIGHT);
				break;
			case(LEFT):
				set_sprite(ENEMY_HEAVY_POISONED_LEFT);
				break;
			case(UP):
				set_sprite(ENEMY_HEAVY_POISONED_UP);
				break;
			case(DOWN):
				set_sprite(ENEMY_HEAVY_POISONED_DOWN);
				break;
			}
			break;
		}
	}
	else
	{
		switch (type)
		{
		case(ENEMY_FAST):
			switch (path[it_path])
			{
			case(RIGHT):
				set_sprite(ENEMY_FAST_RIGHT);
				break;
			case(LEFT):
				set_sprite(ENEMY_FAST_LEFT);
				break;
			case(UP):
				set_sprite(ENEMY_FAST_UP);
				break;
			case(DOWN):
				set_sprite(ENEMY_FAST_DOWN);
				break;
			}
			break;
		case(ENEMY_BOSS):
			switch (path[it_path])
			{
			case(RIGHT):
				set_sprite(ENEMY_BOSS_RIGHT);
				break;
			case(LEFT):
				set_sprite(ENEMY_BOSS_LEFT);
				break;
			case(UP):
				set_sprite(ENEMY_BOSS_UP);
				break;
			case(DOWN):
				set_sprite(ENEMY_BOSS_DOWN);
				break;
			}
			break;
		case(ENEMY_HEAVY):
			switch (path[it_path])
			{
			case(RIGHT):
				set_sprite(ENEMY_HEAVY_RIGHT);
				break;
			case(LEFT):
				set_sprite(ENEMY_HEAVY_LEFT);
				break;
			case(UP):
				set_sprite(ENEMY_HEAVY_UP);
				break;
			case(DOWN):
				set_sprite(ENEMY_HEAVY_DOWN);
				break;
			}
			break;
		}
	}
}