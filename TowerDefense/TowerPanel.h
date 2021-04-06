#pragma once

#include "Object.h"
#include "Tower.h"
#include "enums.h"

/*panel of towers to buy*/
class TowerPanel : public Object
{
public:
	TowerPanel(const TEXTURES &id, const sf::Vector2i _coordinates)
		: Object(id, _coordinates)
	{
		set_sprite_position(_coordinates, panel_size, panel_size);
		get_sprite().setScale(4., 8.);
	}
	const float panel_size = 54.;
	std::vector<std::shared_ptr<Tower>> towers;
	bool can_draw = false;

	void update(bool create);
	
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if (can_draw)
		{
			//draw panel
			target.draw(get_sprite());
			//draw towers
			for (auto const& value : towers)
				target.draw(*value);
		}
	}
};