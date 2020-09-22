// parallel-for-each-structure.cpp
// compile with: /EHsc

#include <array>
#include <sstream>
#include <iostream>


using namespace std;
//do I need to use a board object?
// I need to RETURN a board object...
board parallel_safe(bunch of parameters)
for (j=offset,j<8,j+2)
{
    for dir=1; dir<5; dir++
       if( legalmove)
        board.makemove i,j,dir
        val=max...etc
        if board.val>boardbest.val
        boardbest=board
        board.unmakemove


    return boardbest


}
//must pass in MIN???
threadKonane(i, alpha, beta, depth, levelColor){
int k, m, tshoot, temp;
   int opColor = levelColor%2;
    opColor++;
    /**RESOLVE MATH AFTER SUCCESSFUL TEST**/
	int currentmove[4];
	int val = MIN;

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
    if (val == MIN)
    {
       bval=LOSE;
    }
return board
}
//inital call
board0=thread1 (threadKonane, /*args*/)
board1...
...
board7

join thread0
join thread1
...
join thread7
