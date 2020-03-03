//various includes
/*Order of Game Play*/
		/* 1. determine who is first.
		 * 2. choose to remove pieces if not first
		 * 3. change board to reflect removed pieces
		 *     **GAME LOOP**    *
		 * 4. wait for input or make input
		 * 5.
		 * run legalmove on each position in array when is turn (and board is accurate.)
		 * N,S,E,W determines legalmove direction.
		 *
		 * if i<2 (row) don't run N,
		 * if i>5 don't run S,
		 *
		 * if j<2 (column) don't run W,
		 * if j>5 don't run E.
		 *
		 * so the first square in a column doesn't evaluate the Northern most move and the last square will ot
		 * evaluate the Southernmost... etc
		 *
		 * if legalmove returns true, form node with move and run SEF on board to obtain number.
		 * continue breadth first or depth first?
		 * since we are not starting out with pins in mind, we should focus on
		 * stopping it at depth int d
		 * SEF evaluates simply by counting legal moves for player in that state.
		 * there may be some optimizations possible from this in terms of forming leaves...
		 *
		 * Iteration is accumplished by moving and then undoing the move
		 *
		 *
		 * Dir can = 0 for N, 1 for E, 2 for S, 3 for W
		 */
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;
/*TODO .h file for the class???*/
static const int MAX = 999;
static const int MIN = -999;
static const int LOSE = -199;
static const int WIN = 199;

//color is AI, humanColor is opponent
int depth=1;
int color, humanColor;
bool first;

/*int getFirst{return first;}
int getColor {return color;}
int getPlayerColor {return playerColor;}
int getDepth {return depth;}*/
class board {
	int B = 2;
	int W = 1;
	int X = 0;
	int Dir = 0;
	//deprecated
	int drti = 1;
	/*TODO set this in set color*/


	/*set the Static ints before compile,
	fine tune as needed with each compile*/


	char AtoH[8] = { 'A','B','C','D','E','F','G','H' };
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

	/*SETTERS*/
	void setFirst();
	void setColor();
    int bestmove[4];
    int playermove[4];
	void display();
	void manualOverride(); //piece removal, for fixing board errors and for setup.
	bool isFull(int i, int j);
	//test for legality of move
	bool legal_move(int currentmove[], int i, int j, int Dir);
	bool legal_SEF(int i, int j, int Dir, int dtri);
	void makeMove(int currentmove[], int playerColor);
	void unmakeMove(int currentmove[]);
	int calibrate(int i, int color);
    int alphaBetaMinimax(int alpha, int beta, int level, int depth, int levelColor);
    int SEF();
	void selection(int S);
	/*
	int minimax(int level,int depth);
	/*TODO make below functions
	manualOverride

	*/

};


/***ASSISTS MANUAL OVVERIDE***/
void board::selection(int S) {
	int z = S;
	int i, j;
	cout << "\n \n column (A-B = 1-8): ";
	cin >> j;
	cout << "\n row (1-8): ";
	cin >> i;
	i--;
	j--;
	if (i > 7 || i < 0 || j>7 || j < 0) {
		cout << "\n invalid choice, restarting selection";
	}

	else {
		board[i][j] = z;
	}
}


/***FOR SETUP, TESTING, AND MANUAL BOARD CORRECTIONS IF ERRORS MADE,***
***ASSUMES SOME INTELLIGENCE ON PART OF USER***/
void board::manualOverride() {
	int p = 0;
	int i, j;
	char remadd;
	display();
	cout << "r = Removal of piece, b = add black, w = add white e = exit \n";
	cin >> remadd;
		while (remadd != 'e') {
			if (remadd == 'e'){}
			else if (remadd == 'r')
			{
				cout << "What pieces will be removed? choose row and column for each.  (manual adjacency test)";
				selection(0);
			}
			else if (remadd == 'b')
			{
				cout << "What black pieces will be added? choose row and column for each.  (manual adjacency test)";
				selection(2);
			}
			else if (remadd == 'w') {
				cout << "What white pieces will be added? choose row and column for each.  (manual adjacency test)";
				selection(1);
			}
			else{
				cout <<"\n invalid choice, restarting selection";
			}
	display();
	cout << "r = Removal of piece, b = add black, w = add white e = exit \n";
	cin >> remadd;
	}
}


/***NEEDED FOR FIRST TURN, NOT NEEDED AFTER***/
void board::setFirst() {
	int select=0;
	char ans;
	while (ans != 'y') {
		cout << "who is first? \n select 1 for AI and 2 for opponent: ";
		cin >> select;
		if (select == 2)
		{
		first == false;
		cout << "You go first";
		}
		else if (select == 1)
		{
			first == true;
			cout << " 'I' go first";
		}
		else {
			cout << "error";
		}
		cout << "Is this correct? y for yes";
		cin >> ans;
	}
}


