# Konane AI 
# Made by Tafroze and Sam (Robert).
A.I. that plays Konane at a high level of expertise (Codeblocks/MinGW seem to be required to make this work.  Bugs to fix... sigh)
__________________________________________________________________________________________________________________________________
Competition variation:

We broke some OOP rules (some things made public, some global variables, only one class) in the name of processing speed (stackoverflow indicated that globals often improve performance.)

For the tournament, the AI must move in 15 seconds or forfeit.  
__________________________________________________________________________________________________________________________________
This is now hobbyist & has moved beyond tournament play.
What that means for the code:
This code will be refactored in the following ways
1. it will become more OOP where possible, 
some global constants MAY become class-member variables.  Other alterations will be made to improve modularity and user-friendliness.
2. a zero-player game HAS BEEN implemented to evaluate and enhance State Evaluation Functions and to test.
3. the SEF HAS BEEN enhanced to fix some outputted values that are unexpected.
4. Code HAS BEEN refactored to reduce work done by recursive function.
5. The program will HAS BEEN better timed out so as to verify performance, though the 15 second requirement will be dropped.  Further analysis and optimizations are ongoing.

:::TODO:::
FIX BIG O ISSUE.  It takes far too long to make a move early-game.