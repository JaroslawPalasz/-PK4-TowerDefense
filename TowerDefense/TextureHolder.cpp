#include "TextureHolder.h"

/*loads texture into map, throws exception if couldn't be loaded, closes program is was loaded more than once*/
void TextureHolder::load(TEXTURES id, std::string filename)
{
	std::unique_ptr<sf::Texture> texture(new sf::Texture());

	//texture couldn't be loaded
	if (!texture->loadFromFile(filename))
		throw std::runtime_error("TextureHolder failed to load " + filename);

	//texture was loaded more than one time to the same id
	auto is_inserted = textureMap.insert(std::pair<TEXTURES, std::unique_ptr<sf::Texture>>(id, std::move(texture)));
	assert(("It seems that the texture " + filename + " was loaded more than once", is_inserted.second));
}

/*gets texture from map*/
sf::Texture & TextureHolder::get(const TEXTURES & id)
{
	auto search = textureMap.find(id);

	//Error getting texture
	assert(("Error getting texture", search != textureMap.end()));
	return *search->second;
}

/*loads all of the textures*/
void TextureHolder::load_all()
{
	load(TILE_START, "textures/TILE_START.png");
	load(TILE_END, "textures/TILE_END.png");

	load(TILE_GRASS, "textures/TILE_GRASS.png");
	load(TILE_SAND, "textures/TILE_SAND.png");
	load(TILE_MUD, "textures/TILE_MUD.png");
	load(TILE_ROAD, "textures/TILE_ROAD.png");
	load(TILE_BUILD_GRASS, "textures/TILE_BUILD_GRASS.png");
	load(TILE_BUILD_SAND, "textures/TILE_BUILD_SAND.png");

	load(TOWER_MG_1, "textures/TOWER_MG_1.png");
	load(TOWER_MG_2, "textures/TOWER_MG_2.png");
	load(TOWER_MG_3, "textures/TOWER_MG_3.png");
	load(TOWER_ROCKET_1, "textures/TOWER_ROCKET_1.png");
	load(TOWER_ROCKET_2, "textures/TOWER_ROCKET_2.png");
	load(TOWER_SLOW_1, "textures/TOWER_SLOW_1.png");
	load(TOWER_SLOW_2, "textures/TOWER_SLOW_2.png");
	load(TOWER_POISON_1, "textures/TOWER_POISON_1.png");
	load(TOWER_POISON_2, "textures/TOWER_POISON_2.png");

	load(ENEMY_FAST, "textures/ENEMY_FAST.png");
	load(ENEMY_HEAVY, "textures/ENEMY_HEAVY.png");
	load(ENEMY_BOSS, "textures/ENEMY_BOSS.png");
	load(ENEMY_FAST_FREEZED, "textures/ENEMY_FAST_FREEZED.png");
	load(ENEMY_FAST_POISONED, "textures/ENEMY_FAST_POISONED.png");
	load(ENEMY_HEAVY_FREEZED, "textures/ENEMY_HEAVY_FREEZED.png");
	load(ENEMY_HEAVY_POISONED, "textures/ENEMY_HEAVY_POISONED.png");
	load(ENEMY_BOSS_FREEZED, "textures/ENEMY_BOSS_FREEZED.png");
	load(ENEMY_BOSS_POISONED, "textures/ENEMY_BOSS_POISONED.png");
	load(ENEMY_FAST_FREEZED_POISONED, "textures/ENEMY_FAST_FREEZED_POISONED.png");
	load(ENEMY_HEAVY_FREEZED_POISONED, "textures/ENEMY_HEAVY_FREEZED_POISONED.png");
	load(ENEMY_BOSS_FREEZED_POISONED, "textures/ENEMY_BOSS_FREEZED_POISONED.png");

	load(ENEMY_FAST_RIGHT, "textures/ENEMY_FAST_RIGHT.png");
	load(ENEMY_FAST_LEFT, "textures/ENEMY_FAST_LEFT.png");
	load(ENEMY_FAST_DOWN, "textures/ENEMY_FAST_DOWN.png");
	load(ENEMY_FAST_UP, "textures/ENEMY_FAST_UP.png");
	load(ENEMY_FAST_FREEZED_RIGHT, "textures/ENEMY_FAST_FREEZED_RIGHT.png");
	load(ENEMY_FAST_FREEZED_LEFT, "textures/ENEMY_FAST_FREEZED_LEFT.png");
	load(ENEMY_FAST_FREEZED_DOWN, "textures/ENEMY_FAST_FREEZED_DOWN.png");
	load(ENEMY_FAST_FREEZED_UP, "textures/ENEMY_FAST_FREEZED_UP.png");
	load(ENEMY_FAST_POISONED_RIGHT, "textures/ENEMY_FAST_POISONED_RIGHT.png");
	load(ENEMY_FAST_POISONED_LEFT, "textures/ENEMY_FAST_POISONED_LEFT.png");
	load(ENEMY_FAST_POISONED_DOWN, "textures/ENEMY_FAST_POISONED_DOWN.png");
	load(ENEMY_FAST_POISONED_UP, "textures/ENEMY_FAST_POISONED_UP.png");
	load(ENEMY_FAST_FREEZED_POISONED_RIGHT, "textures/ENEMY_FAST_FREEZED_POISONED_RIGHT.png");
	load(ENEMY_FAST_FREEZED_POISONED_LEFT, "textures/ENEMY_FAST_FREEZED_POISONED_LEFT.png");
	load(ENEMY_FAST_FREEZED_POISONED_DOWN, "textures/ENEMY_FAST_FREEZED_POISONED_DOWN.png");
	load(ENEMY_FAST_FREEZED_POISONED_UP, "textures/ENEMY_FAST_FREEZED_POISONED_UP.png");

	load(ENEMY_HEAVY_RIGHT, "textures/ENEMY_HEAVY_RIGHT.png");
	load(ENEMY_HEAVY_LEFT, "textures/ENEMY_HEAVY_LEFT.png");
	load(ENEMY_HEAVY_DOWN, "textures/ENEMY_HEAVY_DOWN.png");
	load(ENEMY_HEAVY_UP, "textures/ENEMY_HEAVY_UP.png");
	load(ENEMY_HEAVY_FREEZED_RIGHT, "textures/ENEMY_HEAVY_FREEZED_RIGHT.png");
	load(ENEMY_HEAVY_FREEZED_LEFT, "textures/ENEMY_HEAVY_FREEZED_LEFT.png");
	load(ENEMY_HEAVY_FREEZED_DOWN, "textures/ENEMY_HEAVY_FREEZED_DOWN.png");
	load(ENEMY_HEAVY_FREEZED_UP, "textures/ENEMY_HEAVY_FREEZED_UP.png");
	load(ENEMY_HEAVY_POISONED_RIGHT, "textures/ENEMY_HEAVY_POISONED_RIGHT.png");
	load(ENEMY_HEAVY_POISONED_LEFT, "textures/ENEMY_HEAVY_POISONED_LEFT.png");
	load(ENEMY_HEAVY_POISONED_DOWN, "textures/ENEMY_HEAVY_POISONED_DOWN.png");
	load(ENEMY_HEAVY_POISONED_UP, "textures/ENEMY_HEAVY_POISONED_UP.png");
	load(ENEMY_HEAVY_FREEZED_POISONED_RIGHT, "textures/ENEMY_HEAVY_FREEZED_POISONED_RIGHT.png");
	load(ENEMY_HEAVY_FREEZED_POISONED_LEFT, "textures/ENEMY_HEAVY_FREEZED_POISONED_LEFT.png");
	load(ENEMY_HEAVY_FREEZED_POISONED_DOWN, "textures/ENEMY_HEAVY_FREEZED_POISONED_DOWN.png");
	load(ENEMY_HEAVY_FREEZED_POISONED_UP, "textures/ENEMY_HEAVY_FREEZED_POISONED_UP.png");

	load(ENEMY_BOSS_RIGHT, "textures/ENEMY_BOSS_RIGHT.png");
	load(ENEMY_BOSS_LEFT, "textures/ENEMY_BOSS_LEFT.png");
	load(ENEMY_BOSS_DOWN, "textures/ENEMY_BOSS_DOWN.png");
	load(ENEMY_BOSS_UP, "textures/ENEMY_BOSS_UP.png");
	load(ENEMY_BOSS_FREEZED_RIGHT, "textures/ENEMY_BOSS_FREEZED_RIGHT.png");
	load(ENEMY_BOSS_FREEZED_LEFT, "textures/ENEMY_BOSS_FREEZED_LEFT.png");
	load(ENEMY_BOSS_FREEZED_DOWN, "textures/ENEMY_BOSS_FREEZED_DOWN.png");
	load(ENEMY_BOSS_FREEZED_UP, "textures/ENEMY_BOSS_FREEZED_UP.png");
	load(ENEMY_BOSS_POISONED_RIGHT, "textures/ENEMY_BOSS_POISONED_RIGHT.png");
	load(ENEMY_BOSS_POISONED_LEFT, "textures/ENEMY_BOSS_POISONED_LEFT.png");
	load(ENEMY_BOSS_POISONED_DOWN, "textures/ENEMY_BOSS_POISONED_DOWN.png");
	load(ENEMY_BOSS_POISONED_UP, "textures/ENEMY_BOSS_POISONED_UP.png");
	load(ENEMY_BOSS_FREEZED_POISONED_RIGHT, "textures/ENEMY_BOSS_FREEZED_POISONED_RIGHT.png");
	load(ENEMY_BOSS_FREEZED_POISONED_LEFT, "textures/ENEMY_BOSS_FREEZED_POISONED_LEFT.png");
	load(ENEMY_BOSS_FREEZED_POISONED_DOWN, "textures/ENEMY_BOSS_FREEZED_POISONED_DOWN.png");
	load(ENEMY_BOSS_FREEZED_POISONED_UP, "textures/ENEMY_BOSS_FREEZED_POISONED_UP.png");

	load(POWERUP_SLOW, "textures/POWERUP_SLOW.png");
	load(POWERUP_EXPLOSION, "textures/POWERUP_EXPLOSION.png");
	load(POWERUP_FREEZE, "textures/POWERUP_FREEZE.png");
	load(POWERUP_EXPLOSION_COOLDOWN, "textures/POWERUP_EXPLOSION_COOLDOWN.png");
	load(POWERUP_FREEZE_COOLDOWN, "textures/POWERUP_FREEZE_COOLDOWN.png");
	load(POWERUP_SLOW_COOLDOWN, "textures/POWERUP_SLOW_COOLDOWN.png");

	load(GOLD, "textures/GOLD.png");
	load(HEART, "textures/HEART.png");

	load(BUTTON_LEFT, "textures/BUTTON_LEFT.png");
	load(BUTTON_RIGHT, "textures/BUTTON_RIGHT.png");
	load(BUTTON_UP, "textures/BUTTON_UP.png");
	load(BUTTON_DOWN, "textures/BUTTON_DOWN.png");
	load(BUTTON_PAUSE, "textures/BUTTON_PAUSE.png");
	load(BUTTON_RESUME, "textures/BUTTON_RESUME.png");
	load(PANEL, "textures/PANEL.png");

	load(BULLET_MG_1, "textures/BULLET_MG_1.png");
	load(BULLET_MG_2, "textures/BULLET_MG_2.png");
	load(BULLET_ROCKET_1, "textures/BULLET_ROCKET_1.png");
	load(BULLET_ROCKET_2, "textures/BULLET_ROCKET_2.png");
	load(BULLET_SLOW_1, "textures/BULLET_SLOW_1.png");
	load(BULLET_POISON_1, "textures/BULLET_POISON_1.png");

	load(UPGRADE_1, "textures/UPGRADE_1.png");
	load(UPGRADE_2, "textures/UPGRADE_2.png");
	load(UPGRADE_3, "textures/UPGRADE_3.png");
	load(SELL, "textures/SELL.png");

	load(BACKGROUND, "textures/BACKGROUND.png");
	load(BUTTON, "textures/BUTTON.png");
}