/*Order of Game Play*/
/*Game is lost when there are no longer any valid moves.*/
		/* 1. determine who plays Black and is thus first.
		 * 2. choose to remove 2 pieces if not first (another variant has the removal of one piece by each player).
		 *
		 *     **GAME LOOP**    *
		 * 3. wait for input or make input
		 * 4. upon AI move:

		 * run legalmove on each position in array when is turn (and board is accurate.)
		 * N,S,E,W determines legalmove direction.
		 *
		 * the following bounds due to no move possible:
		 * if i<2 (row) don't run N
		 * if i>5 don't run S,
		 *
		 * if j<2 (column) don't run W,
		 * if j>5 don't run E.
		 *
		 * so the first square in a column doesn't evaluate the Northern most move and the last square will not
		 * evaluate the Southernmost... etc
		 * ******************* RECURSIVE CALLS  ***************************
		 * 5. if legalmove returns true, form node (recursibe call with new board) with move and repeat process board to obtain number.
		 * it is a DFS.
		 * 6. the calls eventually reach depth d and the SEF is run.  It is notable that the alpha and beta cutoffs will reduce the number of boards evaluated
		 * WITHOUT any data loss.
		 * (this is a less intuitive action of the recursive function, no data is lost, but branches that the AI will NEVER select are not explored further.
		 * essentially, a node which comes out too high or too low relative to the node examined will not be selected)
		 *
		 **************	State Evaluation function (SEF)*********************
		 *
		 * 7. The SEF evaluates partly by counting legal moves for player in that state.
		 * Additionally, it counts pieces and estimates based on expected piece balance (each move must remove one piece, if more pieces are missing a
		 * double move has occurred.  The SEF assumes that this is always bad for the player who had this happen.)
		 *
		 * The SEF value is passed up to the top of the tree with varied modifications, minimizing levels take the lowest value to pass, maximizing
		 * will take up the largest values
		 *
		 * Dir can = 0 for N, 1 for E, 2 for S, 3 for W
		 */



/* STANDARD INCLUDES FROM LIBRARY FILES AND NAMESPACE */
#include "standard.h"
/**INCLUDE PARALELL PROCESSING??**/
/**INCLUDE PARALELL PROCESSING??**/
#include <algorithm>
#include <chrono>
#include <random>
#include <ratio>
#include <thread>
using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::milli;
/*Include Constants*/
#include "const.h"
using namespace std;
/**REMEMBER TO USE THE DIAGNOSTIC PRINTOUTS FOR FUTURE CHANGES**/
/*dynamic globals, may alter as needed*/

/*AI TURN?*/
/**FUNCTIONAL WITH 14 DEPTH, EASE OF TESTING AT 12 OR 10 DEPTH, GAMEPLAY IS DIFFERENT DEPENDING ON DEPTH**/
int turn;

//color is AI, humanColor is opponent
/***MUST HAVE THESE GLOBALS, COULD PERHAPS EDIT INTO MAIN?***/
int AIcolor, humanColor;
/******************DUE TO FOLLOWING OFFICIAL RULES, COLOR HAS BEEN MERGED WITH FIRST**********************/
/***(setters and getters, removed from code at the moment)***/
/*int getFirst(){return first;}
 *int getColor() {return AIcolor;}
 *int getPlayerColor() {return playerColor;}
 *int getDepth() {return depth;}
 */
class player{
public:
    void jokes();
    void detectWL(int value);
};
void player::jokes()
{
    int jokes;
    std::cout << "Would you like to play a game? \n";
	std::cout << "1. Konane \n2. ALSO Konane\n3. Global Thermonuclear War\n";
	std::cin >> jokes;
	if (jokes == 3) {
		std::cout << "That game is SOOOOOOOO boring,let's play Konane!!!\n";
	}
}

void player::detectWL(int value){}

class board {
    public:
    int bval;
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
	/*all functions void functions until code is fully determined.*/
     //is always maximizing

