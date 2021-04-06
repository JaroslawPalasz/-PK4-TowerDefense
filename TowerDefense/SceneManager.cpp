#include "SceneManager.h"

/*loads appropriate level*/
void SceneManager::load_level(int level)
{
	std::string s_level = "levels/";
	int waves = 0;
	int money = 0;
	switch (level)
	{
	case(0):
		s_level += "testing.txt";
		waves = 4;
		money = 3000;
		enemies_to_spawn = { ENEMY_BOSS, ENEMY_HEAVY, ENEMY_FAST, ENEMY_BOSS, ENEMY_BOSS, ENEMY_HEAVY,
	ENEMY_BOSS ,ENEMY_FAST, ENEMY_BOSS, ENEMY_BOSS, ENEMY_BOSS, ENEMY_BOSS, ENEMY_BOSS, ENEMY_BOSS };
		enemies_per_wave = { 4, 4, 5, 1 };
		path = { RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, DOWN, DOWN, LEFT, LEFT, LEFT, LEFT,
	DOWN, DOWN, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT };
		break;
	case(1):
		s_level += "level1.txt";
		waves = 4;
		money = 400;
		enemies_to_spawn = { ENEMY_FAST, ENEMY_FAST, ENEMY_HEAVY, ENEMY_FAST, ENEMY_FAST, ENEMY_HEAVY,
	ENEMY_HEAVY ,ENEMY_FAST, ENEMY_FAST, ENEMY_FAST, ENEMY_HEAVY, ENEMY_HEAVY, ENEMY_HEAVY, ENEMY_BOSS, ENEMY_FAST, ENEMY_FAST, ENEMY_HEAVY, ENEMY_BOSS,
		ENEMY_BOSS, ENEMY_BOSS, ENEMY_FAST, ENEMY_FAST, ENEMY_HEAVY, ENEMY_HEAVY, ENEMY_BOSS, ENEMY_BOSS, ENEMY_BOSS, ENEMY_FAST, ENEMY_HEAVY, ENEMY_HEAVY };
		enemies_per_wave = { 5, 5, 7, 13 };
		path = { UP, UP, RIGHT, UP, UP, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, DOWN, DOWN, DOWN,
	RIGHT, RIGHT, UP, UP, UP, UP, UP, LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, UP, UP, UP, UP, UP, RIGHT, RIGHT, RIGHT, RIGHT,
		DOWN, DOWN, DOWN, RIGHT, RIGHT, RIGHT, RIGHT, UP, UP, UP, UP, RIGHT, RIGHT, RIGHT };
		break;
	case(2):
		s_level += "level2.txt";
		waves = 6;
		money = 750;
		enemies_to_spawn = { ENEMY_HEAVY, ENEMY_HEAVY, ENEMY_HEAVY, ENEMY_FAST, ENEMY_FAST, ENEMY_FAST, ENEMY_FAST, ENEMY_BOSS, ENEMY_BOSS, ENEMY_HEAVY,
	ENEMY_BOSS, ENEMY_FAST, ENEMY_HEAVY, ENEMY_HEAVY, ENEMY_FAST, ENEMY_FAST, ENEMY_FAST, ENEMY_BOSS, ENEMY_BOSS, ENEMY_BOSS, ENEMY_BOSS, ENEMY_BOSS, 
			ENEMY_BOSS, ENEMY_BOSS, ENEMY_HEAVY, ENEMY_HEAVY, ENEMY_FAST, ENEMY_FAST, ENEMY_BOSS, ENEMY_BOSS, ENEMY_FAST, ENEMY_FAST, ENEMY_HEAVY,
		ENEMY_HEAVY, ENEMY_BOSS, ENEMY_BOSS, ENEMY_HEAVY, ENEMY_FAST, ENEMY_FAST, ENEMY_BOSS };
		enemies_per_wave = { 4, 6, 5, 5, 8, 12 };
		path = { LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, DOWN, DOWN, DOWN, DOWN, DOWN, DOWN,
		RIGHT, RIGHT, UP, UP, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, DOWN, RIGHT, RIGHT, UP, RIGHT, RIGHT, RIGHT, RIGHT };
		break;
	}
	load_level(s_level);
	player = Player(20, money, waves, textures, font);
	set_dir();
}

