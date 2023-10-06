#ifndef STARTSCR_H
#define STARTSCR_H

#include <iostream>
#include <string>

class StartScr
{
public:
	StartScr(); // constructor
	~StartScr(); // destructor
	void initScr(); // function to initialise start screen
	void setDisplay(); // terminal design with header displaying software top of page redrawn after every command!
	void inputScreen(); //layer below display asking for input command
	void helpScreen(); //displays details of avaiable software and commands
	void commandsScreen();
	void showFunctions(); // outputs list of functions
	void showHelp(); // outputs info and list of functions etc.

	bool exitProgram();
private:
	bool _exit;
};

#endif 