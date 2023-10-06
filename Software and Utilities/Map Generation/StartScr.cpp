#include "StartScr.h"

StartScr::StartScr()
{
    std::cout << "New Instance of Start Screen Created! " << std::endl << std::endl;
    _exit = 0;
}

StartScr::~StartScr()
{
    std::cout << "Start Screen Destroyed! " << std::endl;
}

void StartScr::initScr()
{

}

void StartScr::setDisplay()
{
    std::cout << "       oooooooooooooooo                                                       " << std::endl;
    std::cout << "      oooooooo##oooooooo                     _________    _       _  ______   " << std::endl;
    std::cout << "     oooooooo####oooooooo                   /  _   _  / / /     / / / __ /    " << std::endl;
    std::cout << "    oooooooo######oooooooo                 / / / / / / / /     / / / /  /     " << std::endl;
    std::cout << "   oooooooooooooooooooooooo               / / / / / / / /     / / / / /       " << std::endl;
    std::cout << "  oooooooooooooooooooooooooo             / / /_/ / / / /___  / / / /__ /      " << std::endl;
    std::cout << " oooooooo############oooooooo           /_/     /_/ /_____/ /_/ /______/      " << std::endl;
    std::cout << "oooooooo##############oooooooo                                                " << std::endl << std::endl;
    std::cout << "______________________________________________________________________________" << std::endl;
}

void StartScr::inputScreen()
{
    char input;
    
    std::cout << "Welcome to Micheal's simulation environment!" << std::endl;
    std::cout << "For details of available software and commands, type 'h'." << std::endl;
    std::cout << "For a list of avaible commands only, type 'c'." << std::endl;
    std::cout << "To exit, type 'e'." << std::endl;

    std::cin >> input;

    switch (input)
    {
    case 'c':
        std::cout << "Commands: " << std::endl;
        break;
    case 'h':
        std::cout << "Help: " << std::endl;
        break;
    case 'e':
        _exit = 1;
        break;
    default:
        std::cout << "Invalid Command . . ." << std::endl;
 
    }
    
}

void StartScr::showFunctions()
{

}

void StartScr::showHelp()
{

}

bool StartScr::exitProgram()
{
    return _exit;
}