Author          : Sunil S. Jaishankar
Affiliation     : Georgia Institute of Technology


Description
-------------
The program created as part of assignment 4 performs the following
1. Generates 2 square matrices and initializes them with values between 0 and 1
2. Performs matrix multiplication using the following 3 methods, tores them in a result matrix and prints them
- sequential multiplication
- static mapping (parallel processing)
- dyanmic mapping (parallel processing)
3. The program also tracks the time for each operation and outputs them, along with the speedup(K) values as defined in the assignment

The submission has 3 parts
- assg4.c: the main program 
- functions.h : header file for all user defined functions used by the main program
- functions.c : contains function definitions for the prototypes defined in functions.h

Installation
------------

Note to TA: 
- The number of threads used in parallel computation is controlled by '#define numthreads' in line 15 of assg4.c
- The size of the square matrices is controlled using '#define numRows' in line 14 of assg4.c
- These values may be modified for tests if required

To install the software, simply run

    gcc assg4.c functions.c -std=c99 -fopenmp -o parallel


Execution
-----------

Assuming the your executable is called "parallel", run it using

    ./parallel

will execute the program 'parallel' that generates two matrices, multiplies them using three methodologies as required in the assignment and displays their results, computation times and speedup(K) values.