#include <iostream>
using namespace std;
void addOne(int *x){
    *x += 1;
}

int * selectLargest(int *x, int *y)
{
    if (*x > *y){return x;}
    else{return y;}
}

int main(){

    //PASS by POINTER
    int z = 1;
    int *ptr = &z; // ptr "points" to z
    *ptr += 1; // adds 1 to z, without using the name z
    addOne(&z); // adds one to z
    addOne(ptr); // same thing

    // Return by pointer
    int a = 10;
    int b = 5;
    //set the largest of a or b to 100
    *selectLargest(&a, &b) = 100;

    // Null and unitialized pointers
    /* A null pointer has value 0x0 (ie address)
    No objects are allowed to live at address 0.
    A null pointer is interpreted as "not pointing to anything."
    Dereference a null pointer -> runtime error (usually)
    Declare a null pointer like this: int *ptr = nullptr;

    Just like any other vairables of primitive type, an unititialized pointer has no
    value in particular
        It's pointing at some random place in memory!
        Dereference an unitialized pointer -> undefined behavior
            - Maybe it crashes? If the pointer is pointing to memory your program isn't 
            allowed to use, you might get a sedmentation fault.
            Maybe you read some random memory and get junk values?
            Maybe you write some random memory and mess up other values. 

    Object Lifetimes
    You can safely use an object during its lifetime.
    Afterward, its memory may be reused for something else and overwritten with new data

    The const keyword
    */
   const int x = 3; //ok, initialized to 3. Const or int can be written first
   x = 5; // wont compile
   
   int x = 3;
   const int y = 0;

   //regular pointer to int
   int *ptr0 = &x;

   //pointer to const int. Its a read-only pointer
   const int * ptr1 = &x;

   //There is another one idk


   //const and references
   int &ref0 = x; // Bind ref1 to the same object as x. They are now aliases
   const int &ref1 = x; //Reference to const int. Now allowed to modify x through name ref1
    //KINDS OF OBJECTS
    // Atomic --> also known as primitive
    /* int double, char, etc.

    Arrays (homogeneous)
        A contiguous sequence of objects of the same type

    Class-type
        A compund object made up of member subobjects
        The members and their types are defined by a struct or class
    
    We can use both struct and class to create class-type objects in C++

    */
   struct Person{
    int age;
    string name;
    bool isNinja;
   }
   int a;
   Person alex;
   Person jon;
   //This creates an instance of the structure, with all of the variables
   // age, name, isNinja set to default values

   Person jon = {25, "jon", true}; // Now it initializes the member variables

   const Person p1 = {17, "Kim", true};
   // Since this is const, it cannot be changed.

   //structs and Pointers
   /* a pointer can point to a struct.
   Think of this as pointing to the "whole" struct.
   Dereference, then use the . to get members
   */
   Person p = {31, "Aliyah", true};
   Person *ptr = &p;
   p.age = 32;
   (*ptr).age = 33;
   ptr->age = 34;

   // When making a struct you can choose to have it be const or non const in the 
   // argument. Sometimes const is better because it takes both const and non const
   // while non const only takes non const

   /* Abstraction
   Procedural abstraction separates what a function does from how it works. 

   An abstract data type represents some data and associated operations on that data.
   
   Representation invariants 
   we use representations invariants to express valid conditions for our functions

   I/O is short for Input and Output
   
   
   
   
   */



    return 0;
}