
#include "board.h"

/**Parallel Elements not used in Konane**/
int board::calibrate(int i, int playerColor)
{
	if (playerColor == 2)
        {return i % 2;}
	//starting index of an even i will be 0
	//starting index of an even i will be 1
    return (i + 1) % 2;
}

void board::threadKonane(int i,int alpha, int beta, int depth, int levelColor){
   int opColor = levelColor%2;
    opColor++;
    /**RESOLVE MATH AFTER SUCCESSFUL TEST**/
	int currentmove[4];
	int val = MIN;
    int temp = MIN;
	bval = MIN;
for (int j = calibrate(i, levelColor); j < 8; j = j + 2)
	{
		if (objBoard[i][j] > 0)
		{
			for (int Dir = 0; Dir < 4; Dir++) {
				if (legal_move(currentmove, i, j, Dir)) {
					/*****MOVE PIECE*****/
					makeMove(currentmove, levelColor);
					//calls for minimization using the opposing color
					//needs some work.

					//calling serial variation
					val = std::max(val, ABMin(alpha, beta, 1, depth, opColor));


					unmakeMove(currentmove, levelColor, opColor);

                    /**AT ROOT OF RECURSIVE TREE, IS CURRENT MOVE BEST?**/
					/**IF CURRENT MOVE BEST, CHANGE MOVE**/
                    //This normally happens at depth zero
                    //This IS "depth zero" as far as the code
                    //is concerned, hence this can happen here.
                    //could remove from other code.
					alpha = std::max(alpha, val);
                        if (temp < val) {
                            bval=val;
                            //the best move is the highest scoring move selected
                            bestmove[0] = currentmove[0];
                            bestmove[1] = currentmove[1];
                            bestmove[2] = currentmove[2];
                            bestmove[3] = currentmove[3];
                        }
				}
			}
		}
	}
	//cout << "SEF of thread "<<i<<" = "<<bval<<"\n";
return;
}


/***ALPHABETA MINIMAX BELOW***/

/***NEEDS FULL REFACTOR FOR THE PURPOSE OF ZERO PLAYER GAME***/
//for clarifications, refer to user doc.
int board::ABMax(int alpha, int beta, int level, int depth, int levelColor)
{
int sefVal, temp;
	/* Initial values of
	 * Alpha and Beta
	 * Terminating condition. i.e
	 *leaf node, is reached*/
    int opColor = levelColor%2;
    opColor++;
    /**RESOLVE MATH AFTER SUCCESSFUL TEST**/
	int currentmove[4];
	if (level == depth) {
			sefVal = SEF(levelColor);
			//std::cout << "\nSEF= " << tshoot << "\n";
			return sefVal;
	}
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
							val = std::max(val, ABMin(alpha, beta, level+1, depth, opColor));
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

int board::ABMin(int alpha, int beta, int level, int depth, int levelColor)
{
    int val = MAX;
    int opColor = levelColor%2;
    opColor++;
    /**RESOLVE MATH AFTER SUCCESSFUL TEST**/
	int currentmove[4];

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
							val = std::min(val, ABMax(alpha, beta, level+1, depth, opColor));
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
			return WIN;
		}
		return val;
}
// returns best board, to be set as correct board.  Resource intensive.  Has to be a better way.
board board::comparison (board board1, board board2, board board3, board board4, board board5, board board6, board board7, board board8)
{
    if (board1.bval<board2.bval)
    {
        cout << board1.bval<<"\n";
        board1=board2;
    }
    if (board1.bval<board3.bval)
    {
        cout << board1.bval<<"\n";
        board1=board3;
    }
    if (board1.bval<board4.bval)
    {
       cout << board1.bval<<"\n";
        board1=board4;
    }
    if (board1.bval<board5.bval)
    {
        cout << board1.bval<<"\n";
        board1=board5;
    }
    if (board1.bval<board6.bval)
    {
        cout << board1.bval<<"\n";
        board1=board6;
    }
    if (board1.bval<board7.bval)
    {   cout << board1.bval<<"\n";
        board1=board7;
    }
    if (board1.bval<board8.bval)
    {
        cout << board1.bval<<"\n";
        board1=board8;
        cout << board1.bval<<"\n";
    }

    return board1;
}