/*assigns direction to passable tiles in livel, starting from start to end tile*/
void SceneManager::set_dir()
{
	int i = 0;
	int x = start_position_tile_map.x;
	int y = start_position_tile_map.y;
	tile_map[x][y]->dir = path[i];

	while (i < path.size())
	{
		switch (tile_map[x][y]->dir)
		{
		case(UP):
			y--;
			break;
		case(DOWN):
			y++;
			break;
		case(LEFT):
			x--;
			break;
		case(RIGHT):
			x++;
			break;
		}
		tile_map[x][y]->dir = path[i];
		i++;
	}
}

/*updates texture of each enemy*/
void SceneManager::update_texture_enemies()
{
	for (auto const& value : enemies)
	{
		value->update(path);
	}
}

/*updating amount of lives, gold, cooldowns of powerups and text in tower panel*/
void SceneManager::update_text(sf::Time & cooldown_time)
{
	player.update_text(panels, cooldown_time, powers, paused, towers, explosion_used, freeze_used, slow_used);
}

/*removes towers from vector if sold*/
void SceneManager::update_towers()
{
	auto i = towers.begin();
	while (i != towers.end())
	{
		if ((*i)->sold)
		{
			i = towers.erase(i);
		}
		else
		{
			if (i != towers.end())
				++i;
		}
	}
}

/*handles time of powers, calls method updating its textures*/
void SceneManager::update_powers(sf::Time & cooldown_time, sf::Time & power_time)
{
	if (freeze_used || slow_used || explosion_used)
	{
		for (auto const& value : powers)
		{
			if (value->cooldown.asSeconds() > value->cooldown_seconds)
			{
				switch (value->get_id())
				{
				case(POWERUP_EXPLOSION):
					explosion_used = false;
					break;
				case(POWERUP_FREEZE):
					freeze_used = false;
					break;
				case(POWERUP_SLOW):
					slow_used = false;
					break;
				}
				std::cout << "not on cooldown " << value->get_id() << std::endl;
				value->on_cooldown = false;
				value->cooldown = sf::Time();
			}
			else
			{
				if (explosion_used && value->get_id() == POWERUP_EXPLOSION)
					value->on_cooldown = true;
				if (freeze_used && value->get_id() == POWERUP_FREEZE)
					value->on_cooldown = true;
				if (slow_used && value->get_id() == POWERUP_SLOW)
					value->on_cooldown = true;
				value->cooldown += cooldown_time;
			}
		}
	}
	//updating powerpanel textures
	if (std::shared_ptr<PowerPanel> powerpanel = std::dynamic_pointer_cast<PowerPanel>(panels[1]))
	{
		if (powerpanel->can_draw)
		{
			powerpanel->update(true, explosion_used, slow_used, freeze_used);
		}
	}
}

/*sets explosion circle coordinates if power is selected*/
void SceneManager::update_cursor(const sf::Event & evnt, sf::RenderWindow & Window)
{
	if (player.power_pressed && player.id_pressed == POWERUP_EXPLOSION)
	{
		auto mousePos = sf::Mouse::getPosition(Window);	//Vector2i
		auto translatedPos = Window.mapPixelToCoords(mousePos);	//Vector2f

		explosion_circle.setOrigin(explosion_circle.getRadius(), explosion_circle.getRadius());
		explosion_circle.setPosition(translatedPos);
	}
}

