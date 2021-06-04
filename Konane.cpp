/*Order of Game Play*/
/*Game is lost when there are no longer any valid moves.*/
		/* 1. determine who plays Black and is thus first.
		 * 2. choose to remove 2 pieces if not first (another variant has the removal of one piece by each player).
		 *
		 *     **GAME LOOP**    *
		 * 3. wait for input or make input
		 * 4. upon AI move:

		 * run legalmove on each position in array when is turn (and board is accurate.)
		 * N,S,E,W determines legalmove direction.
		 *
		 * the following bounds due to no move possible:
		 * if i<2 (row) don't run N
		 * if i>5 don't run S,
		 *
		 * if j<2 (column) don't run W,
		 * if j>5 don't run E.
		 *
		 * so the first square in a column doesn't evaluate the Northern most move and the last square will not
		 * evaluate the Southernmost... etc
		 * ******************* RECURSIVE CALLS  ***************************
		 * 5. if legalmove returns true, form node (recursive call with new board) with move and repeat process board to obtain number.
		 * it is a DFS.
		 * 6. the calls eventually reach depth d and the SEF is run.  It is notable that the alpha and beta cutoffs will reduce the number of boards evaluated
		 * WITHOUT any data loss.
		 * (this is a less intuitive action of the recursive function, no data is lost, but branches that the AI will NEVER select are not explored further.
		 * essentially, a node which comes out too high or too low relative to the node examined will not be selected)
		 *
		 **************	State Evaluation function (SEF)*********************
		 *
		 * 7. The SEF evaluates partly by counting legal moves for player in that state.
		 * Additionally, it counts pieces and estimates based on expected piece balance (each move must remove one piece, if more pieces are missing a
		 * double move has occurred.  The SEF assumes that this is bad for the player who had this happen to it.)
		 *
		 * The SEF value is passed up to the top of the tree with varied modifications, minimizing levels take the lowest value to pass, maximizing
		 * will take up the largest values
		 *
		 * Dir can = 0 for N (up), 1 for E(right), 2 for S (down), 3 for W (left)
		 */



/* STANDARD INCLUDES FROM LIBRARY FILES AND NAMESPACE */
#include "myincludes.h"

/*Include Constants, depth is defined at compile time, as are some*/
#include "const.h"


/**REMEMBER TO USE THE DIAGNOSTIC PRINTOUTS FOR FUTURE CHANGES**/


/**FUNCTIONAL WITH 16 DEPTH, EASE OF TESTING AT 14 OR 12 DEPTH, GAMEPLAY IS DIFFERENT DEPENDING ON DEPTH**/

/**color is AI, humanColor is opponent**/

/***MUST HAVE THESE GLOBALS, COULD PERHAPS EDIT INTO BOARD?***/
int AIcolor, humanColor;

#include "board.cpp"
/******************DUE TO FOLLOWING OFFICIAL RULES, COLOR HAS BEEN MERGED WITH FIRST**********************/
/***(setters and getters, removed from code at this time)***/
/*int getFirst(){return first;}
 *int getColor() {return AIcolor;}
 *int getPlayerColor() {return playerColor;}
 */



void write_csv(double input[], int totalMoves){

    // Make a CSV file with move record for stat tracking
    // Each column of data is represented by the pair <column name, column data>

    std::ofstream csv("parallel-moves-14-1.csv");
    csv<<"Turn, Time \n";
    for(int i=0;i<totalMoves;i++){
        csv<<i+1<<","<<input[i]<<"\n";
    }


    // Close the file
    csv.close();
}

