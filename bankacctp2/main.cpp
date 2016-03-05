/* -----------------------------------------------------------------------------

FILE:              main.cpp

DESCRIPTION:       A brief description of this source code file ...

COMPILER:          Xcode, GCC

NOTES:             Put other information here ...

MODIFICATION HISTORY:

Author                  Date               Version
---------------         ----------         --------------
Nathan Bertram          2016-03-03         Version 1.0

----------------------------------------------------------------------------- */

#include <iostream>
#include <cstring>
#define CLEAR_SCREEN \
std::cout << "\033[2J\033[1;1H"

// Function Protypes
void helpScreen();
void checkForNoArgs(int);
void checkForSlashes(int, char * []);
void displayErrorMessage();

// Global Constants
const char SLASH = '/';

/* -----------------------------------------------------------------------------
FUNCTION NAME:     name-of-function()
PURPOSE:           Purpose of function ...
RETURNS:           What the function returns ... or ...
RETURNS:           Nothing (void function)
NOTES:             Put important usage notes here ...
----------------------------------------------------------------------------- */
int main(int argc, char * argv[]) {
    checkForNoArgs(argc);
    checkForSlashes(argc, argv);
    return 0;
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     checkForNoArgs()
PURPOSE:           Purpose of function ...
RETURNS:           What the function returns ... or ...
RETURNS:           Nothing (void function)
NOTES:             Put important usage notes here ...
----------------------------------------------------------------------------- */
void checkForNoArgs(int argc)
{
    if (argc == 1)
        helpScreen();
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     helpScreen()
PURPOSE:           Purpose of function ...
RETURNS:           What the function returns ... or ...
RETURNS:           Nothing (void function)
NOTES:             Put important usage notes here ...
----------------------------------------------------------------------------- */
void helpScreen()
{
    std::cout << "I'm a help screen";
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     checkForSlashes()
PURPOSE:           Purpose of function ...
RETURNS:           What the function returns ... or ...
RETURNS:           Nothing (void function)
NOTES:             Put important usage notes here ...
----------------------------------------------------------------------------- */
void checkForSlashes(int argc, char * argv[])
{
    for (int i = 1; i < argc; i++)
    {
        char * argument = argv[i];
        if (argument[0] != SLASH)
        {
            displayErrorMessage();
        }
    }
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     validateArgCombination()
PURPOSE:           Purpose of function ...
RETURNS:           What the function returns ... or ...
RETURNS:           Nothing (void function)
NOTES:             Put important usage notes here ...
----------------------------------------------------------------------------- */

/* -----------------------------------------------------------------------------
FUNCTION NAME:     displayErrorMessage()
PURPOSE:           Purpose of function ...
RETURNS:           What the function returns ... or ...
RETURNS:           Nothing (void function)
NOTES:             Put important usage notes here ...
----------------------------------------------------------------------------- */
void displayErrorMessage()
{
    std::cout << "\n\nSorry that was not a valid parameter, please try again\n\n";
    exit(42);
}
