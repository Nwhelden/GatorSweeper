#include "SpriteManager.h"
using namespace std;

//need to redeclare static members
unordered_map<string, sf::Sprite> SpriteManager::sprites;

//used to store Texture objects used to make sprites
//we need to store Textures, because if a texture a sprite uses falls out of scope, the sprite will draw a white box
unordered_map<string, sf::Texture> SpriteManager::textures;

/*
void SpriteManager::LoadTexture(const char* fileName) {

	//ex: pass in "ship.png"
	string filePath = "images/"; //images/
	filePath += fileName; //images/ship
	filePath += ".png"; //images/ship.png

	//now that we have the path we can load it
	textures[fileName].loadFromFile(filePath);

	//texutre can be repeatedly tiled within a sprite (multiple sprites can use the same texture)
	textures[fileName].setRepeated(true);

}
*/

void SpriteManager::LoadSprite(const char* fileName) {

	//temporary Texture to load image then store it
	sf::Texture texture;

	//ex: pass in "ship.png"
	string filePath = "images/"; //images/
	filePath += fileName; //images/ship
	filePath += ".png"; //images/ship.png

	//now that we have the path we can create the texture
	texture.loadFromFile(filePath);

	//store the Texture to avoid white box problem (Texture used by SPrite object falls out of scope
	//if a sprite uses the same 
	textures.emplace(fileName, texture);

	//now that we have the texture we can convert it to a sprite and store it
	//fileName is the key, when we access map[key] it returns a reference to the value
	//if there is no entry with the specified key, it creates an entry with the key and pairs it with a default Sprite object, 
	//which we can set the value of with setTexture()
	//need to use textures[fileName], because that's stored, texture is in scope
	sprites[fileName].setTexture(textures[fileName]);

}

void SpriteManager::LoadSprites(const char* fileName, int parts, int offset, int x, int y, string partName) {

	sf::Texture texture;

	//texutre can be repeatedly tiled within a sprite (multiple sprites can use the same texture)
	//digits uses the same texture for all of the digit sprites
	texture.setRepeated(true);

	string filePath = "images/"; 
	filePath += fileName; 
	filePath += ".png"; 

	texture.loadFromFile(filePath);

	textures.emplace(fileName, texture);

	for (int i = 0; i < parts; i++) {

		//key is a string
		string counter = to_string(i);

		int offset = i * x;
		
		sprites[partName + counter].setTexture(textures[fileName]);
		sprites[partName + counter].setTextureRect(sf::IntRect(offset, 0, x, y));

	}

}

sf::Sprite& SpriteManager::GetSprite(string spriteKey) {

	//if this is true we couldn't find the Sprite (if find results with the end of the object, then the key didn't exist)
	//if the key doesn't exist, then we should load the Sprite so that it does exist
	/*
	if (sprites.find(spriteKey) == sprites.end()) {

		//now key does exist
		//bypasses the need to call LoadSprite (it's done automatically for us)
		LoadSprite(spriteKey);

	}
	*/

	//returns reference to particular Sprite object paired with the key spriteKey
	return sprites[spriteKey];

}

//when we clear the map, it will invoke the destructor of all of the Sprite objects as each one gets removed from the container
void SpriteManager::Clear() {

	sprites.clear();
	textures.clear();

}