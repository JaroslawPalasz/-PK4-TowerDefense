#pragma once

#include "Object.h"
#include "Button.h"
#include "enums.h"
#include "Power.h"

/*panel of powers to use*/
class PowerPanel : public Object
{
public:
	PowerPanel(const TEXTURES &id, const sf::Vector2i _coordinates)
		: Object(id, _coordinates)
	{

		set_sprite_position(_coordinates, panel_size, panel_size);
		get_sprite().setScale(10., 3.5);
	}
	const float panel_size = 54.;
	std::vector<std::shared_ptr<Power>> powers;
	bool can_draw = false;

	void update(bool create, bool explosion_used, bool slow_used, bool freeze_used);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if (can_draw)
		{
			//draw panel
			target.draw(get_sprite());
			for (auto const& value : powers)
				target.draw(*value);
		}
	}
};