# Konane AI 
# Made by Sam (Robert) and documented by Tafroze.
A.I. that plays Konane at a high level of expertise (Codeblocks/MinGW seem to be required to make this work.  Bugs to fix... sigh)
__________________________________________________________________________________________________________________________________
Competition variation:

We broke some OOP rules (some things made public, some global variables, only one class) in the name of processing speed (stackoverflow indicated that globals often improve performance.)

For the tournament, the AI must move in 15 seconds or forfeit.  
__________________________________________________________________________________________________________________________________
This is now hobbyist (Robert's project) & has moved beyond tournament play.
What that means for the code:
This code will be refactored in the following ways
1. it will become more OOP where possible, 
some global constants MAY become class-member variables.  Other alterations will be made to improve modularity and user-friendliness.

:::TODO:::
Improve Parellel implementation.  While the game is thread-safe, some threads are not being utilized well.
