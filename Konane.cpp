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
/*global variables used due to performance increase (according to stackoverflow)*/
static const int MAX = 999;
static const int MIN = -999;
static const int LOSE = -199;
static const int WIN = 199;
bool first;
//color is AI, humanColor is opponent
int AIcolor, humanColor;


/*int getFirst{return first;}
int getColor {return AIcolor;}
int getPlayerColor {return playerColor;}
int getDepth {return depth;}*/
class board {
	static const int B = 2;
	static const int W = 1;
	/*TODO set this in set color*/


	/*set the Static ints before compile,
	fine tune as needed with each compile*/


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
	void setValues(int b, int w,int x,int dir);
	void setFirst();
	void setColor();
    int bestmove[4];
    int playermove[4];
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
    int SEF();
	void selection(int S);
	/*
	int minimax(int level,int depth);
	TODO make below functions
	manualOverride
	*/

};


/***ASSISTS MANUAL OVVERIDE***/
void board::selection(int S) {
	int z = S;
	int i, j;
	cout << "\n column (A-H = 1-8): ";
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
	cout << "r = Removal of piece, b = add black, w = add white e = exit \n";
	cin >> remadd;
		while (remadd != 'e') {
			if (remadd == 'e'){}
			else if (remadd == 'r')
			{
				cout << "What pieces will be removed? choose row and column for each.  (manual adjacency test)\n";
				selection(0);
			}
			else if (remadd == 'b')
			{
				cout << "What black pieces will be added? choose row and column for each.  (manual adjacency test)\n";
				selection(2);
			}
			else if (remadd == 'w') {
				cout << "What white pieces will be added? choose row and column for each.  (manual adjacency test)\n";
				selection(1);
			}
			else{
				cout <<"\n invalid choice, restarting selection\n";
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
		first = false;
		cout << "\nYou go first";
		}
		else if (select == 1)
		{
			first = true;
			cout << "\n 'I' go first";
		}
		else {
			cout << "\nerror";
		}
		cout << "\nIs this correct? y for yes";
		cin >> ans;
	}
}


/***CRITICAL FOR ENTIRE GAME, SET COLOR HERE***/
void board::setColor() {
	cout << "\n What color is the AI? \n 1 for white and 2 for black:";
	cin >> AIcolor;
	if (AIcolor == 2)
	{
		humanColor = 1;
	}
	else if (AIcolor == 1)
	{
		humanColor = 2;
	}
	else {
		cout << "\nerror";
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
int board::calibrate(int i, int playerColor)
{
	if (playerColor == 2)
	{ return i % 2; }
	//starting index of an even i will be 0
	else
	//starting index of an even i will be 1
	{ return (i + 1) % 2; }
}


/***FAIRLY STANDARD DISPLAY FUNCTION***/
void board::display() {
    cout<< "\n\nX= Black, 0 = White, Spaces for empty squares\n\n";
	int row = 0;
	cout << "   A B C D E F G H \n";
    cout << "   1 2 3 4 5 6 7 8 ";

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
bool board::legal_SEF(int i, int j, int Dir)
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
				state = isFull(k, m);
				if (state == false) {
					return true;
				}
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
					state = isFull(k, m);
					if (state == false) {
						return true;
					}
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
				state = isFull(k, m);
				if (state == false) {
					return true;
				}
			}

		}
	}

	if (Dir == 3) //E
	{
		m++;
		state = isFull(k, m);
		if (state == true) {
			m++;
			state = isFull(k, m);
			if (state == false) {
				return true;
			}
		}

	}
	return false;
}

