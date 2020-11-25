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
		 * 5. if legalmove returns true, form node (recursive call with new board) with move and repeat process board to obtain number.
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
#include <algorithm>
#include <chrono>
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
    cout << "Would you like to play a game? \n";
	cout << "1. Konane \n2. ALSO Konane\n3. Global Thermonuclear War\n";
	cin >> jokes;
	if (jokes == 3) {
		cout << "That game is SOOOOOOOO boring,let's play Konane!!!\n";
	}
}

void player::detectWL(int value){}

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
			//cout << "\nSEF= " << tshoot << "\n";
			return tshoot;
	}
	else if (maximizing == true)
	{/*PROBLEM!!!????*/
		int val = MIN;

		for (int i = 0; i < 8; i++)
		{
			for (int j = calibrate(i, levelColor); j < 8; j = j + 2)
			{
				if (board[i][j] > 0)
				{
					for (int Dir = 0; Dir < 4; Dir++) {
						if (legal_move(currentmove, i, j, Dir)) {
							/*****MOVE PIECE*****/
							makeMove(currentmove, levelColor);
							//calls for minimization using the opposing color
							temp = val;
							val = max(val, alphaBetaMinimax(alpha, beta, level + 1, depth, opColor, false));
							unmakeMove(currentmove, levelColor, opColor);
							/**AT ROOT OF RECURSIVE TREE, IS CURRENT MOVE BEST?**/
							/**IF CURRENT MOVE BEST, CHANGE MOVE**/
							if (level == 0 && temp < val) {
								bestmove[0] = currentmove[0];
								bestmove[1] = currentmove[1];
								bestmove[2] = currentmove[2];
								bestmove[3] = currentmove[3];
							}
							alpha = max(alpha, val);
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
        if (level == 0 && val == MIN && levelColor == 1)
		{
			return GAME_OVER_WHITE;
		}
        if (level == 0 && val == MIN && levelColor == 2)
		{
			return GAME_OVER_BLACK;
		}
		if (val == MIN)
		{
			return LOSE;
		}

    return val;
	}
	else
	{
		//cout << "minimizing \n";
		int val = MAX;
		for (int i = 0; i < 8; i++)
		{
			for (int j = calibrate(i, levelColor); j < 8; j = j + 2)
			{
				if (board[i][j] > 0)
				{
					for (int Dir = 0; Dir < 4; Dir++) {
						if (legal_move(currentmove, i, j, Dir)) {
                            /*    cout << "\n ";
							for (int z = 0; z < 4; z++) {
								cout << currentmove[z] + 1;
							}
                            cout << "\n ";
                            */

							makeMove(currentmove, levelColor);
							val = min(val, alphaBetaMinimax(alpha, beta, level + 1, depth, opColor, true));
							beta = min(beta, val);
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
	cout << "ERROR";
	return -1;
}
/**ZERO PLAYER GAME SELECTION**/
bool board::setZpgame(){
    char ans;
    do{
        cout<<"Will I be playing Myself? \ny/n\n";
        cin>>ans;
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
/*bool board::guardRails(){
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
        cout<<"incorrect move";
        return false;
    }
}*/
/***ASSISTS MANUAL OVVERIDE***/
void board::selection(int S) {
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
		board[i][j] = S;
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

	cout<< "\n\nX= Black, O = White, Spaces for empty squares\n\n";
	cout << "r = Removal of piece, b = add black, w = add white e = exit \n";
	cin >> remadd;
		while (remadd != 'e') {
			if (remadd == 'e'){}
			else if (remadd == 'r')
			{
				cout << "What pieces will be removed? choose row and column for each.  (NO adjacency test)\n";
				selection(0);
			}
			else if (remadd == 'b')
			{
				cout << "What black pieces will be added? choose row and column for each.  (NO adjacency test)\n";
				selection(2);
			}
			else if (remadd == 'w') {
				cout << "What white pieces will be added? choose row and column for each.  (NO adjacency test)\n";
				selection(1);
			}
			else{
				cout <<"\n invalid choice, restarting selection\n";
                display();
                cout<< "\n\nX= Black, O = White, Spaces for empty squares\n\n";
                cout << "r = Removal of piece, b = add black, w = add white e = exit \n";
                cin >> remadd;
			}
        display();
        cout << "r = Removal of piece, b = add black, w = add white e = exit \n";
        cin >> remadd;
	}
    display();
    cout << "\n is board correct? y for yes, n for no \n \n";
	cin >> ans;
}
}



/***  CRITICAL FOR ENTIRE GAME, SET COLOR AND FIRST GLOBALS HERE  ***/
/***GIVEN CURRENT USAGE, IS NOT INCOMPATIBLE WITH ZERO PLAYER GAME***/
bool board::setColor() {
    char ans='n';
    bool first;
    while (ans != 'y') {

		cout << "\nWhat color should 'I' play as? \n 1 for white and 2 for black:\n(black goes first per Konane rules \n black is X, white is O)\n ";
        cin >> AIcolor;

        if (AIcolor == 2)
        {
            humanColor = 1;
            first = true;
        cout<< "\nI play as black and go first.";
        }
        else if (AIcolor == 1)
        {
            humanColor = 2;
            first = false;
            cout<< "\nI play as white and go second.";
        }
        else {
            cout << "\nerror, restarting";
        }
        cout << "\nIs this correct? y for yes:\n";
		cin >> ans;
	}
	return first;
}


/***SPACE TEST FOR PRESENCE OF PIECE***/
/***       COLOR AGNOSTIC           ***/
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


/***FAIRLY SIMPLE DISPLAY FUNCTION***/
void board::display() {
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
				cout << "O ";
			}
			else {
				cout << "  ";
			}
		}
		cout << "\n";
	}
}
void board::displayMove(){
cout<<"\n"<<bestmove[0]+1<<", ";
cout<<bestmove[1]+1<<", to ";
cout<<bestmove[2]+1<<", ";
cout<<bestmove[3]+1<<", \n your move\n";
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
{   //cout<<"making move\n";
    int i,j,k,m;
    bool neq;
	i = currentmove[0];
	j = currentmove[1];
	k = currentmove[2];
	m = currentmove[3];
	//cout<<" "<<i+1<<", "<<j+1<<", "<<k+1<<", "<<m+1<<"\n";
	neq = true;
    do {
    board[i][j] = 0;

    if (k < i)
    {
        board[i - 1][j] = 0;
        board[i - 2][j] = playerColor;
        i=i-2;
    }
    if (k > i)
    {
        board[i + 1][j] = 0;
        board[i + 2][j] = playerColor;
        i=i+2;
    }
    if (m < j)
    {
        board[i][j - 1] = 0;
        board[i][j - 2] = playerColor;
        j=j-2;
    }
    if (m > j)
    {
        board[i][j + 1] = 0;
        board[i][j + 2] = playerColor;
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
        //cout << "\nunmaking move: ";
		board[k][m] = 0;
		if (k > i)
		{
			board[k - 1][m] = opColor;
			board[k - 2][m] = playerColor;
            k=k-2;
            if(k==i)
            {
                break;
            }
		}
		if (k < i)
		{
			board[k + 1][m] = opColor;
			board[k + 2][m] = playerColor;
			k=k+2;
            if(k==i)
            {
            break;
            }
		}
		if (m > j)
		{
			board[k][m-1] = opColor;
			board[k][m-2] = playerColor;
			m=m-2;
            if(m==j)
            {
            break;
            }
		}
		if (m < j)
		{
			board[k][m+1] = opColor;
			board[k][m+2] = playerColor;
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
			if (board[i][j] > 0)
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
			if (board[i][j] > 0)
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
   //cout<<"SEF EXECUTED ON BELOW BOARD\n";
   //display();
    return (sum+(pb-oPiece));
}


void write_csv(double input[], int totalMoves){

    // Make a CSV file with one or more columns of integer values
    // Each column of data is represented by the pair <column name, column data>
    //   as std::pair<std::string, std::vector<int>>
    // The dataset is represented as a vector of these columns
    // Note that all columns should be the same size

    // Create an output filestream object
    std::ofstream csv("normal-moves-14-1.csv");
    csv<<"Turn, Time \n";
    for(int i=0;i<totalMoves;i++){
        csv<<i+1<<","<<input[i]<<"\n";
    }


    // Close the file
    csv.close();
}


/*SHOULD CONSIDER MAKING MORE FUNCTIONS OUT OF THINGS IN MAIN!!*/
int main() {

	int Dir = 0;
	int level=0;
	int turn=0;
	int i,j,k,m,z, alpha, beta, state;
	double tc;
    double csv[50];
    duration<double> timeCount;
    char correct, ans;
	bool first, AIturn, right;
	bool cor=true;
	player player;
	board board;
	/**odd numbered depths are on min nodes, even on max. This doesn't work.**/
	cout<<"depth = "<< depth<<". (This should be an even number)\n";
	cout<<"\n";


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
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
	while (true) {

        //cout<<"\nSEF = " <<state <<"\n";
		if (AIturn) {
                high_resolution_clock::time_point tpre = high_resolution_clock::now();
                //ERROR ON FIRST AND SECOND PARAMETERS?
			state=board.alphaBetaMinimax(1, 2, level, depth, AIcolor, true);
			board.display();

        if (state== WIN)
        {
            cout << "It looks like I will win soon, but I am buggy as heck, so let's keep playing. \n";
            board.makeMove(board.bestmove, AIcolor);
            board.displayMove();
        }
			else if (state == LOSE)
			{
				cout << "It looks like I will lose soon, but we should play it out.\n";
				board.makeMove(board.bestmove, AIcolor);
				board.displayMove();
			}
			else {
				board.makeMove(board.bestmove, AIcolor);
				board.displayMove();

			}
			board.display();
			AIturn = false;
			turn++;
            high_resolution_clock::time_point tpost = high_resolution_clock::now();
			timeCount = duration_cast<duration<double>>(tpost-tpre);
            tc=timeCount.count();
            std::cout<<"\n"<<tc<<"\n";
            csv[turn-1]=tc;
			//cout<<"\nSEF = " <<state <<"\n";
            }
            /** if PLAYING AGAINST ITSELF OR A SIMILAR AI W A DIFFERENT SEF**/
            else if((right) && (AIturn==false)){
            high_resolution_clock::time_point tpre = high_resolution_clock::now();
            state=board.alphaBetaMinimax(1, 2, level, depth, humanColor, true);
			board.display();
			if (state== WIN)
			{
				cout << "It looks like I will win soon, but I am buggy as heck, so let's keep playing. \n";
				board.makeMove(board.bestmove, humanColor);
				board.displayMove();
			}
			else if (state == LOSE)
			{
				cout << "It looks like I will lose soon. If I were built by Cyberdine, I could send someone back to 'fix' this... \n";
				board.makeMove(board.bestmove, humanColor);
				board.displayMove();
			}
			else {
				board.makeMove(board.bestmove, humanColor);
				board.displayMove();
				}
			board.display();
			AIturn = true;
			turn++;
            high_resolution_clock::time_point tpost = high_resolution_clock::now();
            timeCount = duration_cast<duration<double>>(tpost-tpre);
            tc=timeCount.count();
            std::cout<<"\n"<<tc<<"\n";
            csv[turn-1]=tc;
            }
            /** if PLAYING A HUMAN**/
		else {
            do{
                cout << "\nenter piece to move column, 1-8: ";
                cin >> j;
                //accomodate indexing
                j--;
                board.bestmove[1]=j;
                cout << "\nenter piece to move row, 1-8: ";
                cin >> i;
                i--;
                board.bestmove[0]=i;
                cout << "\nenter piece destination column, 1-8: ";
                cin >> m;
                m--;
                board.bestmove[3]=m;
                cout << "\nenter piece destination row, 1-8: ";
                cin >> k;
                k--;
                board.bestmove[2]=k;
                cor=true;
                //guard rails here
            }while(! cor);

			board.makeMove(board.bestmove,humanColor);
			board.displayMove();
			board.display();
			turn++;
			AIturn=true;
			}
			        if(state==GAME_OVER_BLACK)
            {
            cout<<"Black Loses\n";
            break;
            }
        if(state==GAME_OVER_WHITE)
            {
            cout<<"White Loses\n";
            break;
            }
        cout<<  "\nassuming correct board and continue\n";
        //cout << "\n is board correct? y for yes, n for no \n \n";
        //cin >> ans;
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	 duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
	std::cout<<"finished in "<<turn<<" turns";
    std::cout << "It took me " << time_span.count() << " seconds.";
    for(z=0;z<turn;z++)
    {std::cout<<"turn " <<z+1<< " took "<<csv[z]<<" seconds \n";}
    write_csv(csv, turn);
	return 0;
}
