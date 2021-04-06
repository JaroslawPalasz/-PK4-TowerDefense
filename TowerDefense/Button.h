#pragma once
#include "Object.h"

class Button : public Object
{
public:
	Button(const TEXTURES &id, const sf::Vector2i _coordinates)
		: Object(id, _coordinates)
	{
		set_sprite_position(_coordinates, button_size, button_size);
	}

	const float button_size = 54.;
	bool is_pressed = false;
	
private:
	virtual void Drawable::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(get_sprite());
	}

};
