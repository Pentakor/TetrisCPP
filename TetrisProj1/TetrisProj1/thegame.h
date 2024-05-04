#ifndef __THEGAME_H
#define __THEGAME_H
#include "gameboard.h"
#include "gameboard_bot.h"
#include "blocks.h"

class thegame
{
	//values for gotoxy function
	static const int ZERO = 0;
	static const int C1 = 1;
	static const int C2 = 2;
	static const int C3 = 3;
	static const int C4 = 4;
	static const int C5 = 5;

	static const int C10 = 10;
	static const int C11 = 11;
	static const int C12 = 12;
	static const int C13 = 13;
	static const int C18 = 18;

	static const int C20 = 20;
	static const int C26 = 26;
	static const int C30 = 30;
	static const int C40 = 40;
	static const int C50 = 50;
	static const int C55 = 55;
	static const int C56 = 56;
	static const int C57 = 57;

	//values for game mode
	static const int HVH = 0;//HUMAN VS HUMAN
	static const int HVC = 1;//HUMAN VS COMPUTER
	static const int CVC = 2;//COMPUTER VS COMPUTER

	static const int BOMB = 7;//bomb shape value

	//values for sleep function
	static const int B_SLEEP = 500;//long sleep
	static const int S_SLEEP = 50;//short sleep

	static const int P1 = 1;//player 1
	static const int P2 = 2;//player 2
	static const int DRAW = 3;

	gameboard_bot board1_save_bot;//save during pause of player 1 board

	int p1_score;//save player 1 score

	gameboard_bot board2_save_bot;//save during pause of player 1 board

	int p2_score;//save player 2 score

	int botlvl = 3;//computer level

	static const int ESC = 27;//esc button ascii code

	static const int ENTER = 13;//enter buttom ascii code

	static const int GAME_WIDTH = 12;//game board width cells amount

	void gamechooser(bool* newgame, int* mode);//choose the game mode and statrting the game
	void instructions();//showing the instructions and settings screen. in this screen the user can chose computer lvl
	void wasted_screen(int p);//showing the GAME OVER screen
	bool limit_check_bot(const gameboard_bot* b);//checking if the blocks reached the high limit
	bool char_check(char ch);//checking if the char is valid
	void game_process(bool* newgame, int* mode);//function that conains the game proccess
	void game_init_bots(char* pressed_btn, gameboard_bot* board1, gameboard_bot* board2, blocks* current_block1, blocks* current_block2);//initializing the game variabels
	void print_score1(int score);//printing the score of player one
	void print_score2(int score);//printing the score of player two
	void who_lost_bot(const gameboard_bot* board1, const gameboard_bot* board2, int score1, int score2);//checking wich one of the players lost. calling wasted screen function according to it

	//setting up new current blocks for the players, if the player is a computer setting the route for the block
	void newblocks(gameboard_bot* board1, gameboard_bot* board2, blocks* current_block1, blocks* current_block2, int* score1, int* score2, int mode, combination* best1, combination* best2);

	//function for the game process of  human vs human. 
	void hvh_mode(gameboard_bot* board1, gameboard_bot* board2, blocks* current_block1, blocks* current_block2, int score1, int score2, char* pressed_btn, bool* esc_flag);

	//function for the game process of  human vs computer.
	void hvc_mode(gameboard_bot* board1, gameboard_bot* board2, blocks* current_block1, blocks* current_block2, int score1, int score2, char* pressed_btn, bool* esc_flag, combination* best2);

	////function for the game process of  computer vs computer.
	void cvc_mode(gameboard_bot* board1, gameboard_bot* board2, blocks* current_block1, blocks* current_block2, int score1, int score2, char* pressed_btn, bool* esc_flag, combination* best1, combination* best2);
public:
	bool startscreen(bool* newgame, int* mode);//printing start screen to the console
};
#endif
