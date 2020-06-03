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
/* STANDARD INCLUDES FROM LIBRARY FILES AND NAMESPACE */
#include "standard.h"
#include "const.h"

/*dynamic globals, may alter as needed*/

/*AI FIRST*/
bool first;
/*AI TURN*/
int turn;

//color is AI, humanColor is opponent
int AIcolor, humanColor;


/*int getFirst{return first;}
int getColor {return AIcolor;}
int getPlayerColor {return playerColor;}
int getDepth {return depth;}*/
class board {
	static const int B = 2;
	static const int W = 1;

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
    int SEF(int pass);
	void selection(int S);
	/*
	int minimax(int level,int depth);
	TODO make below functions
	manualOverride
	*/

};


/*ALPHABETA MINIMAX BELOW*/
int board::alphaBetaMinimax(int alpha, int beta, int level, int depth, int levelColor, bool maximizing)
{
	int temp;
	int k, m, tshoot;
	/* Initial values of
	 * Alpha and Beta
	 * Terminating condition. i.e
	 *leaf node, is reached*/
	int currentmove[4];
	if (level == depth) {
			tshoot = SEF(depth);
			cout << "\nSEF= " << tshoot << "\n";
			return tshoot;
	}
	else if (maximizing == true)
	{/*PROBLEM!!!????*/
		int val = MIN;

		for (int i = 0; i < 8; i++)
		{
			for (int j = calibrate(i, AIcolor); j < 8; j = j + 2)
			{
				if (board[i][j] > 0)
				{
					for (int Dir = 0; Dir < 4; Dir++) {
						if (legal_move(currentmove, i, j, Dir)) {
							/*****MOVE PIECE*****/
							makeMove(currentmove, AIcolor);
							//calls for minimization using the human color
							temp = val;
							val = max(val, alphaBetaMinimax(alpha, beta, level + 1, depth, humanColor, false));
							unmakeMove(currentmove, AIcolor, humanColor);
							if (level == 0 && temp <= val) {
								bestmove[0] = currentmove[0];
								bestmove[1] = currentmove[1];
								bestmove[2] = currentmove[2];
								bestmove[3] = currentmove[3];
							}
							cout << val;
							alpha = max(alpha, val);

							if (beta <= alpha) {
								return alpha;
							}
						}
					}
				}
			}
		}
		//if no change to value, no legal moves
		if (val == MIN)
		{
			return LOSE;
		}
		if (level == 0 && val == 0)
		{
			return LOSE_GAME;
		}
		return val;
	}
	else
	{
		cout << "minimizing \n";
		int val = MAX;
		for (int i = 0; i < 8; i++)
		{
			for (int j = calibrate(i, humanColor); j < 8; j = j + 2)
			{
				if (board[i][j] > 0)
				{
					for (int Dir = 0; Dir < 4; Dir++) {
						if (legal_move(currentmove, i, j, Dir)) {
							for (int z = 0; z < 4; z++) {
								cout << " " << currentmove[z] + 1 << " ";
							}

							makeMove(currentmove, humanColor);
							val = min(val, alphaBetaMinimax(alpha, beta, level + 1, depth, AIcolor, true));
							//best = min(best, val);
							beta = min(beta, val);
							unmakeMove(currentmove, humanColor, AIcolor);
							// Alpha Beta Pruning
							if (beta <= alpha) {
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
}


/***NEEDED FOR FIRST TURN, NOT NEEDED AFTER
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
***/

/***CRITICAL FOR ENTIRE GAME, SET COLOR AND FIRST GLOBALS HERE***/
void board::setColor() {
    char ans='n';
    while (ans != 'y') {

		cout << "\n What color should 'I' play as? \n 1 for white and 2 for black:\n(black goes first per Konane rules)";
        cin >> AIcolor;

        if (AIcolor == 2)
        {
            humanColor = 1;
            first = true;
        cout<< "\n I play as black and go first.";
        }
        else if (AIcolor == 1)
        {
            humanColor = 2;
            first = false;
            cout<< "\n I play as white and go second.";
        }
        else {
            cout << "\nerror, restarting";
        }
        cout << "\nIs this correct? y for yes";
		cin >> ans;
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
                currentmove[2] = k;display();
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
****MAKES MOVE RECORDED BY LEGAL MOVE***
****MAY BE REFACTORED INTO LEGAL MOVE (NON SEF)***/
void board::makeMove(int currentmove[], int playerColor)
{   cout<<"making move\n";
    int i,j,k,m;
    bool neq;
	i = currentmove[0];
	j = currentmove[1];
	k = currentmove[2];
	m = currentmove[3];
	cout<<" "<<i+1<<", "<<j+1<<", "<<k+1<<", "<<m+1<<"\n";
	neq = true;
    while (neq){
    board[i][j] = 0;

    if (k < i)
    {
        board[i - 1][j] = 0;
        board[i - 2][j] = playerColor;
        i=i-2;
        if(k==i)
        {
        break;
        }
    }
    if (k > i)
    {
        board[i + 1][j] = 0;
        board[i + 2][j] = playerColor;
        i=i+2;
        if(k==i)
        {
        break;
        }
    }
    if (m < j)
    {
        board[i][j - 1] = 0;
        board[i][j - 2] = playerColor;
        j=j-2;
        if(m==j)
        {
        break;
        }
    }
    if (m > j)
    {
        board[i][j + 1] = 0;
        board[i][j + 2] = playerColor;
        j=j+2;
        if(m==j)
        {
        break;
        }
    }
    }
    return;
}



void board::unmakeMove(int currentmove[],int playerColor, int opColor) {
    int i,j,k,m;
    bool neq=true;
	i = currentmove[0];
	j = currentmove[1];
	k = currentmove[2];
	m = currentmove[3];

	while (neq){
        cout << "\nunmaking move: ";
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

	/*AI Game Playing Functions, in a loop every turn
	void ABmax();		//maximizer for AI sim, may want it to be separate from this class?
	void ABmin();       //minimizer for AI sim, may want it to be separate from this class?
	Make a move in-game
	void chosenMove();  //states move chosen, implements... probably unneccessary*/

	/*    if(first){
        pb
    }
The minimax algorithm begins at the current state of the game recursively searching the
game tree for the optimal move depth-first, which means exploring a branch as far as it goes and
then backtracking until a path that has not been explored is found. Once the algorithm reaches a
leaf node, which indicates a terminal state, or reaches the specified search depth in the game tree
the utility(best/worst) value of the node is returned.
*/





int board::SEF(int pass) {
	int sum=0;
	int eb,pb, oPiece;
	//pb=30;
	//eb=(pb-(turn+pass));
    if(first){
       oPiece++;
    }
    else{pb++;}
	for (int i = 0; i < 8; i++)
	{
		for (int j = calibrate(i, AIcolor); j < 8; j++)
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
		for (int j = calibrate(i, humanColor); j < 8; j++)
		{
			if (board[i][j] > 0)
			{
			    oPiece++;
				for (int Dir = 0; Dir < 4; Dir++) {
					if (legal_SEF(i, j, Dir)) {
						sum++;
					}
				}

			}

		}
	}
   cout<<"SEF EXECUTED ON BELOW BOARD";
   display();
    return (sum+(pb-eb));
}




int main() {

	int Dir = 0;
	int i,j,k,m, alpha, beta, state;
	int level=0;
	int jokes;
	//odd numbered depths are on min nodes, even on max.
	int depth, setdepth;
	cout<<"Set Depth?\n";
	cin>>depth;
	setdepth=depth;
	cout<<"\n";
	bool AIturn, ingameState;
	ingameState = true;
	char correct, ans;
	board board;
	cout << "Would you like to play a game? \n";
	cout << "1. Konane \n2. ALSO Konane\n3. Global Thermonuclear War\n";
	cin >> jokes;
	if (jokes == 3) {
		cout << "That game is SOOOOOOOO boring,let's play Konane!!!\n";
	}
	board.setColor();
	if (first == true) {
		AIturn = true;
	}
	else{
        AIturn=false;
	}
	board.display();

	while (ingameState == true) {
		while (ans != 'y') {
			board.manualOverride();
			board.display();
            cout << "\n is board correct? y for yes, n for no \n \n";
			cin >> ans;
		}
		if (AIturn == true) {
			state=board.alphaBetaMinimax(1, 2, level, depth, AIcolor, true);
			board.display();
            if (state == LOSE_GAME)
			{
				//LOSE FIX IN MINMAX
				cout << "I think I just lost.  If I were built by Cyberdine, I could send someone back to 'fix' this... \n";

			}
			else if (state== WIN)
			{
				cout << "It looks like I will win soon, but I am buggy as heck, so let's keep playing. \n";
				board.makeMove(board.bestmove, AIcolor);
			}
			else if (state == LOSE)
			{
				cout << "It looks like I will lose soon, but we should play it out.\n";
				board.makeMove(board.bestmove, AIcolor);
			}
			else {
				board.makeMove(board.bestmove, AIcolor);
				cout<<board.bestmove[0]+1<<", "<<board.bestmove[1]+1<<", to "<<board.bestmove[2]+1<<", "<<board.bestmove[3]+1<<", \n your move\n ";

			}
			board.display();
			AIturn = false;
            }
		else {
			cout << "\nenter piece to move column, 1-8: ";
			cin >> j;
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

			board.makeMove(board.bestmove,humanColor);
			board.display();
			turn++;
			AIturn=true;
		}
            cout << "\n is board correct? y for yes, n for no \n \n";
			cin >> ans;
	}
	return 0;
}
