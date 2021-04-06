#pragma once
#include "Object.h"

/*tile - buildable/not, passable/not, vanity tiles*/
class Tile : public Object
{
public:
	Tile(const TEXTURES &id, const sf::Vector2i _coordinates, bool _is_passable, float _movement_bonus)
		: Object(id, _coordinates)
	{
		is_passable = _is_passable;
		movement_bonus = _movement_bonus;
		set_sprite_position(_coordinates, tile_size, tile_size);

		circle.setRadius(1);
		circle.setOutlineColor(sf::Color::Red);
		circle.setOutlineThickness(1);
		circle.setPosition(get_sprite().getPosition().x + 54. / 2, get_sprite().getPosition().y + 54. / 2);
		circle.setOrigin(circle.getRadius(), circle.getRadius());
	}

	//circle for collision with enemies
	sf::CircleShape circle;
	const float tile_size = 54.;
	bool is_passable;
	bool is_selected = false;
	float movement_bonus;

	DIRECTIONS dir;

private:
	virtual void Drawable::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(get_sprite());
	}
};