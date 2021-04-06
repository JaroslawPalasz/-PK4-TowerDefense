#include "TowerPanel.h"

/*if button is clicked, creates or destroys vector of towers to buy*/
void TowerPanel::update(bool create)
{
	//create vector of towers
	if (create)
	{
		towers = { std::make_shared<Tower>(TOWER_MG_1, sf::Vector2i(16, 3), true),
	std::make_shared<Tower>(TOWER_ROCKET_1, sf::Vector2i(16, 5), true),
	std::make_shared<Tower>(TOWER_SLOW_1, sf::Vector2i(16, 7), true),
	std::make_shared<Tower>(TOWER_POISON_1, sf::Vector2i(16, 9), true) };
	}
	//destroy it
	else
	{
		auto i = towers.begin();
		while (i != towers.end())
		{
			i = towers.erase(i);
			if (i != towers.end())
				++i;
		}
	}
}