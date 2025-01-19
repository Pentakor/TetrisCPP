#include "thegame.h"
#include "gameboard.h"
#include <iostream>
#include <windows.h>
#include "general.h"
#include <conio.h>
#include "blocks.h"
#include "gameboard_bot.h"
#include "combination.h"

bool thegame::startscreen(bool *newgame,int * mode)
{
	
	gotoxy(C50,C26);
	std::cout << "BY I.S & D.W";
	gotoxy(C55, C10);
	std::cout << "PRESS ENTER TO START NEW GAME\n";
	gotoxy(C50, C11);
	std::cout << "    I TO SEE INSTRUCTIONS & SETTINGS\n";
	if (!*newgame)
	{
		gotoxy(C55, C12);
		std::cout << "   U TO RESUME PAUSED GAME\n";
	}

	gotoxy(C57, C13);
	std::cout << "    ESC TO EXIT GAME\n";
	gotoxy(ZERO,ZERO);
	std::cout <<
		" __          ________ _      _____ ____  __  __ ______   _______ ____  \n"
		" \\ \\        / /  ____| |    / ____/ __ \\|  \\/  |  ____| |__   __/ __ \\ \n"
		"  \\ \\  /\\  / /| |__  | |   | |   | |  | | \\  / | |__       | | | |  | |\n"
		"   \\ \\/  \\/ / |  __| | |   | |   | |  | | |\\/| |  __|      | | | |  | |\n"
		"    \\  /\\  /  | |____| |___| |___| |__| | |  | | |____     | | | |__| |\n"
		"     \\/  \\/   |______|______\\_____\\____/|_|  |_|______|    |_|  \\____/ \n"
		<< std::endl;
	std::cout <<
		"  _______ ______ _______ _____  _____  _____  \n"
		" |__   __|  ____|__   __|  __ \\|_   _|/ ____| \n"
		"    | |  | |__     | |  | |__) | | | | (___   \n"
		"    | |  |  __|    | |  |  _  /  | |  \\___ \\  \n"
		"    | |  | |____   | |  | | \\ \\ _| |_ ____) | \n"
		"    |_|  |______|  |_|  |_|  \\_\\_____|_____/  \n"
		<< std::endl;

	
	char btn = 'o';
	if (!*newgame)//with option to continue paused game
	{
		while (((btn != ENTER && btn != 'i') && btn != 'u') && btn != ESC)//wating for button to choose menu option
		{
			btn = _getch();
		}
	}
	else//without the option to continue paused game
	{
		while ((btn != ENTER && btn != 'i') && btn != ESC)//wating for button to choose menu option
		{
			btn = _getch();
		}
	}
	clrscr();
	if (btn == ENTER)//new game selected
	{
		*newgame = true;//new game flag change, //newgame value true/false indicates if new game should start or load the last game
		gamechooser(newgame,mode);
	}
	if (!*newgame)
	{
		if (btn == 'u')//resume paused game
		{
			game_process(newgame,mode);
		}
	}
	if(btn=='i')//call instructions and settings menu
	{
		instructions();
	}	
	if (btn == ESC)
		return true;
	return false;
}
void thegame::gamechooser(bool* newgame, int* mode)
{
	char btn = 'x';
	gotoxy(C40, C10);
	std::cout << "   PRESS A FOR HUMAN VS HUMAN";
	gotoxy(C40, C11);
	std::cout << "  PRESS B FOR HUMAN VS COMPUTER";
	gotoxy(C40, C12);
	std::cout << "PRESS C FOR COMPUTER VS COMPUTER";
	gotoxy(C40, C13);
	std::cout << "     PRESS ESC TO GET BACK";
	gotoxy(C40, C18);
	std::cout << "      COMPUTER LEVEL: "<<botlvl;
	while (((btn != 'a' && btn != 'b') && btn != 'c')&&btn!=ESC)//wating for button to choose menu option
	{
		btn = _getch();
	}
	if (btn == 'a')
	{
		*mode = HVH; //humav vs human mode flag
		clrscr();
		game_process(newgame, mode);//load game
	}
	if(btn == 'c')
	{	
		*mode = CVC;//computer vs computer mode flag
		clrscr();
		game_process(newgame, mode);//load game
	}
	if (btn == 'b')
	{
		*mode = HVC;//human vs computer mode flag
		clrscr();
		game_process(newgame, mode);//load game
	}
	
	clrscr();
}

