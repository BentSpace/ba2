/* -----------------------------------------------------------------------------

FILE:              main.cpp

DESCRIPTION:       A brief description of this source code file ...

COMPILER:          Xcode, GCC

NOTES:             Put other information here ...

MODIFICATION HISTORY: created sortArgCollection() function

Author                  Date               Version
---------------         ----------         --------------
Nathan Bertram          2016-03-04         Version 4.0

----------------------------------------------------------------------------- */

#include <iostream>
#include <cstring>
#include <algorithm>
#define CLEAR_SCREEN \
std::cout << "\033[2J\033[1;1H"

// Function Protypes
void helpScreen();
void checkForNoArgs(int);
void checkForSlashes(int, char * []);
void collectFirstCharArgs(int, char * [], char []);
void sortArgCollection(char argCollection [], int argc);
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
    char argCollection [argc];
    std::cout << "argc = " << argc << std::endl;
    checkForNoArgs(argc);
    checkForSlashes(argc, argv);
    collectFirstCharArgs(argc, argv, argCollection);
    sortArgCollection(argCollection, argc);
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
FUNCTION NAME:     collectFirstCharArgs()
PURPOSE:           Purpose of function ...
RETURNS:           What the function returns ... or ...
RETURNS:           Nothing (void function)
NOTES:             Put important usage notes here ...
----------------------------------------------------------------------------- */
void collectFirstCharArgs(int argc, char * argv[], char argCollection [])
{
    for (int i = 1; i < argc; i++)
    {
        char * argument = argv[i];
        if (argument[1] == 0)
        {
            displayErrorMessage();
        }
        argCollection[i - 1] = argument[1]; // Add letter to arg collectoin
    }
    argCollection[argc - 1] = '\0';  // Set the last element of the array to the null byte
    for (int i = 0; i < argc; i++)
    {
        std::cout << "argCollection[i]" <<argCollection[i] << std::endl;
    }
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     sortArgCollection()
PURPOSE:           Purpose of function ...
RETURNS:           What the function returns ... or ...
RETURNS:           Nothing (void function)
NOTES:             Put important usage notes here ...
----------------------------------------------------------------------------- */
void sortArgCollection(char argCollection [], int argc)
{
    // sorts from first parameter to second parameter
    std::sort(argCollection, argCollection + (argc - 1));
    for (int i = 0; i < argc; i++)
    {
        std::cout << "argCollection[i]" <<argCollection[i] << std::endl;
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