/***NEEDS FULL REFACTOR FOR THE PURPOSE OF ZERO PLAYER GAME***/

/**ZERO PLAYER GAME SELECTION**/
bool board::setZpgame(){
    char ans;
    do{
        cout << "Will I be playing Myself? \ny/n\n";
        cin >>ans;
        if (ans=='y'){
      		return true;
        }
	   if(ans == 'n'){
        	return false;
        }

    }while (true);

}
/**SAFETY FOR USER ERRORS**/
bool board::guardRails(){
    int i,j,k,m;
    i=bestmove[0];
    j=bestmove[1];
    k=bestmove[2];
    m=bestmove[3];
    //check for horizontal movement
    if(i==k||j==m){
		//check for even number of squares traversed, if mod 2 = zero, then move is probably legal, 
	    //player can still break game w illegal move, but player can flip the board in monopoly as well soooo....
        i=(abs(i-k))%2;
        j=(abs(j-m))%2;

        if (i==0&&j==0)
        {
            return true;
        }

    }
    cout << "incorrect move";
    return false;
}
/***ASSISTS MANUAL OVVERIDE***/
void board::selection(int S) {
	int startRow, startColumn;
	cout << "\n column (A-H = 1-8): ";
	cin >> startColumn;
	cout << "\n row (1-8): ";
	cin >> startRow;
	//accommodate array indicies.
	startRow--;
	startColumn--;
	if (startRow > 7 || startRow < 0 || startColumn>7 || startColumn < 0) {
		cout << "\n invalid choice, restarting selection";
	}

	else {
		objBoard[startRow][startColumn] = S;
	}
	return;
}


/***FOR SETUP, TESTING, AND MANUAL BOARD CORRECTIONS IF ERRORS MADE,***
 ***ASSUMES SOME INTELLIGENCE ON PART OF USER***/
 /***ZERO PLAYER GAME COMPATIBLE***/
