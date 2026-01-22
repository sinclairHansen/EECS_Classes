

// Sinclair Hansen
// 11/19/2025
// Structural Recursion

#include <iostream>
using namespace std;


/*
Recursive Data structures -> Lists and trees

Recall: Linked list data representation
struct Node {
int datum;
Node *next;
};

Recursively, a list is either empty or a datum folled by a sub-list
This means that recursion could be used to break down
    calculations of a list into smaller portions

 For example, let's compute the length of a list L.
 Consider the two cases:
1. empty easy enough: length(L) = 0

2. A datum, followed by a sub-list
length(L) = 1 + length( the sub-list )

int length(Node *node) {
if (node == nullptr) { // BASE CASE
return 0;
}
else { // RECURSIVE CASE
return 1 + length(node->next);
}
}

Trees
Recursively a tree is either empty or
    a datum with two sub trees

Tree data representation
*/
struct Node {
int datum;
Node *left;
Node *right;
};
/*
Computing the size of a tree

int size(Node *node) {
// BASE CASE – Empty tree has size 0
if (!node) {
return 0;
}
// RECURSIVE CASE
return 1 + size(node->left) + size(node->right);
}

The time complexity of this funciton is O(N)
    and the stack frame used is equivalent to the height


Computing the height of a tree
*/
int height (Node *node)
{
    //Base case - empty tree has size 0
    if(!node)
    {
        return 0;
    }
    return 1 + max(height(node->left), height(node->right));
}
/*
Linear recursion - it makes at most one recursive call each time the funciton is called
Tail recursion - if it is linear recursive and all
    recursive calls are tail calls, so that no work is done after a recursive call
        Example: fact_tail, max_tail
Tree recursive - if it might make more than one recursive
    call each time the function is called
        Example: Tree size, height


Tree Print:*/

void print(Node *node) {
    if (node) { // RECURSIVE CASE
    cout << node->datum << " ";
    print(node->left);
    print(node->right);
    }
}
/*
Does changing the cout impact how the nodes are printed? YES!

Tree Traversals

 For print(), we have a
    choice of when to process
    a datum
 A preorder traversal
    processes a datum
    before the recursive calls.

 An inorder traversal
    processes a datum
    between the calls.

 A postorder traversal
    processes a datum
    after the recursive calls.



Binary Search Trees

A tree is a binary search tree if...
 ́ It is empty.
OR
 ́ The left and right subtrees are binary search trees.
 ́ All elements in any left subtree are less than the root.
 ́ All elements in any right subtree are greater than the root.

For simplicity, we are assuming there are no duplicate elements

If we're looking for an element in a BST, comparing with
the root tells us where to look.
For example, if our value is less than x (the first node of the tree)
    we search the left. If our value is greater than x, we search the right

*/


//FINAL EXAM SHTUFF
// Traversal by iterator
vector<int> vals = ...;
auto end = vals.end();
for (auto it = vals.begin(); it != end; ++it) {
cout << *it << endl;
}
// Seg fault iterators
int main() {
list<int> list;
list.push_back(1);
list.push_back(2);
list<int>::iterator it = list.begin();
list<int>::iterator it2 = list.begin();
cout << *it << endl; // OK
cout << *it2 << endl; // OK
list.erase(it);
cout << *it << endl; // EXPLODE
cout << ++it << endl; // ALSO EXPLODE
cout << *it2 << endl; // YET AGAIN EXPLODE
}
// Iterator function
template <typename Iter_type>
bool has_two_in_a_row(Iter_type begin, Iter_type end) {
if (begin == end) {
return true;
}
auto prev = begin;
auto current = begin;
++current;
while(current != end) {
if (*prev == *current) {
return true;
}
++previous;
++current;
}
return false;
}
// Note range based for loops (ie. for(string s : word)) make a copy
// need to make a reference (string &s: word) to modify values

// MAPS
// iterating over a map
int main() {
map<string, int> scores;
...
for (auto it = scores.begin();
it != scores.end(); ++it) {
pair<string, int> &entry = *it;
cout << entry.first << ": "
<< entry.second << endl;
}
}
// Note: maps do store the data sorted by key

/*
́ Memory Leaks
Part of your code allocates dynamic memory,
but neglects to free up the space when it’s done.
 ́ Orphaned Memory
You lose the address of a heap object,
meaning it is inevitably leaked.
 ́ Double Free
Attempt to delete a heap object more than once.
 ́ Bad Delete
Give delete an address not pointing to a heap object1.
 ́ Dangling Pointers
Be careful not to dereference any pointers to dead objects!
*/

// Changes underlying representation to use a (grow function)
// dynamic array of 2 * capacity elements
void grow() {
T *newArr = new T[2 * capacity];
for (int i = 0; i < elts_size; ++i) {
newArr[i] = elts[i];
}
capacity *= 2;
delete[] elts;
elts = newArr;
}
};

