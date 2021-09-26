#include "Board.h"
#include "SpriteManager.h"
#include "Random.h"
#include <iostream>
#include <fstream>
using namespace std;

Board::Board() {

	//creates the Tile objects stored in the board
	//counter keeps track of the Tile number in the 2d array, from Tile 0 to Tile 399
	//need to keep track of Tile numbers, because Tiles objects in 2d array hold the boolean data for the Tile sprites stored in a 1d
	//array of size 400
	int counter = 0;
	for (int i = 0; i < 16; i++) {

		for (int j = 0; j < 25; j++) {

			//creates a tile, and appends the current number tile to the stored key (which by default, is tile)
			//need tile# as key, because a map of unrevealed_tile sprites uses tile1, tile2, ... as keys to the Sprite object
			//if i = 0 and j = 0, we have the 0th tile, i = 0 and j = 24 we have the 24th, i = 1 and j = 0 we have the 25th
			//stores the created tile into the 
			//Tile defaultTile;
			//defaultTile.key += to_string(counter);

			//as soon as you declared array, there are 400 Tile objects created, just need to modify them
			//don't need to use new to create the objects, as soon as you create the array, there'
			//2D array of pointers, store on stack
			//inidividual elements: tile pointers, use new for every single Tile (not necessary)
			tiles[i][j].key += to_string(counter);

			//assigns the tiles a number from 0 to 399 (gives 1d representation)
			tiles[i][j].tileNum = counter;

			//assigns the positions of the tile on the board (used for determining where to draw its sprite and any other sprites over it)
			//tiles and their components are 32 x 32 pixels 
			//tile position = current i (y-axis/rows) * 32 and current j (x-axis/columns) * 32
			tiles[i][j].xPosition = j * 32;
			tiles[i][j].yPosition = i * 32;

			//??
			//if you have a pointer to an object, you can change the values of that object, which changes what the pointer points to
			//can set the ad
			
			//sets the adjacencies of the Tile object in relation to 8 possible Tiles on the board
			//if i = 0, the tile is in the first row
			if (i == 0) {

				//???????/
				//arrays itself are pointers, but the elements are Tile objects so need to dereference the stored value to get a pointer
				//tiles[i][j] is a pointer to a Tile*, while &tiles[i][j] is the actual Tile*

				//in the 1st row, there is always a tile directly below in the next row at the same column
				//i is row, up/down, while j is column left/right
				tiles[i][j].tileP.push_back(&tiles[i + 1][j]);

				//if the tile is in the first column, it's adjacent ot the tile next to it and the tile below that
				if (j == 0) {

					tiles[i][j].tileP.push_back(&tiles[i][j + 1]);
					tiles[i][j].tileP.push_back(&tiles[i + 1][j + 1]);

				}

				//if the tile is in the last column, it is adjacent to the previous tile and the tile right below that
				else if (j == 24) {

					tiles[i][j].tileP.push_back(&tiles[i][j - 1]);
					tiles[i][j].tileP.push_back(&tiles[i + 1][j - 1]);

				}

				//if the tile is in between the first and last column, it is adjacent to the tiles on both sides
				//and the tiles below those two
				else {

					tiles[i][j].tileP.push_back(&tiles[i][j + 1]);
					tiles[i][j].tileP.push_back(&tiles[i][j - 1]);

					tiles[i][j].tileP.push_back(&tiles[i + 1][j + 1]);
					tiles[i][j].tileP.push_back(&tiles[i + 1][j - 1]);

				}

			}
			
			//if i = 15, the tile is in the last row
			else if (i == 15) {

				//in the last row, there is always a tile directly above in the previous row at the same column
				tiles[i][j].tileP.push_back(&tiles[i - 1][j]);

				//if the tile is in the first column, it is adjacent to the tile next to it and the tile above that
				if (j == 0) {

					tiles[i][j].tileP.push_back(&tiles[i][j + 1]);
					tiles[i][j].tileP.push_back(&tiles[i - 1][j + 1]);

				}

				//if the tile is in the last column, it is adjacent to the tile before it and the tile above that
				else if (j == 24) {

					tiles[i][j].tileP.push_back(&tiles[i][j - 1]);
					tiles[i][j].tileP.push_back(&tiles[i - 1][j - 1]);

				}

				//if the tile is in between the first and last column, it is adjacent to the tiles on both sides
				//and the tiles above those two
				else {

					tiles[i][j].tileP.push_back(&tiles[i][j + 1]);
					tiles[i][j].tileP.push_back(&tiles[i][j - 1]);

					tiles[i][j].tileP.push_back(&tiles[i - 1][j + 1]);
					tiles[i][j].tileP.push_back(&tiles[i - 1][j - 1]);

				}

			}

			//if a tile is not in the first or last row, 
			else {

				//tile always has another tile above and below it in the same oclumn
				tiles[i][j].tileP.push_back(&tiles[i + 1][j]);
				tiles[i][j].tileP.push_back(&tiles[i - 1][j]);

				//if the tile is in the first column, then it is adjacent to the next tile and those above and below it
				if (j == 0) {

					tiles[i][j].tileP.push_back(&tiles[i][j + 1]);
					tiles[i][j].tileP.push_back(&tiles[i + 1][j + 1]);
					tiles[i][j].tileP.push_back(&tiles[i - 1][j + 1]);

				}

				//if the tile is in the last column, then it is adjacent to the previous tile and those above and below it
				else if (j == 24) {

					tiles[i][j].tileP.push_back(&tiles[i][j - 1]);
					tiles[i][j].tileP.push_back(&tiles[i + 1][j - 1]);
					tiles[i][j].tileP.push_back(&tiles[i - 1][j - 1]);

				}

				//if the tile is not in the first or last column or first or last row, it is adjacent to all 8 tiles near it
				else {

					tiles[i][j].tileP.push_back(&tiles[i][j + 1]);
					tiles[i][j].tileP.push_back(&tiles[i + 1][j + 1]);
					tiles[i][j].tileP.push_back(&tiles[i - 1][j + 1]);

					tiles[i][j].tileP.push_back(&tiles[i][j - 1]);
					tiles[i][j].tileP.push_back(&tiles[i + 1][j - 1]);
					tiles[i][j].tileP.push_back(&tiles[i - 1][j - 1]);

				}

			}

			counter++;

		}

	}

	//initializes the game conditions and sets the bombs and numbers of the Tile objects
	newGame();

}

