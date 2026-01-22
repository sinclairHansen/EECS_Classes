

// Week 10
// Deep copies and the big three
// 10/29/2025


#include <iostream>
using namespace std;


// When using destructors in polymorphism, the destructor must be virtual
// if there are derived classes. This is because when the destructor is called,
// it will otherwise use the static type. If there are derived member variables, they will 
// not get called
class Example {

private:
    int x; double y;
public:
    Example(int x_in,
    double y_in)
    : x(x_in), y(y_in) { }
};
int main() {
    Example e1(2, 3.5);
    // init e2 as copy of e1
    Example e2(e1);
    // This syntax is equivalent
    // Example e2 = e1;

    int func(Example a); // pass by value
    Example a1(2, 3.5);
    Example a2(a1); // init a2 as copy of a1
    Example a3 = a1; // init a3 as copy of a1
    func(a1); // init parameter a as copy of a1

//     The Copy Constructor
//  ́ When a compound object is initialized from another of
// the same type, a copy constructor is used.

    class Example {
    private:
    int x; double y;
    };

// Copy constructor examples
    Example(int x_in, double y_in)
    : x(x_in), y(y_in) { }

    Example(const Example &other) {
    x = other.x;
    y = other.y;
    }
    // You must pass by reference because if you don't
    // there would be an infinite loop because the copy const. would
    // get called over and over again

    /*
    However, all classes already have a built in copy constructor
    just like this that the compiler provides for you.
        - It just does a member by member copy
        - The built in version is provided even if you made
        the other constructors (inlike the built in default ctor)
    
    UnsortedSet copy constructor
    - Here's the built-in copy constructor for unsortedset:
    */
    template <typename T>
    class UnsortedSet {
    private:
        T *elts;
        int capacity;
        int elts_size;
    public:
        UnsortedSet(const UnsortedSet &other)
            : elts(other.elts),
            capacity(other.capacity),
            elts_size(other.elts_size) { }
};
/*
The rule of the big three
The big 3:
    - Destructor
    - copy constructor 
    - assignment operator
The rule of the big three is: if you need to provide a custom implementation of ANY of them...
... you almost certainly need to provide a custom implementation for all of them

*/


}