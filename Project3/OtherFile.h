#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

bool checkingRow(int num, int rows);
bool checkingCol(int num, int cols);


//sf::RectangleShape setRectangle(sf::Vector2f size, float positionx, float positiony, float originx, float originy, sf::Color color);
//sf::Text setText(string fontFile, string message, unsigned int size, sf::Color color);
//sf::Sprite makeSprite(string file, float x, float y);

struct Resources {
	sf::Texture hiddenTile;
	sf::Texture mine;
	sf::Texture flag;
	sf::Texture none;
	sf::Texture one;
	sf::Texture two;
	sf::Texture three;
	sf::Texture four;
	sf::Texture five;
	sf::Texture six;
	sf::Texture seven;
	sf::Texture eigtht;
	//vector <sf::Texture> nums;
	Resources();
};

struct Tile {
	sf::Sprite baseSprite;
	sf::Sprite hideSprite;
	sf::Sprite tileSprite;
	sf::Sprite flagSprite;
	sf::Sprite mineSprite;
	bool flag;
	bool mine;
	bool reveal;
	bool clicked;
	int adjacentTiles;

	Tile(Resources& resources, bool flag, bool mine, bool reveal, float positionx, float positiony, int adjacentTiles, bool clicked);
	void minePlace(Resources& resources);
	void flagPlace(Resources& resources);
	void hiddenPlace(Resources& resources);
	void placeNum(Resources& resources, int num);
};

struct Board {
	vector <vector<Tile>> tilesVec;
};

void generateMine(string height, string width, Resources& resources, Board& board, string mineCount);
//void showMines(Resources& resources, Board& board);
//void hideBoard(Resources& resources, Board& board);
//void generateMine(string height, string width, Resources& resources, Board& board, string mineCount);
void time(int min, int currMin, int sec, int currSec, int& min1num, int& min2num, int& sec1num, int& sec2num);
void checkTile(int i, int j, Board& board, string height, string width, Resources& resources);
bool checkWin(Board& board);