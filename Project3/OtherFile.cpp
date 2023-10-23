#include "OtherFile.h"

bool checkingRow(int num, int rows) {
    if (num < 0 || num >= rows) {
        return false;
    }
    return true;
}

bool checkingCol(int num, int cols) {
    if (num < 0 || num >= cols) {
        return false;
    }
    return true;
}

//void showMines(Board &board) {
//    for (int i = 0; i < board.tilesVec.size(); i++) {
//        for (int j = 0; j < board.tilesVec[i].size(); j++) {
//            if (board.tilesVec[i][j].mine == true) {
//                board.tilesVec[i][j].mineSprite;
//            }
//        }
//    }
//}

//void hideBoard(Resources &resources, Board &board) {
//    for (int i = 0; i < board.tilesVec.size(); i++) {
//        for (int j = 0; j < board.tilesVec[i].size(); j++) {
//            board.tilesVec[i][j].hiddenPlace(resources);
//        }
//    }
//}

void time(int min, int currMin, int sec, int currSec, int &min1num, int &min2num, int &sec1num, int &sec2num) {
    int tempMin = min + currMin;
    int tempSec = sec + currSec;
    while (tempSec >= 60) {
        tempMin += 1;
        tempSec -= 60;
    }
    min1num = tempMin / 10;
    min2num = tempMin % 10;
    sec1num = tempSec / 10;
    sec2num = tempSec % 10;
}
//16 row = height
// 25 = width

//void Sprites(sf::Sprite &face, sf::Texture &textureFace, sf::Sprite &debug, sf::Sprite &pp, sf::Texture &texturePlay, sf::Texture &texturePause, sf::Sprite &leaderboard, sf::Sprite &mine1, sf::Sprite &mine2, sf::Sprite &mine3, sf::Sprite &min1, sf::Sprite &min2, sf::Sprite &sec1, sf::Sprite &sec2, string height, string width) {
//	//sf::Sprite face;
//	//sf::Texture textureFace;
//	textureFace.loadFromFile("files/images/face_happy.png");
//	face.setTexture(textureFace);
//	face.setPosition(((stoi(width) / 2.0) * 32) - 32, 32 * (stoi(height) + 0.5f));
//
//	//sf::Sprite debug;
//	sf::Texture textureBug;
//	textureBug.loadFromFile("files/images/debug.png");
//	debug.setTexture(textureBug);
//	debug.setPosition((stoi(width) * 32) - 304, 32 * ((stoi(height) + 0.5f)));
//
//	//sf::Sprite pp;
//	//sf::Texture texturePlay;
//	texturePlay.loadFromFile("files/images/play.png");
//	//sf::Texture texturePause;
//	texturePause.loadFromFile("files/images/pause.png");
//	pp.setTexture(texturePause);
//	pp.setPosition(((stoi(width)) * 32) - 240, 32 * ((stoi(height)) + 0.5f));
//
//	//sf::Sprite leaderboard;
//	sf::Texture textureLead;
//	textureLead.loadFromFile("files/images/leaderboard.png");
//	leaderboard.setTexture(textureLead);
//	leaderboard.setPosition(((stoi(width)) * 32) - 176, 32 * ((stoi(height)) + 0.5f));
//
//	//sf::Sprite mine1;
//	sf::Texture texturemine1;
//	texturemine1.loadFromFile("files/images/digits.png");
//	mine1.setTexture(texturemine1);
//	mine1.setPosition(33, 32 * (stoi(height) + 0.5f) + 16);
//
//	//sf::Sprite mine2;
//	sf::Texture texturemine2;
//	texturemine2.loadFromFile("files/images/digits.png");
//	mine2.setTexture(texturemine2);
//	mine2.setPosition(33 + 21, 32 * (stoi(height) + 0.5f) + 16);
//
//	//sf::Sprite mine3;
//	sf::Texture texturemine3;
//	texturemine3.loadFromFile("files/images/digits.png");
//	mine3.setTexture(texturemine3);
//	mine3.setPosition(33 - 21, 32 * (stoi(height) + 0.5f) + 16);
//
//	//sf::Sprite min1;
//	sf::Texture texturemin1;
//	texturemine1.loadFromFile("files/images/digits.png");
//	min1.setTexture(texturemine1);
//	min1.setPosition((stoi(width) * 32) - 97, 32 * (stoi(height) + 0.5f) + 16);
//
//	//sf::Sprite min2;
//	sf::Texture texturemin2;
//	texturemine2.loadFromFile("files/images/digits.png");
//	min2.setTexture(texturemine2);
//	min2.setPosition(((stoi(width) * 32) - 97) + 21, 32 * (stoi(height) + 0.5f) + 16);
//
//	//sf::Sprite sec1;
//	sf::Texture texturesec1;
//	texturesec1.loadFromFile("files/images/digits.png");
//	sec1.setTexture(texturesec1);
//	sec1.setPosition((stoi(width) * 32) - 54, 32 * (stoi(height) + 0.5f) + 16);
//
//	//sf::Sprite sec2;
//	sf::Texture texturesec2;
//	texturesec2.loadFromFile("files/images/digits.png");
//	sec2.setTexture(texturesec2);
//	sec2.setPosition(((stoi(width) * 32) - 54) + 21, 32 * (stoi(height) + 0.5f) + 16);
//}


