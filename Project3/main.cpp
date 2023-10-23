#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include <chrono>
#include "OtherFile.h"
#include <sstream>

using namespace std;

int main()
{
	fstream file;
	string width;
	string height;
	string mineCount;
	string name2 = "";
	file.open("files/board_config.cfg", ios_base::in);
	if (file.is_open()) {
		getline(file, width);
		getline(file, height);
		getline(file, mineCount);
	}
	cout << height << endl;
	cout << stoi(width) * 32 << endl;
	cout << stoi(height) * 32 + 88;

	int widthf = stoi(width) * 32;
	int heightf = stoi(height) * 32 + 100;

	sf::Text startText;
	sf::Font font;
	if (font.loadFromFile("files/font.ttf")) {
		startText.setFont(font);
	}
	startText.setString("WELCOME TO MINESWEEPER!");
	startText.setCharacterSize(24);
	startText.setFillColor(sf::Color::White);
	startText.setStyle(sf::Text::Bold | sf::Text::Underlined);

	sf::FloatRect textRec = startText.getGlobalBounds();
	startText.setOrigin(textRec.width / 2.0f, textRec.height / 2.0f);
	startText.setPosition(widthf / 2.0f, heightf / 2.0f - 150);


	sf::Text name;
	sf::Font nameFont;
	if (nameFont.loadFromFile("files/font.ttf")) {
		name.setFont(nameFont);
	}
	name.setString("Enter your name:");
	name.setCharacterSize(20);
	name.setFillColor(sf::Color::White);
	name.setStyle(sf::Text::Bold);

	sf::FloatRect nameRec = name.getGlobalBounds();
	name.setOrigin(nameRec.width / 2.0f, nameRec.height / 2.0f);
	name.setPosition(widthf / 2.0f, heightf / 2.0f - 75);

	sf::Text cursor;
	sf::Font curFont;
	if (curFont.loadFromFile("files/font.ttf")) {
		cursor.setFont(curFont);
	}
	cursor.setString("|");
	cursor.setCharacterSize(18);
	cursor.setFillColor(sf::Color::Yellow);
	cursor.setStyle(sf::Text::Bold);

	/*sf::FloatRect cursorRec = cursor.getGlobalBounds();
	cursor.setOrigin(cursorRec.width / 2.0f, cursorRec.height / 2.0f);
	cursor.setPosition(widthf / 2.0f, heightf / 2.0f - 45);*/

	sf::Text input;
	input.setFont(font);
	input.setCharacterSize(18);
	input.setFillColor(sf::Color::Yellow);
	input.setStyle(sf::Text::Bold);

	bool gameWind = false;
	//Starting window 
	sf::RenderWindow window(sf::VideoMode(widthf, heightf), "Welcome Window", sf::Style::Close);
	
	const int maxChar = 10;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::TextEntered) {
				if ((event.text.unicode >= 65 && event.text.unicode <= 90) || (event.text.unicode >= 97 && event.text.unicode <= 122)) {
					if (name2.size() < maxChar) {
						if (isalpha(event.text.unicode)) {
							if (name2.size() == 0) {
								event.text.unicode = toupper(event.text.unicode);
							}
							else {
								event.text.unicode = tolower(event.text.unicode);
							}
							name2 += event.text.unicode;
							input.setString(name2);
						}
					}
				}
			}
			else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::BackSpace) {
					if (name2.size() != 0) {
						name2.pop_back();
						input.setString(name2);
					}
				}
				if (name2.size() > 0) {
					if (event.key.code == sf::Keyboard::Enter) {
						window.close();
						gameWind = true;
						cout << name2;
					}
				}
			}

		}
		sf::FloatRect intRec = input.getGlobalBounds();
		input.setOrigin(intRec.width / 2.0f, intRec.height / 2.0f);
		input.setPosition(widthf / 2.0f, heightf / 2.0f - 45);

		cursor.setOrigin(intRec.width / 2.0f, intRec.height / 2.0f);
		cursor.setPosition(widthf / 2.0f + intRec.width, heightf / 2.0f - 45);

		window.clear(sf::Color::Blue);
		window.draw(startText);
		window.draw(name);
		window.draw(cursor);
		window.draw(input);
		window.display();
	}
	
	/*bool gameLose = false;
	bool gameWin = false;
	bool gameCont = true;
	int flagCount = 0;*/

	if (gameWind) {
		Resources resources;
		int currMin = 0;
		int currSec = 0;
		int min1num = 0;
		int min2num = 0;
		int sec1num = 0;
		int sec2num = 0;
		bool gameWinLead = false;
		bool gameLose = false;
		bool gameWin = false;
		bool gameCont = true;
		int flagCount = 0;
		bool debugBut = false;
		bool ppBut = true;	//play: true, pause: false
		bool leaderOpen = false; //false not open
		Board board;
		generateMine(height, width, resources, board, mineCount);
		//for (int i = 0; i < stoi(height); i++) {
		//	vector <Tile> tileRow;
		//	for (int j = 0; j < stoi(width); j++) {
		//		Tile tile(resources, false, false, j*32, i*32);
		//		tileRow.push_back(tile);
		//	}
		//	board.tilesVec.push_back(tileRow);
		//}
		//srand(time(0));
		//for (unsigned int i = 0; i < stoi(mineCount); i++) {
		//	float x = rand() % stoi(width);
		//	float y = rand() % stoi(height);
		//	while (board.tilesVec[y][x].mine == true) {
		//		x = rand() % stoi(width);
		//		y = rand() % stoi(height);
		//	}
		//	board.tilesVec[y][x].mine = true;
		//}

		//for (int i = 0; i < board.tilesVec.size(); i++) {
		//	for (int j = 0; j < board.tilesVec[i].size(); j++) {
		//		int count = 0;
		//		bool minus = false;
		//		bool add = false;
		//		if (board.tilesVec[i][j].mine == false) {
		//			if (checkingRow(i - 1, stoi(height))) {
		//				if (board.tilesVec[i - 1][j].mine == true) {
		//					count += 1;
		//				}
		//				if (checkingCol(j - 1, stoi(width))) {
		//					minus = true;
		//					if (board.tilesVec[i - 1][j - 1].mine == true) {
		//						count += 1;
		//					}
		//				}
		//				if (checkingCol(j + 1, stoi(width))) {
		//					add = true;
		//					if (board.tilesVec[i - 1][j + 1].mine == true) {
		//						count += 1;
		//					}
		//				}
		//			}
		//			if (minus) {
		//				if (board.tilesVec[i][j - 1].mine == true) {
		//					count += 1;
		//				}
		//			}
		//			if (add) {
		//				if (board.tilesVec[i][j + 1].mine == true) {
		//					count += 1;
		//				}
		//			}
		//			if (checkingRow(i + 1, stoi(height))) {
		//				if (board.tilesVec[i + 1][j].mine == true) {
		//					count += 1;
		//				}
		//				if (checkingCol(j - 1, stoi(width))) {
		//					minus = true;
		//					if (board.tilesVec[i + 1][j - 1].mine == true) {
		//						count += 1;
		//					}
		//				}
		//				if (checkingCol(j + 1, stoi(width))) {
		//					add = true;
		//					if (board.tilesVec[i + 1][j + 1].mine == true) {
		//						count += 1;
		//					}
		//				}
		//			}
		//		}
		//		board.tilesVec[i][j].adjacentTiles = count;
		//	}
		//}

		//Buttons
		sf::Sprite face;
		sf::Texture textureFace;
		sf::Texture textureFace2;
		textureFace.loadFromFile("files/images/face_happy.png");
		face.setTexture(textureFace);
		face.setPosition(((stoi(width)/ 2.0) * 32) - 32, 32 * (stoi(height) + 0.5f));
		//sf::Sprite happyFace = makeSprite("files/images/face_happy.png", ((stoi(width) / 2.0) * 32) - 32, 32 * (stoi(height) + 0.5f));

		sf::Sprite debug;
		sf::Texture textureBug;
		textureBug.loadFromFile("files/images/debug.png");
		debug.setTexture(textureBug);
		debug.setPosition((stoi(width) * 32) - 304, 32 * ((stoi(height) + 0.5f)));
		//bool debugBut = false;
		//bool ppBut = true;	//play: true, pause: false

		sf::Sprite pp;
		sf::Texture texturePlay;
		texturePlay.loadFromFile("files/images/play.png");
		sf::Texture texturePause;
		texturePause.loadFromFile("files/images/pause.png");
		pp.setTexture(texturePause);
		pp.setPosition(((stoi(width)) * 32) - 240, 32 * ((stoi(height)) + 0.5f));

		sf::Sprite leaderboard;
		sf::Texture textureLead;
		textureLead.loadFromFile("files/images/leaderboard.png");
		leaderboard.setTexture(textureLead);
		leaderboard.setPosition(((stoi(width)) * 32) - 176, 32 * ((stoi(height)) + 0.5f));

		sf::Sprite mine1;
		sf::Texture texturemine1;
		texturemine1.loadFromFile("files/images/digits.png");
		mine1.setTexture(texturemine1);
		mine1.setPosition(33, 32 * (stoi(height) + 0.5f) + 16);

		sf::Sprite mine2;
		sf::Texture texturemine2;
		texturemine2.loadFromFile("files/images/digits.png");
		mine2.setTexture(texturemine2);
		mine2.setPosition(33+21, 32 * (stoi(height) + 0.5f) + 16);

		sf::Sprite mine3;
		sf::Texture texturemine3;
		texturemine3.loadFromFile("files/images/digits.png");
		mine3.setTexture(texturemine3);
		mine3.setPosition(33-21, 32 * (stoi(height) + 0.5f) + 16);

		sf::Sprite min1;
		sf::Texture texturemin1;
		texturemine1.loadFromFile("files/images/digits.png");
		min1.setTexture(texturemine1);
		min1.setPosition((stoi(width) * 32) - 97,32 * (stoi(height) + 0.5f) + 16);

		sf::Sprite min2;
		sf::Texture texturemin2;
		texturemine2.loadFromFile("files/images/digits.png");
		min2.setTexture(texturemine2);
		min2.setPosition(((stoi(width) * 32) - 97)+21, 32 * (stoi(height) + 0.5f) + 16);

		sf::Sprite sec1;
		sf::Texture texturesec1;
		texturesec1.loadFromFile("files/images/digits.png");
		sec1.setTexture(texturesec1);
		sec1.setPosition((stoi(width) * 32) - 54, 32 * (stoi(height) + 0.5f) + 16);

		sf::Sprite sec2;
		sf::Texture texturesec2;
		texturesec2.loadFromFile("files/images/digits.png");
		sec2.setTexture(texturesec2);
		sec2.setPosition(((stoi(width) * 32) - 54)+21, 32 * (stoi(height) + 0.5f) + 16);

		int lwidth = stoi(width) * 16;
		int lheight = (stoi(height) * 16) + 50;
		sf::Text title;
		title.setString("LEADERBOARD");
		title.setFont(font);
		title.setCharacterSize(20);
		title.setFillColor(sf::Color::White);
		title.setStyle(sf::Text::Bold | sf::Text::Underlined);
		sf::FloatRect titleRec = title.getGlobalBounds();
		title.setOrigin(titleRec.width / 2.0f, titleRec.height / 2.0f);
		title.setPosition(lwidth/ 2.0f, lheight/ 2.0f - 120);

		sf::Text nameTimes;
		nameTimes.setFont(font);
		nameTimes.setCharacterSize(18);
		nameTimes.setFillColor(sf::Color::White);
		nameTimes.setStyle(sf::Text::Bold);
		nameTimes.setPosition(lwidth / 2.0f, lheight/ 2.0f + 20);

		string name1;
		string time1;
		string rtime1;
		string rname1;
		
		//Buttons
		/*sf::Sprite face;
		sf::Texture textureFace;
		sf::Sprite debug;

		sf::Sprite pp;
		sf::Texture texturePlay;
		sf::Texture texturePause;
		sf::Sprite leaderboard;
		sf::Sprite mine1;
		sf::Sprite mine2;
		sf::Sprite mine3;
		sf::Sprite min1;
		sf::Sprite min2;
		sf::Sprite sec1;
		sf::Sprite sec2;*/

		//Sprites(face, textureFace, debug, pp, texturePlay, texturePause, leaderboard, mine1, mine2, mine3, min1, min2, sec1, sec2, height, width);
		sf::RenderWindow gameWindow(sf::VideoMode(widthf, heightf), "Game window", sf::Style::Close);
		sf::Clock start;
		while (gameWindow.isOpen()) {
			sf::Time temp = start.getElapsedTime();
			int timer = temp.asSeconds();
			int min = timer/ 60;
			int sec = timer - (min*60);
			sf::Event event;
			while (gameWindow.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					gameWindow.close();
				}
				if (event.type == sf::Event::MouseButtonPressed) {
					sf::Mouse mouse;
					auto coordinate = mouse.getPosition(gameWindow);

					auto rectbounds = debug.getGlobalBounds();
					auto rectboundsp = pp.getGlobalBounds();
					auto rectboundFace = face.getGlobalBounds();
					auto rectboundLeader = leaderboard.getGlobalBounds();
					//leaderboard & restart button
					if (rectboundFace.contains(coordinate.x, coordinate.y)) {
						cout << "true";
						gameCont = true;
						debugBut = false;
						gameLose = false;
						gameWin = false;
						ppBut = true;
						gameWinLead = false;
						temp = start.restart();
						flagCount = 0;
						currMin = 0;
						currSec = 0;
						min1num = 0;
						min2num = 0;
						sec1num = 0;
						sec2num = 0;
						leaderOpen = false;
						generateMine(height, width, resources, board, mineCount);
						face.setTexture(textureFace);
						/*for (int i = 0; i < board.tilesVec.size(); i++) {
							for (int j = 0; j < board.tilesVec[i].size(); j++) {
								board.tilesVec[i][j].flag == false;
								board.tilesVec[i][j].clicked = false;

							}
						}*/
					}
					if (rectboundLeader.contains(coordinate.x, coordinate.y)) {
						leaderOpen = !leaderOpen;
					}
					if (gameCont == true && leaderOpen == false) {
						if (rectbounds.contains(coordinate.x, coordinate.y)) {
							if (ppBut == true) {
								debugBut = !debugBut;
							}
						}
						if (rectboundsp.contains(coordinate.x, coordinate.y)) {
							ppBut = !ppBut;
							if (!ppBut) {
								if (leaderOpen == false) {
									currMin += min;
									currSec += sec;
								}
							}
							else {
								temp = start.restart();
							}
						}
						if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
							for (int i = 0; i < board.tilesVec.size(); i++) {
								for (int j = 0; j < board.tilesVec[i].size(); j++) {
									auto tilebounds = board.tilesVec[i][j].tileSprite.getGlobalBounds();
									if (tilebounds.contains(coordinate.x, coordinate.y)) {
										if (board.tilesVec[i][j].flag == false) {
											board.tilesVec[i][j].clicked = true;
										}
									}
								}
							}
						}
						else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
							for (int i = 0; i < board.tilesVec.size(); i++) {
								for (int j = 0; j < board.tilesVec[i].size(); j++) {
									auto tilebounds = board.tilesVec[i][j].tileSprite.getGlobalBounds();
									if (tilebounds.contains(coordinate.x, coordinate.y)) {
										if (board.tilesVec[i][j].reveal == false) {
											if (board.tilesVec[i][j].flag == false) {
												board.tilesVec[i][j].flag = true;
												//board.tilesVec[i][j].clicked = false;
												flagCount += 1;
											}
											else {
												board.tilesVec[i][j].flag = false;
												//board.tilesVec[i][j].clicked = false;
												flagCount -= 1;
											}
										}
									}
								}
							}
						}
					}
				}
			}

			gameWindow.clear(sf::Color::White);

			//if clicked 
			for (int i=0; i < board.tilesVec.size() && gameCont == true; i++) {
				for (int j = 0; j < board.tilesVec[i].size() && gameCont == true; j++) {
					/*if (board.tilesVec[i][j].flag == true) {
						board.tilesVec[i][j].flagPlace(resources);

					}*/
					if (board.tilesVec[i][j].clicked == true) {
						if (board.tilesVec[i][j].mine == true) {
							textureFace2.loadFromFile("files/images/face_lose.png");
							face.setTexture(textureFace2);
							gameLose = true;
							gameCont = false;
							currMin += min;
							currSec += sec;
						}
						else  {
							if (board.tilesVec[i][j].adjacentTiles == 0) {
								board.tilesVec[i][j].placeNum(resources, board.tilesVec[i][j].adjacentTiles);
								board.tilesVec[i][j].reveal = true;
								board.tilesVec[i][j].clicked = false;
								checkTile(i,j, board,  height,  width,  resources);
							}
							else {
								board.tilesVec[i][j].placeNum(resources, board.tilesVec[i][j].adjacentTiles);
								board.tilesVec[i][j].reveal = true;
								board.tilesVec[i][j].clicked = false;
							}
						}
					}
					if (checkWin(board)) {
						textureFace2.loadFromFile("files/images/face_win.png");
						face.setTexture(textureFace2);
						//time stop
						gameCont = false;
						gameWin = true;
						currMin += min;
						currSec += sec;
						flagCount = stoi(mineCount);
						gameWinLead = true;
					}
				}
			}
			
			for (int i = 0; i < board.tilesVec.size(); i++) {
				for (int j = 0; j < board.tilesVec[i].size(); j++) {
					gameWindow.draw(board.tilesVec[i][j].hideSprite);
					if (board.tilesVec[i][j].reveal == true) {
						gameWindow.draw(board.tilesVec[i][j].baseSprite);
						gameWindow.draw(board.tilesVec[i][j].tileSprite);
					}
					else {
						gameWindow.draw(board.tilesVec[i][j].hideSprite);
					}
					if (board.tilesVec[i][j].flag == true) {
						gameWindow.draw(board.tilesVec[i][j].hideSprite);
						gameWindow.draw(board.tilesVec[i][j].flagSprite);
					}
				}
			}
			if (gameLose == true) {
				for (int i = 0; i < board.tilesVec.size(); i++) {
					for (int j = 0; j < board.tilesVec[i].size(); j++) {
						if (board.tilesVec[i][j].mine == true) {
							gameWindow.draw(board.tilesVec[i][j].mineSprite);
						}
					}
				}
			}
			else if (gameWin == true) {
				for (int i = 0; i < board.tilesVec.size(); i++) {
					for (int j = 0; j < board.tilesVec[i].size(); j++) {
						if (board.tilesVec[i][j].mine == true) {
							gameWindow.draw(board.tilesVec[i][j].flagSprite);
						}
					}
				}
				
			}
			if (debugBut == true) {
				for (int i = 0; i < board.tilesVec.size(); i++) {
					for (int j = 0; j < board.tilesVec[i].size(); j++) {
						if (board.tilesVec[i][j].mine == true) {
							gameWindow.draw(board.tilesVec[i][j].mineSprite);
						}
					}
				}
			}

			if (ppBut == false) {
				for (int i = 0; i < board.tilesVec.size(); i++) {
					for (int j = 0; j < board.tilesVec[i].size(); j++) {
						gameWindow.draw(board.tilesVec[i][j].baseSprite);
					}
				}
			}

			if (gameCont == false) {
				time(0, currMin, 0, currSec, min1num, min2num, sec1num, sec2num);
			}
			else {
				if (ppBut == true) {
					pp.setTexture(texturePause);
					time(min, currMin, sec, currSec, min1num, min2num, sec1num, sec2num);
					/*int tempMin = min + currMin;
					int tempSec = sec + currSec;
					while (tempSec >= 60) {
						tempMin += 1;
						tempSec -= 60;
					}
					min1num = tempMin / 10;
					min2num = tempMin % 10;
					sec1num = tempSec / 10;
					sec2num = tempSec % 10;*/
				}
				else {
					pp.setTexture(texturePlay);
					//hide board 
					time(0, currMin, 0, currSec, min1num, min2num, sec1num, sec2num);
					/*int tempMin =  currMin;
					int tempSec =  currSec;
					while (tempSec >= 60) {
						tempMin += 1;
						tempSec -= 60;
					}
					min1num = tempMin / 10;
					min2num = tempMin % 10;
					sec1num = tempSec / 10;
					sec2num = tempSec % 10;*/
				}
			}

			int tens = (stoi(mineCount) - flagCount) / 10;
			int ones = (stoi(mineCount) - flagCount) % 10;
			if ((stoi(mineCount) - flagCount) < 0) {
				ones *= -1;
				tens *= -1;
				mine3.setTextureRect(sf::IntRect(21 * 10, 0, 21, 32));
			}
			else {
				mine3.setTextureRect(sf::IntRect(21 * 0, 0, 21, 32));
			}
			mine1.setTextureRect(sf::IntRect(21 * tens, 0, 21, 32));
			mine2.setTextureRect(sf::IntRect(21 * ones, 0, 21, 32));

			min1.setTextureRect(sf::IntRect(21 * min1num, 0, 21, 32));
			min2.setTextureRect(sf::IntRect(21 * min2num, 0, 21, 32));
			sec1.setTextureRect(sf::IntRect(21 * sec1num, 0, 21, 32));
			sec2.setTextureRect(sf::IntRect(21 * sec2num, 0, 21, 32));


			gameWindow.draw(face);
			gameWindow.draw(debug);
			gameWindow.draw(pp);
			gameWindow.draw(leaderboard);
			gameWindow.draw(mine3);
			gameWindow.draw(mine1);
			gameWindow.draw(mine2);
			gameWindow.draw(min1);
			gameWindow.draw(min2);
			gameWindow.draw(sec1);
			gameWindow.draw(sec2);

			gameWindow.display();

			if (leaderOpen == true) {
				cout << "\nprinting";
				gameWinLead = false;
				if (gameCont == true && ppBut == true) {
					currMin += min;
					currSec += sec;
				}
				if (leaderOpen == true && (gameWin == false && gameLose == false)) {
					for (int i = 0; i < board.tilesVec.size(); i++) {
						for (int j = 0; j < board.tilesVec[i].size(); j++) {
							gameWindow.draw(board.tilesVec[i][j].baseSprite);
						}
					}
					pp.setTexture(texturePlay);
					gameWindow.draw(pp);
					gameWindow.display();
				}
				
				//cout << "hello" << endl;
				map <string, string> players;
				map <string, string>::iterator iter;

				fstream file;
				file.open("files/leaderboard.txt", ios::in);
				while (getline(file, time1, ',') && getline(file, name1)) {
					//cout << time1 << " " << name1 << endl;
					string tempor = time1.substr(0, 2) + time1.substr(3, 5);
					cout << "temp: " << tempor << " " << name1 << endl;
					players.emplace(tempor, name1);
				}
				string finalTime = "";
				if (gameWin == true) {
					//cout << min1num << min2num << ":" << sec1num << sec2num;
					string newTime = to_string(min1num) + to_string(min2num) + to_string(sec1num) + to_string(sec2num);
					finalTime = newTime.substr(0, 2) + ":" + newTime.substr(2, 4);
					players.emplace(newTime, name2);
				}
				file.close();

				ofstream file2;
				file2.open("files/leaderboard.txt");
				int count = 0;
				for (iter = players.begin(); iter != players.end() && count < 5; ++iter) {
					file2 << iter->first.substr(0, 2) + ":" + iter->first.substr(2, 4) + "," + iter->second << endl;;
					count += 1;
				}
				file2.close();
				ifstream file3;
				file3.open("files/leaderboard.txt");

				string setTimeNames = "";
				int counting = 1;
				while (getline(file3, rtime1, ',') && getline(file3, rname1)) {
					if (rtime1 == finalTime) {
						rname1 += "*";
					}
					setTimeNames += to_string(counting) + ".\t" + rtime1 + "\t" + rname1 + "\n\n";
					cout << setTimeNames;
					counting += 1;
				}

				nameTimes.setString(setTimeNames);
				/*nameTimes.setString("1.\t" + rtime1 + "\t" + rname1 + "\n\n" + "2.\t" + rtime2 + "\t" + rname2 + "\n\n" +
					"3.\t" + rtime3 + "\t" + rname3 + "\n\n" + "4.\t" + rtime4 + "\t" + rname4 + "\n\n" + "5.\t" + rtime5 + "\t" + rname5 + "\n\n");*/
				sf::FloatRect nameTimeRec = nameTimes.getLocalBounds();
				nameTimes.setOrigin(nameTimeRec.width / 2.0f, nameTimeRec.height / 2.0f);

				sf::RenderWindow leadWindow(sf::VideoMode(lwidth, lheight), "Leaderboard window", sf::Style::Close);
				while (leadWindow.isOpen()) {
					sf::Event event;
					while (leadWindow.pollEvent(event)) {
						if (event.type == sf::Event::Closed) {
							leaderOpen = false;
							leadWindow.close();
							if (gameCont == true) {
								temp = start.restart();
							}
						}
					}
					leadWindow.clear(sf::Color::Blue);
					leadWindow.draw(title);
					leadWindow.draw(nameTimes);
					leadWindow.display();
				}
			}
		}
	}
	return 0;
}
