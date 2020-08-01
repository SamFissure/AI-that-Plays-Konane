# Konane AI 
# Made by Tafroze and Sam (Robert).
A.I. that plays Konane at a high level of expertise
--------------------------------------------------------------------------------
AS OF 3/25/2020 THE COMPETITION HAS PASSED AND THIS IS PURE HOBBYIST!!
__________________________________________________________________________________________________________________________________
Competition variation:
Significant contributions by both members.
(i.e., using OOP we were able to get alot done in less time)
We broke some OOP rules (some things made public, some global variables) in the name of processing speed (stackoverflow indicated that globals often improve performance.)

For the tournament, the AI must move in 15 seconds or forfeit.  
Big-O time seems to double with each successive move for the first few moves, which caused some needed adaptations to solve the issue.
Some experimentation should be able to verify this result.
__________________________________________________________________________________________________________________________________
This is now hobbyist.
What that means for the code:
This code will be refactored in the following ways
1. it will become more OOP where possible, 
some global constants MAY become class-member variables.  Other alterations will be made to improve modularity and user-friendliness.
2. a zero-player game has been implemented and will be expanded to evaluate and enhance State Evaluation Functions and to test.
3. Multiple SEFs will be created.
4. Code may be refactored to include better recursive algorithims (Minimax will be replaced with 2 recursive functions to improve memory use and possibly speed)
5. The program will be better timed out so as to verify performance, though the 15 second requirement may be dropped.

:::TODO, NOT NECCESSARILY IN THIS ORDER:::
1. alphaBetaMinimax becomes alphaBetaMin and alphaBetaMax

2.Parallel processing
3. Backend

4. Frontend

5. OOP principles to make the game function smoothly, remove code from board class in a way that doesn't impact performance.