void generateMine(string height, string width, Resources& resources, Board &board, string mineCount) {
	board.tilesVec.clear();
	for (int i = 0; i < stoi(height); i++) {
		vector <Tile> tileRow;
		for (int j = 0; j < stoi(width); j++) {
			Tile tile(resources, false, false, false, j*32, i*32, -1, false);
			tileRow.push_back(tile);
		}
		board.tilesVec.push_back(tileRow);
	}
	srand(time(0));
	for (unsigned int i = 0; i < stoi(mineCount); i++) {
		float x = rand() % stoi(width);
		float y = rand() % stoi(height);
		while (board.tilesVec[y][x].mine == true) {
			x = rand() % stoi(width);
			y = rand() % stoi(height);
		}
		board.tilesVec[y][x].mine = true;
	}

	for (int i = 0; i < board.tilesVec.size(); i++) {
			for (int j = 0; j < board.tilesVec[i].size(); j++) {
				bool minus = false;
				bool add = false;
				if (board.tilesVec[i][j].mine == false) {
					int count = 0;
					if (checkingRow(i - 1, stoi(height))) {
						if (board.tilesVec[i - 1][j].mine == true) {
							count += 1;
						}
						if (checkingCol(j - 1, stoi(width))) {
							//minus = true;
							if (board.tilesVec[i - 1][j - 1].mine == true) {
								count += 1;
							}
						}
						if (checkingCol(j + 1, stoi(width))) {
							//add = true;
							if (board.tilesVec[i - 1][j + 1].mine == true) {
								count += 1;
							}
						}
					}
					if (checkingCol(j - 1, stoi(width))) {
						if (board.tilesVec[i][j - 1].mine == true) {
							count += 1;
						}
					}
					if (checkingCol(j + 1, stoi(width))) {
						if (board.tilesVec[i][j + 1].mine == true) {
							count += 1;
						}
					}
					if (checkingRow(i + 1, stoi(height))) {
						if (board.tilesVec[i + 1][j].mine == true) {
							count += 1;
						}
						if (checkingCol(j - 1, stoi(width))) {
							minus = true;
							if (board.tilesVec[i + 1][j - 1].mine == true) {
								count += 1;
							}
						}
						if (checkingCol(j + 1, stoi(width))) {
							add = true;
							if (board.tilesVec[i + 1][j + 1].mine == true) {
								count += 1;
							}
						}
					}
					board.tilesVec[i][j].adjacentTiles = count;
				}
			}
		}
}

