#ifndef BOARD_H
#define BOARD_H


class board {
    public:
    //records best value, used for parallel root
    int bval;
    //2D array, Black and white pieces value B= 2 and W= 1 respectively
    //empty spaces will be treated as zeros.
	int objBoard[8][8] = {
		{B,W,B,W,B,W,B,W},
		{W,B,W,B,W,B,W,B},
		{B,W,B,W,B,W,B,W},
		{W,B,W,B,W,B,W,B},
		{B,W,B,W,B,W,B,W},
		{W,B,W,B,W,B,W,B},
		{B,W,B,W,B,W,B,W},
		{W,B,W,B,W,B,W,B}
		};
     //is always maximizing
     //sets zero player game
    bool zpgame;
	bool setZpgame();

	//Sets both color and first player.
	bool setColor();

    //returns first and color
    bool guardRails();

    //returns first and color
	void setValues(int b, int w,int x,int dir);

	 //displays board
	void display();

	//piece removal, for fixing board errors and for setup
	void manualOverride();

	//returns True if a space is full, False if it is not.
	bool isFull(int i, int j);

	//test for legality of move
	bool legal_move(int currentmove[], int i, int j, int Dir);
	//tests for legality of move inside the SEF (uses different logic) Uses isFull to do checks
	bool legal_SEF(int i, int j, int Dir);
	/*
	 *makes a move at each node and also makes the chosen move in the game.
	 *currentmove[] is passed along with player color to make the move.
	 *makeMove MUST receive correct input, as it assumes such
	 *this is handled by other functions in the case of a user.
	 */
	void makeMove(int currentmove[], int playerColor);

	//unmakes a move after a move is chosen.
	void unmakeMove(int currentmove[], int playerColor, int opColor);

	//serial variation of alphaBetaMinimax, divided into Min and Max (change 12/22/2020)
	//Check design document for more information
	//level is the level it is processing, depth is the level to which it will travel
	//levelColor is the color being examined at this level

    int ABMin(int alpha, int beta, int level, int depth, int levelColor);

    int ABMax(int alpha, int beta, int level, int depth, int levelColor);

    //State Evaluation Function.  Does not work alone, uses legal_SEF pass is for future modifications
    int SEF(int pass);

    //Checks if chosen move by player is on the board.
	void selection(int S);

	//Displays move numerically
	void displayMove();

	//Compares 8 boards at root of tree (needed, serial implementation) returns board with highest bvalue (bval) after each board is done
    board comparison (board board1, board board2, board board3, board board4, board board5, board board6, board board7, board board8);

    //Called on each thread, imitates the maximizing node of the tree.
    void threadKonane(int i,int alpha, int beta, int depth, int levelColor);

    //Calibrates the for loop that loops through the board for moves.  Checks moves that player
    //or opponent will make based on the node.
    int calibrate(int i, int playerColor);

	//RECORDS MOVES BESTMOVE HOLDS FIRST MOVE AND THEN ANY MOVE THAT IS BETTER.
	int bestmove[4];

};


#endif // BOARD_H