/*handles mouse clicking by calling different methods depending on what object was clicked*/
void SceneManager::process_click(const sf::Event & evnt, sf::RenderWindow & Window, sf::Time & cooldown_time, sf::Time & power_time)
{
	auto mousePos = sf::Mouse::getPosition(Window);	//Vector2i
	auto translatedPos = Window.mapPixelToCoords(mousePos);	//Vector2f

	//cancelling buying tower or using powerup explosion
	if ((evnt.type == sf::Event::MouseButtonPressed) && (evnt.key.code == sf::Mouse::Right))
		if (player.is_pressed)
		{
			player.id_pressed = NONE;
			player.is_pressed = false;
		}
	if ((evnt.type == sf::Event::MouseButtonPressed) && (evnt.key.code == sf::Mouse::Left))
	{
		handle_active_tower_click(translatedPos);
		
		if (player.is_pressed)
		{
			//**************************************TURRET_PRESSEd**************************************
			handle_turret_click(translatedPos);
			//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^TURRET_PRESSEd^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


			//**************************************EXPLOSION_PRESSED**************************************
			handle_explosion_click(translatedPos);
			//**************************************EXPLOSION_PRESSED**************************************
		}

		//**************************************BUTTONS**************************************
		handle_button_click(translatedPos);
		//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^BUTTONS^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


		//**************************************PANELS**************************************
		handle_panel_click(translatedPos);
		//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^PANELS^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

		switch (id)
		{
		case(TOWER_MG_1):
		case(TOWER_POISON_1):
		case(TOWER_ROCKET_1):
		case(TOWER_SLOW_1):
			player.turret_pressed = true;
			player.id_pressed = id;
			player.is_pressed = true;
			std::cout << "player pressed - turret " << player.id_pressed << std::endl;
			break;
		case(POWERUP_EXPLOSION):
			player.power_pressed = true;
			player.id_pressed = id;
			player.is_pressed = true;
			std::cout << "player pressed - power " << player.id_pressed << std::endl;

			break;
		case(POWERUP_FREEZE):
		case(POWERUP_SLOW):
			for (auto const& value : powers)
			{
				if (value->get_id() == id)
				{
					std::cout << "player pressed - power " << id << std::endl;
					std::cout << "cooldown started " << id << std::endl;
					value->cooldown = sf::Time();
					if (id == POWERUP_FREEZE)
					{
						for (auto const& value : enemies)
						{
							value->is_frozen = true;
						}
						freeze_used = true;
					}
					else if (id == POWERUP_SLOW)
					{
						for (auto const& value : enemies)
						{
							value->is_slowed = true;
						}
						slow_used = true;
					}
				}
			}
			break;
		}
	}
}

/*handles event when tower which was already built is clicked - upgrading, selling, showing range*/
void SceneManager::handle_active_tower_click(sf::Vector2f translatedPos)
{
	if (player.id_pressed == NONE)
	{
		for (auto const& value : towers)
		{
			if (value->get_sprite().getGlobalBounds().contains(translatedPos))
			{
				if (value->is_pressed)
				{
					//only upgrade button clicked
					if (value->upgrade_to_level.getGlobalBounds().contains(translatedPos) &&
						!value->sell.getGlobalBounds().contains(translatedPos))
					{
						if (player.money >= value->upgrade_cost)
						{
							//check levels for different towers
							if (value->can_upgrade())
							{
								//update money
								std::cout << "upgrade" << std::endl;
								std::cout << "before buying " << player.money << std::endl;
								player.update_money(value->upgrade_cost, true);
								value->upgrade_tower();
								std::cout << "after buying " << player.money << std::endl;
							}
						}
					}
					//only sell button clicked
					else if (value->sell.getGlobalBounds().contains(translatedPos) &&
						!value->upgrade_to_level.getGlobalBounds().contains(translatedPos))
					{
						//sold = yes, update
						value->sold = true;
						std::cout << "sell" << std::endl;
						std::cout << "before selling " << player.money << std::endl;
						player.update_money(value->value, false);
						std::cout << "after selling " << player.money << std::endl;
					}
					//click tower again to cancel
					else
					{
						value->is_pressed = false;
					}
				}
				//tower is not pressed
				else
				{
					value->is_pressed = true;
				}
			}
		}
	}
}