/***CRITICAL FOR ENTIRE GAME, SET COLOR HERE***/
void board::setColor() {
	cout << "\n What color is the AI? \n 1 for white and 2 for black:";
	cin >> color;
	if (color == 2)
	{
		humanColor == 1;
	}
	else if (color == 1)
	{
		humanColor == 2;
	}
	else {
		cout << "error";
	}
}


/***SPACE TEST FOR PRESENCE OF PIECE***/
bool board::isFull(int i, int j) {

	if (board[i][j] == 0){
		return false;
	}

	else {
		return true;
	}
}


/***ASSISTS WITH CALIBRATION OF SQUARES, DEALS WITH DOUBLE WHITE/BLACK BOARD EDGE ISSUE***/
int board::calibrate(int i, int color)
{
	/*takes row index to ensure correct color
	square used for operating calling calibrate
	the math is both neccessary for an even numbered board
	and more efficient than other calibration methods tried
	*/
	if (color == 2)
	{ return i % 2; }
	//starting index of an even i will be 0
	else
	//starting index of an even i will be 1
	{ return (i + 1) % 2; }
}


/***FAIRLY STANDARD DISPLAY FUNCTION***/
void board::display() {
    cout<< "X= Black, 0 = White, Spaces for empty \n\n";
	cout << "   ";
	int row = 0;
	for (int i = 0; i < 8; i++){
		cout << AtoH[i];
		cout << " ";
	}
	cout<< "\n \n";
	for (int i = 0; i < 8; i++) {
        cout << ++row <<"  ";

		for (int j = 0; j < 8; j++) {


			if (board[i][j] > 1) {
				cout << "X ";
			}
			else if (board[i][j] > 0) {
				cout << "0 ";
			}
			else {
				cout << "  ";
			}
		}
		cout << "\n";
	}
}

/***TESTS LEGALITY OF MOVE***/
//NOT TESTED YET!!!  MAY WANT TO REFACTOR!
bool board::legal_SEF(int i, int j, int Dir, int dtri)
{
	int k = i;
	int m = j;
	bool state;
	if (Dir == 0) //N
	{
		if (i > 1) {
			k--;
			state = isFull(k, m);
			if (state == true) {
				k--;
			}
			state = isFull(k, m);
			if (state == false) {
				return true;
			}
		}
	}
	if (Dir == 1) //S
		if (i < 5) {
			{
				k++;
				state = isFull(k, m);
				if (state == true) {
					k++;
				}
				state = isFull(k, m);
				if (state == false) {
					return true;
				}
			}
		}
	if (Dir == 2)  //W
	{
		if (j > 1) {
			m--;
			state = isFull(k, m);
			if (state == true) {
				m--;
			}
			state == isFull(k, m);
			if (state == false) {
				return true;
			}
		}
	}

	if (Dir == 3) //E
	{
		m++;
		state == isFull(k, m);
		if (state == true) {
			m++;
		}
		state == isFull(k, m);
		if (state == false) {
			return true;
		}
	}
}