	bool setZpgame();
	bool setColor();
    bool zpgame;
    bool guardRails();
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
    int alphaBetaMinimax(int alpha, int beta, int level, int depth, int levelColor, bool maximizing);
    int SEF(int pass);
	void selection(int S);
	void displayMove();
    board comparison (board board1, board board2, board board3, board board4, board board5, board board6, board board7, board board8);
    void threadKonane(int i,int alpha, int beta, int depth, int levelColor);
    int calibrate(int i, int playerColor);
	//RECORDS MOVES BESTMOVE HOLDS FIRST MOVE AND THEN ANY MOVE THAT IS BETTER.
	int bestmove[4];
	int playermove[4];

};



void board::threadKonane(int i,int alpha, int beta, int depth, int levelColor){
int k, m, temp;
   int opColor = levelColor%2;
    opColor++;
    /**RESOLVE MATH AFTER SUCCESSFUL TEST**/
	int currentmove[4];
	int val = MIN;
    bval= MIN;
for (int j = calibrate(i, levelColor); j < 8; j = j + 2)
	{
		if (objBoard[i][j] > 0)
		{
			for (int Dir = 0; Dir < 4; Dir++) {
				if (legal_move(currentmove, i, j, Dir)) {
					/*****MOVE PIECE*****/
					makeMove(currentmove, levelColor);
					//calls for minimization using the opposing color
					temp = val;
					//needs some work.
					val = max(val, alphaBetaMinimax(alpha, beta, 1, depth, opColor, false));


					unmakeMove(currentmove, levelColor, opColor);

                    /**AT ROOT OF RECURSIVE TREE, IS CURRENT MOVE BEST?**/
					/**IF CURRENT MOVE BEST, CHANGE MOVE**/
                    //This normally happens at depth zero
                    //This IS "depth zero" as far as the code
                    //is concerned, hence this can happen here.
                    //could remove from other code.
					alpha = max(alpha, val);
                        if (temp < val) {
                            bval=val; //add a bval variable to board.
                            bestmove[0] = currentmove[0];
                            bestmove[1] = currentmove[1];
                            bestmove[2] = currentmove[2];
                            bestmove[3] = currentmove[3];
                        }
					//Alpha cutoff
					//DO WE NEED AN ALPHA CUTOFF IF PARALLEL?
					//THERE WILL NEVER BE AN UNEXPLORED MOVE AT ROOT
					//CUTOFFS WILL DEFINITELY HAPPEN LOWER IN TREE
					/*if (beta <= alpha) {
                        return alpha;
						}*/
				}
			}
		}
	}
	cout<<"SEF of thread "<<i<<" = "<<bval<<endl;
return;
}


/***ALPHABETA MINIMAX BELOW***/