/*handles placing tower on map, checks if can be placed - player has enough money and checks if a tile is buildable*/
void SceneManager::handle_turret_click(sf::Vector2f translatedPos)
{
	if (player.id_pressed == TOWER_MG_1 || player.id_pressed == TOWER_POISON_1 ||
		player.id_pressed == TOWER_ROCKET_1 || player.id_pressed == TOWER_SLOW_1)
	{
		for (int row = 0; row < 20; row++)
		{
			for (int col = 0; col < 20; col++)
			{
				if ((tile_map[row][col]->get_sprite().getGlobalBounds().contains(translatedPos)) &&
					(tile_map[row][col]->get_id() == TILE_BUILD_GRASS ||
						tile_map[row][col]->get_id() == TILE_BUILD_SAND))
				{
					//can or cant buy
					bool tower_already_placed = false;
					for (auto const& value : towers)
					{
						if (value->get_coordinates() == sf::Vector2i(row, col))
						{
							tower_already_placed = true;
							break;
						}
					}
					//check money
					if (!tower_already_placed)
					{
						//checking buy cost
						int buy_cost;
						switch (player.id_pressed)
						{
						case(TOWER_MG_1):
							buy_cost = 200;
							break;
						case(TOWER_POISON_1):
							buy_cost = 260;
							break;
						case(TOWER_ROCKET_1):
							buy_cost = 300;
							break;
						case(TOWER_SLOW_1):
							buy_cost = 150;
							break;
						}
						if (player.money < buy_cost)
						{
							player.is_pressed = false;
							player.id_pressed = NONE;
							player.turret_pressed = false;
						}
						else
						{
							towers.push_back(std::make_shared<Tower>(player.id_pressed,
								sf::Vector2i(row, col), false));
							std::cout << "Tower built" << std::endl;
							for (auto const& value : towers)
							{
								if (value->get_coordinates() == sf::Vector2i(row, col))
								{
									player.update_money(value->upgrade_cost, true);
									break;
								}
							}
							player.is_pressed = false;
							player.id_pressed = NONE;
							player.turret_pressed = false;
						}
					}
				}
			}
		}
	}
}

/*handles using explosion powerup - hits enemies in radius, resets cooldown*/
void SceneManager::handle_explosion_click(sf::Vector2f translatedPos)
{
	if (player.id_pressed == POWERUP_EXPLOSION)
	{
		bool can_use = true;
		for (size_t i = 0; i < buttons.size(); i++)
		{
			if (buttons[i].get_sprite().getGlobalBounds().contains(translatedPos))
			{
				std::cout << buttons[i].get_id() << std::endl;
				can_use = false;
			}
		}
		if (can_use)
		{
			explosion_used = true;
			for (auto const& value : powers)
			{
				if (value->get_id() == player.id_pressed)
				{
					value->cooldown = sf::Time();
				}
			}
			//TODO: range following mouse, cooldown
			for (auto const& value : enemies)
			{
				if (explosion_circle.getGlobalBounds().intersects(value->circle.getGlobalBounds()))
				{
					value->hitpoints -= 6.;
				}
			}
			std::cout << "Boom" << std::endl;
			std::cout << "cooldown started " << player.id_pressed << std::endl;
			player.id_pressed = NONE;
			player.is_pressed = false;
			player.power_pressed = false;
		}
	}
}

/*checks if a button (right, left, up, down and pause/resume) is pressed and sets appropriate bools*/
void SceneManager::handle_button_click(sf::Vector2f translatedPos)
{
	for (size_t i = 0; i < buttons.size(); i++)
	{
		if (buttons[i].get_sprite().getGlobalBounds().contains(translatedPos))
		{
			switch (buttons[i].get_id())
			{
				//panel buttons
			case BUTTON_LEFT:
				buttons[i].set_sprite(BUTTON_RIGHT);
				std::cout << "show towers" << std::endl;
				if (std::shared_ptr<TowerPanel> towerpanel = std::dynamic_pointer_cast<TowerPanel>(panels[0]))
				{
					towerpanel->can_draw = true;
					towerpanel->update(true);
				}
				break;
			case BUTTON_RIGHT:
				buttons[i].set_sprite(BUTTON_LEFT);
				std::cout << "hide towers" << std::endl;
				if (std::shared_ptr<TowerPanel> towerpanel = std::dynamic_pointer_cast<TowerPanel>(panels[0]))
				{
					towerpanel->can_draw = false;
					towerpanel->update(false);
				}
				break;
			case BUTTON_UP:
				buttons[i].set_sprite(BUTTON_DOWN);
				std::cout << "show powers" << std::endl;
				if (std::shared_ptr<PowerPanel> powerpanel = std::dynamic_pointer_cast<PowerPanel>(panels[1]))
				{
					powerpanel->can_draw = true;
					powerpanel->update(true, explosion_used, slow_used, freeze_used);
				}
				break;
			case BUTTON_DOWN:
				buttons[i].set_sprite(BUTTON_UP);
				std::cout << "hide powers" << std::endl;
				if (std::shared_ptr<PowerPanel> powerpanel = std::dynamic_pointer_cast<PowerPanel>(panels[1]))
				{
					powerpanel->can_draw = false;
					powerpanel->update(false, explosion_used, slow_used, freeze_used);
				}
				break;
				//pressing for the first time - spawning enemies (start level)
			case BUTTON_RESUME:
				if (!level_started)
					level_started = true;
				else if (paused)
				{
					paused = false;
					std::cout << "game resumed" << std::endl;
				}
				break;
				//pause game - can still click, enemies dont move, towers dont shoot, clock does not count time
			case BUTTON_PAUSE:
				std::cout << "game paused" << std::endl;
				paused = true;
				break;
			default:	//heart, gold - nothing happens
				if (buttons[i].is_pressed)
					buttons[i].is_pressed = false;
				else
					buttons[i].is_pressed = true;
				break;
			}
		}
	}
}

