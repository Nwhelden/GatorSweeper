#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Board.h"
#include "SpriteManager.h"
#include "Random.h"
using namespace std;

//draw board function
//has conditionals depending on what is clicked
//if new game
//if 

void rightClick(Board& game, sf::Vector2i& mPosition) {

    if (!game.gameOver) {

        for (int i = 0; i < 16; i++) {

            for (int j = 0; j < 25; j++) {

                //retrieves the key of the tile's sprite
                auto tileSprite = SpriteManager::GetSprite(game.tiles[i][j].key);

                if (tileSprite.getGlobalBounds().contains(sf::Vector2f(mPosition.x, mPosition.y))) {

                    //if the tile does not have a flag and is not revealed, we can place a flag
                    if (!game.tiles[i][j].hasFlag) {

                        if (!game.tiles[i][j].isRevealed) {

                            game.tiles[i][j].hasFlag = true;
                            game.flagCounter++;

                        }

                    }

                    //if the tile already has a flag, we can remove it
                    else {

                        game.tiles[i][j].hasFlag = false;
                        game.flagCounter--;

                    }

                }

            }

        }

    }

}

void leftClick(Board& game, sf::Vector2i& mPosition) {

    //a left mouse click can only click one thing at a time
    //if the face was clicked, reset the game
    if (SpriteManager::GetSprite("face_happy").getGlobalBounds().contains(sf::Vector2f(mPosition.x, mPosition.y))) {

        game.newGame();

    }

    //if any of the texts were clicked, load the respective test board
    else if (SpriteManager::GetSprite("test_1").getGlobalBounds().contains(sf::Vector2f(mPosition.x, mPosition.y))) {

        //want to use a function, because the Board object "game" was already constructed
        //we modify the board based on the data passed in
        game.loadBoard("boards/testboard1.brd");

    }

    else if (SpriteManager::GetSprite("test_2").getGlobalBounds().contains(sf::Vector2f(mPosition.x, mPosition.y))) {

        game.loadBoard("boards/testboard2.brd");

    }

    else if (SpriteManager::GetSprite("test_3").getGlobalBounds().contains(sf::Vector2f(mPosition.x, mPosition.y))) {

        game.loadBoard("boards/testboard3.brd");

    }

    //if debug was clicked, toggle debug on/off
    else if (SpriteManager::GetSprite("debug").getGlobalBounds().contains(sf::Vector2f(mPosition.x, mPosition.y))) {

        //want to be able to toggle the debug mode, so if it's enabled (true), disable it (false)
        //if the debug is disabled (False), enable it (true)
        if (game.debugMode) {

            game.debugMode = false;

        }
        else {

            game.debugMode = true;

        }

    }

    //if nothing else was clicked, check if a tile was clicked
    //better than always checking if a tile was clicked, so you don't have to always go through 400 tiles
    else {

        if (!game.gameOver) {

            //tiles array has 16 rows (first loop) and 25 columns (second loop)
            //whenever a left mouse click, go through each tile to determine if the mouse was over a tile 
            for (int i = 0; i < 16; i++) {

                for (int j = 0; j < 25; j++) {

                    //retrievesthe tile's sprite using its stored key
                    auto tileSprite = SpriteManager::GetSprite(game.tiles[i][j].key);

                    //rectangle around sprite
                    //auto var = tileSprite.getGlobalBounds();

                    //conditional checks if the mouse's position at the time of the click was over the tile's sprite
                    if (tileSprite.getGlobalBounds().contains(sf::Vector2f(mPosition.x, mPosition.y))) {


                        //if the tile is not flagged, we can click it
                        if (!game.tiles[i][j].hasFlag) {

                            //if the tile is not revealed, clicking it will reveal it
                            if (!game.tiles[i][j].isRevealed) {

                                //replace with reveal function??
                                //game.tiles[i][j].isRevealed = true;
                                //function reveals the tile and any of its adjacent itles if possible (recursive)
                                game.tiles[i][j].reveal();

                                //victory check; after we reveal a tile, did we reveal a mine and lose, or did we reveal all 
                                //of the tiles without a mine and win?
                                game.victoryCheck();

                            }

                        }

                        //can only click one tile at a time
                        //conditional to break out of nested loop, break;

                    }

                }

            }

        }

    }

}

