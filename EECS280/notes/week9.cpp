
// Week 9 notes
// They are going to be shorter because I skipped Monday lecutre



#include <iostream>
using namespace std;

/*
The new Operator
 ́ Use new to create a dynamic object.

 ́ Here’s what happens:
 ́Space for an int is created on the heap.
 ́The int is initialized with value 3.
 ́The new expression evaluates to the
address of the object.

Keeping Track of Dynamic Objects

 ́ For a local object (automatic storage)...
 ́ The lifetime of the object is tied to the scope
of the variable’s declaration!
 ́ When the variable goes out of scope, the
object dies and can’t be used.

 ́ But a dynamic object isn’t created from a
declaration that has any particular scope!
 ́ We keep track of it using a pointer that holds
its address.

The delete Operator
 ́ Use delete to destroy a dynamic object.
 ́ The operand is the address of the
dynamic object (i.e. a pointer to it).

 ́ Here’s what happens:
 ́Follow the pointer to a dynamic object.
 ́Destroy whatever object was there.
*/

/*
́ Memory Leaks
Part of your code allocates dynamic memory,
but neglects to free up the space when it’s done.
 ́ Orphaned Memory
You lose the address of a heap object,
meaning it is inevitably leaked.*/
void helper ()
{
    int *ptr = new int(10);
    ptr = new int(20);
    delete ptr;
}
/*
Dangling Pointers
- We can help ourselves out by limmiting the scope of a variable, so the 
compiler notices when we use the wrong vairable*/
void example() {
int x = 0;
int *ptr = new int(42);
delete ptr;
int *ptr1 = new int(3);
cout << *ptr << " "; // oops, we meant to type ptr1
delete ptr1;
}
int main()
{


    return 0;
}