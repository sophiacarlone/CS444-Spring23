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

#include <iostream>
#include <fstream>

using namespace std;

int main(){
    ofstream out;
    string filename = "keys_logged.txt";
    
    //this is the file that is logging all the characters. Does it need more information?
    out.open(filename);

    /*dont need to use threads because people can really only really give one keyboard input at a time
    *even if you try to press at the same time there is a slight difference. */
    char c; //character (do it one at a time or can I do something more efficient)

    while(true){
        //getting keys
        c = getchar();
        if( c == '}') break;
        out << c;
    }
}