void loadSprites() {

    SpriteManager::LoadSprite("mine");
    SpriteManager::LoadSprite("tile_hidden");
    SpriteManager::LoadSprite("number_1");
    SpriteManager::LoadSprite("number_2");
    SpriteManager::LoadSprite("number_3");
    SpriteManager::LoadSprite("number_4");
    SpriteManager::LoadSprite("number_5");
    SpriteManager::LoadSprite("number_6");
    SpriteManager::LoadSprite("number_7");
    SpriteManager::LoadSprite("number_8");
    SpriteManager::LoadSprite("flag");
    SpriteManager::LoadSprite("face_happy");
    SpriteManager::LoadSprite("face_win");
    SpriteManager::LoadSprite("face_lose");
    SpriteManager::LoadSprite("debug");
    SpriteManager::LoadSprite("test_1");
    SpriteManager::LoadSprite("test_2");
    SpriteManager::LoadSprite("test_3");

    //creates 400 distinct tile sprites; distinct because no offset (sprites use the same Rect and texture)
    //we want distinct sprites, because we want to find whenever a mouse clicks over one
    //creates 11 digit sprites from a single texture using an offset
    //sprites are stored in an unordered map using a tile1 or digit1 key
    SpriteManager::LoadSprites("tile_revealed", 400, 0, 32, 32, "tile");
    SpriteManager::LoadSprites("digits", 11, 21, 21, 32, "digit");

}

void setPositions() {

    //sets hte positions of the unrevealed_tile Sprite objects
    //each unrevealed_tile Sprite is unique and changes when clicked on a mouse, whereas revealed_tile Sprite is just a cover
    //400 unrevealed_tile Sprite objects in a 1d vector corresponding to a Tile object that is stored in a 2d array
    int xCounter = 0;
    int yCounter = 0;
    for (int i = 0; i < 400; i++) {

        //unordered map, need to pass in key value to get sprites (sprites have tilei key from i = 0 to 399) 
        string key = "tile" + to_string(i);
        SpriteManager::GetSprite(key).setPosition(32 * xCounter, 32 * yCounter);
        xCounter++;

        //we only have 0 to 24 columns (x), so after we draw 25 tiles for a row, we want to increment the row (y) and restart 
        //at the first column 
        if (xCounter == 25) {

            xCounter = 0;
            yCounter++;

        }

    }

    //board is made up of 32 x 32 pixel tiles,in a 25 x 16 board (25 columns x 16 rows: 800 x 512)

    //sets position of faces, which are at the bottom of the board (512 - y) at the center (800 /2 - x)
    //faces are 64 x 64
    SpriteManager::GetSprite("face_happy").setPosition(400, 512);
    SpriteManager::GetSprite("face_win").setPosition(400, 512);
    SpriteManager::GetSprite("face_lose").setPosition(400, 512);

    //sets position of debug mode and tests 
    //offset the farthest to the left from 800 by 64, since that's how much space it takes up
    SpriteManager::GetSprite("debug").setPosition(544, 512);
    SpriteManager::GetSprite("test_1").setPosition(608, 512);
    SpriteManager::GetSprite("test_2").setPosition(672, 512);
    SpriteManager::GetSprite("test_3").setPosition(736, 512);

    //??????/ HOW TO SET POSITIONS OF NUMBER??? may need 2 sets of sprites  (how to do 22?)
    //sets the position of the 

    //half the window
    //

}

int main()
{

    sf::RenderWindow window(sf::VideoMode(800, 600), "Project 3: Minesweeper");

    //initialize board object
    //contructor sets booleans to false and initializes the array of tiles for creating the board
    Board game;

    //load all the sprites needed
    //function passes all the required filenames into the SpriteManager object and creates a map of sprites
    loadSprites();

    //sets the positions of the sprites loaded to meet what the code requires
    setPositions();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {

                window.close();

            }
            else if (event.type == sf::Event::MouseButtonPressed) {

                //gets the current position of the mouse relative to the RenderWindow object, window
                sf::Vector2i mPosition = sf::Mouse::getPosition(window);

                //if the left mouse was clicked, we want to reveal a tile, enable debug mode, enable a test mode, or reset the game
                if (event.mouseButton.button == sf::Mouse::Left) {

                    leftClick(game, mPosition);

                }

                //if the right mouse was clicked, we want to place a flag on a tile
                else if (event.mouseButton.button == sf::Mouse::Right) {

                    rightClick(game, mPosition);

                }


            }

                //manage possibilities of the mouseclick here
                //get mouse position 

                //conditionals
                //if over tile
                //if over reset button
                //if over debug button
                //set boolean in board object

                //tile isRevealed, hasMine, hasNumber.... 
                //if isRevealed is false, set it to true, then if it's true, then don't draw the tile_hidden sprite

        }

        window.clear();
        game.drawBoard(window);
        window.display();
    }

    return 0;
}