/***NEEDS FULL REFACTOR FOR THE PURPOSE OF ZERO PLAYER GAME***/
int board::alphaBetaMinimax(int alpha, int beta, int level, int depth, int levelColor, bool maximizing)
{
	int k, m, tshoot, temp;
	/* Initial values of
	 * Alpha and Beta
	 * Terminating condition. i.e
	 *leaf node, is reached*/
    int opColor = levelColor%2;
    opColor++;
    /**RESOLVE MATH AFTER SUCCESSFUL TEST**/
	int currentmove[4];
	if (level == depth) {
			tshoot = SEF(levelColor);
			//std::cout << "\nSEF= " << tshoot << "\n";
			return tshoot;
	}
	else if (maximizing == true)
	{/*PROBLEM!!!????*/
		int val = MIN;

		for (int i = 0; i < 8; i++)
		{
			for (int j = calibrate(i, levelColor); j < 8; j = j + 2)
			{
				if (objBoard[i][j] > 0)
				{
					for (int Dir = 0; Dir < 4; Dir++) {
						if (legal_move(currentmove, i, j, Dir)) {
							/*****MOVE PIECE*****/
							makeMove(currentmove, levelColor);
							//calls for minimization using the opposing color
							temp = val;
							val = std::max(val, alphaBetaMinimax(alpha, beta, level + 1, depth, opColor, false));
							unmakeMove(currentmove, levelColor, opColor);
							/**AT ROOT OF RECURSIVE TREE, IS CURRENT MOVE BEST?**/
							/**IF CURRENT MOVE BEST, CHANGE MOVE**/
							if (level == 0 && temp < val) {
								bestmove[0] = currentmove[0];
								bestmove[1] = currentmove[1];
								bestmove[2] = currentmove[2];
								bestmove[3] = currentmove[3];
							}
							alpha = std::max(alpha, val);
							//Alpha cutoff
							if (beta <= alpha) {
								return alpha;
							}
						}
					}

				}
			}
		}
		/**Program can predict loss, and will end properly if loss.**/
		if (val == MIN)
		{
			return LOSE;
		}

    return val;
	}
	else
	{
		//std::cout << "minimizing \n";
		int val = MAX;
		for (int i = 0; i < 8; i++)
		{
			for (int j = calibrate(i, levelColor); j < 8; j = j + 2)
			{
				if (objBoard[i][j] > 0)
				{
					for (int Dir = 0; Dir < 4; Dir++) {
						if (legal_move(currentmove, i, j, Dir)) {
                            /*    std::cout << "\n ";
							for (int z = 0; z < 4; z++) {
								std::cout << currentmove[z] + 1;
							}
                            std::cout << "\n ";
                            */

							makeMove(currentmove, levelColor);
							val = std::min(val, alphaBetaMinimax(alpha, beta, level + 1, depth, opColor, true));
							beta = std::min(beta, val);
							unmakeMove(currentmove, levelColor, opColor);
							// Alpha Beta Pruning
							if (beta <= alpha) {
                                    //Beta cutoff
								return beta;
							}
						}
					}
				}
			}
		}
		if (val == MAX)
		{

			/*ran out of moves on mimimzer
			**The SEF needs tuning, but MAY work here
			**(some assumptions have been made here)
			**once tuned, it should perform ideally*/
			return WIN;
		}
		return val;
	}
	std::cout << "ERROR";
	return -1;
}

board board::comparison (board board1, board board2, board board3, board board4, board board5, board board6, board board7, board board8)
{
    if (board1.bval<board2.bval)
    {
        cout<<board1.bval<<endl;
        board1=board2;
    }
    if (board1.bval<board3.bval)
    {
        cout<<board1.bval<<endl;
        board1=board3;
    }
    if (board1.bval<board4.bval)
    {
       cout<<board1.bval<<endl;
        board1=board4;
    }
    if (board1.bval<board5.bval)
    {
        cout<<board1.bval<<endl;
        board1=board5;
    }
    if (board1.bval<board6.bval)
    {
        cout<<board1.bval<<endl;
        board1=board6;
    }
    if (board1.bval<board7.bval)
    {   cout<<board1.bval<<endl;
        board1=board7;
    }
    if (board1.bval<board8.bval)
    {
        cout<<board1.bval<<endl;
        board1=board8;
        cout<<board1.bval<<endl;
    }

    return board1;
}
int board::calibrate(int i, int playerColor)
{
	if (playerColor == 2)
        {return i % 2;}
	//starting index of an even i will be 0
	else
	//starting index of an even i will be 1
        {return (i + 1) % 2;}
}

/**ZERO PLAYER GAME SELECTION**/
bool board::setZpgame(){
    char ans;
    do{
        std::cout<<"Will I be playing Myself? \ny/n\n";
        std::cin>>ans;
        if (ans=='y'){
        return true;
        }
    else if(ans == 'n'){
        return false;
        }
        else{}
    }while (true);

}
/**SAFETY FOR USER ERRORS**/
bool board::guardRails(){
    bool correct=false;
    int i,j,k,m;
    i=bestmove[0];
    j=bestmove[1];
    k=bestmove[2];
    m=bestmove[3];
    if(i==k||j==m){
        i=(i-k)%2;
        j=(j-m)%2;
        i=i-j;
        if (i==0)
        {
            return true;
        }
        std::cout<<"incorrect move";
        return false;
    }
    return true;
}
/***ASSISTS MANUAL OVVERIDE***/
void board::selection(int S) {
	int i, j;
	std::cout << "\n column (A-H = 1-8): ";
	std::cin >> j;
	std::cout << "\n row (1-8): ";
	std::cin >> i;
	i--;
	j--;
	if (i > 7 || i < 0 || j>7 || j < 0) {
		std::cout << "\n invalid choice, restarting selection";
	}

	else {
		objBoard[i][j] = S;
	}
	return;
}