void Board::Tile::reveal() {

	//the tile can't be revealed already 
	//infinite loop, because each neighbor will check a neighbor, which will recheck the same neighbor
	if (!isRevealed) {

		//if the tile does not have a flag, we can reveal it 
		if (!hasFlag) {

			//if the tile does not have a bomb, we can reveal it
			if (!hasMine) {

				//if the tile does not have a number, call reveal
				if (!hasNum) {

					isRevealed = true;

					//a tile can have 8 pointers to other tiles
					for (unsigned int i = 0; i < tileP.size(); i++) {

						tileP[i]->reveal();

					}

				}
				//if the tile does have a number, we don't want to call reveal, but want to reveal the single tile
				else {

					isRevealed = true;

				}

			}

			//if it has a mine, only reveal the single tile
			else {

				isRevealed = true;
				//Board::Tile::gameOver = true;

			}

		}

	}

}

void Board::resetBoard() {

	//initializes the starting conditions of the board
	flagCounter = 0;
	gameOver = false;
	victory = false;
	test1Mode = false;
	test2Mode = false;
	test3Mode = false;
	winTiles.clear();
	bombTiles.clear();

	//initializes the starting conditions of the tiles
	for (int i = 0; i < 16; i++) {

		for (int j = 0; j < 25; j++) {

			tiles[i][j].isRevealed = false;
			tiles[i][j].hasNum = false;
			tiles[i][j].hasFlag = false;
			tiles[i][j].hasMine = false;
			tiles[i][j].adjacentMines = 0;

		}

	}

}

