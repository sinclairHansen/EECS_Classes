
//Week 2 lecture notes
// 9/3/2025
// Sinclair Hansen

#include <iostream>
using namespace std;


/* C++ standard library types
Generally considered part of cpp, but must be brought in via a proper #include directive.
using namespace std; allows you to omit the std::
*/
#include <utility>
pair<int, bool> p = {142, false}; // a pair is used for multiple typed values
tuple<int, bool, string> t = {14, true, "Hello"}; 
//Tuple is the way to have more than two types

variant<string, int> var;
//variant is used to have one type OR another.
#include <vector>
int main(){
    vector<int> v = {1,2,3};
    for(size_t i = 0; i < v.size(); i++) //size_t is a bit more broad that int, and it can only be positive
    // as sizes can't be negative
    {
        cout<<v[i]<<endl;
    }
    
    string str1 = "make a "; //This is a C++ style string. A lot better than C-style as
    //it allows for better comparisons and functions
    string str2 = "wish";

    str1 < str2; //true, alphabetic comparison

    string str3 = str1 + str2; // "make a wish"
    str3[0] = str3[7];
    str3[7] = "f"; //make a fish --> might be wrong since it's erroring but idk



    //std::pair
    std::pair<int,bool> p1;
    p1.first = 5;
    p1.second = false;


    //std::vector
    vector<double> nums = {1, 2, 3, 4, 5};
    vector<string> pets = {"solo", "stryder"};


    //There are several other ways to initialize a vector
    vector<int>v;//empty
    vector<int>v2(5); // 0, 0, 0, 0, 0,
    vector<int>v3(3, 42); //42, 42, 42

    v.push_back(1); 
    v.push_back(2);
    v.push_back(3);
    //v contains {1, 2, 3}

    v.pop_back();
    // v contains {1, 2}
    v.clear(); 
    // v contains {}

    /* VECTOR FUNCTIONS

    size -> returns size of the vector
    front -> returns a reference to the first element
    back -> returns a reference to the last element
    at -> works like indexing, but does bounds checking
    empty -> returns whether the vector is empty (as a bool)
    clear -> removes all elements from the vector
    push_back -> adds a new element to the back of the vector
    pop_back -> removes the last element in the vector

    PROCEDURAL ABSTRACTION
    It is using ingredients without knowing how or why they work
    In general it helps manage complexity and hides details

    In computer programs it makes programs easier to maintain and modify, and
    it separates what code does from how it works. Functions are the main tool for this in C++

    
    
    
    
    */

    return 0;
}


