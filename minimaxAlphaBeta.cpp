/*
The minimax algorithm begins at the current state of the game recursively searching the
game tree for the optimal move depth-first, which means exploring a branch as far as it goes and
then backtracking until a path that has not been explored is found. Once the algorithm reaches a
leaf node, which indicates a terminal state, or reaches the specified search depth in the game tree
the utility(best/worst) value of the node is returned.
*/

int board::minimax(int level,int depth)
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
            		if(board[i][j]>0)
            		{
            		    for(int Dir=0;Dir<4;Dir++){
            			if(legal_move(i,j,Dir)){
            			board[i][j]=B; //assuming black is the AI and its' trying to maximize

            			// Call minimax recursively and choose
                    	// the maximum value
                    	best = max( best_value, minimax(, level+1,depth) );

                    	// Undo the move
                   		 board[i][j] = 0;
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
            		if(board[i][j]>0)
            		{
            		    for(int Dir=0;Dir<4;Dir++){
                            if(legal_move(i,j,Dir)){
                                board[i][j]=B; //assuming black is the AI and its' trying to maximize

            			// Call minimax recursively and choose
                    	// the maximum value
                                best = max(best_value, minimax(board, level+1,depth) );

                    	// Undo the move
                                board[i][j] = 0;
                            }

            		    }
            	}
            }
            }
        }
            return best_value;
        }



int board::alphaBetaMinimax( int alpha,
            int beta, int level, int depth)
{
// Initial values of
// Aplha and Beta
// Terminating condition. i.e
// leaf node is reached
    if (level == depth)
        return board.static_eval(board); //Need to fix the board

     if (level % 2 == 0)
    {
        int best = MIN;

        for(int i=0;i<8;i++)
            {
            	for(int j=0;j<8;j++)
            	{
            		if(board[i][j]>0)
            		{

            			int val = minimax(alpha, beta, level+1,depth);
            			best = max(best, val);
           				alpha = max(alpha, best);

            			// Alpha Beta Pruning
            			if (beta <= alpha)
                		break;
        			}
        		return best;
    			}
    		}
    }
    else
    {
        int best = MAX;


        for(int i=0;i<8;i++)
            {
            	for(int j=0;j<8;j++)
            	{
            		if(board[i][j]>0)
            		{

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