/***FOR SETUP, TESTING, AND MANUAL BOARD CORRECTIONS IF ERRORS MADE,***
 ***ASSUMES SOME INTELLIGENCE ON PART OF USER***/
 /***ZERO PLAYER GAME COMPATIBLE***/
void board::manualOverride() {
	int p = 0;
	int i, j;
	char remadd, ans;
			while (ans != 'y') {
            display();

	std::cout<< "\n\nX= Black, O = White, Spaces for empty squares\n\n";
	std::cout << "r = Removal of piece, b = add black, w = add white e = exit \n";
	std::cin >> remadd;
		while (remadd != 'e') {
			if (remadd == 'e'){}
			else if (remadd == 'r')
			{
				std::cout << "What pieces will be removed? choose row and column for each.  (NO adjacency test)\n";
				selection(0);
			}
			else if (remadd == 'b')
			{
				std::cout << "What black pieces will be added? choose row and column for each.  (NO adjacency test)\n";
				selection(2);
			}
			else if (remadd == 'w') {
				std::cout << "What white pieces will be added? choose row and column for each.  (NO adjacency test)\n";
				selection(1);
			}
			else{
				std::cout <<"\n invalid choice, restarting selection\n";
                display();
                std::cout<< "\n\nX= Black, O = White, Spaces for empty squares\n\n";
                std::cout << "r = Removal of piece, b = add black, w = add white e = exit \n";
                std::cin >> remadd;
			}
        display();
        std::cout << "r = Removal of piece, b = add black, w = add white e = exit \n";
        std::cin >> remadd;
	}
    display();
    std::cout << "\n is board correct? y for yes, n for no \n \n";
	std::cin >> ans;
}
}



/***  CRITICAL FOR ENTIRE GAME, SET COLOR AND FIRST GLOBALS HERE  ***/
/***GIVEN CURRENT USAGE, IS NOT INCOMPATIBLE WITH ZERO PLAYER GAME***/
bool board::setColor() {
    char ans='n';
    bool first;
    while (ans != 'y') {

		std::cout << "\nWhat color should 'I' play as? \n 1 for white and 2 for black:\n(black goes first per Konane rules \n black is X, white is O)\n ";
        std::cin >> AIcolor;

        if (AIcolor == 2)
        {
            humanColor = 1;
            first = true;
        std::cout<< "\nI play as black and go first.";
        }
        else if (AIcolor == 1)
        {
            humanColor = 2;
            first = false;
            std::cout<< "\nI play as white and go second.";
        }
        else {
            std::cout << "\nerror, restarting";
        }
        std::cout << "\nIs this correct? y for yes:\n";
		std::cin >> ans;
	}
	return first;
}


/***SPACE TEST FOR PRESENCE OF PIECE***/
/***       COLOR AGNOSTIC           ***/
bool board::isFull(int i, int j) {

	if (objBoard[i][j] == 0){
		return false;
	}

	else {
		return true;
	}
}


/***ASSISTS WITH CALIBRATION OF SQUARES, DEALS WITH DOUBLE WHITE/BLACK BOARD EDGE ISSUE***/



/***FAIRLY SIMPLE DISPLAY FUNCTION***/
void board::display() {
	int row = 0;
	std::cout << "   A B C D E F G H \n";
    std::cout << "   1 2 3 4 5 6 7 8 ";

	std::cout<< "\n \n";
	for (int i = 0; i < 8; i++) {
        std::cout << ++row <<"  ";

		for (int j = 0; j < 8; j++) {


			if (objBoard[i][j] > 1) {
				std::cout << "X ";
			}
			else if (objBoard[i][j] > 0) {
				std::cout << "O ";
			}
			else {
				std::cout << "  ";
			}
		}
		std::cout << "\n";
	}
}
void board::displayMove(){
std::cout<<"\n"<<bestmove[0]+1<<", ";
std::cout<<bestmove[1]+1<<", to ";
std::cout<<bestmove[2]+1<<", ";
std::cout<<bestmove[3]+1<<", \n your move\n";
}
/***       TESTS LEGALITY OF MOVE FOR SEF        ***/

