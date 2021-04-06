#pragma once
#include "enums.h"

class TextureHolder
{
public:
	TextureHolder()
	{
		load_all();
	}
	
	//loads texture from file
	void load(TEXTURES id, std::string filename);

	//returns texture object
	sf::Texture& get(const TEXTURES &id);

private:
	//map containing id - texture pair
	std::map<TEXTURES, std::unique_ptr<sf::Texture>> textureMap;

	void load_all();
	
};