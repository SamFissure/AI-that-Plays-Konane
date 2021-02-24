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

//Includes for parallel processing
#include "parallelincludes.h"

/*Include Constants, depth is defined at compile time, as are some*/
#include "const.h"


/**REMEMBER TO USE THE DIAGNOSTIC PRINTOUTS FOR FUTURE CHANGES**/


/**FUNCTIONAL WITH 16 DEPTH, EASE OF TESTING AT 14 OR 12 DEPTH, GAMEPLAY IS DIFFERENT DEPENDING ON DEPTH**/

/**color is AI, humanColor is opponent**/

/***MUST HAVE THESE GLOBALS, COULD PERHAPS EDIT INTO MAIN?***/
int AIcolor, humanColor;

#include "board.cpp"
/******************DUE TO FOLLOWING OFFICIAL RULES, COLOR HAS BEEN MERGED WITH FIRST**********************/
/***(setters and getters, removed from code at this time)***/
/*int getFirst(){return first;}
 *int getColor() {return AIcolor;}
 *int getPlayerColor() {return playerColor;}
 */
class player{
public:
    void wargamesReference();
};

void player::wargamesReference()
{
    int jokes;
    std::cout << "Would you like to play a game? \n";
	std::cout << "1. Konane \n2. ALSO Konane\n3. Global Thermonuclear War (Obligatory Wargames Reference)\n";
	std::cin >> jokes;
	if (jokes == 3) {
		std::cout << "That game is SOOOOOOOO boring,let's play Konane!!!\n";
	}
}


void write_csv(double input[], int totalMoves){

    // Make a CSV file with one or more columns of integer values
    // Each column of data is represented by the pair <column name, column data>
    // The dataset is represented as a vector of these columns

    // Create an output filestream object
    std::ofstream csv("parallel-moves-14-1.csv");
    csv<<"Turn, Time \n";
    for(int i=0;i<totalMoves;i++){
        csv<<i+1<<","<<input[i]<<"\n";
    }


    // Close the file
    csv.close();
}



/**TODO:: TOO MUCH IN MAIN!! REFACTOR!!**/