/***State Evaluation form of Legal Move.         ***
*** Exists for the purposes of tallying possible ***
*** moves, this is sufficient a refactor         ***
*** may be desirable.  ZERO PLAYER GAME AGNOSTIC ***/
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

/***ACCOMODATING NEW COORDINATE SYSTEM ANNOUNCED      ***
 ***MESSY, REFACTOR IF TIME, IT IS COLOR AGNOSTIC     ***/

bool board::legal_move(int currentmove[], int i, int j, int Dir)
{
    bool state;
    int k = i;
	int m = j;
	if (Dir == 0) //N
	{
		if (k > 1) {
            k--;
            state = isFull(k, m);
            if (state == true) {
				k--;
				state = isFull(k, m);
			if (state == false) {
                currentmove[0] = i;
                currentmove[1] = j;
                currentmove[2] = k;
                currentmove[3] = m;
                    if(k>1){
                        k--;
                        state = isFull(k, m);
                        if (state == true) {
                            k--;
                            state = isFull(k, m);
                            if (state == false) {
                                currentmove[2] = k;
                                currentmove[3] = m;
                            }

					}
                    }
					return true;
                }
			}
		}
	}
	if (Dir == 1) //S
	{
        if (k < 6) {
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
                    if(k<6){
                        k++;
                        state = isFull(k, m);
                        if (state == true) {
                            k++;
                            state = isFull(k, m);
                            if (state == false) {
                                currentmove[2] = k;
                                currentmove[3] = m;
                            }

					}
                    }
					return true;
                }
			}
		}
	}
	if (Dir == 2)  //W
	{
		if (m > 1) {
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
                    if(m>1){
                        m--;
                        state = isFull(k, m);
                        if (state == true) {
                            m--;
                            state = isFull(k, m);
                            if (state == false) {
                                currentmove[2] = k;
                                currentmove[3] = m;
                            }

					}
                    }
					return true;
                }
			}
		}
	}

	if (Dir == 3) //E
	{
		if (m <6) {
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
                    if(m<6){
                        m++;
                        state = isFull(k, m);
                        if (state == true) {
                            m++;
                            state = isFull(k, m);
                            if (state == false) {
                                currentmove[2] = k;
                                currentmove[3] = m;
                            }

					}
                    }
					return true;
                }
			}
		}
	}
	//if no move at all
	return false;
}


/***ASSUMES LEGAL MOVE HAS BEEN EXECUTED,***
/***MAKES MOVE RECORDED BY LEGAL MOVE    ***/

/** DOES NOT NEED REFACTORING FOR ZERO PLAYER GAME **/
void board::makeMove(int currentmove[], int playerColor)
{   //std::cout<<"making move\n";
    int i,j,k,m;
    bool neq;
	i = currentmove[0];
	j = currentmove[1];
	k = currentmove[2];
	m = currentmove[3];
	//std::cout<<" "<<i+1<<", "<<j+1<<", "<<k+1<<", "<<m+1<<"\n";
	neq = true;
    do {
    objBoard[i][j] = 0;

    if (k < i)
    {
        objBoard[i - 1][j] = 0;
        objBoard[i - 2][j] = playerColor;
        i=i-2;
    }
    if (k > i)
    {
        objBoard[i + 1][j] = 0;
        objBoard[i + 2][j] = playerColor;
        i=i+2;
    }
    if (m < j)
    {
        objBoard[i][j - 1] = 0;
        objBoard[i][j - 2] = playerColor;
        j=j-2;
    }
    if (m > j)
    {
        objBoard[i][j + 1] = 0;
        objBoard[i][j + 2] = playerColor;
        j=j+2;
    }
    if((i==k)&&(m==j)){neq=false;}
    } while (neq);
    return;
}

/**UNMAKE MOVE IS COLOR-AGNOSTIC, ZERO PLAYER GAME WILL NOT REQUIRE A CHANGE HERE**/

