

//Notes for week 6
//Sinclair Hansen
// September 29, 2025
// Derived classes and inheritance
#include <iostream>
using namespace std;

class Bird {
private:
    int age; 
    string name;
public:
    Bird(const string &name_in)
: age(0), name(name_in) { //We need to initialize the variables
                //if we don't they will get 'junk'. Either here or in the private tab. 
cout << "Bird ctor" << endl;
}
string getName() const {return name;}
int getAge() const { return age; }
void haveBirthday() { ++age; }
void talk() const {
    cout << "tweet" << endl;
}
};

class Chicken : public Bird {
private:
    int roadsCrossed;
public:
    Chicken(const string &name_in)
    : Bird(name_in), roadsCrossed(0) {
        cout << "Chicken ctor" << endl;
}

void crossRoad() { ++roadsCrossed; }

void talk() const {
    cout << "bawwk" << endl;
}
};
class Duck : public Bird{
    private:
        int breadFed;
    public:
        Duck();
        Duck(string &name1) : Bird(name1), breadFed(0){}
};

/* Calling a base-class ctor
    - A constructor in a derived class always calls a constructor for a base class.
    - If no explicit call is made in the member initializer list, the default 
        constructor of the base is implicitly called

    Varieties of Inheritance
    - C++ offers three different varieties of inheritance: public, protected, private
    - We only conver public inheritance

    Desctructors are called whenever a class object's lifetime ends 
        (depends on storage duration)
    It gets called automatically when the object dies. So when they go out of scope.

    CTors and Dtors in derived types
    - Desctructors are the analog of constructors, called
    whel an object is destroyed.
    - When creating or destroying an object of a class with a base type,
    a constructor or destructor is used for each level of hierarchy.
    - For constructors, we get top down behavior.

    Function Overloading
        - the use of a single name to represent many functions
            within the same scope
        - This will be shown by the same function having different parameters


    Static vs. Dynamic type
    - the static types of a pointer/reference is the 
    type it is declared with and is known at compile time.
    - The ynamic type of a pointer is the type of 
    object it is actually pointing to at run time
*/
Chicken c("Myrtle");
Duck d;

Bird *ptr = &c;
// Static type is Bird*
// Dynamic type is Chicken

//Static cast is when we convert one type to another explicitly

/*
Explicit Downcast
    - A dynamic_cast performs an explicit downcast.
    - if the pointed-to object is not of the requested type
        (or a type derived from it), the result is null.
*/
int main()
{
    Chicken c("BOB");
    Bird *bPtr = &c;
    Chicken *cPtr = dynamic_cast<Chicken * >(bPtr);
    if(cPtr != nullptr){ // check for null
        //something chicken -specific
    }
}
/*
Virtual Functions
- for virtual functions, the function is not chosen until the call happens
    at runtime! This is called dynamic binding.
- Based on the dynamic type of the receiver.


Overriding vs. Overloading
    Overriding
        - Allowing a subclass to redefine the behavior for one of
        its inherited (virtual) member functions.
    Overloading
        - A single name can refer to many different functions, 
        depending on their parameter types.

The override keyword tells the compiler to sanity check that the overriding 
    function signature actually matches a virual function in the base class.
*/
void tak () const {cout <<"quack"<<endl;}
//If we were trying to call to the talk() class and miss type 
// the compiler would not catch this.

void tak() const override{cout<<"quack"<<endl;}
//The override here would then double check that we are matching a base class
    //function. Due to the typo, it will say there is an error. 

/*
Pure virtual functions.

This can be used when it does not make sense to have a default funciton in 
the base class. For example, it may not be beneficial to say all birds tweet.
It would be better to not provide implementation, and have it decided in the derived
classes. This can be accomplished using pure virtual funcitons
*/

virtual void talk() const = 0;

//the const = 0 is not setting anything equal to zero, it is just
// stating that this is a pure virtual funciton. 
// Sub classes must override the function to provide proper implementation.

/* Bird is now an abstract class, as it is missing implementation
which means that we cannot create a bird object.*/

Bird b; // This would not be allowed, as the Bird class is abstract

Duck a;
Bird * ptr = &a; //This would work since this is now a dynamic type. 


/*

An interface is a class where all functions are pure virtual.

Other classes that derive from it are said to "implement" the base class
*/

class Shape
{
    public:
        virtual double area() const = 0;
        virtual double perimeter() const = 0;
        virtual void scale(double s) = 0;
};

//This is an interface, and Circle Triangle would implement Shape


/*

Dynamic Polymorphism
    - With subtype polymorphism, we can make the decision on what type to use 
        during runtime
    For example, in the Euchre project we will have two derived classes
    from the Player class. When the program is run, the user can then
    decide what type of player they want. Since it is not hardcoded,
    it would be this type of polymorphism. 


    Subtypes vs derived types
    - not all derived types are subtypes!
    - anything that inherits members is a derived type
    - a subtype must follow the is-a relationship

    - What does the "is-a" relationship mean?
        - Liskov Substitution Principle.


*/