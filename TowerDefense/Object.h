#pragma once
#include "enums.h"
#include "TextureHolder.h"

class Object : public sf::Drawable
{
public:
	static TextureHolder * textureMap;
	Object()
	{

	}
	Object(const TEXTURES &id, const sf::Vector2i _coordinates) 
		: coordinates(_coordinates),
		id(id)
	{
		set_texture(id);
		set_sprite(id);
	}

	//getters & setters
	void set_sprite(const TEXTURES &id);
	
	void set_texture(const TEXTURES &id);
	
	void set_coordinates(const sf::Vector2i _coordinates);
	
	void set_sprite_position(const sf::Vector2i _coordinates, const float size_x, const float size_y);
	
	sf::Sprite& get_sprite();
	
	sf::Sprite get_sprite() const;
	
	TEXTURES& get_id();
	
	TEXTURES get_id() const;
	
	const sf::Texture& get_texture() const;
	
	sf::Texture& get_texture();
	
	sf::Vector2i& get_coordinates();
	
	sf::Vector2i get_coordinates() const;

private:
	
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2i coordinates;
	TEXTURES id;

	virtual void Drawable::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(sprite);
	}
};