void board::unmakeMove(int currentmove[],int playerColor, int opColor) {
    int i,j,k,m;
    bool neq=true;
	i = currentmove[0];
	j = currentmove[1];
	k = currentmove[2];
	m = currentmove[3];

	while (neq){
        //std::cout << "\nunmaking move: ";
		objBoard[k][m] = 0;
		if (k > i)
		{
			objBoard[k - 1][m] = opColor;
			objBoard[k - 2][m] = playerColor;
            k=k-2;
            if(k==i)
            {
                break;
            }
		}
		if (k < i)
		{
			objBoard[k + 1][m] = opColor;
			objBoard[k + 2][m] = playerColor;
			k=k+2;
            if(k==i)
            {
            break;
            }
		}
		if (m > j)
		{
			objBoard[k][m-1] = opColor;
			objBoard[k][m-2] = playerColor;
			m=m-2;
            if(m==j)
            {
            break;
            }
		}
		if (m < j)
		{
			objBoard[k][m+1] = opColor;
			objBoard[k][m+2] = playerColor;
			m=m+2;
            if(m==j)
            {
            break;
            }
		}
}
}

/**DEBRIS COMMENTS, NEED TO RECONCILE WITH CURRENT VERSION**/
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



/**TO ACHIEVE ZERO PLAYER GAME, THE SEF NEEDS EDITS**/

int board::SEF(int playerColor) {
	int sum=0;    //sum of total moves for SEF player
	int eb=0;     //deprecated but potentially useful
	int pb=0;     //Player pieces
	int oPiece=0; //Opponent pieces
	//pb=30;
	//eb=(pb-(turn+pass));
	//ABOVE NEEDS SOME WORK
	int opColor = playerColor%2;
	opColor++;
	/**PIECE BALANCE ADJUSTMENT MAy BE NEEDED BASED ON WHO IS FIRST IF PLAYER IS SECOND, INCREMENT PIECES**/
	for (int i = 0; i < 8; i++)
	{
		for (int j = calibrate(i, playerColor); j < 8; j = j + 2)
		{
			if (objBoard[i][j] > 0)
			{
			    pb++;
				for (int Dir = 0; Dir < 4; Dir++) {
					if (legal_SEF(i, j, Dir)) {
						sum++;
					}
				}

			}

		}
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = calibrate(i, opColor); j < 8; j = j + 2)
		{
			if (objBoard[i][j] > 0)
			{
			    oPiece++;
				for (int Dir = 0; Dir < 4; Dir++) {
					if (legal_SEF(i, j, Dir)) {
						sum--;
					}
				}

			}

		}
	}
   //std::cout<<"SEF EXECUTED ON BELOW BOARD\n";
   //display();
    return (sum+(pb-oPiece));
}



