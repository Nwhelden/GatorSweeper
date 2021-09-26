#pragma once
#include <SFML/Graphics.hpp> //in order to use sf::Texture
#include <unordered_map>
#include <string>

//want to avoid using namespace std; in header files
using std::unordered_map;
using std::string;

//if we have static members that we want to access, or call functions without objects, the functions also need to be static
class SpriteManager
{

	static unordered_map<string, sf::Texture> textures;

	//unordered map used as a container, because we have an identifier/key, the name of the sprite, and a value the sprite object 
	//itself, where the order pairs are empalced does not matter
	static unordered_map<string, sf::Sprite> sprites;

public:

	//static void LoadTexture(const char* fileName);

	//loads a texture, makes it a sprite, then stores it in map
	static void LoadSprite(const char* fileName);

	static void LoadSprites(const char* fileName, int parts, int offset, int x, int y, string partName);

	//LoadSprite is a helper function for GetSprite, we just call GetSprite to fill map with Sprite objects and give a key to
	//retrieve a value after it's been filled
	static sf::Sprite& GetSprite(string textureKey);

	//clean up (clear all sprites from the unordered map)
	static void Clear();

};