void thegame::game_init_bots(char* pressed_btn, gameboard_bot* board1, gameboard_bot* board2, blocks* current_block1, blocks* current_block2)
{
	board1->initializeboard();
	board1->printboard1();
	current_block1->initialize();
	board1->printblock(current_block1);

	board1->setlvl(botlvl);
	board2->setlvl(botlvl);

	board2->initializeboard();
	board2->printboard2();
	current_block2->initialize();
	board2->printblock(current_block2);
	Sleep(500);
	clrscr();

	board1->printboard1();
	board2->printboard2();
	*pressed_btn = 'q';//setting the value to not be NULL

	
}

bool thegame::limit_check_bot(const gameboard_bot* b)
{
	for (int i = 0; i < GAME_WIDTH; i++)
	{
		if (b->get_board_value(0, i) == '0')
			return true;
	}
	return false;
}
void thegame::wasted_screen(int p)
{
	gotoxy(C30, ZERO);
	std::cout << "   _____          __  __ ______    ______      ________ _____  \n";
	gotoxy(C30, C1);
	std::cout << "  / ____|   /\\   |  \\/  |  ____|  / __ \\ \\    / /  ____|  __ \\ \n";
	gotoxy(C30, C2);
	std::cout << " | |  __   /  \\  | \\  / | |__    | |  | \\ \\  / /| |__  | |__) |\n";
	gotoxy(C30, C3);
	std::cout << " | | |_ | / /\\ \\ | |\\/| |  __|   | |  | |\\ \\/ / |  __| |  _  / \n";
	gotoxy(C30, C4);
	std::cout << " | |__| |/ ____ \\| |  | | |____  | |__| | \\  /  | |____| | \\ \\ \n";
	gotoxy(C30, C5);
	std::cout << "  \\_____/_/    \\_\\_|  |_|______|  \\____/   \\/   |______|_|  \\_\\\n";
	gotoxy(C40, C18);
	if (p == P1)//player 1 lost
	{
		std::cout << "PLAYER 2 WON! ";
	}
	else if (p==P2)//player 2 lost
	{
		std::cout << "PLAYER 1 WON! ";
	}
	else
		std::cout << "DRAW! ";
	std::cout << "PRESS ESC TO CONTINUE";
	while (_getch() != ESC)
	{

	}
	clrscr();
	
}
void thegame::print_score1(int score)
{
	gotoxy(ZERO,C20);
	std::cout << "     P1 SCORE: " << score;
	gotoxy(ZERO, ZERO);
}
void thegame::print_score2(int score)
{
	gotoxy(C30, C20);
	std::cout << "     P2 SCORE: " << score;
	gotoxy(ZERO, ZERO);
}