/*SHOULD CONSIDER MAKING MORE FUNCTIONS OUT OF THINGS IN MAIN!!*/
int main() {

	int Dir = 0;
	int level=0;
	int i,j,k,m, alpha, beta, state;

    char correct, ans;
	bool first, AIturn, ingameState, right;
	bool cor=true;
	player player;
	board board, board1, board2, board3, board4, board5, board6, board7, board8;
	/**odd numbered depths end on min nodes, even on max. This doesn't work.**/
	std::cout<<"depth = "<< depth<<". (This should be an even number)\n";
	std::cout<<"\n";
	ingameState = true;

	player.jokes();
	right=board.setZpgame();
	if (right){
        board.zpgame=true;
	}
	first=board.setColor();
	if (first == true) {
		AIturn = true;
	}
	else{
        AIturn=false;
	}
	/**SETS BOARD UP**/
    board.manualOverride();
    board1=board;
    board2=board;
    board3=board;
    board4=board;
    board5=board;
    board6=board;
    board7=board;
    board8=board;
	while (ingameState == true) {
        if(board.bval<-500){
            if(AIcolor=1)
            {
                cout<<"Game Over, Black loses";
            }
            else
            {
                cout<<"Game over, White loses";
            }
        break;
        }

		if (AIturn) {
            board1=board;
            board2=board;
            board3=board;
            board4=board;
            board5=board;
            board6=board;
            board7=board;
            board8=board;
			thread th1( &board::threadKonane, &board1, 0, 1,2,depth,AIcolor);
			thread th2( &board::threadKonane, &board2, 1, 1,2,depth,AIcolor);
			thread th3( &board::threadKonane, &board3, 2, 1,2,depth,AIcolor);
			thread th4( &board::threadKonane, &board4, 3, 1,2,depth,AIcolor);
			thread th5( &board::threadKonane, &board5, 4, 1,2,depth,AIcolor);
			thread th6( &board::threadKonane, &board6, 5, 1,2,depth,AIcolor);
			thread th7( &board::threadKonane, &board7, 6, 1,2,depth,AIcolor);
			thread th8( &board::threadKonane, &board8, 7, 1,2,depth,AIcolor);
			th1.join();
			th2.join();
			th3.join();
			th4.join();
			th5.join();
			th6.join();
			th7.join();
			th8.join();
			board = board.comparison(board1, board2, board3, board4, board5, board6, board7, board8);
			board.display();

            board.makeMove(board.bestmove, AIcolor);
            board.displayMove();
			board.display();
			AIturn = false;
			turn++;
            if(board.bval<-500){
                if(AIcolor=1)
                {
                    cout<<"Game Over, Black loses";
                }
                else
                {
                    cout<<"Game over, White loses";
                }
                break;
            }
            }
            /** if PLAYING AGAINST ITSELF OR A SIMILAR AI W A DIFFERENT SEF**/
            if((right) && (AIturn==false)){
                board1=board;
                board2=board;
                board3=board;
                board4=board;
                board5=board;
                board6=board;
                board7=board;
                board8=board;
                thread th1( &board::threadKonane, &board1, 0, 1,2,depth,humanColor);
                thread th2( &board::threadKonane, &board2, 1, 1,2,depth,humanColor);
                thread th3( &board::threadKonane, &board3, 2, 1,2,depth,humanColor);
                thread th4( &board::threadKonane, &board4, 3, 1,2,depth,humanColor);
                thread th5( &board::threadKonane, &board5, 4, 1,2,depth,humanColor);
                thread th6( &board::threadKonane, &board6, 5, 1,2,depth,humanColor);
                thread th7( &board::threadKonane, &board7, 6, 1,2,depth,humanColor);
                thread th8( &board::threadKonane, &board8, 7, 1,2,depth,humanColor);
                th1.join();
                th2.join();
                th3.join();
                th4.join();
                th5.join();
                th6.join();
                th7.join();
                th8.join();
                board = board.comparison (board1, board2, board3, board4, board5, board6, board7, board8);
                board.display();

				board.makeMove(board.bestmove, humanColor);
				board.displayMove();

                board.display();
                AIturn = true;
                turn++;
                if(board.bval<-500){
                    if(humanColor=2)
                    {
                        cout<<"Game Over, Black loses";
                    }
                    else
                    {
                        cout<<"Game over, White loses";
                    }
                    break;
                }
                }
            /** if PLAYING A HUMAN**/
		if((!right) && (AIturn==false)) {
            do{
                std::cout << "\nenter piece to move column, 1-8: ";
                std::cin >> j;
                //accomodate indexing
                j--;
                board.bestmove[1]=j;
                std::cout << "\nenter piece to move row, 1-8: ";
                std::cin >> i;
                i--;
                board.bestmove[0]=i;
                std::cout << "\nenter piece destination column, 1-8: ";
                std::cin >> m;
                m--;
                board.bestmove[3]=m;
                std::cout << "\nenter piece destination row, 1-8: ";
                std::cin >> k;
                k--;
                board.bestmove[2]=k;
                cor=board.guardRails();
            }while(! cor);

			board.makeMove(board.bestmove,humanColor);
			board.displayMove();
			board.display();
			turn++;
			AIturn=true;
			}
        std::cout<<  "\nassuming correct board and continue\n";
        //std::cout << "\n is board correct? y for yes, n for no \n \n";
        //std::cin >> ans;
	}
	std::cout<<"finished in "<<turn<<" turns";
	std::cin>>ans;
	return 0;
}


