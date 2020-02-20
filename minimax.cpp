/*
The minimax algorithm begins at the current state of the game recursively searching the
game tree for the optimal move depth-first, which means exploring a branch as far as it goes and
then backtracking until a path that has not been explored is found. Once the algorithm reaches a
leaf node, which indicates a terminal state, or reaches the specified search depth in the game tree
the utility(best/worst) value of the node is returned. 
*/

int minimax(int board ,int level,int depth)
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
            		if(board[i][j]==0 and legal_move(board,i,j,0))
            		{
            			// Make the move 
            			board[i][j]=B; //assuming black is the AI and its' trying to maximize

            			// Call minimax recursively and choose 
                    	// the maximum value 
                    	best = max( best_value, minimax(board, level+1,depth) ); 
  
                    	// Undo the move 
                   		 board[i][j] = 0; 
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
            		if(board[i][j]==0 and legal_move(board,i,j,0))
            		{
            			// Make the move 
            			board[i][j]=W; //assuming white is the opponent and its' trying to minimize

            			// Call minimax recursively and choose 
                    	// the minimum value 
                    	best = min( best_value, minimax(board, level+1,depth) ); 
  
                    	// Undo the move 
                   		 board[i][j] = 0; 
            		}
            	}
            }
            return best_value;
        }
    
}
