/* -----------------------------------------------------------------------------

FILE:              bankacctp2.cpp

DESCRIPTION:       A brief description of this source code file ...

COMPILER:          Xcode, GCC

NOTES:             Put other information here ...

MODIFICATION HISTORY: created readFromDatabase Function

Author                  Date               Version
---------------         ----------         --------------
Nathan Bertram          2016-03-11         Version 6.0

----------------------------------------------------------------------------- */

#include <iostream>
#include <cstring>
#include <algorithm>
#include <fstream>
#include "bankacctp2.hpp"

// Function Protypes
void helpScreen();
void checkForNoArgs(int);
void checkForSlashes(int, char * []);
void collectFirstCharArgs(int, char * [], char []);
void sortArgCollection(char [], int);
void matchArgCombination(char [], int);
void displayErrorMessage();
void readFromDatabaseFile(Record []);

// Global Constants
const char SLASH = '/';

// Valid command line parameter combinations
const char HELP [] = "?";
const char DISPLAY_INFO [] = "DINP";
const char CHANGE_FIRST_NAME [] = "DFNP";
const char CHANGE_LAST_NAME [] = "DLNP";
const char CHANGE_MIDDLE_INTIAL [] = "DMNP";
const char CHANGE_SSN [] = "DNPS";
const char CHANGE_AREA_CODE [] = "ADNP";
const char CHANGE_PHONE_NUMBER [] = "DHNP";
const char TRANSFER [] = "DNNPPT";
const char CHANGE_PASSWORD [] = "DNPW";
const char PRODUCE_REPORT [] = "DR";

/* -----------------------------------------------------------------------------
FUNCTION NAME:     main()
PURPOSE:           Purpose of function ...
RETURNS:           What the function returns ... or ...
RETURNS:           Nothing (void function)
NOTES:             Put important usage notes here ...
----------------------------------------------------------------------------- */
int main(int argc, char * argv[]) {
    char argCollection [argc];
    Record bankAccountDatabase [100];
    
    //std::cout << "argc = " << argc << std::endl;
    readFromDatabaseFile(bankAccountDatabase);
    checkForNoArgs(argc);
    checkForSlashes(argc, argv);
    collectFirstCharArgs(argc, argv, argCollection);
    sortArgCollection(argCollection, argc);
    matchArgCombination(argCollection, argc);
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
    exit(0);
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
//    for (int i = 0; i < argc; i++)
//    {
//        std::cout << "argCollection[i]" <<argCollection[i] << std::endl;
//    }
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
//    for (int i = 0; i < argc; i++)
//    {
//        std::cout << "argCollection[i]" <<argCollection[i] << std::endl;
//    }
    
}
/* -----------------------------------------------------------------------------
FUNCTION NAME:     matchArgCombination()
PURPOSE:           Purpose of function ...
RETURNS:           What the function returns ... or ...
RETURNS:           Nothing (void function)
NOTES:             Put important usage notes here ...
----------------------------------------------------------------------------- */
void matchArgCombination(char argCollection [], int argc)
{
    if (strcmp(argCollection, HELP) == 0)
        helpScreen();
    else if (strcmp(argCollection, DISPLAY_INFO) == 0)
        std::cout << "displayInfo()";
    else if (strcmp(argCollection, CHANGE_FIRST_NAME) == 0)
        std::cout << "changeFirstName()";
    else if (strcmp(argCollection, CHANGE_LAST_NAME) == 0)
        std::cout << "changeLastName()";
    else if (strcmp(argCollection, CHANGE_MIDDLE_INTIAL) == 0)
        std::cout << "changeMiddleIntial()";
    else if (strcmp(argCollection, CHANGE_SSN) == 0)
        std::cout << "changeSSN()";
    else if (strcmp(argCollection, CHANGE_AREA_CODE) == 0)
        std::cout << "changeAreaCode()";
    else if (strcmp(argCollection, CHANGE_PHONE_NUMBER) == 0)
        std::cout << "changePhoneNumber()";
    else if (strcmp(argCollection, TRANSFER) == 0)
        std::cout << "transfer()";
    else if (strcmp(argCollection, CHANGE_PASSWORD) == 0)
        std::cout << "changePassword()";
    else if (strcmp(argCollection, PRODUCE_REPORT) == 0)
        std::cout << "produceReport()";
    else
        displayErrorMessage();
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
    std::cout << "\nSorry those were not a valid parameters, please try again\n\n";
    exit(42);
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     readFromDatabase()
PURPOSE:           Purpose of function ...
RETURNS:           What the function returns ... or ...
RETURNS:           Nothing (void function)
NOTES:             Put important usage notes here ...
----------------------------------------------------------------------------- */
void readFromDatabaseFile(Record bankAccountDatabase [])
{
    char dataFileName [] = "database.txt";
    char lineBuffer [100]; // A place to store the one line from the database file
    std::ifstream dataFile;
    int i = 0; // counter
    
    dataFile.open(dataFileName);
    
    while (dataFile >> bankAccountDatabase[i].firstName) {
        dataFile >> bankAccountDatabase[i].lastName;
        dataFile >> bankAccountDatabase[i].middleInitial;
        dataFile >> bankAccountDatabase[i].ssNum;
        dataFile >> bankAccountDatabase[i].phoneNumAreaCode;
        dataFile >> bankAccountDatabase[i].phoneNum;
        dataFile >> bankAccountDatabase[i].balance;
        dataFile >> bankAccountDatabase[i].accountNum;
        dataFile >> bankAccountDatabase[i].password;
        std::cout << bankAccountDatabase[i].firstName << std::endl;
        std::cout << bankAccountDatabase[i].lastName << std::endl;
        std::cout << bankAccountDatabase[i].middleInitial << std::endl;
        std::cout << bankAccountDatabase[i].ssNum << std::endl;
        std::cout << bankAccountDatabase[i].phoneNumAreaCode << std::endl;
        std::cout << bankAccountDatabase[i].phoneNum << std::endl;
        std::cout << bankAccountDatabase[i].balance << std::endl;
        std::cout << bankAccountDatabase[i].accountNum << std::endl;
        std::cout << bankAccountDatabase[i].password << std::endl;
        i++;
    }
    
    dataFile.close();
}

