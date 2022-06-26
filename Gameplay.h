#pragma once
#include "GameObject.h"
#include "Pacman.h"
#include "Fruit.h"
#include "Ghost.h"

class Gameplay
{
	int currGamePoints = 0;
	int remainingLives = 3;

public:
	void init();
	int run(char level, string mapName, int* remLives);
	void pauseGame()const;
	void getFilesFromDirectory(vector<string>& tmparr);
	void showPacmanLogo()const;
	void showMenu()const;
	void printKeys()const;
	string playSpecificMap();
	void resetGhosts(Board& b, vector<Point>locations, GameObject* objectsArr[6]);
};

