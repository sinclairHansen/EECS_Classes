

//Notes for week 5
// File I/O Streams wee woo
// Sinclair Hansen
// September 22, 2025


#include <iostream>
#include <fstream> // This is needed for file operations
using namespace std;

int main(){
    ifstream fin("text.txt"); //When opening a file, check if it opened
    if(!fin.is_open())
    {
        cout<<"open failed" <<endl;
        return 1;// If not, return a fail message
    }

    string item; //creates a string variable
    fin >> item; //extracts a string from the txt file

    double weight; // creates a double object
    fin >> weight;// extracts the double from the txt
    fin.close(); // close the file after using it. Not always necessary if forgotten



    // File Output: ofstream

    ofstream fout("text.txt");
    if(!fin.is_open())
    {
        cout<<"open failed" <<endl;
        return 1;// If not, return a fail message
    }
    for (int i = 1; i < 1000; i++)
    {
        fout << i << endl; //Sends the value of i to the file. Each output creates a new line
    }
    string word;
    while(fin >> word) // reads until end of file
    {
        if(word == "bee"){fout << "cat" << endl;}
        else {fout << word << endl;}


    } //When the loop exits, we know we made it to the end of the file.

    while(fin) // This would compile, but it is not reccomended because it will repeat the last word twice. It doesn't check if the extraction is
    // successful until after the word gets printed.
    {
        fin >> word;
        cout << word << endl;
    }

    string line;
    getline(fin, line);
    cout << line << endl; // This is also something to be weary of if you are getting string from the line. Only use for printing whole lines. 


    /*Exit codes
    When a process finishes execution, it passes back an integer "exit status"
    or "exit code"

    At the terminal, $? gives the exit status of the previous command. Use echo $?
    to see it. Code 0 indicate success.

    */
   fin >> item >> weight; // Multiple read operations on one line. 


    //String streams and testing
    //istringstream 
    // an input stream that uses a string as its source.
    // useful for simulating stream input from a "hardcoded" string

    //ostringstream
    //  an output stream that writes into a string.
    //  useful for capturing output as a string that can be checked for corectness

    return 0;
}
//argv and argc
// Two parameters to main:
//  argc - the number of arguments
//  argv - an array of the arguments (sort of)

int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        cout << "Usage: ./redact WORD INFILE OUTFILE NUM_STARS"<<endl;
        return 1;
    }
    //Use caution when comparing elements of argv.

    //BAD, compares addresses
    if(argv[1] == "--debug"){}
    //OK, wrap one in a std::string
    if (std::string(argv[1] == "--debug")){}

    //OK, ""s suffix creates a std::string
    if(argv[1] == "debug"s){}

    

    //stoi() parses an integer encoded in a string
    #include <string> // needed for stoi() and stod()
    int numStars = stoi(argv[4]);//Yes - parse string "10" to int 10

    //stod() parses a double encoded in a string
    





    /* ABSTRACT DATA TYPES IN C++

    In C-style ADTs, we have a structure that is independent 
    ex
    struct Triangle{double a, b, c};

    Then the funcitons for this structure are made on their own

    void Triangle_init(..){..};

    within the main, we call the structure:
        Triangle t1;
    
    Then initialize it:
        Triangle_init(...);

    Moving on to C++ style ADTs we get classes. They combine the structure with the member funcitons

    Struct -> C style, contains only data, undefined by default, all data is accessible

    Class -> heterogeneous aggregate data type, C++ style, contains data and functions, constructors can be used to initalize, control of data access  
    */


    //Lets make Triangle a C++ ADT

    class Triangle{
        private: //Private means we can only access these variables within the scope of the class
            double a;
            double b;
            double c;
        public: //Sometimes its better to put public first. If people are reading through code they care more about the interface
            Triangle(double a_in, double b_in, double c_in : a(a_in), b(b_in), c(c_in){...} //Constructors are usually public
            //The part after the : does default initialization for the variables. Otherwise they are not initialized -> usually no beuno
            double perimeter() const {...}
            void scale(double s){...}
        //Member initializer lists
        //Warning! the order of initialization depends on the declaration order.
            // NOT the order of the member initializer list. 
        //In this ^ class, a will always get initialized first, regardless of what order we put the variables in the constructor

    }
    int main(){ //oof third main
        Triangle t1(3,4,5); // This must be initialized, unless we have a constructor that allows no initialization
        //or
        Triangle t1{3,4,5};
        //OR
        Triangle t1 = {3,4,5};
        
        t1.scale(2); //Calls member function
        cout << t1.perimeter();
    }

    //Constructors
    // Whenever you create an object of class type, a constructor for that class is called on the object to initialize it. ALWAYS
    // A constructor is basically a function, but you don't call it yourself - the compiler does it automatically
    // All of these use a Triangle constructor
    Triangle t1;
    Triangle t2(3, 4, 5);
    Triangle t3 = Triangle(3,4,5);
    //By the time we get to the start of the body of the constructor, all member variables have been initialized.
    // This means it would be best to have that taken care of prior, so we don't initalize more than once
    //Do not do
    // Triangle t1(); -> that is a function declaration.


    //Multiple constructors
        //A class may have several different constructors
    
    class Triangle{
        private:
        double a, b, c;

    public:
        Triangle() : a(1), b(1), c(1) {} // DEFAULT constructor

        Triangle(double side) 
            : a(side), b(side), c(side) {}
        
        Triangle(double a_in, double b_in, double c_in)
            : a(a_in), b(b_in), c(c_in){}
        //Depending on what we input when we call the ADT, a different
            //constructor will get called

        //We don't have to have a default constructor. If so Triangle t1; will not compile
    }

    //Class-type objects as members
        //Members are default initialized if left out of the member0initializer list for a constructor
        // If you put no constructors in the class, then C++ will make a default constructor
        // If you make a constructor, then you need to make your own default constructor for it to compile a class
            // call with no arguments. C++ will not make a default constructor automatically in this case.

    //Default initialization
    /*  Objects that are not explicitly initalized are default initialized
    Atomic objects (ints, double, bool, char, pointers) are default initialized by doing nothing
        - They retain whatever value what previously in the memory

        Array objects are default initialized by default
            initializing each element.
 ́       Compound (i.e. class-type) objects are default
            initialized by calling the default constructor.

    The implicit default constructor
        -If you don’t define any constructors, the
            compiler provides a default constructor for you.

    struct vs. class
        In the C++ language, the only difference between the struct and class keywords is the default access levels
            struct - public by default
            class - private by default
        However, by convention we use structs and classes very differently!

    Review: Representation Invariants
        - A problem for compund types...
            -Some combinations of member values don't make sense together.
        We use represenation invariants to express the conditions for a valid compund object

    GET AND SET FUNCTIONS
         - Some classes provide functions to get and set private member variables
         The reason we use private variables/functions is to separate the implementation from the user interface.
         Lets say we want to change the implementation for the Triangle such that we use sides and angles, we can keep the
         user interface the same but change whats under the hood.
    */

}