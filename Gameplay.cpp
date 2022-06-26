#include "Gameplay.h"
#define ESC 27
void Gameplay::init()
{
	hideCursor();
	bool runGame = true;
	while (runGame)
	{
		remainingLives = 3;
		clear_screen();
		showMenu();
		currGamePoints = 0;
		char key = 0;
		int choice = 0;
		vector<string>filesArr; // first, when starting the game, give me all screen files.
		getFilesFromDirectory(filesArr);
		do // press anything possible from main menu
		{
			if (_kbhit())
			{
				key = _getch();
				if (key == '1' || key == '8' || key == '9')
				{
					choice = key - 48;
				}
			}
		} while (key != '1' && key != '8' && key != '9');

		if (key == '1' && filesArr.size() == 0)
		{
			cout << "0 Maps found! Can't start any game! " << endl;
			pressAnyKeyToContinue();
		}
		else // there are screens to run. lets see what does the user want.
		{
			currGamePoints = 0;
			switch (choice)
			{
			case 1:
			{
				cout << "PRESS 1 TO PLAY IN NOVICE LEVEL" << endl << "PRESS 2 TO PLAY IN GOOD LEVEL" << endl << "PRESS 3 TO PLAY IN BEST LEVEL" << endl;
				cout << "PRESS 9 TO PLAY A SPECIFIC MAP" << endl;
				char ch = 2;
				do
				{
					if (_kbhit())
					{
						ch = _getch();
					}
				} while (ch != '1' && ch != '2' && ch != '3' && ch != '9');
				if (ch == '9')
				{
					string mapName = playSpecificMap();
					if (mapName == "-1")
					{
						cout << "You have entered illegal map name. Please try again. " << endl;
						pressAnyKeyToContinue();
						continue;
					}
					else
					{
						cout << "PRESS 1 TO PLAY IN NOVICE LEVEL" << endl << "PRESS 2 TO PLAY IN GOOD LEVEL" << endl << "PRESS 3 TO PLAY IN BEST LEVEL" << endl;
						char ch2 = 2;
						do
						{
							if (_kbhit())
							{
								ch2 = _getch();
							}
						} while (ch2 != '1' && ch2 != '2' && ch2 != '3');
						run(ch2, mapName, &remainingLives);
					}
				}
				else
				{
					for (int i = 0; i < filesArr.size(); i++)
					{
						int thisCurrentSingleGamePoints = run(ch, filesArr[i], &remainingLives);
						if (thisCurrentSingleGamePoints != -1) // if -1  so -----> we lost the game.
							currGamePoints = thisCurrentSingleGamePoints;
						else
						{
							currGamePoints = 0; 
							break;
						}
					}
					if (currGamePoints != 0)
					{
						winPageOfAllMaps();
					}
					currGamePoints = 0;
				}
				break;
			}
			case 8:
			{
				printKeys();
				clear_screen();
				break;
			}
			case 9:
			{
				clear_screen();
				cout << "Exiting game" << endl;
				exit(1);
			}
			}
		}
	}
}

