
#include "board.h"

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
