# Konane AI 
# Made by Tafroze and Sam (Robert).
A.I. that plays Konane.
--------------------------------------------------------------------------------
AS OF 3/25/2020 THE COMPETITION HAS PASSED AND THIS IS PURE HOBBYIST!!
Competition variation:
Significant contributions by both members.
(i.e., using OOP we were able to get alot done in less time)
We broke some OOP rules (some things made public, some global variables) in the name of processing speed (stackoverflow indicated that globals often improve performance.)

For the tournament, the AI must move in 15 seconds or forfeit.  
Big-O time seems to double with each successive move for the first few moves, which caused some needed adaptations to solve the issue.
Some experimentation should be able to verify this result.

Konane.cpp is an effective AI, but not optimal, this will be fixed in the hobbyist phase
__________________________________________________________________________________________________________________________________
This is now hobbyist.
What that means for the code:
This code will be refactored in the following ways
1. it will become more OOP where possible, 
some global constants MAY become class-member variables.  Other alterations will be made to improve modularity and user-friendliness.
2. the original (and KonaneAgain) will be preserved for performance reasons and comparative testing.
3. a zero-player game will be implemented to evaluate and enhance State Evaluation Functions and to test.
4. the SEF will be enhanced to fix some outputted values that are unexpected.
5. Code may be refactored to include more recursion where applicable.
6. The program will be better timed out so as to verify performance, though the 15 second requirement will be dropped.
