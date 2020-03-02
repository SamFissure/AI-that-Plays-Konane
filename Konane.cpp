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


int depth;
int color;
int humanColor;
bool first=true;

/*int getFirst{return first;}
int getColor {return color;}
int getPlayerColor {return playerColor;}
int getDepth {return depth;}*/
class board {
	int B = 2;
	int W = 1;
	int X = 0;
	int Dir = 0;
	int drti = 0;
	/*TODO set this in set color*/

	/*set the Static ints before compile,
	fine tune as needed with each compile*/


	int bestmove[4];
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

	void display();
	void manualOverride(); //piece removal, for fixing board errors and for setup.
	bool isFull(int i, int j);
	//test for legality of move
	bool legal_move(int i, int j, int Dir);
	void makeMove(int i, int j, int Dir, int playerColor);
	int calibrate(int i, int color);
    int alphaBetaMinimax(int alpha, int beta, int level, int depth);
    int static_eval();
	void selection(int S);
	/*
	int minimax(int level,int depth);
	/*TODO make below functions
	manualOverride

	*/

};

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

void board::manualOverride() {
	int p = 0;
	int i, j;
	char ans, ans2, remadd;
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



void board::setFirst() {
	int select;
	char ans;
	while (ans != y) {
		cout << "who is first? \n select 1 for AI and 2 for opponent: ";
		cin >> select;
		if {select = 2)
		{
		first == false;
		cout << "You go first";
		}
		else if (select = 1)
		{
			first == true;
			cout << " 'I' go first";
		}
		else {
			cout << "error"
		}
		cout << "Is this correct? y for yes";
		cin << ans;
	}
	}
}

void board::setColor() {
	cout << "\n What color is the AI? \n 1 for white and 2 for black:";
	cin >> color;
	if (color = 2)
	{
		humanColor == 1;
	}
	else if (color = 1)
	{
		humanColor == 2;
	}
	else {
		cout << "error"
	}
}
/*MAY NOT BE NEEDED*/

bool board::isFull(int i, int j) {

	if (board[i][j] = 0){
		return false;
	}

	else {
		return true;
	}
}


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





bool board::legal_move(int i, int j, int Dir, int dtri)
{
    int k = i;
	int m = j;
    bool state;
	if (Dir = 0) //N
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
	if (Dir = 1) //S
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
	if (Dir = 2)  //W
	{
		if (j > 1) {
			m--;
			state = isFull(k, m);
			if (state == true) {
				m--;
			}
			state = isFull(k, m);
			if (state == false) {
				return true;
			}
		}
	}

	if (Dir = 3) //E
	{
		m++;
		state = isFull(k, m);
		if (state == true) {
			m++;
		}
		state = isFull(k, m);
		if (state == false) {
			return true;
		}
	}
	//make move? or not.
}

void board::makeMove(int i, int j, int Dir, int playerColor, int dtri) {

	board[i][j] = 0 ;

	if (i > 1 && Dir == 0)
	{
		board[i - 1][j] = 0;
		board[i - 2][j] = playerColor;
	}
	if (i < 6 && Dir == 1)
	{
		board[i + 1][j] = 0;
		board[i + 2][j] = playerColor;
	}
	if (j > 1 && Dir == 2)
	{
		board[j - 1][j] = 0;
		board[j - 2][j] = playerColor;
	}
	if (j < 6 && Dir == 3)
	{
		board[j + 1][j] = 0;
		board[j + 2][j] = playerColor;
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



int board::alphaBetaMinimax(int alpha, int beta, int level, int depth)
{
	// Initial values of
	// Alpha and Beta
	// Terminating condition. i.e
	// leaf node is reached
	if (level == depth) {
		return board.static_eval(); //Need to fix the board
	}
     if (level % 2 == 0)
    {/*PROBLEM!!!????*/
        int best = MIN;

        for(int i=0;i<8;i++)
            {
            	for(int j=calibrate(i, color);j<8;j+2)
            	{
            		if(board[i][j]>0)
            		{
						for (int Dir = 0; Dir < 4; Dir++) {
							legal_move(i, j, Dir);
							/*****MOVE PIECE*****/
							int val = minimax(alpha, beta, level + 1, depth);
							held = max(best, val);
							best = max(best, val);
							alpha = max(alpha, best);
							if (val > best && level == 0) {
								//record move to array in terms of i,j,k,m
							}
							else {
								//no change to array
							}
							alpha = max(alpha, best);
							if (level == 0) {

							}
							// Alpha Beta Pruning
							if (beta <= alpha) {
								break;
							}
						}
						if (beta <= alpha) {
							break;
						}
        			}
					if (beta <= alpha) {
						break;
					}

    			}
				if (beta <= alpha) {
					break;
				}
    		}
		return best;
    }
    else
    {
        int best = MAX;


        for(int i=0;i<8;i++)
            {
            	for(int j=calibrate(i, playerColor);j<8;j+2)
            	{
            		if(board[i][j]>0)
            		{
						/*****MOVE PIECE*****/
            			int val = minimax(alpha, beta, level+1,depth);
            			best = min(best, val);
            			beta = min(beta, best);

            			// Alpha Beta Pruning
            			if (beta <= alpha)
                			break;
        		}
        		return best;
   		}
	   }
	}

}

int board::static_eval() {

            for(int i=0;i<8;i++)
            {
            	for(int j=0;j<8;j++)
            	{
            		if(board[i][j]>0)
            		{
            			int count=0;
            		    for(int Dir=0;Dir<4;Dir++){
            				if(legal_move(i,j,Dir)){
            					count++;
							}

            			}

            		}
            		return count;
            	}
            }
}
*/

int board::static_eval() {
	int count = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (board[i][j] > 0)
			{

				for (int Dir = 0; Dir < 4; Dir++) {
					if (legal_move(i, j, Dir)) {
						count++;
					}

				}

			}
			return count;
		}
	}
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
	bool color, first AIturn;
	bool, ingameState == true;
	char correct;
	board board;

	board.setFirst();
	if (first == true) {
		AIturn == true
	}
	board.setColor();
	board.display();
	board.manualOverride();
	cout << "\n is board correct? y for yes, n for no \n \n";
	while (ingameState == true) {
		while (ans != 'y') {
			board.manualOverride();
			cout << "\n is board correct? y for yes, n for no \n \n";
			board.display();
			cin << ans;
		}

		if (AIturn == true) {
			board.
			//make move
		}

		else {
			//Need a take player input function
			board.makeMove(i, j, Dir, playerColor);
			//take input for move from player
		}

	}
	
/*	if (board.getFirst = 1)
	{
		//generate tree
		//move
		//move order is set in class.
	}
	else
	{
		//take input and wait.
	}*/
	return 0;
}