/***ACCOMODATING NEW COORDINATE SYSTEM ANNOUNCED***/
bool board::legal_move(int currentmove [],int i, int j, int Dir)
{
    int k = i;
	int m = j;
    bool state;
	if (Dir = 0) //N
	{
		if (i > 1) {
			k--;
			state == isFull(k, m);
			if (state == true) {
				k--;
			}
			state == isFull(k, m);
			/*if invalid move, recursive call will return false
			but will not edit array
			if VALID move, recursive call calls again until false
			probem with losing initial move*/
			if (state == false) {
				currentmove[0] = i;
				currentmove[1] = j;
				currentmove[2] = k;
				currentmove[3] = m;
				//tests state of Legal Move and NOT the presence of a piece on a space
				state == legal_move(currentmove, k, m, 0);
				if (state == false){

					return true;
				}
				return true;
			}
		}
	}
	if (Dir == 1) //S
		if (i < 6) {
			{
				k++;
				state == isFull(k, m);
				if (state == true) {
					k++;
				}
				state == isFull(k, m);
				if (state == false) {
					currentmove[0] = i;
					currentmove[1] = j;
					currentmove[2] = k;
					currentmove[3] = m;
					//tests state of Legal Move and NOT the presence of a piece on a space
					state == legal_move(currentmove, k, m, 1);
					if (state == false) {

						return true;
					}
					return true;
				}
			}
		}
	if (Dir == 2)  //W
	{
		if (j > 1) {
			m--;
			state == isFull(k, m);
			if (state == true) {
				m--;
			}
			state == isFull(k, m);
			if (state == false) {
				currentmove[0] = i;
				currentmove[1] = j;
				currentmove[2] = k;
				currentmove[3] = m;
				//tests state of Legal Move and NOT the presence of a piece on a space
				state == legal_move(currentmove, k, m, 2);
				if (state == false) {

					return true;
				}
				return true;
			}
		}
	}

	if (Dir == 3) //E
	{
		m++;
		state == isFull(k, m);
		if (state == true) {
			m++;
		}
		state == isFull(k, m);
		if (state == false) {

			currentmove[0] = i;
			currentmove[1] = j;
			currentmove[2] = k;
			currentmove[3] = m;
			//tests state of Legal Move and NOT the presence of a piece on a space
			state == legal_move(currentmove, k, m, 3);
			if (state == false) {

				return true;
			}
			return true;
		}
	}
	//if no move valid
return false;
}
/***ASSUMES LEGAL MOVE HAS BEEN EXECUTED,***
****MAKES MOVE RECORDED BY LEGAL MOVE***
****MAY BE REFACTORED INTO LEGAL MOVE (NON SEF)***/
void board::makeMove(int currentmove[], int playerColor)
{
    int i,j,k,m;
    bool neq;
	i = currentmove[0];
	j = currentmove[1];
	k = currentmove[2];
	m = currentmove[3];
	neq == true;

	while (neq) {
		board[i][j] = 0;
		if (k < i)
		{
			board[i - 1][j] = 0;
			board[i - 2][j] = playerColor;
			if (i - 2 == k) {
				neq == false;
			}
			else {
				//since moves are not finished, i starts again 2 spaces away
				i = i - 2;
			}
		}
		if (k > i)
		{
			board[i + 1][j] = 0;
			board[i + 2][j] = playerColor;
			if (i + 2 == k) {
				neq == false;
			}
			else {
				i = i + 2;
			}
		}
		if (m < j)
		{
			board[i][j - 1] = 0;
			board[i][j - 2] = playerColor;
			if (j - 2 == m) {
				neq == false;
			}
			else {
				j = j - 2;
			}
		}
		if (m > j)
		{
			board[i][j + 1] = 0;
			board[i][j + 2] = playerColor;
			if (j + 2 == m) {
				neq == false;
			}
			else {
				j = j + 2;
			}
		}
	}
}



void board::unmakeMove(int currentmove[]) {
    int i,j,k,m;
    bool neq;
	i = currentmove[0];
	j = currentmove[1];
	k = currentmove[2];
	m = currentmove[3];
	neq == true;

	while (neq) {
		board[i][j] = humanColor;
		if (k < i)
		{
			board[i - 1][j] = humanColor;
			board[i - 2][j] = 0;
			if (i - 2 == k) {
				neq == false;
			}
			else {
				//since moves are not finished, i starts again 2 spaces away
				i = i - 2;
			}
		}
		if (k > i)
		{
			board[i + 1][j] = humanColor;
			board[i + 2][j] = 0;
			if (i + 2 == k) {
				neq == false;
			}
			else {
				i = i + 2;
			}
		}
		if (m < j)
		{
			board[j - 1][j] = humanColor;
			board[j - 2][j] = 0;
			if (j - 2 == m) {
				neq == false;
			}
			else {
				j = j - 2;
			}
		}
		if (m > j)
		{
			board[j + 1][j] = humanColor;
			board[j + 2][j] = 0;
			if (j + 2 == m) {
				neq == false;
			}
			else {
				j = j + 2 ;
			}
		}
	}
}

	/*AI Game Playing Functions, in a loop every turn
	void ABmax();		//maximizer for AI sim, may want it to be separate from this class?
	void ABmin();       //minimizer for AI sim, may want it to be separate from this class?

	Make a move in-game
	void chosenMove();  //states move chosen, implements... probably unneccessary*/

	/*
The minimax algorithm begins at the current state of the game recursively searching the
game tree for the optimal move depth-first, which means exploring a branch as far as it goes and
then backtracking until a path that has not been explored is found. Once the algorithm reaches a
leaf node, which indicates a terminal state, or reaches the specified search depth in the game tree
the utility(best/worst) value of the node is returned.
*/


/*ALPHABETA MINIMAX BELOW*/


	/*TODO Some issues with this function, requires some surgery
I feel TERRIBLE saying this, but it likely requires MORE break statements..
and the return is in the wrong place I think...
I have to write some yucky code (Break statements should be sparse in good code)*/

int board::SEF() {
    int count=0;
    int dtri;
    int Dir;
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(board[i][j]>0)
            {
      		    for(int Dir=0;Dir<4;Dir++){
                    if(legal_SEF(i,j,Dir,dtri)){
                        count++;
                    }

                }

            }

        }
    }
    return count;
}