/*handles clicking object from tower or panel panel*/
void SceneManager::handle_panel_click(sf::Vector2f translatedPos)
{
	id = NONE;
	for (size_t i = 0; i < panels.size(); i++)
	{
		//check towers to buy
		if (std::shared_ptr<TowerPanel> towerpanel = std::dynamic_pointer_cast<TowerPanel>(panels[i]))
		{
			for (auto const& value : towerpanel->towers)
			{
				value->is_pressed = false;
				if (value->get_sprite().getGlobalBounds().contains(translatedPos))
				{
					id = value->get_id();
					value->is_pressed = true;
					std::cout << value->get_id() << " clicked" << std::endl;
				}
			}

		}
		//check powerups
		if (std::shared_ptr<PowerPanel> powerpanel = std::dynamic_pointer_cast<PowerPanel>(panels[i]))
		{
			for (auto const& value : powerpanel->powers)
			{
				//value->is_drawable = false;
				if (value->get_sprite().getGlobalBounds().contains(translatedPos))
				{
					//value->is_drawable = true;
					id = value->get_id();
					std::cout << value->get_id() << " clicked" << std::endl;
				}
			}
		}
	}
}

/*calls method responsible for spawning, moving of enemies and bullets, erases entities from vector if conditions are met*/
void SceneManager::process_enemies(sf::RenderWindow & Window, sf::Time & spawn_time, sf::Time & wave_time, sf::Time & shoot_time, sf::Time & power_time, sf::Time & poison_time)
{
	spawn(spawn_time, wave_time);
	move(power_time, poison_time);

	//shoot - spawn bullets
	for (auto const& value : towers)
	{
		value->shoot(enemies, bullets, end_position, shoot_time);
	}
	//move bullets
	for (auto const& value : bullets)
	{
		value->shoot(enemies);
	}
	//update enemies
	auto i = enemies.begin();
	while (i != enemies.end())
	{
		if ((*i)->end == true)
		{
			player.lives -= (*i)->damage;
		}
		if ((*i)->hitpoints <= 0)
		{
			int money = 0;
			switch ((*i)->type)
			{
			case(ENEMY_FAST):
				money = 100;
				break;
			case(ENEMY_HEAVY):
				money = 150;
				break;
			case(ENEMY_BOSS):
				money = 300;
				break;
			}
			player.update_money(money, false);
		}
		if ((*i)->is_alive == false || (*i)->hitpoints <= 0)
		{
			i = enemies.erase(i);
		}
		else
		{
			if (i != enemies.end())
				++i;
		}
	}
	//update bullets
	auto j = bullets.begin();
	while (j != bullets.end())
	{
		if ((*j)->hit_target)
		{
			j = bullets.erase(j);
		}
		else
		{
			++j;
		}
	}
}

