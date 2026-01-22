
// Week 12 Notes
// 11/10/2025
// Sinclair Hansen

#include <iostream>
using namespace std;

/*
́ A key strength of iterators is that we can write
functions to work with iterators, rather than with a
particular container.
 ́ This allows the same function to be used with
many different containers!
 ́ The standard library contains many functions, like
std::sort, that work on iterator ranges.

Iterator Invalidation

 ́ Invalidated iterators are like dangling pointers –
it’s no longer safe to dereference them and try
to access the object they point to.
 ́ Seemingly innocuous operations on a container
can result in iterator invalidation.
 ́ For example, iterators pointing into a vector are
invalidated if an operation causes a grow.
 ́ A function’s documentation should specify
which iterators, if any, it may invalidate.


// Lecture 20 
Function Objects and Imposter Syndrome

Review: Traversal by Iterator
 ́ Walk an iterator across the elements.
 ́ To get an element, just dereference the iterator!
 ́ Get iterators that define the range from the
container using begin() and end() functions.
*/
List<int> list;
int arr[3] = { 1, 2, 3 };
fillFromArray(list, arr, 3);

List<int>::Iterator end = list.end();
for (List<int>::Iterator it = list.begin(); it != end; ++it) {
cout << *it << endl;

/*
Review: The Iterator Interface

 ́ Iterators provide a common interface for iteration.
 ́ A generalized version of traversal by pointer.
 ́ An iterator “points” to an element in a container and can
be “incremented” to move to the next element.

 ́ Iterators1 support these operations:
 ́ Dereference – access the current element.
*it
 ́ Increment – move forward to the next element.
++it
 ́ Equality – check if two iterators point to the same place.
it1 == it2
it1 != it2

Function Pointers

 ́ Variables that can store a function.
 ́ The instructions for executing a function are stored
somewhere – a function pointer actually stores the
address of the machine code for the function.
 ́ Unlike a regular pointer, you don’t need to
dereference a function pointer to use it.
 ́ The syntax for declaring a function pointer looks a
lot like the functions it can hold.
*/
int max(int x, int y) { return x > y ? x : y; }
int min(int x, int y) { return x < y ? x : y; }
int (*fn)(int, int) = max; // fn starts as max
fn = min; // set fn to be min

Returns an int. cout << fn(2, 5); // uses min, prints 2

int main()
{



    return 0;
}

/*
Recursion and Tail Recursion

What does this program output?
*/
#include <iostream>
using namespace std;

void count(int number) {
if (number == 0) return;
cout << number;
count(number - 1);
cout << number;
} // end-function count

void main() {
count(4);
} // end-function main
/*
The output would be 4, 3, 2, 1, 1, 2, 3, 4

When you do recurison think of it as calling a seperate function,
letting it do its thing and then we complete what we want
This is because every calling of the function has its own stack
and is treated independently

Recursion: The basics
 A recursive method is one that calls itself
• Like iteration, recursive control structures repeat execution of a block of code, but
the underlying mechanics and memory usage are very different.
• Recursive methods use a divide and conquer decomposition where we construct
solutions using one or more decomposed subcases of simpler/smaller instances of
the same general problem.
• If this continues infinitely, then you’ll get a stack overflow.
• Recursive methods must have one or more trivial or base cases in
which they do not need to call themselves to provide a solution
 Example: Searching for a word in a dictionary
• Start at middle of the book, are you one the right page?
• If not, lets focus on only the portion of the book in the correct direction (basically,
we now have a smaller book to search.. but the problem is otherwise the same)
• Repeat, until we find the right page!

Recursion: Big picture
 There are many ways to decompose problems in computer science.
 Recursion is one of the more important tools in our toolbelt.
 We’ve already encountered many programming features that decompose towards
simplicity.
• Delegation to base case functions
• Dealing with aggregate objects (deep copies, for example)

 Recursion requires decomposition to the same problem... but smaller.
 Thinking recursively takes time and practice
• Recursive is not always better (often not, in fact)
• Recursive is sometimes simpler or easier to read/understand/maintain
 In some instances a LOT simpler
• Recursive approaches are particularly effective on some data structures
*/