void Board::setNumbers() {

	//??????????
	//after tile bombs are assigned, assigns the numbers of each tile (assigns a tile a number if it is adjacent to bombs)
	for (int i = 0; i < 16; i++) {

		for (int j = 0; j < 25; j++) {

			//can't have number if tile already has mine
			if (!tiles[i][j].hasMine) {

				//while checking for adjacent mines, label each nonmine tile as a "win" tile
				//pointer to tile, so we are not copying it 
				//having winTiles in a vector makes it easier to check the win condition (if all winTiles are revealed)
				winTiles.push_back(&tiles[i][j]);

				//goes through vector of adjacent tiles and increments whenever each adjacent tile has a mine
				for (unsigned int k = 0; k < tiles[i][j].tileP.size(); k++) {

					if (tiles[i][j].tileP[k]->hasMine) {

						tiles[i][j].hasNum = true;
						tiles[i][j].adjacentMines++;

					}

				}

			}

		}

	}

}

void Board::newGame() {

	//resets tile conditions and empties vectors that hold the previous game's winning tiles and bomb tiles
	resetBoard();

	//randomly assigns tile bombs
	//don't need helepr function, because randomly assigning is only called when newGame is called (smile face clicked; test board 
	//loading uses predefined bombs, but still needs to have tiles reset and numebrs assigned)
	int bombsX[50];
	int bombsY[50];
	for (int i = 0; i < 50; i++) {

		//resets bool to keep track if every new random value pair is unique
		bool duplicate = false;

		//could isntead generate a number for horizontal and vertical axis, since you used a 2d array to store tiles
		//int bombLocation = Random::Int(0, 399); //inclusive
		int bombLocationX = Random::Int(0, 24); //columns are horizontal
		int bombLocationY = Random::Int(0, 15); //rows are vertical

		//goes through both arrays, and checks what's currently filled
		//starts iterating when i = 1 (when i = 0, there's nothing to compare)
		for (int j = 0; j < i; j++)

			//50 bombs are created using 50 x locations and 50 y locations (each pair is a bomb location on the board)
			//each pair shares the same index since they are both stored in arrays of 50
			//if a the x and y locations already exist in the arrays at the same index, don't want to add a duplicate bomb
			if (bombLocationX == bombsX[j] && bombLocationY == bombsY[j]) {

				//decrement i if the randomly generated location was not unique (same pair already stored)
				duplicate = true;
				i--;

				break;

			}

		//only unique pairs are added
		//if duplicate is true and i was decremented, a new random pair will be generated and tested for the ith position
		if (duplicate == false) {

			bombsX[i] = bombLocationX;
			bombsY[i] = bombLocationY;

			tiles[bombLocationY][bombLocationX].hasMine = true;

			//store bombTiles in a vector so displaying the bombs for debug mode or a loss is easier
			bombTiles.push_back(&tiles[bombLocationY][bombLocationX]);

		}

	}

	//after bombs are assigned to each tile, set the numbers of each adjacent tile
	setNumbers();
	
}

void Board::victoryCheck() {

	int counter = 0;

	//check to see if all the tiles without a bomb are revealed
	for (unsigned int i = 0; i < winTiles.size(); i++) {

		if (winTiles[i]->isRevealed) {

			counter++;

		}

	}

	//if the amount of revealed tiles = the amount of tiles without bombs, 
	if (counter == winTiles.size()) {

		gameOver = true;
		victory = true;

	}

	//check to see if a mine is revealed
	for (unsigned int i = 0; i < bombTiles.size(); i++) {

		if (bombTiles[i]->isRevealed) {

			gameOver = true;
			victory = false;

		}

	}

	if (gameOver) {

		//if the game is won, place flags over each tile with a bomb
		if (victory) {

			for (unsigned int i = 0; i < bombTiles.size(); i++) {

				bombTiles[i]->hasFlag = true;
				flagCounter++;

			}

		}

		//if the game is lost, reveal all bomb tiles
		else {
		
			for (unsigned int i = 0; i < bombTiles.size(); i++) {

				bombTiles[i]->isRevealed = true;

			}

		}

	}

}

