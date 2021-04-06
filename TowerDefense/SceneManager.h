#pragma once
#include "enums.h"
#include "TextureHolder.h"
#include "Object.h"
#include "Tile.h"
#include "Button.h"
#include "Player.h"
#include "TowerPanel.h"
#include "PowerPanel.h"
#include "Tower.h"
#include "Enemy.h"
#include "Bullet.h"

class SceneManager : public sf::Drawable
{
public:
	SceneManager();	//default constructor needed
	SceneManager(TextureHolder * textures)
		:textures(textures)
	{
		tile_map = std::vector<std::vector<std::shared_ptr<Tile>>>(20, std::vector<std::shared_ptr<Tile>>(20));
		std::string filename = "fonts/arial.ttf";
		if (!font.loadFromFile(filename))
		{
			throw std::runtime_error("failed to load font " + filename);	
		}
	}
	//game is paused
	bool paused = false;

	void load_level(int level);

	void set_dir();

	void update_texture_enemies();

	void update_text(sf::Time &cooldown_time);

	void update_towers();

	void update_powers(sf::Time &cooldown_time, sf::Time &power_time);

	void update_cursor(const sf::Event & evnt, sf::RenderWindow &Window);

	void process_click(const sf::Event & evnt, sf::RenderWindow &Window, sf::Time &cooldown_time,
		sf::Time &power_time);

	void handle_active_tower_click(sf::Vector2f translatedPos);

	void handle_turret_click(sf::Vector2f translatedPos);

	void handle_explosion_click(sf::Vector2f translatedPos);

	void handle_button_click(sf::Vector2f translatedPos);

	void handle_panel_click(sf::Vector2f translatedPos);

	void process_enemies(sf::RenderWindow &Window, sf::Time &spawn_time, sf::Time &wave_time,
		sf::Time &shoot_time, sf::Time &power_time, sf::Time &poison_time);
	
	void spawn(sf::Time &spawn_time, sf::Time &wave_time);

	void move(sf::Time &power_time, sf::Time &poison_time);

	int getLives();

	bool isfinished();

	int get_enemies();

private:
	TextureHolder * textures;	//pointer to object holding all of the textures
	std::vector<std::vector<std::shared_ptr<Tile>>> tile_map;	//game map, grass, sand, start/end tiles
	std::vector<std::shared_ptr<Tower>> towers;	//towers bought by player
	std::vector<Button> buttons;	//game speed, gold and health - fixed place
	std::vector<std::shared_ptr<Object>> panels;	//tower and power panel
	std::vector<std::shared_ptr<Power>> powers;
	std::vector<std::shared_ptr<Bullet>> bullets;
	std::vector<std::shared_ptr<Enemy>> enemies;
	
	//used for spawning enemies
	std::vector<TEXTURES> enemies_to_spawn;
	std::vector<int> enemies_per_wave;
	int spawn1 = 1;
	int current_enemy = 0;
	int enemy_to_spawn = 0;

	//used for moving enemies
	std::vector<DIRECTIONS> path;
	sf::Vector2i start_position_tile_map;
	sf::Vector2f start_position;
	sf::Vector2f end_position;

	sf::Time wave_time;
	sf::Time spawn_time;

	//bools for powers and wave handling
	bool level_started = false;
	bool next_wave = false;
	bool waves_finished = false;
	bool freeze_used = false;
	bool slow_used = false;
	bool explosion_used = false;
	
	Player player;
	sf::Font font;

	//used for handling clicking
	TEXTURES id = NONE;
	//explosion circle
	sf::CircleShape explosion_circle;

	bool load_level(std::string &filename);
	
	/*draws all objects in a scene*/
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		//tiles
		for (int row = 0; row < 20; row++)
		{
			for (int col = 0; col < 20; col++)
			{
				target.draw(*(tile_map[row][col]));
			}
		}
		for (auto const& value : towers)
			target.draw(*value);
		for (auto const& value : enemies)
			target.draw(*value);
		for (auto const& value : bullets)
			target.draw(*value);
		for (auto const& value : panels)
			target.draw(*value);
		for (auto const& value : buttons)
			target.draw(value);
		if (player.power_pressed && player.id_pressed == POWERUP_EXPLOSION)
			target.draw(explosion_circle);
		target.draw(player);	//text
	}
};