#include "Object.h"

TextureHolder * Object::textureMap = nullptr;

/*sets texture sprite and its id*/
void Object::set_sprite(const TEXTURES & id)
{
	sprite.setTexture(textureMap->get(id));
	this->id = id;
}

/*holds texture*/
void Object::set_texture(const TEXTURES & id)
{
	texture = textureMap->get(id);
	this->id = id;
}

/*sets coordinates in tile_map vector array*/
void Object::set_coordinates(const sf::Vector2i _coordinates)
{
	coordinates = _coordinates;
}

/*sets position of a sprite and scale*/
void Object::set_sprite_position(const sf::Vector2i _coordinates, const float size_x, const float size_y)
{
	sprite.setPosition(_coordinates.x*size_x, _coordinates.y*size_y);
	sprite.setScale(size_x / 64., size_y / 64.);
}

/*gets sprite object*/
sf::Sprite & Object::get_sprite()
{
	return sprite;
}

sf::Sprite Object::get_sprite() const
{
	return sprite;
}

/*gets id of an object*/
TEXTURES & Object::get_id()
{
	return id;
}

TEXTURES Object::get_id() const
{
	return id;
}

/*gets texture object*/
const sf::Texture & Object::get_texture() const
{
	return texture;
}

sf::Texture & Object::get_texture()
{
	return texture;
}

/*gets coordinates in tile_map*/
sf::Vector2i & Object::get_coordinates()
{
	return coordinates;
}

sf::Vector2i Object::get_coordinates() const
{
	return coordinates;
}