void Board::drawBoard(sf::RenderWindow& window) {

	//draws each individual tile at a time
	for (int i = 0; i < 16; i++) {

		//draws a single row first (each column in a row) before switching to the next
		for (int j = 0; j < 25; j++) {

			//tiles[i][j] have a key 0 to 399, and the unordered_map of sprites have tilei keys corresponding to a respective Sprite
			//object to the Tile object with keysi = 0 to 399
			//draws the tile Sprite at current i and j; positions already initialized since they are static
			//tileSprite.setPosition(tileSprite.getPosition.x * j, tileSprite.getPosition.y * i);
			//window.draw(SpriteManager::GetSprite(tiles[i][j].key));
			sf::Sprite tileSprite = SpriteManager::GetSprite(tiles[i][j].key);

			auto var = tileSprite.getGlobalBounds();

			window.draw(tileSprite);

			//if the Tile at i row and j column has a mine, draw it over the unrevealed_tile sprite
			if (tiles[i][j].hasMine) {

				//because the loop iterates 400 times before clearing, multiple instances of the same sprite can be drawn 
				//after changing posiiton
				//SpriteManager::GetSprite("mine").setPosition(xPosition, yPosition);
				//window.draw(SpriteManager::GetSprite("mine"));
				sf::Sprite mine = SpriteManager::GetSprite("mine");
				mine.setPosition(tiles[i][j].xPosition, tiles[i][j].yPosition);
				window.draw(mine);

			}
			
			//if the tile has a numb
			else if (tiles[i][j].hasNum) {

				string key = "number_" + to_string(tiles[i][j].adjacentMines);

				sf::Sprite number = SpriteManager::GetSprite(key);
				number.setPosition(tiles[i][j].xPosition, tiles[i][j].yPosition);
				window.draw(number);

			}

			//?? Alternatively: array of tiles with bombs and without bombs, iterate through when needed and set conditions for
			//if victory
			//if debug mode
			//if gameover
			//if the tile is not revealed, want to draw the tile_hidden sprite over the tile_revealed sprite
			if (!tiles[i][j].isRevealed) {

				sf::Sprite coverSprite = SpriteManager::GetSprite("tile_hidden");
				coverSprite.setPosition(tiles[i][j].xPosition, tiles[i][j].yPosition);
				window.draw(coverSprite);
				
				//flag drawn after hidden tile is drawn
				//tile can only have a flag if it is not revealed yet
				if (tiles[i][j].hasFlag) {

					sf::Sprite flag = SpriteManager::GetSprite("flag");
					flag.setPosition(tiles[i][j].xPosition, tiles[i][j].yPosition);
					window.draw(flag);

				}

			}

		}

	}

	//draws faces 
	//positions already set
	//always draw the happy face, and if the game is over draw over it
	//only the smile face's rect looks for a mouse click and resets the game, the other faces only signify win/lose
	window.draw(SpriteManager::GetSprite("face_happy"));
	if (gameOver) {

		//if the game is over and you won
		if (victory) {

			window.draw(SpriteManager::GetSprite("face_win"));

		}

		//if you lost 
		else {

			window.draw(SpriteManager::GetSprite("face_lose"));

		}

	}

	//draws button options
	window.draw(SpriteManager::GetSprite("debug"));
	window.draw(SpriteManager::GetSprite("test_1"));
	window.draw(SpriteManager::GetSprite("test_2"));
	window.draw(SpriteManager::GetSprite("test_3"));

	//REFACTOR: ONLY MAKE DIGITS ONCE FOR + AND -
	//draws mine counter
	int remaining = bombTiles.size() - flagCounter;
	if (remaining >= 0) {

		//possible positive digits
		int digit100Place = remaining / 100;
		int digit10Place = (remaining % 100) / 10;
		int digit1Place = (remaining % 100) % 10;

		//when creating a sprite for each digit, the keys were stored as digiti, with i = 0-10, and i = 10 being - and i = 0 being 0
		//each digit is 21 (width) x 32 (height), so need to offset each one by 21
		sf::Sprite digit1 = SpriteManager::GetSprite("digit" + to_string(digit100Place));
		sf::Sprite digit2 = SpriteManager::GetSprite("digit" + to_string(digit10Place));
		sf::Sprite digit3 = SpriteManager::GetSprite("digit" + to_string(digit1Place));
		digit1.setPosition(0, 512);
		digit2.setPosition(21, 512);
		digit3.setPosition(42, 512);
		window.draw(digit1);
		window.draw(digit2);
		window.draw(digit3);

	}
	else {

		//there are only 400 tiles, and the counter starts at 50, which means the counter can go as low as -350
		//- sprite comes first
		sf::Sprite negative = SpriteManager::GetSprite("digit10");
		negative.setPosition(0, 512);
		window.draw(negative);

		//if the counter is less than -99 (-100 and lower), need to have 3 digits including -
		if (remaining < -99) {

			//321 / 100 = 3
			//321 % 100 = 21
			//21 / 10 = 2
			//21 % 10 = 1
			int digit100Place = -1 * (remaining / 100);
			int digit10Place = -1 * ((remaining % 100) / 10);
			int digit1Place = -1 * ((remaining % 100) % 10);

			sf::Sprite digit1 = SpriteManager::GetSprite("digit" + to_string(digit100Place));
			sf::Sprite digit2 = SpriteManager::GetSprite("digit" + to_string(digit10Place));
			sf::Sprite digit3 = SpriteManager::GetSprite("digit" + to_string(digit1Place));
			digit1.setPosition(21, 512);
			digit2.setPosition(42, 512);
			digit3.setPosition(63, 512);
			window.draw(digit1);
			window.draw(digit2);
			window.draw(digit3);

		}
		else {

			int digit10Place = -1 * (remaining / 10);
			int digit1Place = -1 * (remaining % 10);

			sf::Sprite digit0 = SpriteManager::GetSprite("digit0");
			sf::Sprite digit1 = SpriteManager::GetSprite("digit" + to_string(digit10Place));
			sf::Sprite digit2 = SpriteManager::GetSprite("digit" + to_string(digit1Place));
			digit0.setPosition(21, 512);
			digit1.setPosition(42, 512);
			digit2.setPosition(63, 512);
			window.draw(digit0);
			window.draw(digit1);
			window.draw(digit2);

		}

	}

	//debug mode
	//if debug mode is toggled on, draw a mine over every hidden_tile that is over a tile with a mine
	if (debugMode) {

		for (unsigned int i = 0; i < bombTiles.size(); i++) {

			sf::Sprite mine = SpriteManager::GetSprite("mine");
			mine.setPosition(bombTiles[i]->xPosition, bombTiles[i]->yPosition);
			window.draw(mine);

		}

	}

}