/***ACCOMODATING NEW COORDINATE SYSTEM ANNOUNCED***/
bool board::legal_move(int currentmove[], int i, int j, int Dir)
{
	if (i > 7) { return false; }
	if (j > 7) { return false; }
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
				state = isFull(k, m);
				/*if invalid move, recursive call will return false
				but will not edit array
				if VALID move, recursive call calls again until false
				probem with losing initial move*/
				if (state == false) {
					currentmove[0] = i;
					currentmove[1] = j;
					currentmove[2] = k;
					currentmove[3] = m;
					cout<<i<<", "<<j<<", "<<k<<", "<<m<<"\n";
					//tests state of Legal Move and NOT the presence of a piece on a space
					//state = legal_move(currentmove, k, m, 0);
					return true;
				}
			}
		}
	}
	if (Dir == 1) //S
	{
		if (i < 6)
			{
				k++;
				state = isFull(k, m);
				if (state == true) {
					k++;
					state = isFull(k, m);
					if (state == false) {
						currentmove[0] = i;
						currentmove[1] = j;
						currentmove[2] = k;
						currentmove[3] = m;
						cout<<i<<", "<<j<<", "<<k<<", "<<m<<"\n";
						//tests state of Legal Move and NOT the presence of a piece on a space
						//state = legal_move(currentmove, k, m, 1);}
						return true;
					}
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
				state = isFull(k, m);
				if (state == false) {
					currentmove[0] = i;
					currentmove[1] = j;
					currentmove[2] = k;
					currentmove[3] = m;
					cout<<i<<", "<<j<<", "<<k<<", "<<m<<"\n";
					//tests state of Legal Move and NOT the presence of a piece on a space
					//state = legal_move(currentmove, k, m, 2);
					return true;
				}
			}

		}
	}

	if (Dir == 3) //E
	{
		if (j < 6) {
			m++;
			state = isFull(k, m);
			if (state == true) {
				m++;
				state = isFull(k, m);
				if (state == false) {

					currentmove[0] = i;
					currentmove[1] = j;
					currentmove[2] = k;
					currentmove[3] = m;
					cout<<i<<", "<<j<<", "<<k<<", "<<m<<"\n";
					//tests state of Legal Move and NOT the presence of a piece on a space
					//state = legal_move(currentmove, k, m, 3);
					return true;
				}
			}


		}
		//if no move valid

	}
	return false;
}
/***ASSUMES LEGAL MOVE HAS BEEN EXECUTED,***
****MAKES MOVE RECORDED BY LEGAL MOVE***
****MAY BE REFACTORED INTO LEGAL MOVE (NON SEF)***/
void board::makeMove(int currentmove[], int playerColor)
{   cout<<"making move";
    int i,j,k,m;
    bool neq;
	i = currentmove[0];
	j = currentmove[1];
	k = currentmove[2];
	m = currentmove[3];
	cout<<"\n"<<i+1<<", "<<j+1<<", "<<k+1<<", "<<m+1<<"\n";
	neq = true;


    board[i][j] = 0;
    if (k < i)
    {
        board[i - 1][j] = 0;
        board[i - 2][j] = playerColor;/*
			else {
				//since moves are not finished, i starts again 2 spaces away
				i = i - 2;
			}*/
    }
    if (k > i)
    {
        board[i + 1][j] = 0;
        board[i + 2][j] = playerColor;
    }
    if (m < j)
    {
        board[i][j - 1] = 0;
        board[i][j - 2] = playerColor;
    }
    if (m > j)
    {
        board[i][j + 1] = 0;
        board[i][j + 2] = playerColor;
    }
}



void board::unmakeMove(int currentmove[],int playerColor, int opColor) {
    int i,j,k,m;
	i = currentmove[0];
	j = currentmove[1];
	k = currentmove[2];
	m = currentmove[3];
	cout << "unmaking move \n";
		board[i][j] = playerColor;
		if (k < i)
		{
			board[i - 1][j] = opColor;
			board[i - 2][j] = 0;
		}
		if (k > i)
		{
			board[i + 1][j] = opColor;
			board[i + 2][j] = 0;
		}
		if (m < j)
		{
			board[i][j-1] = opColor;
			board[i][j-2] = 0;
		}
		if (m > j)
		{
			board[i][j+1] = opColor;
			board[i][j+2] = 0;
		}
		cout << "\n" << i + 1 << ", " << j + 1 << ", " << k + 1 << ", " << m + 1 << "\n";
		display();
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
        for(int j=calibrate(i,AIcolor);j<8;j++)
        {
            if(board[i][j]>0)
            {
      		    for(int Dir=0;Dir<4;Dir++){
                    if(legal_SEF(i,j,Dir)){
                        count++;
                    }

                }

            }

        }
    }
    return count;
}