//Board::Board(string height, string width, Resources resources, string mineCount, int &currMin, int &currSec, int &min1num, int &min2num, int &sec1num, int &sec2num, bool &debugBut, bool &ppBut) {
//    //Board board;
//	for (int i = 0; i < stoi(height); i++) {
//		vector <Tile> tileRow;
//		for (int j = 0; j < stoi(width); j++) {
//			Tile tile(resources, false, false, j * 32, i * 32);
//			tileRow.push_back(tile);
//		}
//		tilesVec.push_back(tileRow);
//	}
//	srand(time(0));
//	for (unsigned int i = 0; i < stoi(mineCount); i++) {
//		float x = rand() % stoi(width);
//		float y = rand() % stoi(height);
//		while (tilesVec[y][x].mine == true) {
//			x = rand() % stoi(width);
//			y = rand() % stoi(height);
//		}
//		tilesVec[y][x].mine = true;
//	}
//
//	for (int i = 0; i < tilesVec.size(); i++) {
//		for (int j = 0; j < tilesVec[i].size(); j++) {
//			int count = 0;
//			bool minus = false;
//			bool add = false;
//			if (tilesVec[i][j].mine == false) {
//				if (checkingRow(i - 1, stoi(height))) {
//					if (tilesVec[i - 1][j].mine == true) {
//						count += 1;
//					}
//					if (checkingCol(j - 1, stoi(width))) {
//						minus = true;
//						if (tilesVec[i - 1][j - 1].mine == true) {
//							count += 1;
//						}
//					}
//					if (checkingCol(j + 1, stoi(width))) {
//						add = true;
//						if (tilesVec[i - 1][j + 1].mine == true) {
//							count += 1;
//						}
//					}
//				}
//				if (minus) {
//					if (tilesVec[i][j - 1].mine == true) {
//						count += 1;
//					}
//				}
//				if (add) {
//					if (tilesVec[i][j + 1].mine == true) {
//						count += 1;
//					}
//				}
//				if (checkingRow(i + 1, stoi(height))) {
//					if (tilesVec[i + 1][j].mine == true) {
//						count += 1;
//					}
//					if (checkingCol(j - 1, stoi(width))) {
//						minus = true;
//						if (tilesVec[i + 1][j - 1].mine == true) {
//							count += 1;
//						}
//					}
//					if (checkingCol(j + 1, stoi(width))) {
//						add = true;
//						if (tilesVec[i + 1][j + 1].mine == true) {
//							count += 1;
//						}
//					}
//				}
//			}
//			tilesVec[i][j].adjacentTiles = count;
//		}
//	}
//
//	currMin = 0;
//	currSec = 0;
//	min1num = 0;
//	min2num = 0;
//	sec1num = 0;
//	sec2num = 0;
//	debugBut = false;
//	ppBut = true;
//
//    //return board;
//}

//sf::RectangleShape setRectangle(sf::Vector2f size, float positionx, float positiony, float originx, float originy, sf::Color color) {
//    sf::RectangleShape rect;
//    rect.setSize(size);
//    rect.setPosition(positionx, positiony);
//    rect.setOrigin(originx, originy);
//    rect.setFillColor(color);
//    return rect;
//}

//sf::Text setText(string fontFile, string message, unsigned int size, sf::Color color) {
//    sf::Text text;
//    sf::Font font;
//    if (font.loadFromFile(fontFile)) {
//        text.setFont(font);
//    }
//    text.setString(message);
//    text.setCharacterSize(size);
//    text.setFillColor(color);
//
//    return text;
//}

//sf::Sprite makeSprite(string file, float x, float y) {
//    sf::Sprite sp;
//    sf::Texture textureFace;
//    textureFace.loadFromFile(file);
//    sp.setTexture(textureFace);
//    sp.setPosition(x, y);
//    return sp;
//}

Tile::Tile(Resources &resources, bool flag, bool mine, bool reveal, float positionx, float positiony, int adjacentTiles, bool clicked) {
    //sf::Texture tileTexture;
    //tileTexture.loadFromFile(file);
    //this->resources = resources;
    //this->tileSprite.setTexture(this->resources.hiddenTile);


    this->tileSprite.setTexture(resources.hiddenTile);
    this->tileSprite.setPosition(positionx, positiony);

    this->flag = flag;
    this->mine = mine;
	this->reveal = reveal;
	this->adjacentTiles = adjacentTiles;
	this->clicked = clicked;

	this->baseSprite.setTexture(resources.none);
	this->baseSprite.setPosition(positionx, positiony);

	this->flagSprite.setTexture(resources.flag);
	this->flagSprite.setPosition(positionx, positiony);

	this->mineSprite.setTexture(resources.mine);
	this->mineSprite.setPosition(positionx, positiony);

	this->hideSprite.setTexture(resources.hiddenTile);
	this->hideSprite.setPosition(positionx, positiony);

}