void Board::loadBoard(const char* fileName) {

	//loading a board is the same as creating a new game, so need to reset initial tile conditions
	resetBoard();

	//input file stream
	//files contain a bunch of 0s (empty) and 1s (mines) to represent the layout of a particular map
	//16 lines/rows, each with 25 characters/columns
	ifstream board(fileName);
	int counter = 0;
	string line;

	//iterate until end of the file
	while (!board.eof()) {

		//gets a line from the file, or a row for the board, and stores it in "line"
		getline(board, line);

		//for loop goes through each character in the line
		for (int i = 0; i < 25; i++) {

			//if the character read is 0, it's not a mine
			if (line[i] == '0') {

				winTiles.push_back(&tiles[counter][i]);

			}
			else {

				tiles[counter][i].hasMine = true;
				bombTiles.push_back(&tiles[counter][i]);

			}
			
		}

		//counter keeps track of the row (16 lines in file = 16 rows
		counter++;

	}

	//after mines are loaded and assigned, set the numbers of the neighboring tiles
	setNumbers();

}

//initializing position before drawing is less time consuming

//first figure if -
//then do modulo
//if modulo 10 = number, that's the first digit
//divide by 10
//then do moduklo 10 and thats the next  digit
//module 10 is the next digit....

//???? need to handle -100?