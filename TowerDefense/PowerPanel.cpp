#include "PowerPanel.h"

/*creates vector of powers to use or destroys it*/
void PowerPanel::update(bool create, bool explosion_used, bool slow_used, bool freeze_used)
{
	//create vector of powers
	if (create)
	{
		powers = { std::make_shared<Power>(POWERUP_EXPLOSION, sf::Vector2i(5, 16)),
		std::make_shared<Power>(POWERUP_FREEZE, sf::Vector2i(7, 16)),
		std::make_shared<Power>(POWERUP_SLOW, sf::Vector2i(9, 16)) };
		if (explosion_used)
		{
			powers[0] = std::make_shared<Power>(POWERUP_EXPLOSION_COOLDOWN, sf::Vector2i(5, 16));
		}
		if (freeze_used)
		{
			powers[1] = std::make_shared<Power>(POWERUP_FREEZE_COOLDOWN, sf::Vector2i(7, 16));
		}
		if (slow_used)
		{
			powers[2] = std::make_shared<Power>(POWERUP_SLOW_COOLDOWN, sf::Vector2i(9, 16));
		}
	}
	//destroy it
	else
	{
		auto i = powers.begin();
		while (i != powers.end())
		{
			i = powers.erase(i);
			if (i != powers.end())
				++i;
		}
	}
}