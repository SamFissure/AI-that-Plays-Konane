/*
The minimax algorithm begins at the current state of the game recursively searching the
game tree for the optimal move depth-first, which means exploring a branch as far as it goes and
then backtracking until a path that has not been explored is found. Once the algorithm reaches a
leaf node, which indicates a terminal state, or reaches the specified search depth in the game tree
the utility(best/worst) value of the node is returned. 
*/
int minimax(struct node *head ,int level,int depth)
{
	// if node is at depth limit...
        if (level == depth)
           // do a static evaluation, return result and the best move
            return (static_eval(node));  //Have to write the static_eval function

       // generate successor nodes
        successor_nodes = generate_successor_nodes(board, node); //Have to write the generate_successor_nodes function

        //if node is at a maximizing level (if level is even)
        if (level % 2 == 0)
        {
            best_move = ()
            double value = -99999;
          

            // for each successor node, call minimax recursively
            while(successor_nodes)
           {
                rval = minimax(successor);

                //look for the highest bv
                if (rval[0] > value){
                    value = rval[0];
                    best_move = successor_move;   
                }
            }

            return (value);
        }

        //if node is at a minimizing level (if level is odd)
        else
        {
            best_move = ()
            double value = 99999;

            // for each successor node, call minimax recursively
           while(successor_nodes)
           {
                rval = minimax(successor)

                // look for the lowest bv
                if (rval[0] < value){
                    value = rval[0];
                    best_move = successor_move;
                }
            }


            return (value)
        }
    
}