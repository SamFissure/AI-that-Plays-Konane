#ifndef myincludes_h
#define myincludes_h

/*seems like a good way to do this... might want to do in the future.

All includes for the program, and the namespace.
There is possibly an argument for reducing includes and removing the namespace.
This can happen in future iterations of the program
*/
#include <iostream>
#include <cstdlib>

#include <fstream>
#include <utility>

#include <algorithm>

#include <chrono>
#include <ratio>


using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::milli;
using std::cin;
using std::cout;
#endif // myincludes_h