int board::alphaBetaMinimax(int alpha, int beta, int level, int depth, int levelColor)
{
    int currentmove[4];
    int bestmove[4];
	int temp;
    int k, m;
	// Initial values of
	// Alpha and Beta
	// Terminating condition. i.e
	// leaf node, is reached
	currentmove[-1, -1, -1, -1];
	if (level == depth) {
		return SEF(); //Need to fix the board
	}
     if (level % 2 == 0)
    {/*PROBLEM!!!????*/
        int val = MIN;

        for(int i=0;i<8;i++)
            {
            	for(int j=calibrate(i, color);j<8;j+2)
            	{
            		if(board[i][j]>0)
            		{
						for (int Dir = 0; Dir < 4; Dir++) {
							/***NEEDS WORK ON LM***/

							if (legal_move(currentmove,i, j, Dir)) {
								/*****MOVE PIECE*****/
								makeMove(currentmove, color);
								//calls for minimization using the human color
								temp = alphaBetaMinimax(alpha, beta, level + 1, depth, humanColor);
								if (level == 0 && val < temp) {
                                    for(int z=0;z<4;z++){
                                        bestmove[z] = currentmove[z];
                                    }
								}
								val = max(temp, val);

								alpha = max(alpha, val);
								unmakeMove(currentmove);

								/*
								unmakeMove(i, j, k, m, dtri);  */
								// Alpha Beta Pruning

								if (beta <= alpha) {
									return val;
								}
							}
						}

        			}



				}
    		}
		if (bestmove[0] == -1)
		{
	
			cout << "you win";
			return -10000000;
		}

    }
    else
    {
		int val = MAX;
        for(int i=0;i<8;i++)
           {
           	for(int j=calibrate(i, humanColor);j<8;j+2)
           	{
				if (board[i][j] > 0)
				{
					makeMove(currentmove, humanColor);
					val = min(val, alphaBetaMinimax(alpha, beta, level + 1, depth, color));
					//best = min(best, val);
					beta = min(beta, val);
					/*
					unmakeMove(i, j, k, m, dtri);
					// Alpha Beta Pruning*/
					if (beta <= alpha) {
						return val;
					}
				}
        	}
 		}
		return val;
	}
	 cout << "ERROR";
	 return -50000000;
}


/*STRICT MINIMAX BELOW*/

/* int board::minimax(int level,int depth)
{
	// if node is at depth limit...
		if (level == depth)
		   // do a static evaluation, return result and the best move
			return (static_eval(node));  //Have to write the static_eval function



		//if node is at a maximizing level (if level is even)
		if (level % 2 == 0)
		{

			int best_value = -99999;

			for(int i=0;i<8;i++)
			{
				for(int j=0;j<8;j++)
				{
					if(board[i][j]==0)
					{
						for(int Dir=0;Dir<4;Dir++){
						if(legal_move(i,j,Dir)){
						board[i][j]=B; //assuming black is the AI and its' trying to maximize

						// Call minimax recursively and choose
						// the maximum value
						best = max( best_value, minimax(level+1,depth) );

						// Undo the move
						// board[i][j] = 0;
						}

						}

					}
				}
			}
			return best_value;
		}



		else
		{

			int best_value = 99999;
			for(int i=0;i<8;i++)
			{
				for(int j=0;j<8;j++)
				{
					if(board[i][j]==0)
					{
						for(int Dir=0;Dir<4;Dir++){
							if(legal_move(i,j,Dir)){
								board[i][j]=B; //assuming black is the AI and its' trying to maximize

						// Call minimax recursively and choose
						// the maximum value
								best = max(best_value, minimax(board, level+1,depth) );

						// Undo the move
						 //       board[i][j] = 0;
							}

						}
				}
			}
			}
		}
			return best_value;
		}
		*/


int main() {

	int B = 2;
	int W = 1;
	int Dir = 0;
	int i,j,k,m, alpha, beta, level;
	bool AIturn, ingameState;
	ingameState == true;
	char correct, ans;
	board board;

	board.setFirst();
	if (first == true) {
		AIturn == true;
	}
	else{
        AIturn==false;
	}
	board.setColor();
	board.display();
	board.manualOverride();

	while (ingameState == true) {
		while (ans != 'y') {
			cout << "\n is board correct? y for yes, n for no \n \n";
			board.manualOverride();
			board.display();
			cin >> ans;
		}
		if (AIturn == true) {
			board.alphaBetaMinimax(alpha, beta, level, depth, color);
			board.makeMove(board.bestmove, color);
			board.display();
		}
		else {
			cout << "enter piece to move row, 1-8";
			cin >> i;
			i--;

			cout << "enter piece to move column, 1-8";
			cin >> j;
			j--;

			cout << "enter piece destination row, 1-8";
			cin >> k;
			k--;

			cout << "enter piece destination column, 1-8";
			cin >> m;
			m--;
			board.bestmove[i,j,k,m];
			board.makeMove(board.bestmove,humanColor);
			board.display();
		}
	}
	return 0;
}
