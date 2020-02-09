//various includes
int main()
{
	//full board
	//rewrite board to intzs
	char board[8][8] = {
		{b,w,b,w,b,w,b,w}
		{w,b,w,b,w,b,w,b}
		{b,w,b,w,b,w,b,w}
		{w,b,w,b,w,b,w,b}
		{b,w,b,w,b,w,b,w}
		{w,b,w,b,w,b,w,b}
		{b,w,b,w,b,w,b,w}
		{w,b,w,b,w,b,w,b}
	}
		/* 1. determine who is first.
		 * 2. choose to remove pieces if not first
		 * 3. change board to reflect removed pieces
		 *     **GAME LOOP**    *
		 * 4. wait for input or make input
		 * 5. begin to construct tree when is turn
		 * run legalmove on each position in array when is turn (and board is accurate.)
		 * N,S,E,W determines legalmove followed by index notation.  This is the key for the tree pointers.
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
		 *
		 *
		 *
		 * Dir can = 0 for N, 1 for E, 2 for S, 3 for W
		 */
		//index for structs i,j,Dir 
		void makeMove() {

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

