#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

//contains information about sprites on board
class Board
{

public:

	//contains information about sprites on tile
	struct Tile {

		//string or const char*??? 
		std::string key = "tile";
		int xPosition;
		int yPosition;
		int tileNum;
		int adjacentMines;
		bool isRevealed;
		bool hasNum;
		bool hasFlag;
		bool hasMine;

		//there can be up to 8 adjacent tiles
		//in constructor of Tile, add pointers to a Tile is the adjacency is valid
		//can't have a vector of references, because we need to initialzie references
		//want vector of pointers, because we want to access the actual Tile, not a copy stored
		std::vector<Tile*> tileP;

		//????? How does it have a copy? are the stored tiles not the actual tiles???

		void reveal();

	};

	int flagCounter;
	bool gameOver;
	bool victory;
	bool debugMode = false;
	bool test1Mode;
	bool test2Mode;
	bool test3Mode;

	//could store Tile objects in 1d array, but harder to find adjacent tiles
	Tile tiles[16][25]; //16 rows, 25 columns

	std::vector<Tile*> winTiles;
	std::vector<Tile*> bombTiles;

	Board();
	void setNumbers();
	void resetBoard();
	void newGame();
	void drawBoard(sf::RenderWindow& window);
	void loadBoard(const char* fileName);
	void victoryCheck();

};

