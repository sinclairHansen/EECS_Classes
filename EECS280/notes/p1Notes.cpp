//Sinclair Hansen
// Lecture One Notes 
// 8/27/2025


#include <iostream> //Standard library that contains print functions and input functions
using namespace std; // A way of organizing names so there is not a conflict between names

//You could write std::cout<< or using namespace std means that every name is std, therefore it
//is not necessary to write it in. There are some drawbacks because the std library is quite big and we
// may be pulling in A LOT. 

// YOU CAN USE STD IN A CPP FILE, NOT IN HPP

int main(){ // code must live inside a main function. They currently don't take arguments
    /*If we want arguments later on, from the terminal, we can add them.
    If no return value is put at the botton, the compiler will auto return 0 if it is successful */

    //print a greeting
    cout << "Hello World!" <<endl; /*Flushing is putting all the outputs onto the screen at once.
    The program auto buffers the output, because putting big outputs out infrequently is better than putting 
    small ones out ofter. */

    /* Times to use endl;
    1. Input and output so its easier for the user
    2. Debugging. For example, if we're debugging an infinite loop, it is easier
    to see the issue if we use endl and flush out the outputs */


    
    //Declare some variables
    int x = 10 + 5;
    int y = 0;
    y = x;
    x = 20;

    // Print out the results

    cout << "x = " << x << " y = " << y << endl;

    return 0;



}

/* Running the compiler from the cammand-line using:

g++ --std=c++17 p1Notes.cpp -o p1Notes.exe

Then run the executable from the command line:

    ./p1Notes.exe

There are two inplementations for running a program

1. an interpreter, like in python, emulates the program. If there is an addition, the program
emulates the addition.

2. compilation puts in a translation step. It takes the code and translates it into
a code that the computer will directly understand. We will get low level code that the computer
can read. 

COMPILE ERRORS

If there are any compile errors, no p1Notes.exe file is created.
    An example of this would be a syntax error. When it is run, it will tell you where
    the code had the error and what the issue is. The debugger may catch these prior to the 
    code being run.


FORMATTING

Spaces and line breaks don't affect functionality.
    They DO make your code more readable. Tip: Many editors have auto-formatters built-in.
    Use proper indenting for better reading for yourself and others. 


STATEMENTS
    C++ is an imperative programming language - we provide a sequence of statements to run in order.
    A program starts execution in the main function.
    A statement has side effects, which means it alters/modifies variable, outputs, etc. Does it do something?

EXPRESSIONS
    Expressions generally have one of two purposes*

    1. to compute something : 10 + x + sqrt(x)
        We say an expression evaluates to the compute value.
    2. to do something: cout << "Hello"
        We say the expression has a side effect.

    VARIABLES AND MEMORY
    A variable is a name in the program's source code that refers to an object in the memory.

    //declare some variables */
    int x = 10 + 5;
    int y = x;
    double z = 3.14159;

    /* Date is stored in BYTES, composed of 8 bits - binary digits 0 or 1.
    
    A variable's type determines:
        How much space it needs e.g. int = 4 bytes, double = 8 bytes.
        
    Let's say
    x = []
    y = x then means that y is a vector that contains the same values. If we change either one going forward,
        it will not automatically change the other.
        
    UNINITIALIZED VARIABLES
        Warning! Initialize variables before using them.
            Unfortunately, the compiler can't always check this for you.

        int x; x is unititialized - has some "random" value

        //Runtime Error - Compiles successfully, but has undefined behavior when the program runs.

        cout<<x; 

        x = 3; OK - x now has value 3
        cout << x; Behavior is now well-defined

        Some errors can be caught at compile time whereas others don't necessarily occur until runtime.

        IMPLICIT CONVERSIONS
            In some cases, the compiler allows an expression to be inplicitly conversted to a different type. 
                int -> double 3 -> 3.0 Value unchanged. (A widening conversion.)

            double -> int 3.7 -> 3   -3.7 -> -3
            Value is truncated. (A narrowing conversion)

            numeric -> Boolean
            Zero is false. Anything else is true.


        EXPLICIT CONVERSIONS (Casts)
            In some cases, it may be necessary or more stylistically appropriate to use an explicit cast */

            double value = 4.3;

            //implicit conversion, too easy to miss

            int x = value;

            // C-style cast, avoid doing this

            int x = (int) value;

            //C++ style cast, compiler checks
            int x = static_cast<int>(value);


/*FUNCTIONS

    Abstraction - using a tool without actually knowing the behind the scenes of how it works. For example, I am using my laptop but dont know
    anything about the hardware, software, etc. There are specializations that allow people to understand one part without understanding the other

    

    Functions allow for procedural abstraction.
        eg Use sqrt() to compute a square tool
        eg call extract_columns() on P1 to read data from a file

    The interface for a function describes how we use it:
        eg sqrt(): "Pass in a number. It returns the square root"
    
    The implementation is the actual code for the function.


*/