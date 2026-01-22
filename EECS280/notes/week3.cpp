#include <iostream>
#include <string>

using namespace std;

int main()
{
    /*EFFECTS and Modified
    Effects specifies what the function actually does. What is the meaning of the return value? 
    Are there any side effects? (eg modifying a data structure)
    
    Modifies indicates which things are potentially changed as a results of the side effects
        eg. A reference parameter, cout, global variables, etc.
        
        REQUIRES (i.e. ASSUMES)
        Prerequisites for the function to make sense
        Behavior in cases that break the requires clause is undefined by the interface
        The function implementation only needs to cover cases allowed by the interface's REQUIRES clause.


        Testing vs debugging
        Testing: Discovering that something is broken.
        Debugging: Fixing something once you know it's broken.

        Unit testing:
        - one piece at a time (e.g. a function)
        - find and fix bugs early! This saves you time!
            - test smaller, lexx complex, easier to understand units.
            - you just wrote the code - so it's easier to debug.
        
        System testing
            - entire project (code base)
            - do this after unit testing
        
        Regression testing 
            - automatically run all unit an system tests after a code change
        

        Test Cases:
        Simple. Ex assert(mode({1,2,3,2}) == 2);
        Edge cases. assert(mode({3}) == 3);
                    assert(mode({1,2,2,1}) == 1);
        Stress: Take the mode of a really, really big vector. Used for performance-critical
        applications like web servers to test how well they handle on intense load. 
        */
        int x = 5; 
        int y = 4;

        int v = (x > y)? 0: 1; // If x is greater than y then v is 0. Otherwise, v is 1. 
        cout<<v; // v = 0

        /*C++ has value semantics. Variables always refer to the same object once
        they are declared.
        An assignment copies a value from one object to another object. 
            It does not move a variable to refer to some other object.

        // r values and l values
        // y = x; x is the r value, as we are looking for the contents of x
                    y is the l values, as we are looking for the locations of y
        
        ADDRESSES
            Every object lives at some address in memory
            The & operator yields the address of an object
        */ 
       cout << &x; //This prints the address of x

        
    // A reference declaration binds a variable to an already existing object.
        //This give an object multiple names or aliases.
    int a = 10 + 5;
    int b = a;
    int &r = a;
    double z = 3.14159;

    cout << &a; // address of a
    cout << &b; //address of b
    cout << &r; // address of a


    //POINTERS 
    /* We can use addresses as pointers to indirectly access objects
        Example: a variable that stores the address of something else

    int * = "pointer to int"

    User the & operator to get a pointer to an object
    */
    int *ptr = &x;

    cout << ptr; // prints address of x
    cout << *ptr; // prints value of x
    cout << &ptr; // prints address of ptr because it is its own object
    

    /* Arithmetic Promotion
    The arithmetic operations require a common type
    If numeric operand types differ, one operand may be promoted via implicit conversion
    */

    /*Reference: Function Calls
    To call a function, the computer must...
    1. Evaluate the actual arguments to the function
    2. make a new and unique invocation of the called function
        Push a stack frame (space for parameters and locals)
        Pass parameters
    3. Pause the original function
        Active flow
        4. Run the called funciton
        5. Re
    */

    

    return 0;
}