int main() {
	int Dir = 0;
	int level=0;
	int turn=0;
	int i,j,k,m,z, alpha, beta, state;
	double tc;
	//for recording time
    double csv[50];
    duration<double> timeCount;
    char correct, ans;
    //who is first, whose turn is it?
	bool first, AIturn, right;
	//
	bool cor=true;
	player player;
	board board, board1, board2, board3, board4, board5, board6, board7, board8;
	/**odd numbered depths end on min nodes, even on max. This doesn't work. This is to check for that**/
	std::cout<<"depth = "<< depth<<". (This should be an even number)\n";
	std::cout<<"\n";

	player.wargamesReference();
	//Zero Player Game?
	right=board.setZpgame();
	if (right){
        board.zpgame=true;
	}
	//Who is black, goes first?
	first=board.setColor();
	if (first == true) {
		AIturn = true;
	}
	else{
        AIturn=false;
	}
	/**SETS BOARD UP**/
    board.manualOverride();
    /**SETS UP BOARDS FOR THREADS**/
    board1=board;
    board2=board;
    board3=board;
    board4=board;
    board5=board;
    board6=board;
    board7=board;
    board8=board;
    //Starts the clock.
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
	while (true) {
            //if all moves lose.

        if(board.bval<-500){
            std::cout<<"Game over, White loses";
            break;
                }
		if (AIturn) {
            /**This should be refactored into a function.
            *This initializes every board object to the same state, starts the clock on the move and
            *makes the **/



            high_resolution_clock::time_point tpre = high_resolution_clock::now();
            board1=board;
            board2=board;
            board3=board;
            board4=board;
            board5=board;
            board6=board;
            board7=board;
            board8=board;
            //Initiates threads, calls them on the rows of the board
            //Alpha and Beta NOT set to Min and Max at first call.  This has improved efficiency and reduced error.
            //They ARE set to MAX and MIN later.
			thread th1( &board::threadKonane, &board1, 0, 1,2,depth,AIcolor);
			thread th2( &board::threadKonane, &board2, 1, 1,2,depth,AIcolor);
			thread th3( &board::threadKonane, &board3, 2, 1,2,depth,AIcolor);
			thread th4( &board::threadKonane, &board4, 3, 1,2,depth,AIcolor);
			thread th5( &board::threadKonane, &board5, 4, 1,2,depth,AIcolor);
			thread th6( &board::threadKonane, &board6, 5, 1,2,depth,AIcolor);
			thread th7( &board::threadKonane, &board7, 6, 1,2,depth,AIcolor);
			thread th8( &board::threadKonane, &board8, 7, 1,2,depth,AIcolor);

			//Joins threads to main program after program run (some efficiencies to realize here).
			th1.join();
			th2.join();
			th3.join();
			th4.join();
			th5.join();
			th6.join();
			th7.join();
			th8.join();
			//makes a comparison between the 8 boards and selects the ideal board from them
            board = board.comparison(board1, board2, board3, board4, board5, board6, board7, board8);
            //displays prior board
			board.display();
			//if no valid moves
            if(board.bval<-500){
                cout<<"Game Over, Black Loses";
                break;
                }

            //Uses the "bestmove" array to make the move chosen by algorithim
            board.makeMove(board.bestmove, AIcolor);
            //displays the move in start i, start j, destination i, destination j, format.
            board.displayMove();
            //displays the board
			board.display();

			//Passes turn
			AIturn = false;
			//increments turn counter
			turn++;
			//stops clock and counts value
			high_resolution_clock::time_point tpost = high_resolution_clock::now();
			timeCount = duration_cast<duration<double>>(tpost-tpre);
            tc=timeCount.count();
            //gives amount of time taken
            std::cout<<"\n"<<tc<<"\n";
            //records time and turn to array
            csv[turn-1]=tc;
            }
            /** if PLAYING AGAINST ITSELF OR A SIMILAR AI W A DIFFERENT SEF**/
            //same as above
            if((right) && (AIturn==false)){

                high_resolution_clock::time_point tpre = high_resolution_clock::now();
                board1=board;
                board2=board;
                board3=board;
                board4=board;
                board5=board;
                board6=board;
                board7=board;
                board8=board;
                thread th1( &board::threadKonane, &board1, 0, 1,2,depth,humanColor);
                thread th2( &board::threadKonane, &board2, 1, 1,2,depth,humanColor);
                thread th3( &board::threadKonane, &board3, 2, 1,2,depth,humanColor);
                thread th4( &board::threadKonane, &board4, 3, 1,2,depth,humanColor);
                thread th5( &board::threadKonane, &board5, 4, 1,2,depth,humanColor);
                thread th6( &board::threadKonane, &board6, 5, 1,2,depth,humanColor);
                thread th7( &board::threadKonane, &board7, 6, 1,2,depth,humanColor);
                thread th8( &board::threadKonane, &board8, 7, 1,2,depth,humanColor);
                th1.join();
                th2.join();
                th3.join();
                th4.join();
                th5.join();
                th6.join();
                th7.join();
                th8.join();
                board = board.comparison (board1, board2, board3, board4, board5, board6, board7, board8);
                board.display();
                //if no valid moves
                if(board.bval<-500){
                std::cout<<"Game over, White loses";
                break;
                }
                board.makeMove(board.bestmove, humanColor);
                board.displayMove();

                board.display();


                AIturn = true;
                turn++;
                //record timing.
                high_resolution_clock::time_point tpost = high_resolution_clock::now();
                timeCount = duration_cast<duration<double>>(tpost-tpre);
                tc=timeCount.count();
                std::cout<<"\n"<<tc<<"\n";
                csv[turn-1]=tc;
                }
            /** if PLAYING A HUMAN**/
		if((!right) && (AIturn==false)) {
            do{
                std::cout << "\nenter piece to move column, 1-8: ";
                //source column
                std::cin >> j;
                //accomodate indexing
                j--;
                //enters player move into array
                board.bestmove[1]=j;
                std::cout << "\nenter piece to move row, 1-8: ";
                std::cin >> i;
                i--;
                //source row
                board.bestmove[0]=i;
                std::cout << "\nenter piece destination column, 1-8: ";
                std::cin >> m;
                m--;
                //destination column
                board.bestmove[3]=m;
                std::cout << "\nenter piece destination row, 1-8: ";
                std::cin >> k;
                k--;
                //destination row
                board.bestmove[2]=k;

            }while(! cor);
            //is this move legal?
            cor=board.guardRails();

			board.makeMove(board.bestmove,humanColor);
			board.displayMove();
			board.display();
			turn++;
			AIturn=true;
			}
        std::cout<<  "\nassuming correct board and continue\n";
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	 duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
	std::cout<<"finished in "<<turn<<" turns";
    std::cout << "It took me " << time_span.count() << " seconds.\n";
    for(z=0;z<turn;z++)
        {std::cout<<"turn " <<z+1<< " took "<<csv[z]<<" seconds \n";}
    //write_csv(csv, turn);
	return 0;
}