// 1 EASY
// 2 MID
// 3 HARD
int Gameplay::run(char level, string mapName, int* remLives) // return 1 = continue to next map, 2 = lost game.
{
	Board b(mapName);
	b.setRemainingLives(*remLives);
	b.setBoardPoints(currGamePoints);
	GameObject* objectsArr[6];
	for (int i = 0; i < 6; i++)
		objectsArr[i] = nullptr;
	vector<Point> ghostsLocations = b.getGhostsVector();
	int j = 2;
	for (int k = 0; k < ghostsLocations.size(); k++)
	{
		Ghost* tmp = new Ghost(ghostsLocations[k]);
		objectsArr[j] = tmp;
		j++;
	}
	// [PACMAN,FRUIT,GHOST1,GHOST2,GHOST3,GHOST4]
	// IF SOME GHOSTS ARE NULL - "MOVE" WILL NOT WORK ON THEM.
	Pacman p(b.getPacmanStartingPoint());
	Fruit f;
	f.resetMovesCount();
	Direction dir = STAY;
	objectsArr[0] = &p;
	objectsArr[1] = &f;
	char key = 0;
	bool tmp = true;
	clear_screen();
	b.printBoard();
	while (tmp)
	{
		bool gameRun = true;
		do
		{
			if (_kbhit())
			{
				key = _getch();
				if (key == ESC)
				{
					pauseGame();
					clear_screen();
					b.printBoard();
				}
				if ((dir = p.getDirection(key)) != -1)
					p.setDirection(dir);
			}
			objectsArr[0]->move(b, dir); // pacman move
			if (objectsArr[0]->getPoint() == objectsArr[1]->getPoint()) // if pacman eats fruit
			{
				char currItem = f.getUnderFruit();
				b.addFruitPoints(f.getFruitNum());
				if (currItem == FOOD) 
					b.minusOneFood();
				b.setBoardItem(f.getPoint().getX(), f.getPoint().getY(), f.getUnderFruit());
				f.setUnderFruit(b.getBoardItem(f.getPoint().getX(), f.getPoint().getY()));
				f.resetPoint();
				f.resetMovesCount();
				Fruit::pacmanEatFruit();
			}
			int w = 2;
			for (int ww = 0; ww < ghostsLocations.size(); ww++) // if pacman eats ghost
			{
				if (((objectsArr[w] != nullptr)) && (objectsArr[0]->getPoint() == objectsArr[w]->getPoint()))
				{
					losePage();
					if (b.getRemainingLives() == 1)
					{
						lostAllGames();
						*remLives = 0;
						for (int k = 0; k < ghostsLocations.size(); k++)
						{
							delete objectsArr[k+2];
						}
						return -1;
					}
					else
					{
						b.minusOneLife();
						*remLives = *remLives - 1;
						resetGhosts(b, ghostsLocations, objectsArr);
						int pacmanEatenPointX = p.getPoint().getX();
						int pacmanEatenPointY = p.getPoint().getY();
						b.setBoardItem(pacmanEatenPointX, pacmanEatenPointY, SPACE);
						objectsArr[0]->resetPoint(b.getPacmanStartingPoint());
						p.setDirection(STAY);
						b.printBoard();
					}
				}
				w++;
			}
			b.printLegend();
			// ghost->move ++ check if pacman is eaten
			for (int k = 2; k < 6; k++)
			{
				if (objectsArr[k] != nullptr)
				{
					Ghost* tmp = dynamic_cast<Ghost*>(objectsArr[k]);
					switch (level)
					{
					case '1':
					{
						tmp->easyGhostMove(b, STAY);
						break;
					}
					case '2':
					{
					 tmp->midMove(b);
						break;
					}

					case '3':
					{
						Direction tmpDir;
						objectsArr[k]->move(b, STAY);
						break;
					}
					}
					if (tmp->getUnderGhost() == PACMAN)
					{
						losePage();
						clear_screen();
						if (b.getRemainingLives() == 1)
						{
							lostAllGames();
							*remLives = 0;
							for (int k = 0; k < ghostsLocations.size(); k++)
							{
								delete objectsArr[k + 2];
							}
							return -1;
						}
						else
						{
							b.minusOneLife();
							*remLives = *remLives - 1;
							int pacmanEatenPointX = p.getPoint().getX();
							int pacmanEatenPointY = p.getPoint().getY();
							resetGhosts(b, ghostsLocations, objectsArr);
							b.setBoardItem(pacmanEatenPointX, pacmanEatenPointY, SPACE);
							objectsArr[0]->resetPoint(b.getPacmanStartingPoint());
							p.setDirection(STAY);
							if(f.getMovesCount() >= 20)
								b.setBoardItem(f.getPoint().getX(), f.getPoint().getY(), f.getUnderFruit());
							f.resetPoint();
							f.resetMovesCount();
							char item = b.getBoardItem(0, 0);
							f.setUnderFruit(item);
							k = 6;
							clear_screen();
							b.printBoard();
						}
					}
				}
			}

			// fruit->move
			Direction tmpDir = objectsArr[1]->getDir();
			objectsArr[1]->move(b, tmpDir);
			if (f.getUnderFruit() == PACMAN)
			{
				b.addFruitPoints(f.getFruitNum());
				int currX = f.getPoint().getX();
				int currY = f.getPoint().getY();
				b.setBoardItem(currX, currY, PACMAN);
				p.getPoint().draw(PACMAN);
				f.setUnderFruit(-1);
				f.resetPoint();
				f.resetMovesCount();
				Fruit::pacmanEatFruit();
			}
			if (b.getCurrFood() == 0)
			{
				for (int k = 0; k < ghostsLocations.size(); k++)
				{
					delete objectsArr[k + 2];
				}
				winPage();
				gameRun = false;
			}
			Sleep(134);
		} while (key != 8 && gameRun); // 8 = backspace
		tmp = false;
	}
	if (b.getCurrFood() == 0)
	{
		return b.getBoardPoints();
	}
	return -1;
}

