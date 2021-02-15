#ifndef BOARD_H
#define BOARD_H
class board {
	int board[8][8] = {
		{B,W,B,W,B,W,B,W},
		{W,B,W,B,W,B,W,B},
		{B,W,B,W,B,W,B,W},
		{W,B,W,B,W,B,W,B},
		{B,W,B,W,B,W,B,W},
		{W,B,W,B,W,B,W,B},
		{B,W,B,W,B,W,B,W},
		{W,B,W,B,W,B,W,B}
		};

public:
	/*all functions void functions until code is fully determined.*/
	bool setZpgame();
	bool setColor();
    bool zpgame;
    /*bool guardRails();*/
	void setValues(int b, int w,int x,int dir);
	 //returns first and color
	void display();
	void manualOverride(); //piece removal, for fixing board errors and for setup.
	bool isFull(int i, int j);
	//test for legality of move
	bool legal_move(int currentmove[], int i, int j, int Dir);
	bool legal_SEF(int i, int j, int Dir);
	void makeMove(int currentmove[], int playerColor);
	void unmakeMove(int currentmove[], int playerColor, int opColor);
	int calibrate(int i, int playerColor);
    int alphaBetaMinimax(int alpha, int beta, int level, int depth, int levelColor, bool maximizing);
    int SEF(int pass);
	void selection(int S);
	void displayMove();


	//RECORDS MOVES BESTMOVE HOLDS FIRST MOVE AND THEN ANY MOVE THAT IS BETTER.
	int bestmove[4];
	int playermove[4];

};

#endif // BOARD_H