// The big three
// copy constructor
Example(const Example &other)
: x(other.x), y(other.y) { }
};
// Unsorted Set Copy Ctor
UnsortedSet(const UnsortedSet &other)
: elts(new T[other.capacity]),
capacity(other.capacity),
elts_size(other.elts_size) {

for (int i = 0; i < elts_size; ++i) {
elts[i] = other.elts[i];
}}
/*
́ Destructor
1. Free resources1
 ́ Copy Constructor
1. Copy regular members from other
2. Deep copy resources from other
 ́ Assignment Operator
1. Check for self-assignment
2. Free old resources
3. Copy regular members from rhs
4. Deep copy resources from rhs
5. return *this
*/
// Functors example
class GreaterN {
private:
int threshold;
public:
GreaterN(int threshold_in)
: threshold(threshold_in) { }
bool operator()(int n) const {
return n > threshold;
}
};
int main() {
List<int> list; // Fill with numbers
GreaterN g0(0);
cout << any_of(list.begin(), list.end(), g0);
cout << any_of(list.begin(), list.end(), GreaterN(32));
}
// more
// REQUIRES: begin is before end (or begin == end)
// EFFECTS: Returns true if there is an element in
// [begin, end) for which pred returns true.
template <typename Iter_type, typename Predicate>
bool any_of(Iter_type begin, Iter_type end,
Predicate pred) {
for (Iter_type it = begin; it != end; ++it) {
if (pred(*it)) { return true; }
}
return false;
}
// printer
template <typename T>
class Printer {
public:
Printer(ostream &os_in) : os(os_in) { }
void operator()(const T &x) const { os << x << " "; }
private:
ostream &os;
};
int main() {
List<int> list; // Fill with numbers
ofstream fout("list.out");
for_each(list.begin(), list.end(),
Printer<int>(fout));
}

  static Node * insert_impl(Node *node, const T &item, Compare less) {

    if(node == nullptr)
    {
      return new Node{item, nullptr, nullptr};
    }
    if(less(item, node->datum))
    {
      node->left = insert_impl(node->left, item, less);
    }
    else{node->right =  insert_impl(node->right, item, less);}

    return node;
  }

  static Node * min_element_impl(Node *node) {
    if(empty_impl(node)){return nullptr;}
    if(node->left == nullptr){return node;}
    return min_element_impl(node->left);
  }

class PlayerException : public std::exception {
public:
    PlayerException(const std::string &msg_in) : msg(msg_in) { }
    const char *what() const noexcept override { return msg.c_str(); }
private:
    std::string msg;
};

// Example of throwing
Player *Player_factory(char strategy) {
    if (strategy == 'h') return new HumanPlayer();
    if (strategy == 'r') return new RandomPlayer();
    throw PlayerException("Unknown strategy");
}

// Example of catching
try {
    Player *p = Player_factory('x');
    // use p
    delete p;
} catch (const PlayerException &e) {
    std::cerr << e.what() << std::endl;
}


struct Node {
    int datum;
    Node *next;
};

class IntList {
public:
    IntList()
        : head(nullptr) {
    }

    ~IntList() {
        clear();
    }

    IntList(const IntList &other)
        : head(nullptr) {
        copy_from(other);
    }

    IntList &operator=(const IntList &other) {
        if (this == &other) {
            return *this;
        }
        clear();
        copy_from(other);
        return *this;
    }

    // Push front example
    void push_front(int value) {
        Node *n = new Node;
        n->datum = value;
        n->next = head;
        head = n;
    }

private:
    Node *head;

    // helper to free the list
    void clear() {
        while (head) {
            Node *tmp = head;
            head = head->next;
            delete tmp;
        }
    }

    // helper to deep copy from another list
    void copy_from(const IntList &other) {
        if (!other.head) {
            head = nullptr;
            return;
        }

        // copy first node
        head = new Node;
        head->datum = other.head->datum;
        head->next = nullptr;

        Node *curr = head;
        Node *other_curr = other.head->next;

        // copy rest
        while (other_curr) {
            Node *n = new Node;
            n->datum = other_curr->datum;
            n->next = nullptr;

            curr->next = n;
            curr = n;
            other_curr = other_curr->next;
        }
    }
};


class IntArray {
public:
    // default constructor
    IntArray()
        : data(nullptr), size(0), capacity(0) {
    }

    // constructor with capacity
    explicit IntArray(int cap)
        : data(nullptr), size(0), capacity(cap) {
        if (capacity > 0) {
            data = new int[capacity];
        }
    }

    // destructor
    ~IntArray() {
        delete[] data;
    }

    // copy constructor
    IntArray(const IntArray &other)
        : data(nullptr), size(other.size), capacity(other.capacity) {
        if (capacity > 0) {
            data = new int[capacity];
            for (int i = 0; i < size; ++i) {
                data[i] = other.data[i];   // deep copy
            }
        }
    }

    // copy assignment operator
    IntArray &operator=(const IntArray &other) {
        if (this == &other) {
            return *this;  // self assignment guard
        }

        // free old data
        delete[] data;

        // copy size and capacity
        size = other.size;
        capacity = other.capacity;

        // allocate new array and copy
        data = nullptr;
        if (capacity > 0) {
            data = new int[capacity];
            for (int i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }

        return *this;
    }

    // other methods like push_back, operator[]
    // ...

private:
    int *data;
    int size;
    int capacity;
};