void board::manualOverride() {
	char remadd, ans;
			while (ans != 'y') {
            display();

	cout <<  "\n\nX= Black, O = White, Spaces for empty squares\n\n";
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
                cout <<  "\n\nX= Black, O = White, Spaces for empty squares\n\n";
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
        cout <<  "\nI play as black and go first.";
        }
        else if (AIcolor == 1)
        {
            humanColor = 2;
            first = false;
            cout <<  "\nI play as white and go second.";
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

	if (objBoard[i][j] == 0){
		return false;
	}
	return true;
}



/***FAIRLY SIMPLE DISPLAY FUNCTION***/
void board::display() {
	int row = 0;
	cout << "   A B C D E F G H \n";
    cout << "   1 2 3 4 5 6 7 8 ";

	cout <<  "\n \n";
	for (int i = 0; i < 8; i++) {
        cout << ++row <<"  ";

		for (int j = 0; j < 8; j++) {


			if (objBoard[i][j] > 1) {
				cout << "X ";
			}
			else if (objBoard[i][j] > 0) {
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
cout << "\n"<<bestmove[0]+1<<", ";
cout << bestmove[1]+1<<", to ";
cout << bestmove[2]+1<<", ";
cout << bestmove[3]+1<<", \n your move\n";
}
/***       TESTS LEGALITY OF MOVE FOR SEF        ***/

/***State Evaluation form of Legal Move.         ***
*** Exists for the purposes of tallying possible ***
*** moves, this is sufficient a refactor         ***
*** may be desirable.  ZERO PLAYER GAME AGNOSTIC ***/
bool board::legal_SEF(int startRow, int startColumn, int Dir)
{
    int N = 0;
    int S = 1;
    int W = 2;
    int E = 3;

	int destRow = startRow;

	int destColumn = startColumn;

	bool state;

	if (Dir == N)
	{
		if (startRow > 1) {
			destRow--;
			state = isFull(destRow, destColumn);
			if (state == true) {
				destRow--;
				state = isFull(destRow, destColumn);
				if (state == false) {
					return true;
				}
			}

		}
	}
	if (Dir == S)
	{
		if (startRow < 6) {
				destRow++;
				state = isFull(destRow, destColumn);
				if (state == true) {
					destRow++;
					state = isFull(destRow, destColumn);
					if (state == false) {
						return true;
					}
				}
				}

		}
	if (Dir == W)
	{
		if (startColumn > 1) {
			destColumn--;
			state = isFull(destRow, destColumn);
			if (state == true) {
				destColumn--;
				state = isFull(destRow, destColumn);
				if (state == false) {
					return true;
				}
			}

		}
	}

	if (Dir == E)
	{
		if(startColumn < 6){
			destColumn++;
			state = isFull(destRow, destColumn);
			if (state == true) {
				destColumn++;
				state = isFull(destRow, destColumn);
				if (state == false) {
					return true;
				}
		}

		}
	}
	return false;
}

/***ACCOMODATING NEW COORDINATE SYSTEM ANNOUNCED      ***
 ***MESSY, REFACTOR IF TIME, IT IS COLOR AGNOSTIC     ***/

bool board::legal_move(int currentmove[], int startRow, int startColumn, int Dir)
{
    bool state;
    int destRow = startRow;
	int destColumn = startColumn;
	if (Dir == 0) //N
	{
		if (destRow > 1) {
            destRow--;
            state = isFull(destRow, destColumn);
            if (state == true) {
				destRow--;
				state = isFull(destRow, destColumn);
			if (state == false) {
                currentmove[0] = startRow;
                currentmove[1] = startColumn;
                currentmove[2] = destRow;
                currentmove[3] = destColumn;
                    if(destRow>1){
                        destRow--;
                        state = isFull(destRow, destColumn);
                        if (state == true) {
                            destRow--;
                            state = isFull(destRow, destColumn);
                            if (state == false) {
                                currentmove[2] = destRow;
                                currentmove[3] = destColumn;
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
        if (destRow < 6) {
            destRow++;
            state = isFull(destRow, destColumn);
            if (state == true) {
				destRow++;
				state = isFull(destRow, destColumn);
			if (state == false) {
                currentmove[0] = startRow;
                currentmove[1] = startColumn;
                currentmove[2] = destRow;
                currentmove[3] = destColumn;
                    if(destRow<6){
                        destRow++;
                        state = isFull(destRow, destColumn);
                        if (state == true) {
                            destRow++;
                            state = isFull(destRow, destColumn);
                            if (state == false) {
                                currentmove[2] = destRow;
                                currentmove[3] = destColumn;
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
		if (destColumn > 1) {
            destColumn--;
            state = isFull(destRow, destColumn);
            if (state == true) {
				destColumn--;
				state = isFull(destRow, destColumn);
			if (state == false) {
                currentmove[0] = startRow;
                currentmove[1] = startColumn;
                currentmove[2] = destRow;
                currentmove[3] = destColumn;
                    if(destColumn>1){
                        destColumn--;
                        state = isFull(destRow, destColumn);
                        if (state == true) {
                            destColumn--;
                            state = isFull(destRow, destColumn);
                            if (state == false) {
                                currentmove[2] = destRow;
                                currentmove[3] = destColumn;
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
		if (destColumn < 6) {
            destColumn++;
            state = isFull(destRow, destColumn);
            if (state == true) {
				destColumn++;
				state = isFull(destRow, destColumn);
			if (state == false) {
                currentmove[0] = startRow;
                currentmove[1] = startColumn;
                currentmove[2] = destRow;
                currentmove[3] = destColumn;
                    if(destColumn<6){
                        destColumn++;
                        state = isFull(destRow, destColumn);
                        if (state == true) {
                            destColumn++;
                            state = isFull(destRow, destColumn);
                            if (state == false) {
                                currentmove[2] = destRow;
                                currentmove[3] = destColumn;
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
{   //cout << "making move\n";
    int startRow,startColumn,destRow,destColumn;
    bool neq;
	startRow = currentmove[0];
	startColumn = currentmove[1];
	destRow = currentmove[2];
	destColumn = currentmove[3];
	//cout << " "<<startRow+1<<", "<<startColumn+1<<", "<<destRow+1<<", "<<destColumn+1<<"\n";
	neq = true;
    do {
    objBoard[startRow][startColumn] = 0;

    if (destRow < startRow)
    {
        objBoard[startRow - 1][startColumn] = 0;
        objBoard[startRow - 2][startColumn] = playerColor;
        startRow=startRow-2;
    }
    if (destRow > startRow)
    {
        objBoard[startRow + 1][startColumn] = 0;
        objBoard[startRow + 2][startColumn] = playerColor;
        startRow=startRow+2;
    }
    if (destColumn < startColumn)
    {
        objBoard[startRow][startColumn - 1] = 0;
        objBoard[startRow][startColumn - 2] = playerColor;
        startColumn=startColumn-2;
    }
    if (destColumn > startColumn)
    {
        objBoard[startRow][startColumn + 1] = 0;
        objBoard[startRow][startColumn + 2] = playerColor;
        startColumn=startColumn+2;
    }
    if((startRow==destRow)&&(destColumn==startColumn)){neq=false;}
    } while (neq);
    return;
}

/**UNMAKE MOVE IS COLOR-AGNOSTIC, ZERO PLAYER GAME WILL NOT REQUIRE A CHANGE HERE**/

void board::unmakeMove(int currentmove[],int playerColor, int opColor) {
    int startRow,startColumn,destRow,destColumn;
    bool neq=true;
	startRow = currentmove[0];
	startColumn = currentmove[1];
	destRow = currentmove[2];
	destColumn = currentmove[3];

	while (neq){
        //cout << "\nunmaking move: ";
		objBoard[destRow][destColumn] = 0;
		if (destRow > startRow)
		{
			objBoard[destRow - 1][destColumn] = opColor;
			objBoard[destRow - 2][destColumn] = playerColor;
            destRow=destRow-2;
            if(destRow==startRow)
            {
                break;
            }
		}
		if (destRow < startRow)
		{
			objBoard[destRow + 1][destColumn] = opColor;
			objBoard[destRow + 2][destColumn] = playerColor;
			destRow=destRow+2;
            if(destRow==startRow)
            {
            break;
            }
		}
		if (destColumn > startColumn)
		{
			objBoard[destRow][destColumn-1] = opColor;
			objBoard[destRow][destColumn-2] = playerColor;
			destColumn=destColumn-2;
            if(destColumn==startColumn)
            {
            break;
            }
		}
		if (destColumn < startColumn)
		{
			objBoard[destRow][destColumn+1] = opColor;
			objBoard[destRow][destColumn+2] = playerColor;
			destColumn=destColumn+2;
            if(destColumn==startColumn)
            {
            break;
            }
		}
}
}


int board::SEF(int playerColor) {
	int sumMoves=0;    //sum of total moves for SEF player
	int pb=0;     //Player pieces versus opponent pieces, ("piece balance")

	int opColor = playerColor%2;
	opColor++;
	for (int i = 0; i < 8; i++)
	{
		for (int j = calibrate(i, playerColor); j < 8; j = j + 2)
		{
			if (objBoard[i][j] > 0)
			{
				//pieces AI
			    pb++;
				for (int Dir = 0; Dir < 4; Dir++) {
					if (legal_SEF(i, j, Dir)) {
						//possible moves AI
						sumMoves++;
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
				//pieces player
			    pb--;
				for (int Dir = 0; Dir < 4; Dir++) {
					if (legal_SEF(i, j, Dir)) {
						//AI moves minus possible moves player
						sumMoves--;
					}
				}

			}

		}
	}
	
    return (sumMoves+pb); //all the moves possible for AI less the total moves possible by the player and the piece balance
}