void thegame::game_process(bool *newgame,int* mode)
{
	bool esc_flag = false;//indicate if client pressed escape game button
	char pressed_btn;
	gameboard_bot board1, board2;
	blocks current_block1, current_block2;
	int score1 = 0;
	int score2 = 0;
	bool lost = false;
	combination best1, best2;
	game_init_bots(&pressed_btn, &board1, &board2, &current_block1, &current_block2);
	if (!*newgame)//if the game is not a new game load the boards and scores from save
	{
		board1 = board1_save_bot;
		score1 = p1_score;

		board2 = board2_save_bot;
		score2 = p2_score;
	}

	//before first itteretion calculate the best routes for the computer players
	if (*mode != HVH)
		best2 = board2.calculatebestroute(&current_block2);
	if (*mode == CVC)
		best1 = board1.calculatebestroute(&current_block1);

	while (!esc_flag)//the game runs untill escape button is pressed
	{
		print_score1(score1);
		print_score2(score2);
		if (limit_check_bot(&board1) == 0 && limit_check_bot(&board2) == 0)//the game runs until no one of the players is won(by second player loosing)
		{
				while (!board1.touchground(&current_block1)&& !board2.touchground(&current_block2)&&!esc_flag)//while no one of the current blocks  is got to the ground
				{

					if (*mode == HVH)
						hvh_mode(&board1, &board2, &current_block1, &current_block2, score1, score2, &pressed_btn, &esc_flag);
					else if (*mode == CVC)
						cvc_mode(&board1, &board2, &current_block1, &current_block2, score1, score2, &pressed_btn, &esc_flag, &best1, &best2);
					else
						hvc_mode(&board1, &board2, &current_block1, &current_block2, score1, score2, &pressed_btn, &esc_flag, &best2);

					//each time every current block is going one step down
					board1.clrblock_fromboard(&current_block1);
					current_block1.movedown(board1.get_board());
					board1.printblock(&current_block1);

					board2.clrblock_fromboard(&current_block2);
					current_block2.movedown(board2.get_board());
					board2.printblock(&current_block2);

					clrscr();
					print_score1(score1);
					board1.printboard1();

					print_score2(score2);
					board2.printboard2();
				}
				//itteration ended. load new blocks where appropriate.
				newblocks(&board1, &board2, &current_block1, &current_block2, &score1, &score2,*mode,&best1,&best2);
		}
		else//someone lost
		{
			who_lost_bot(&board1,&board2,score1,score2);
			lost = true;
			esc_flag = true;
		}
	}
	board1.clr_active_block();
	board2.clr_active_block();

	//save the data of the game
	board1_save_bot = board1;
	board2_save_bot = board2;
	p1_score = score1;
	p2_score = score2;
	clrscr();
	if (!lost)
		*newgame = false;
	else
		*newgame = true;
}
void thegame::hvh_mode(gameboard_bot* board1, gameboard_bot* board2, blocks* current_block1, blocks* current_block2, int score1, int score2, char* pressed_btn,bool * esc_flag)
{
	Sleep(B_SLEEP);
	while (_kbhit() != 0)
	{
		Sleep(S_SLEEP);
		*pressed_btn = _getch();
		if (*pressed_btn == ESC)//escape button press
			*esc_flag = true;
		else //make move
		{
			board1->move1(*pressed_btn, current_block1);
			board1->printblock(current_block1);

			board2->move2(*pressed_btn, current_block2);
			board2->printblock(current_block2);

			clrscr();

			print_score1(score1);
			board1->printboard1();

			print_score2(score2);
			board2->printboard2();
		}
	}
}

void thegame::hvc_mode(gameboard_bot* board1, gameboard_bot* board2, blocks* current_block1, blocks* current_block2, int score1, int score2, char* pressed_btn, bool* esc_flag,combination* best2)
{
	Sleep(B_SLEEP);
	//computer move:
	for (int i = 0; i < 2; i++)//to make the computer play more "humanly" and efficient two moves are allowed
	{
		Sleep(S_SLEEP);
		board2->clrblock_fromboard(current_block2);
		clrscr();
		board2->move(current_block2, best2);
		board2->printblock(current_block2);

		clrscr();

		print_score1(score1);
		board1->printboard1();

		print_score2(score2);
		board2->printboard2();
	}
	//human move:
	while (_kbhit() != 0)
	{
		Sleep(S_SLEEP);
		*pressed_btn = _getch();
		if (*pressed_btn == ESC)//escape button press
			*esc_flag = true;
		else //make move
		{
			board1->move1(*pressed_btn, current_block1);
			board1->printblock(current_block1);

			clrscr();

			print_score1(score1);
			board1->printboard1();

			print_score2(score2);
			board2->printboard2();
		}
	}
}

