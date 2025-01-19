#include <conio.h> // for kbhit+getch
#include <iostream>
#include <windows.h> // for Sleep and colors
#include "general.h"
#include "gameboard.h"
#include "thegame.h"
#include "blocks.h"


int main()
{
	srand((int)time(NULL));//initializing randomizer 

	int mode;//game mode (human vs human, computer vs computer, human vs computer)

	thegame game;

	bool newgame = true;// the first game is a new game always

	bool exit_prog = false;//exit programm flag

	while (!exit_prog)
	{
		exit_prog = game.startscreen(&newgame,&mode);
	}
}