/*SHOULD CONSIDER MAKING MORE FUNCTIONS OUT OF THINGS IN MAIN!!*/
int main() {

	int level=0;
	int turn=0;
	int i,j,k,m,z, alpha, beta, state;
	double tc;
    double csv[50];
    duration<double> timeCount;
    char correct, ans;
	bool first, AIturn, right;
	bool cor=true;
	player player;
	board board;
	/**odd numbered depths are on min nodes, even on max. This doesn't work.**/
	cout<<"depth = "<< depth<<". (This should be an even number)\n";
	cout<<"\n";


	right=board.setZpgame();
	if (right){
        board.zpgame=true;
	}
	first=board.setColor();
	if (first == true) {
		AIturn = true;
	}
	else{
        AIturn=false;
	}
	/**SETS BOARD UP**/
    board.manualOverride();
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
	while (true) {

        //cout<<"\nSEF = " <<state <<"\n";
		if (AIturn) {
                high_resolution_clock::time_point tpre = high_resolution_clock::now();
                //ERROR ON FIRST AND SECOND PARAMETERS?
			state=board.ABMax(1, 2, level, depth, AIcolor);
			board.display();

        if (state== WIN)
        {
            cout << "It looks like I will win soon, but I am buggy as heck, so let's keep playing. \n";
            board.makeMove(board.bestmove, AIcolor);
            board.displayMove();
        }
			else if (state == LOSE)
			{
				cout << "It looks like I will lose soon, but we should play it out.\n";
				board.makeMove(board.bestmove, AIcolor);
				board.displayMove();
			}
			else {
				board.makeMove(board.bestmove, AIcolor);
				board.displayMove();

			}
			board.display();
			AIturn = false;
			turn++;
            high_resolution_clock::time_point tpost = high_resolution_clock::now();
			timeCount = duration_cast<duration<double>>(tpost-tpre);
            tc=timeCount.count();
            std::cout<<"\n"<<tc<<"\n";
            csv[turn-1]=tc;
			//cout<<"\nSEF = " <<state <<"\n";
            }
            /** if PLAYING AGAINST ITSELF OR A SIMILAR AI W A DIFFERENT SEF**/
            else if((right) && (AIturn==false)){
            high_resolution_clock::time_point tpre = high_resolution_clock::now();
            state=board.ABMax(1, 2, level, depth, humanColor);
			board.display();
			if (state== WIN)
			{
				cout << "It looks like I will win soon, but I am buggy as heck, so let's keep playing. \n";
				board.makeMove(board.bestmove, humanColor);
				board.displayMove();
			}
			else if (state == LOSE)
			{
				cout << "It looks like I will lose soon. If I were built by Cyberdine, I could send someone back to 'fix' this... \n";
				board.makeMove(board.bestmove, humanColor);
				board.displayMove();
			}
			else {
				board.makeMove(board.bestmove, humanColor);
				board.displayMove();
				}
			board.display();
			AIturn = true;
			turn++;
            high_resolution_clock::time_point tpost = high_resolution_clock::now();
            timeCount = duration_cast<duration<double>>(tpost-tpre);
            tc=timeCount.count();
            std::cout<<"\n"<<tc<<"\n";
            csv[turn-1]=tc;
            }
            /** if PLAYING A HUMAN**/
		else {
            do{
                cout << "\nenter piece to move column, 1-8: ";
                cin >> j;
                //accomodate indexing
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
                cor=true;
                //guard rails here
            }while(! cor);

			board.makeMove(board.bestmove,humanColor);
			board.displayMove();
			board.display();
			turn++;
			AIturn=true;
			}
			        if(state==GAME_OVER_BLACK)
            {
            cout<<"Black Loses\n";
            break;
            }
        if(state==GAME_OVER_WHITE)
            {
            cout<<"White Loses\n";
            break;
            }
        cout<<  "\nassuming correct board and continue\n";
        //cout << "\n is board correct? y for yes, n for no \n \n";
        //cin >> ans;
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	 duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
	std::cout<<"\nfinished in "<<turn<<" turns";
    std::cout << "\nIt took me " << time_span.count() << " seconds.\n";
    for(z=0;z<turn;z++)
    {std::cout<<"turn " <<z+1<< " took "<<csv[z]<<" seconds \n";}
    write_csv(csv, turn);
	return 0;
}
