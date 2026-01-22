
// Week 11
// Sinclair Hansen

// Lecture 18 - Linked Lists
/*
Using contiguous memory
- contiguous memory allows indexing through pointer arithmetic, but
it has some drawbacks...

Inserting a new element into the middle of the sequence requires shifting over elements.

- Increasing the capacity requires allocating an entirely new chunk of memory
(eg grow() for UnsortedSet). 


String Elements Non-Contiguously
- How can we store a sequence without needing a contiguous chunk of memory?
- We can no longer just move forward one space in memory
to get to the next element
- Instead we must somehow also keep track of the next element at each point in the list
- POINTERS RAHHHHHH

Nodes
- Each 'piece' of the list includes a dataum, but also a next pointer containing 
    address of the next 'piece'
- We'll call these 'pieces' NODES
- Let's use a struct to represent each node
    - Groups together the datum and next pointer
    - It's 'plain old data' (POD). No need for a class
    - For simplicity, we'll just work with ints for now
    */
struct Node {
int datum; // used to store an element of the list
Node *next; // contains the address of the next node in the list
};
// The amount of work it takes to do an insertion is constant time
// with the exception that you are already at the location for the insertion
// then, worse case it will be linear time
#include <cassert>
// Lets also use a class to represent an entire list
class IntList
{
    public:
    // EFFECTS: constructs an empty list
    IntList() : first(nullptr) { }

    // EFFECTS: returns true if the list is empty
    bool empty() const {
    return first == nullptr;} // If the list is empty, the first pointer will be null

    // REQUIRES: the list is not empty
    // EFFECTS: Returns (by reference) the first element
    int & front() {
    assert(!empty());
    return first->datum;
        }

    // EFFECTS: inserts datum at the front of the list
    void push_front(int datum) {
    Node *p = new Node;
    p->datum = datum;
    p->next = first;
    first = p;
    }
    void print(ostream &os) const {
    for (Node *np = first; np; np = np->next) {
    os << np->datum << " ";
    }
    }

    // REQUIRES: the list is not empty
    // EFFECTS: removes the first element
    void pop_front() {
    assert(!empty());
    Node *victim = first;
    first = first->next;
    delete victim;
}
    void pop_all() {
    while (!empty()) {
    pop_front();
    }
    }
    // EFFECTS: copies all nodes from the other list
    // to this list
    void push_all(const IntList &other) {
    for (Node *np = other.first; np; np = np->next) {
    push_back(np->datum);
    }
    }
    void push_back(int datum) {
    Node *p = new Node;
    p->datum = datum;
    p->next = nullptr;
    last->next = p;
    last = p;
    }

    // Information Hiding
    // Put the struct for the node within the IntList class
    // so it can only be used within the class
    private:
    struct Node {
        int datum; // used to store an element of the list
        Node *next; // contains the address of the next node in the list
        };
    Node *first;
    Node *last;

    // The big three, now using the helper functions we make
    ~IntList() {
        pop_all();
    }
    IntList(const IntList &other)
        : first(nullptr), last(nullptr) {
        push_all(other);
    }
    IntList & operator=(const IntList &rhs) {
        if (this == &rhs) { return *this; }
        pop_all();
        push_all(rhs);
        return *this;
    }

}
/*
Exercise: Traversing a Linked List

 ́ You can use a pointer to traverse a linked list.
 ́ Start it pointing to the first Node.
 ́ Move it to each Node in turn via next pointers.
 ́ At each step, access the datum of the current Node.
 ́ Stop when you get to the null pointer.
 ́ Use this pattern to write a print function.

class IntList {
private:
struct Node {
int datum;
Node *next;
};
Node *first;

public:
// MODIFIES: os
// EFFECTS: prints the list to os
void print(ostream &os) const {
for (Node *np = first; np; np = np->next) {
os << np->datum << " ";
}
}
...
};


Recall: Custom Big Three
 ́ When do we need our own custom versions?
 ́ If you need a deep copy.
 ́ You need a deep copy if the object owns and
manages any resources (e.g. dynamic memory).

 ́ Hints:
 ́ Check the constructor. If it creates dynamic
memory, you probably need the big three.
 ́ Look at the members. If some of them are pointers,
you might need the Big Three.

The Big Three
 ́ Destructor
1. Free resources1
  Copy Constructor
1. Copy regular members from other
2. Deep copy resources from other
 ́ Assignment Operator
1. Check for self-assignment
2. Free resources
3. Copy regular members from rhs
4. Deep copy resources from rhs
5. return *this


*/

#include <iostream>
using namespace std;

int main()
{
    IntList list; // ( )
    list.push_front(1); // ( 1 )
    list.push_front(2); // ( 2 1 )
    list.push_front(3); // ( 3 2 1 )

    cout << list.front(); // 3

    list.front() = 4; // ( 4 2 1 )

    list.pop_front(); // ( 2 1 )
    list.pop_front(); // ( 1 )
    list.pop_front(); // ( )

    cout << list.empty(); // true (or 1)




    return 0;
}


/*
Lecture 19 - Iterators
iterating through a list:
*/
int main() {
    List<int> list;
    int arr[3] = { 1, 2, 3 };
    fillFromArray(list, arr, 3);
    for (List<int>::Node *np = list.first; np != nullptr; np = np->next) {
    cout << np->datum << endl; // print each element
}
}
/*
́ Problems:
 ́ This breaks the interface of the List. Nodes are an
implementation detail we don’t want to mess with here.
 ́ The Node type is private, so this won’t even compile.

 Recall: The Iterator Interface

 ́ Iterators provide a common, “pointer-like”
interface for traversing a container of elements.
 ́ They allow us to reuse the same code to work
with many different kinds of containers as long as
they provide an iterator interface.
 ́ The STL containers work this way. For example:

*/
vector<int> vec = ...;

vector<int>::iterator end = vec.end(); // Notice end is really one past the end
for (vector<int>::iterator it = vec.begin(); it != end; ++it) {
cout << *it << endl; // dereference it to current element
}

/*
The Iterator Interface

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

1 There are many different kinds of iterators. These
operations are specifically required for input iterators.



What is an Iterator?

 ́ An iterator is an object that “works like a pointer”.
 ́ This can be implemented by a class that overloads the
appropriate operators (*, ++, ==, !=).

class Iterator {
public:
___ & operator*() const;
Iterator & operator++();
bool operator==(Iterator rhs) const;
bool operator!=(Iterator rhs) const;
...
};
*/