void Gameplay::pauseGame()const
{
	clear_screen();
	gotoxy(0, 8);
	cout << "The game is paused. Please press ESC again to continue. ";
	char key = 0;
	do
	{
		if (_kbhit())
		{
			key = _getch();
			if (key == ESC)
				return;
		}
	} while (key != ESC);
}

void Gameplay::getFilesFromDirectory(vector<string>& tmparr)
{
	string tmp;
	for (const auto& i : std::filesystem::directory_iterator(std::filesystem::current_path()))
	{
		tmp = i.path().filename().u8string();
		if (tmp.size() > 7 && tmp.size() - 7 == tmp.rfind(".screen"))
			tmparr.push_back(tmp);
	}
}

void Gameplay::showPacmanLogo()const
{
	cout << "   _______    _______    _______    __     __    _______    __      _      " << endl;
	cout << "  |  ___  |  |  ___  |  |  _____|  |  \\   /  |  |  ___  |  |  \\    | |     " << endl;
	cout << "  | |   | |  | |   | |  | |        |   \\_/   |  | |   | |  |   \\   | |     " << endl;
	cout << "  | |___| |  | |___| |  | |        | |\\   /| |  | |___| |  | |\\ \\  | |     " << endl;
	cout << "  |  _____|  |  ___  |  | |        | | \\_/ | |  |  ___  |  | | \\ \\ | |     " << endl;
	cout << "  | |        | |   | |  | |        | |     | |  | |   | |  | |  \\ \\| |     " << endl;
	cout << "  | |        | |   | |  | |_____   | |     | |  | |   | |  | |   \\ \\ |     " << endl;
	cout << "  |_|        |_|   |_|  |_______|  |_|     |_|  |_|   |_|  |_|    \\__|     " << endl << endl;
}

void Gameplay::showMenu()const
{
	showPacmanLogo();
	cout << "Welcome to Pacman! Please choose your choice:" << endl;
	cout << "1. Start a new game. " << endl;
	cout << "8. Present instructions and keys. " << endl;
	cout << "9. Exit.  " << endl << endl;
}


void Gameplay::printKeys()const
{
	clear_screen();
	cout << "Instructions: " << endl;
	cout << "You control Pac-Man, who must eat all the dots inside an enclosed maze while avoiding two ghosts." << endl;
	cout << "Keys:" << endl;
	cout << "LEFT - A" << endl << "RIGHT - D" << endl << "UP - W" << endl << "DOWN - X" << endl << "STAY - S" << endl;
	cout << "THE GAME HAS 3 LEVELS, SO CHOOSE WISELY! " << endl << "BEST - THE GHOSTS TRY TO CHASE THE PACMAN!" <<
		endl << "GOOD - THE GHOSTS TRY CHASE PACMAN, BUT CHANGE MOVES EVERY 20 STEPS!" << endl << "NOVICE - NO SPECIAL MOVEMENT THAT LETS THE GHOSTS CHASE PACMAN!" << endl;
	pressAnyKeyToContinue();
}

string Gameplay::playSpecificMap()
{
	clear_screen();
	cout << "Please enter the name of the map you want to play (CASE SENSITIVE!!): ";
	string t;
	cin >> t;
	string tmp;
	for (const auto& i : std::filesystem::directory_iterator(std::filesystem::current_path()))
	{
		tmp = i.path().filename().u8string();
		if (tmp.size() > 7 && tmp.size() - 7 == tmp.rfind(".screen"))
			if (strcmp(tmp.c_str(), t.c_str()) == 0)
				return t.c_str();
	}
	return "-1";
}

void Gameplay::resetGhosts(Board& b, vector<Point>locations, GameObject* objectsArr[6])
{
	int aa = 2;
	for (int cc = 0; cc < locations.size(); cc++)
	{
		Ghost* tmp = dynamic_cast<Ghost*>(objectsArr[aa]);
		if (tmp != nullptr)
		{
			int x = tmp->getPoint().getX();
			int y = tmp->getPoint().getY();
			if (tmp->getUnderGhost() != PACMAN)
				b.setBoardItem(x, y, tmp->getUnderGhost());
			else
				b.setBoardItem(x, y, SPACE); // redundant -- pacman alrdy does this
			tmp->resetPoint(locations[cc]);

			char newUnderGhost = b.getBoardItem(locations[cc].getX(), locations[cc].getY());
			tmp->setUnderGhost(newUnderGhost);
		}
		aa++;
	}
}