void Tile::minePlace(Resources &resources) {
    this->tileSprite.setTexture(resources.mine);
	this->reveal = true;
}

void Tile::flagPlace(Resources& resources) {
    this->tileSprite.setTexture(resources.flag);
	cout << "flag lacking";
}

void Tile::hiddenPlace(Resources& resources) {
    this->tileSprite.setTexture(resources.hiddenTile);
}

void Tile::placeNum(Resources& resources, int num) {
    /*if (num != -1) {
        this->tileSprite.setTexture(resources.nums[num]);
    }*/
	if (num == 1) {
		this->tileSprite.setTexture(resources.one);
	}
	else if (num == 2) {
		this->tileSprite.setTexture(resources.two);
	}
	else if (num == 3) {
		this->tileSprite.setTexture(resources.three);
	}
	else if (num == 4) {
		this->tileSprite.setTexture(resources.four);
	}
	else if (num == 5) {
		this->tileSprite.setTexture(resources.five);
	}
	else if (num == 6) {
		this->tileSprite.setTexture(resources.six);
	}
	else if (num == 7) {
		this->tileSprite.setTexture(resources.seven);
	}
	else if (num == 8) {
		this->tileSprite.setTexture(resources.eigtht);
	}
	else if (num == 0) {
		this->tileSprite.setTexture(resources.none);
		//cout << "hi";
	}
}

bool checkWin(Board& board) {
	for (int i = 0; i < board.tilesVec.size(); i++) {
		for (int j = 0; j < board.tilesVec[i].size(); j++) {
			if (board.tilesVec[i][j].mine == false) {
				if (board.tilesVec[i][j].reveal == false) {
					return false;
				}
			}
		}
	}
	return true;
}