/*spawns enemies in waves in certain time intervals*/
void SceneManager::spawn(sf::Time & spawn_time, sf::Time & wave_time)
{
	if (level_started)
	{
		//spawn first enemy
		if (this->spawn1 == 1)
		{
			enemies.push_back(std::make_shared<Enemy>(enemies_to_spawn[0], start_position_tile_map, start_position));
			player.waves.x = 0;	//current wave
			current_enemy = 1;
			enemy_to_spawn = 1;
			spawn1++;

			this->spawn_time = sf::Time();
		}
		else
			this->spawn_time += spawn_time;

		//good
		if (next_wave)
		{
			//new wave each 3 seconds
			if (this->wave_time.asSeconds() > 3)
			{
				std::cout << "New wave " << this->wave_time.asSeconds() << std::endl;
				next_wave = false;
				this->wave_time = sf::Time();
			}
			else
			{
				this->wave_time += wave_time;
			}
		}
		else if (this->spawn_time.asSeconds() > 1.5)
		{
			//spawn enemy each 1.5 s
			if (player.waves.x < player.waves.y)
			{
				if (current_enemy < enemies_per_wave[player.waves.x])
				{
					enemies.push_back(std::make_shared<Enemy>(enemies_to_spawn[enemy_to_spawn],
						start_position_tile_map, start_position));
					current_enemy++;
					enemy_to_spawn++;
					std::cout << "New enemy" << this->spawn_time.asSeconds() << std::endl;
					this->spawn_time = sf::Time();
				}
				else
				{
					//wave clock reset
					this->wave_time = sf::Time();
					next_wave = true;
					current_enemy = 0;
					player.waves.x++;
				}
			}
			else
				waves_finished = true;
		}
		else if (this->spawn_time.asSeconds() <= 1.5)
		{
			this->spawn_time += spawn_time;
		}
	}
}

/*moves each enemy by checking if its circleshape collides with that of a tile, sets the direction of an enemy
also slows, freezes and poisons enemy if it has that condition*/
void SceneManager::move(sf::Time & power_time, sf::Time & poison_time)
{
	for (auto const& value : enemies)
	{
		std::vector< std::vector<std::shared_ptr<Tile>> >::const_iterator row;
		std::vector< std::shared_ptr<Tile>>::const_iterator col;
		sf::FloatRect intersects;
		sf::Vector2i on_map;
		int i = 0;
		bool to_break = false;
		float movement_bonus;
		DIRECTIONS prev_dir;
		DIRECTIONS dir;

		if (value->it_path < path.size())
		{
			dir = path[value->it_path];
		}
		if (value->it_path == 0)
		{
			value->coordinates = sf::Vector2i(start_position_tile_map.x, start_position_tile_map.y);
			movement_bonus = tile_map[start_position_tile_map.x][start_position_tile_map.y]->movement_bonus;
		}
		for (row = tile_map.begin(); row != tile_map.end(), to_break != true; ++row)
		{
			for (col = row->begin(); col != row->end(); ++col)
			{
				//center of tile - change direction, sprite
				if (value->circle.getGlobalBounds().intersects((*col)->circle.getGlobalBounds())
					&& value->coordinates != (*col)->get_coordinates() && (*col)->is_passable)
				{
					if (value->it_path != 0)
					{

						dir = path[value->it_path];

					}
					value->coordinates = (*col)->get_coordinates();
					value->it_path++;
					movement_bonus = (*col)->movement_bonus;

					to_break = true;
					break;
				}
				if (value->circle.getGlobalBounds().intersects((*col)->get_sprite().getGlobalBounds()))
				{
					if ((*col)->get_id() == TILE_END)
					{
						value->is_alive = false;
						value->end = true;
					}

					intersects = (*col)->get_sprite().getGlobalBounds();
					on_map = (*col)->get_coordinates();
					to_break = true;
					movement_bonus = (*col)->movement_bonus;
					break;
				}
			}
		}

		//checks if enemy is slowed, frozen, poisoned
		if (value->is_alive)
		{
			float frozen = 1.f;
			float slowed = 0.f;
			if (value->is_frozen)
			{
				frozen = 0;
				if (value->freeze_time.asSeconds() > 4)
				{
					value->freeze_time = sf::Time();
					frozen = 1.f;
					value->is_frozen = false;
				}
				else
				{
					value->freeze_time += power_time;
				}
			}
			if (value->is_slowed)
			{
				slowed = 0.3f;
				if (value->slow_time.asSeconds() > 4)
				{
					value->slow_time = sf::Time();
					slowed = 0.f;
					value->is_slowed = false;
				}
				else
				{
					value->slow_time += power_time;
				}
			}
			if (value->is_poisoned)
			{
				//poison duration
				if (value->poison_time.asSeconds() > 3)
				{
					value->poison_time = sf::Time();
					value->poison_each_second = sf::Time();
					value->is_poisoned = false;
				}
				else
				{
					value->poison_time += power_time;
					if (value->poison_each_second.asSeconds() > 1)
					{
						value->poison_each_second = sf::Time();
						value->hitpoints -= 1;
					}
					else
					{
						value->poison_each_second += poison_time;
					}
				}
			}

			sf::Vector2f movement(0.f, 0.f);
			switch (dir)
			{
			case(RIGHT):
				movement.x += ((value->speed*movement_bonus - slowed)*frozen);
				break;
			case(LEFT):
				movement.x -= ((value->speed*movement_bonus - slowed)*frozen);
				break;
			case(DOWN):
				movement.y += ((value->speed*movement_bonus - slowed)*frozen);
				break;
			case(UP):
				movement.y -= ((value->speed*movement_bonus - slowed)*frozen);
				break;
			}
			value->circle.move(movement);
			value->get_sprite().move(movement);
		}
	}
}

