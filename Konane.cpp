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

class board {
	int B = 2;
	int W = 1;
	int Dir = 0;
	int depth;
	int color;
	int first;

	int board[8][8] = {
		{B,W,B,W,B,W,B,W}
		{W,B,W,B,W,B,W,B}
		{B,W,B,W,B,W,B,W}
		{W,B,W,B,W,B,W,B}
		{B,W,B,W,B,W,B,W}
		{W,B,W,B,W,B,W,B}
		{B,W,B,W,B,W,B,W}
		{W,B,W,B,W,B,W,B};
	}
public:
	/*all functions void functions until code is fully determined.*/
	void setFirst();
	int getFirst();
	void setColor();
	int getColor();
	void display();
	void setBoard();
};
void board::setFirst() {
	cout << "who is first? \n select 1 for AI and 2 for opponent: ";
	cin >> first;
}
void board::setColor() {
	cout << "\n What color is the AI? \n 1 for white and 2 for black:";
	cin >> color;
}
int board::getFirst() { return first; }
int board::getColor() { return color; }
void board::display() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j] > 1) {
				cout << "B_";
			}
			else if (board[i][j] > 0) {
				cout << "W_";
			}
			else {
				cout << "0_";
			}
		}
		cout << "\n";
	}
}

void board::setBoard() {
	int p = 0;
	int i, j;
	cout << "What pieces will be removed? choose row and column for each.  (manual adjacency test)";
	while (p < 2) {
		cout << "\n row :";
		cin >> j;
		cout << " \n column: ";
		cin >> i;

		p++;
		if (i > 7 || i < 0 || j>7 || j < 0)
		{
			cout << "invalid choice, restarting selection";
			p = 0;
		}
		else
		{
			i = 0;
			j = 0;
			cout << "\n row :";
			cin >> i;
			cout << " \n column: ";
			cin >> j;

			p++;
			if (i > 7 || i < 0 || j>7 || j < 0)
			{
				cout << "invalid choice, restarting selection";
				p = 0;
			}

		}
		i = 0;
		j = 0;
	}
}

	void setDepth();   //sets depth for sim 

	/*AI Game Playing Functions, in a loop every turn*/
	void legalMove();   //test for legality of move
	void makeMove();	//move chosen for recursive call, else chosen for game
	void ABmax();		//maximizer for AI sim, may want it to be separate from this class?
	void ABmin();       //minimizer for AI sim, may want it to be separate from this class?
	void SEF();         //State Evaluation Function, primitive for now, tests number of moves possible for player.

	/*Make a move in-game*/
	void chosenMove();  //states move chosen, implements... probably unneccessary
}


}
int main() {

	int B = 2;
	int W = 1;
	int Dir = 0;
	int depth;
	bool color;
	bool first;
	int p = 0;
	int i=0;
	int j = 0;
	char correct;
	board board;

	board.setFirst();
	board.setColor();
	board.setBoard();
	//print board
	//set correct as user

	return 0;
}



bool legal_move(board, i, j, Dir)
{
	if (Dir = N)
	{
		i = i - 1;
		state=isFull(board, i, j);
		if state ==true
		i = i - 1;


bool isFull(board, i, j)
{
	if (board[i][j] = 0)
	{
		return false;
	}
	else {
		return true;
	}
}