int board::alphaBetaMinimax(int alpha, int beta, int level, int depth, int levelColor, bool maximizing)
{

	int temp;
    int k, m, tshoot;
	// Initial values of
	// Alpha and Beta
	// Terminating condition. i.e
	// leaf node, is reached
	int currentmove[4];
	if (level == depth) {
		tshoot= SEF(); //Need to fix the board
		cout<<"\nSEF= "<<tshoot<<"\n";
		return tshoot;
	}
	else if (maximizing==true)
    {/*PROBLEM!!!????*/
        int val = MIN;

        for(int i=0;i<8;i++)
            {
            	for(int j=calibrate(i, AIcolor);j<8;j=j+2)
            	{
            		if(board[i][j]>0)
            		{
						for (int Dir = 0; Dir < 4; Dir++) {
							if (legal_move(currentmove, i, j, Dir)) {
								/*****MOVE PIECE*****/
								makeMove(currentmove, AIcolor);
								//calls for minimization using the human color
								temp=val;
								val=max(val,alphaBetaMinimax(alpha, beta, level + 1, depth, humanColor, false));
								unmakeMove(currentmove,AIcolor,humanColor);
								if (level == 0 && temp<=val) {
                                        bestmove[0]=currentmove[0];
                                        bestmove[1]=currentmove[1];
                                        bestmove[2]=currentmove[2];
                                        bestmove[3]=currentmove[3];
								}
                                cout<<val;
								alpha = max(alpha, val);

								if (beta <= alpha) {
									return val;
								}
							}
						}
        			}
				}
    		}
    return val;
    }
    else
    {
        cout<<"minimizing \n";
		int val = MAX;
        for(int i=0;i<8;i++)
           {
           	for(int j=calibrate(i, humanColor);j<8;j=j+2)
           	{
				if (board[i][j] > 0)
				{
				    for (int Dir = 0; Dir < 4; Dir++) {
						if (legal_move(currentmove, i, j, Dir)) {
                                    for (int z=0;z<4;z++){
                                    cout<<" "<<currentmove[z]+1<<" ";
                                    }

                                    makeMove(currentmove, humanColor);
                                    val = min(val, alphaBetaMinimax(alpha, beta, level + 1, depth, AIcolor, true));
                                    //best = min(best, val);
                                    beta = min(beta, val);
                                    unmakeMove(currentmove, humanColor, AIcolor);
                                    // Alpha Beta Pruning
                                    if (beta <= alpha) {
                                        return val;
                                    }
                                }
                                else{}
                            }
                }
        	}
 		}
		return val;
	}
	cout << "ERROR";
	return -1;
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
			}5
		}
			return best_value;
		}
		*/


int main() {

	int B = 2;
	int W = 1;
	int Dir = 0;
	int i,j,k,m, alpha, beta;
	int level=0;
	int depth = 7;
	bool AIturn, ingameState;
	ingameState = true;
	char correct, ans;
	board board;

	board.setFirst();
	if (first == true) {
		AIturn = true;
	}
	else{
        AIturn=false;
	}
	board.setColor();
	board.display();

	while (ingameState == true) {
		while (ans != 'y') {
			board.manualOverride();
			board.display();
            cout << "\n is board correct? y for yes, n for no \n \n";
			cin >> ans;
		}
		if (AIturn == true) {
			board.alphaBetaMinimax(1, 2, level, depth, AIcolor, true);
			cout << "\nMAKING ACTUAL MOVE";
			board.display();
			board.makeMove(board.bestmove, AIcolor);
			board.display();
            AIturn=false;
            }
		else {
			cout << "enter piece to move row, 1-8";
			cin >> i;
			i--;
			board.bestmove[0]=i;
			cout << "enter piece to move column, 1-8";
			cin >> j;
			j--;
			board.bestmove[1]=j;
			cout << "enter piece destination row, 1-8";
			cin >> k;
			k--;
			board.bestmove[2]=k;
			cout << "enter piece destination column, 1-8";
			cin >> m;
			m--;
			board.bestmove[3]=m;
			board.makeMove(board.bestmove,humanColor);
			board.display();
			AIturn=true;
		}
	}
	return 0;
}