/*returns lives*/
int SceneManager::getLives()
{
	return player.lives;
}

/*checks if all waves are finished*/
bool SceneManager::isfinished()
{
	return waves_finished;
}

/*checks number of enemies alive*/
int SceneManager::get_enemies()
{
	return enemies.size();
}

/*loads level from file and prepares whole scene*/
bool SceneManager::load_level(std::string & filename)
{
	std::ifstream level(filename);
	if (!level || !level.is_open())
	{
		std::cout << "Error loading file." << std::endl;
		return false;
	}
	std::string tile_type = "";
	TEXTURES texture_type;
	sf::Vector2i tile_position;
	bool is_passable = false;
	double movement_bonus = 0;
	while (!level.eof())
	{
		is_passable = false;
		movement_bonus = 0;
		level >> tile_type;
		if (tile_type == "g")
			texture_type = TILE_GRASS;
		if (tile_type == "s")
			texture_type = TILE_SAND;
		if (tile_type == "bg")
			texture_type = TILE_BUILD_GRASS;
		if (tile_type == "bs")
			texture_type = TILE_BUILD_SAND;

		if (tile_type == "st")
		{
			texture_type = TILE_START;
			start_position_tile_map = sf::Vector2i(tile_position);
			movement_bonus = 1;
			is_passable = true;
		}
		if (tile_type == "e")
		{
			texture_type = TILE_END;
			movement_bonus = 1;
			is_passable = true;
		}
		if (tile_type == "m")
		{
			texture_type = TILE_MUD;
			is_passable = true;
			movement_bonus = 0.5;
		}
		if (tile_type == "r")
		{
			texture_type = TILE_ROAD;
			is_passable = true;
			movement_bonus = 1.25;
		}

		std::shared_ptr<Tile> tile(new Tile(texture_type, tile_position, is_passable, movement_bonus));
		tile_map[tile_position.x][tile_position.y] = tile;
		if (tile_type == "st")
		{
			start_position = sf::Vector2f(tile_map[tile_position.x][tile_position.y]->
				get_sprite().getPosition());
		}
		if (tile_type == "e")
		{
			end_position = sf::Vector2f(tile_map[tile_position.x][tile_position.y]->
				get_sprite().getPosition());
		}

		tile_position.x++;
		if (level.peek() == '\n')
		{
			tile_position.x = 0;
			tile_position.y++;
		}
	}

	//buttons
	buttons.push_back(Button(BUTTON_LEFT, sf::Vector2i(19, 2)));
	buttons.push_back(Button(BUTTON_UP, sf::Vector2i(3, 19)));

	buttons.push_back(Button(BUTTON_RESUME, sf::Vector2i(18, 0)));
	buttons.push_back(Button(BUTTON_PAUSE, sf::Vector2i(16, 0)));

	//panels
	panels.push_back(std::make_shared<TowerPanel>(PANEL, sf::Vector2i(15, 2)));		//0
	panels.push_back(std::make_shared<PowerPanel>(PANEL, sf::Vector2i(3, 15)));		//1

	//powers
	powers.push_back(std::make_shared<Power>(POWERUP_EXPLOSION));
	powers.push_back(std::make_shared<Power>(POWERUP_FREEZE));
	powers.push_back(std::make_shared<Power>(POWERUP_SLOW));

	//sets explosion circle
	explosion_circle.setRadius(100);
	explosion_circle.setOutlineColor(sf::Color::Red);
	explosion_circle.setOutlineThickness(1);
	explosion_circle.setFillColor(sf::Color::Transparent);
}