void thegame::cvc_mode(gameboard_bot* board1, gameboard_bot* board2, blocks* current_block1, blocks* current_block2, int score1, int score2, char* pressed_btn, bool* esc_flag,combination *best1, combination* best2)
{
	Sleep(B_SLEEP);
	if (_kbhit() != 0)
	{
		*pressed_btn = _getch();
	}
	if (*pressed_btn == ESC)//escape button press
		*esc_flag = true;
	else //make move
	{
		for (int i = 0; i < 2; i++)//to make the computer play more "humanly" and efficient two moves are allowed
		{
			Sleep(S_SLEEP);
			board1->clrblock_fromboard(current_block1);
			clrscr();
			board1->move(current_block1, best1);
			board1->printblock(current_block1);

			board2->clrblock_fromboard(current_block2);
			clrscr();
			board2->move(current_block2, best2);
			board2->printblock(current_block2);

			clrscr();

			print_score1(score1);
			board1->printboard1();

			print_score2(score2);
			board2->printboard2();
		}
	}
}
void thegame::who_lost_bot(const gameboard_bot* board1,const  gameboard_bot* board2, int score1, int score2)
{
	board1_save_bot.initializeboard();//if someone lost we want to clear the saves
	board2_save_bot.initializeboard();
	p1_score = 0;
	p2_score = 0;
	clrscr();
	if (limit_check_bot(board1) != 0 && limit_check_bot(board2) == 0)
	{
		wasted_screen(P1);//player 1 lost
	}
	else if (limit_check_bot(board1) == 0 && limit_check_bot(board2) != 0)
	{
		wasted_screen(P2);//player 2 lost
	}
	else
	{
		if (score1 > score2)
			wasted_screen(P2);//player 2 lost
		else if (score1 < score2)
			wasted_screen(P1);//player 1 lost
		else
			wasted_screen(DRAW);//draw
	}
}
bool thegame::char_check(char ch)
{
	if (ch == ESC || ch == 'w' || ch == 'a' || ch == 's' || ch == 'd' ||
		ch == 'x' || ch == 'i' || ch == 'j' || ch == 'k' || ch == 'l' || ch == 'm')
		return true;
	else
		return false;
}
void thegame::instructions()
{
	char btn = 'o';
	gotoxy(ZERO, ZERO);
	std::cout << "INSTRUCTIONS:\n\nPLAYER 1:\na-move left\nd-move right\nw-rotate anticlockwise\ns-rotate clockwise\nx-drop\n";
	std::cout << "\nPLAYER 2:\nj-move left\nl-move right\ni-rotate anticlockwise\nk-rotate clockwise\nm-drop\n";

	std::cout << "\nWHEN PLAYING AGAINST COMPUTER:\nplayer 1 - human\nplayer 2 - computer\n\nthere are 3 levels of computer\nchoose the level before starting the game\nby standard level is set to best\n";

	std::cout << "\nSETTINGS:\nenter 1 for novice lvl\nenter 2 for good lvl\nenter 3 for best lvl";
	std::cout << "\n\nPRESS ESC TO GO BACK TO MENU";
	gotoxy(C40, C26);
	std::cout << "CURRENT LVL SET TO: "<<botlvl;
	while (btn != ESC)
	{
		if (btn == '1')
		{
			botlvl = 1;
			gotoxy(C40, C26);
			std::cout << "CURRENT LVL SET TO: " << botlvl;
		}
		else if (btn == '2')
		{
			botlvl = 2;
			gotoxy(C40, C26);
			std::cout << "CURRENT LVL SET TO: " << botlvl;
		}
		else if (btn == '3')
		{
			botlvl = 3;
			gotoxy(C40, C26);
			std::cout << "CURRENT LVL SET TO: " << botlvl;
		}
		btn = _getch();
	}
	clrscr();
}
void thegame::newblocks(gameboard_bot * board1, gameboard_bot* board2,blocks * current_block1, blocks* current_block2,int * score1,int * score2,int mode, combination* best1, combination* best2)
{
	if (board1->touchground(current_block1))//if player 1 block touched ground reset his current block
	{
		if (current_block1->get_bshape() == BOMB)//if the blcok is bomb detonate it
		{
			board1->detonate(current_block1);
		}
		current_block1->initialize();
		board1->printblock(current_block1);

		*score1 += board1->clear_full_rows();//add to score if there is cleared row

		
		if (mode == CVC)//if the player is computer 
		{
			if (board1->shouldbe_rand())//check if the move should be random
			{
				*best1 = board1->calculaterandomrute();//make random route
			}
			else
			{
				*best1 = board1->calculatebestroute(current_block1);//make best route
			}
		}	
	}
	if (board2->touchground(current_block2))//if player 2 block touched ground reset his current block
	{
		if (current_block2->get_bshape() == BOMB)//if the blcok is bomb detonate it
		{
			board2->detonate(current_block2);
		}
		//if bot add line to call the calculating best route function of gameboard_bot
		current_block2->initialize();
		board2->printblock(current_block2);

		*score2 += board2->clear_full_rows();//add to score if there is cleared row

		if (mode != HVH)//if the player is computer 
		{
			if (board2->shouldbe_rand())//check if the move should be random
			{
				*best2 = board2->calculaterandomrute();//make random route
			}
			else
			{
				*best2 = board2->calculatebestroute(current_block2);//make best route
			}
		}
			
	}
	clrscr();
	print_score1(*score1);
	board1->printboard1();

	print_score2(*score2);
	board2->printboard2();
}