void checkTile(int i, int j, Board &board, string height, string width, Resources &resources) {
	bool minus = false;
	bool add = false;
	/*if (board.tilesVec[i][j].reveal == false) {
		board.tilesVec[i][j].placeNum(resources, board.tilesVec[i][j].adjacentTiles);
		board.tilesVec[i][j].reveal = true;
	}*/


	if (checkingRow(i - 1, stoi(height))) {
		if (board.tilesVec[i - 1][j].mine == false && board.tilesVec[i - 1][j].reveal == false && board.tilesVec[i - 1][j].flag == false) {
			board.tilesVec[i - 1][j].placeNum(resources, board.tilesVec[i - 1][j].adjacentTiles);
			board.tilesVec[i - 1][j].reveal = true;
			board.tilesVec[i - 1][j].clicked = false;
			if (board.tilesVec[i-1][j].adjacentTiles == 0) {
				checkTile(i - 1, j, board, height, width, resources);
			}
		}
		if (checkingCol(j - 1, stoi(width))) {
			if (board.tilesVec[i - 1][j - 1].mine == false && board.tilesVec[i - 1][j - 1].reveal == false && board.tilesVec[i - 1][j - 1].flag == false) {
				board.tilesVec[i - 1][j - 1].placeNum(resources, board.tilesVec[i - 1][j-1].adjacentTiles);
				board.tilesVec[i - 1][j - 1].reveal = true;
				board.tilesVec[i - 1][j - 1].clicked = false;
				if (board.tilesVec[i - 1][j - 1].adjacentTiles == 0) {
					checkTile(i - 1, j - 1, board, height, width, resources);
				}
			}
		}
		if (checkingCol(j + 1, stoi(width))) {
			if (board.tilesVec[i - 1][j + 1].mine == false && board.tilesVec[i - 1][j + 1].reveal == false && board.tilesVec[i - 1][j + 1].flag == false) {
				board.tilesVec[i - 1][j + 1].placeNum(resources, board.tilesVec[i - 1][j + 1].adjacentTiles);
				board.tilesVec[i - 1][j + 1].reveal = true;
				board.tilesVec[i - 1][j + 1].clicked = false;
				if (board.tilesVec[i - 1][j + 1].adjacentTiles == 0) {
					checkTile(i - 1, j + 1, board, height, width, resources);
				}
			}
		}
	}
	if (checkingCol(j - 1, stoi(width))) {
		if (board.tilesVec[i][j - 1].mine == false && board.tilesVec[i][j - 1].reveal == false && board.tilesVec[i][j - 1].flag == false) {
			board.tilesVec[i][j - 1].placeNum(resources, board.tilesVec[i][j - 1].adjacentTiles);
			board.tilesVec[i][j - 1].reveal = true;
			board.tilesVec[i][j - 1].clicked = false;
			if (board.tilesVec[i][j - 1].adjacentTiles == 0) {
				checkTile(i, j - 1, board, height, width, resources);
			}
		}
	}
	if (checkingCol(j + 1, stoi(width))) {
		if (board.tilesVec[i][j + 1].mine == false && board.tilesVec[i][j + 1].reveal == false && board.tilesVec[i][j + 1].flag == false) {
			board.tilesVec[i][j + 1].placeNum(resources, board.tilesVec[i][j + 1].adjacentTiles);
			board.tilesVec[i][j + 1].reveal = true;
			board.tilesVec[i][j + 1].clicked = false;
			if (board.tilesVec[i][j + 1].adjacentTiles == 0) {
				checkTile(i, j + 1, board, height, width, resources);
			}
		}
	}

	if (checkingRow(i + 1, stoi(height))) {
		if (board.tilesVec[i + 1][j].mine == false && board.tilesVec[i + 1][j].reveal == false && board.tilesVec[i + 1][j].flag == false) {
			board.tilesVec[i + 1][j].placeNum(resources, board.tilesVec[i + 1][j].adjacentTiles);
			board.tilesVec[i + 1][j].reveal = true;
			board.tilesVec[i + 1][j].clicked = false;
			if (board.tilesVec[i + 1][j].adjacentTiles == 0) {
				checkTile(i + 1, j, board, height, width, resources);
			}
		}
		if (checkingCol(j - 1, stoi(width))) {
			if (board.tilesVec[i + 1][j - 1].mine == false && board.tilesVec[i + 1][j - 1].reveal == false && board.tilesVec[i + 1][j - 1].flag == false) {
				board.tilesVec[i + 1][j - 1].placeNum(resources, board.tilesVec[i + 1][j - 1].adjacentTiles);
				board.tilesVec[i + 1][j - 1].reveal = true;
				board.tilesVec[i + 1][j - 1].clicked = false;
				if (board.tilesVec[i + 1][j - 1].adjacentTiles == 0) {
					checkTile(i + 1, j - 1, board, height, width, resources);
				}
			}
		}
		if (checkingCol(j + 1, stoi(width))) {
			if (board.tilesVec[i + 1][j + 1].mine == false && board.tilesVec[i + 1][j + 1].reveal == false && board.tilesVec[i + 1][j + 1].flag == false) {
				board.tilesVec[i + 1][j + 1].placeNum(resources, board.tilesVec[i + 1][j + 1].adjacentTiles);
				board.tilesVec[i + 1][j + 1].reveal = true;
				board.tilesVec[i + 1][j + 1].clicked = false;
				if (board.tilesVec[i + 1][j + 1].adjacentTiles == 0) {
					checkTile(i + 1, j + 1, board, height, width, resources);
				}
			}
		}
	}
}

Resources::Resources() {
    this->hiddenTile.loadFromFile("files/images/tile_hidden.png");
    this->mine.loadFromFile("files/images/mine.png");
    this->flag.loadFromFile("files/images/flag.png");

    this->none.loadFromFile("files/images/tile_revealed.png");
    this->one.loadFromFile("files/images/number_1.png");
    this->two.loadFromFile("files/images/number_2.png");
    this->three.loadFromFile("files/images/number_3.png");
    this->four.loadFromFile("files/images/number_4.png");
    this->five.loadFromFile("files/images/number_5.png");
    this->six.loadFromFile("files/images/number_6.png");
    this->seven.loadFromFile("files/images/number_7.png");
    this->eigtht.loadFromFile("files/images/number_8.png");
    //this->nums = {none, one, two, three, four, five, six, seven, eigtht};
}
