#include "io_utils.h"

void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout << flush;
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

void hideCursor()
{
	HANDLE myconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CURSOR;
	CURSOR.dwSize = 1;
	CURSOR.bVisible = FALSE;
	SetConsoleCursorInfo(myconsole, &CURSOR);//second argument need pointer
}

void clear_screen()
{
	system("cls"); 
}

void winPage()
{
	clear_screen();
	cout << "_____________________" << endl;
	cout << "     ,--.    ,--.    |" << endl;
	cout << "    |oo  |    \\  `.  |" << endl;
	cout << "o  o|~~  |    /   ;  |" << endl;
	cout << "    |/\\/\\|   '._,'   |" << endl;
	cout << "_____________________|" << endl;


	cout << "You -WON- the the current map! Congratulations!" << endl;
	cout << "Moving to next map (if any). " << endl;
	pressAnyKeyToContinue();
}

void pressAnyKeyToContinue()
{
	std::cout << "Press any key to continue. " << endl;
	char key = 0;
	while (key == 0)
		if (_kbhit())
			key = _getch();
	clear_screen();
}

void losePage()
{
	clear_screen();
	cout << "_______________________________" << endl;
	cout << "     .-.   .-.     .--.        |" << endl;
	cout << "    | OO| | OO|   / _.-'       |" << endl;
	cout << "    |   | |   |   \\  '-.       |" << endl;
	cout << "    '^^^' '^^^'    '--'        |" << endl;
	cout << "_______________________________|" << endl;


	std::cout << "A ghost ate pacman! That's not allowed! You lost one life!" << endl;
	pressAnyKeyToContinue();
}

void lostAllGames()
{
	clear_screen();
	cout << "   _______    _______    __     __    _______         _______   _            _   _______    _______     " << endl;
	cout << "  |  _____|  |  ___  |  |  \\   /  |  |  _____|       |  ___  | \\ \\          / / |  _____|  |  ____ \\  " << endl;
	cout << "  | |        | |   | |  |   \\_/   |  | |             | |   | |  \\ \\        / /  | |        | |____||   " << endl;
	cout << "  | |  ___   | |___| |  | |\\   /| |  | |_____        | |   | |   \\ \\      / /   | |_____   | |_____/   " << endl;
	cout << "  | | |_  |  |  ___  |  | | \\_/ | |  |  _____|       | |   | |    \\ \\    / /    |  _____|  | |\\ \\    " << endl;
	cout << "  | |   | |  | |   | |  | |     | |  | |             | |   | |     \\ \\  / /     | |        | | \\ \\  " << endl;
	cout << "  | |___| |  | |   | |  | |     | |  | |_____        | |___| |      \\ \\/ /      | |_____   | |  \\ \\ " << endl;
	cout << "  |_______|  |_|   |_|  |_|     |_|  |_______|       |_______|       \\__/       |_______|  |_|   \\_\\ " << endl << endl;
	cout << "You lost the whole game! You had 1 life remaining, but ghost ate you! " << endl;
	pressAnyKeyToContinue();
}

void winPageOfAllMaps()
{
	clear_screen();
	cout << "  __        __   _______    _     _             _                  _    _______    __      _        " << endl;
	cout << "  \\ \\      / /  |  ___  |  | |   | |           \\ \\                / /  |  ___  |  |  \\    | |  " << endl;
	cout << "   \\ \\    / /   | |   | |  | |   | |            \\ \\              / /   | |   | |  |   \\   | |  " << endl;
	cout << "    \\ \\  / /    | |   | |  | |   | |             \\ \\            / /    | |   | |  | |\\ \\  | | " << endl;
	cout << "     \\ \\/ /     | |   | |  | |   | |              \\ \\    /\\    / /     | |   | |  | | \\ \\ | |" << endl;
	cout << "      |  |      | |   | |  | |   | |               \\ \\  //\\\\  / /      | |   | |  | |  \\ \\| | " << endl;
	cout << "      |  |      | |___| |  | |___| |                \\ \\//  \\\\/ /       | |___| |  | |   \\ \\ | " << endl;
	cout << "      |__|      |_______|  |_______|                 \\_/    \\_/        |_______|  |_|    \\__|    " << endl << endl;

	cout << "You won the whole maps!! Don't forget doing a selfie with this message !!! " << endl;
	pressAnyKeyToContinue();
}