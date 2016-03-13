/* -----------------------------------------------------------------------------

FILE:              bankacctp2.cpp

DESCRIPTION:       A brief description of this source code file ...

COMPILER:          Xcode, GCC

NOTES:             Put other information here ...

MODIFICATION HISTORY: created parseArguments and updated readFromDatabaseFile

Author                  Date               Version
---------------         ----------         --------------
Nathan Bertram          2016-03-12         Version 7.0

----------------------------------------------------------------------------- */

#include <iostream>
#include <cstring>
#include <algorithm>
#include <fstream>
#include "bankacctp2.hpp"

using std::cout;
using std::endl;

// Function Protypes
void helpScreen();
void checkForNoArgs(int);
void checkForSlashes(int, char * []);
void collectFirstCharArgs(int, char * [], char []);
void sortArgCollection(char [], int);
void matchArgCombination(int, char * [], char [],  Record []);
void displayErrorMessage();
void readFromDatabaseFile(Record [], char []);
void displayInfo(int, char * [], Record []);
int findAccountNumber(Record [], char []);
void parseArguments(int, char * [], CommandLineParameters&);
bool validateAccountNumberPassword(char [], char [], Record []);

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
    Record bankAccountDatabase [100] = { 0 };
    CommandLineParameters params = { 0 };
    //char accountNumber [] = "F123C";
    
    //cout << "argc = " << argc << endl;
    
    checkForNoArgs(argc);
    checkForSlashes(argc, argv);
    collectFirstCharArgs(argc, argv, argCollection);
    sortArgCollection(argCollection, argc);
    parseArguments(argc, argv, params);
    readFromDatabaseFile(bankAccountDatabase, params.D);
    matchArgCombination(argc, argv, argCollection, bankAccountDatabase);
    //findAccountNumber(bankAccountDatabase, accountNumber);
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
    cout << "I'm a help screen";
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
//        cout << "argCollection[i]" <<argCollection[i] << endl;
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
//        cout << "argCollection[i]" <<argCollection[i] << endl;
//    }
    
}
/* -----------------------------------------------------------------------------
FUNCTION NAME:     matchArgCombination()
PURPOSE:           Purpose of function ...
RETURNS:           What the function returns ... or ...
RETURNS:           Nothing (void function)
NOTES:             Put important usage notes here ...
----------------------------------------------------------------------------- */
void matchArgCombination(int argc, char * argv[], char argCollection [], Record bankAccountDatabase [])
{
    if (strcmp(argCollection, HELP) == 0)
        helpScreen();
    else if (strcmp(argCollection, DISPLAY_INFO) == 0)
        displayInfo(argc, argv, bankAccountDatabase);
    else if (strcmp(argCollection, CHANGE_FIRST_NAME) == 0)
        cout << "changeFirstName()";
    else if (strcmp(argCollection, CHANGE_LAST_NAME) == 0)
        cout << "changeLastName()";
    else if (strcmp(argCollection, CHANGE_MIDDLE_INTIAL) == 0)
        cout << "changeMiddleIntial()";
    else if (strcmp(argCollection, CHANGE_SSN) == 0)
        cout << "changeSSN()";
    else if (strcmp(argCollection, CHANGE_AREA_CODE) == 0)
        cout << "changeAreaCode()";
    else if (strcmp(argCollection, CHANGE_PHONE_NUMBER) == 0)
        cout << "changePhoneNumber()";
    else if (strcmp(argCollection, TRANSFER) == 0)
        cout << "transfer()";
    else if (strcmp(argCollection, CHANGE_PASSWORD) == 0)
        cout << "changePassword()";
    else if (strcmp(argCollection, PRODUCE_REPORT) == 0)
        cout << "produceReport()";
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
    cout << "\nSorry those were not a valid parameters, please try again\n\n";
    exit(42);
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     readFromDatabase()
PURPOSE:           Purpose of function ...
RETURNS:           What the function returns ... or ...
RETURNS:           Nothing (void function)
NOTES:             Put important usage notes here ...
----------------------------------------------------------------------------- */
void readFromDatabaseFile(Record bankAccountDatabase [], char databaseName [])
{
    char lineBuffer [100]; // A place to store the one line from the database file
    std::ifstream dataFile;
    int i = 0; // counter
    
    dataFile.open(databaseName);
    if (dataFile)
    {
        while (dataFile >> bankAccountDatabase[i].firstName) {
            dataFile >> bankAccountDatabase[i].lastName;
            dataFile >> bankAccountDatabase[i].middleInitial;
            dataFile >> bankAccountDatabase[i].ssNum;
            dataFile >> bankAccountDatabase[i].phoneNumAreaCode;
            dataFile >> bankAccountDatabase[i].phoneNum;
            dataFile >> bankAccountDatabase[i].balance;
            dataFile >> bankAccountDatabase[i].accountNum;
            dataFile >> bankAccountDatabase[i].password;
            i++;
        }
    }
    else
        cout << "\n\nError opening the database file.\n";

    dataFile.close();
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     displayInfo()
PURPOSE:           Purpose of function ...
RETURNS:           What the function returns ... or ...
RETURNS:           Nothing (void function)
NOTES:             Put important usage notes here ...
----------------------------------------------------------------------------- */
void displayInfo(int argc, char * argv[], Record bankAccountDatabase [])
{
    //char accountNumber [] = "C123A";
    char databaseName [100] = {0};
    char accountNumber [100] = {0};
    char password [100] = {0};
    int databaseIndex;
    
    for (int i = 1; i < argc; i++)
    {
        char * argument = argv[i];
        
        if (argument[1] == 'D')
            strcpy(databaseName, &argument[2]);
        if (argument[1] == 'N')
            strcpy(accountNumber, &argument[2]);
        if (argument[1] == 'P')
            strcpy(password, &argument[2]);
    }
    
    if (validateAccountNumberPassword(accountNumber, password, bankAccountDatabase))
    {
        databaseIndex = findAccountNumber(bankAccountDatabase, accountNumber);
        cout << bankAccountDatabase[databaseIndex].firstName << endl;
        cout << bankAccountDatabase[databaseIndex].lastName << endl;
        cout << bankAccountDatabase[databaseIndex].middleInitial << endl;
        cout << bankAccountDatabase[databaseIndex].ssNum << endl;
        cout << bankAccountDatabase[databaseIndex].phoneNumAreaCode << endl;
        cout << bankAccountDatabase[databaseIndex].phoneNum << endl;
        cout << bankAccountDatabase[databaseIndex].balance << endl;
        cout << bankAccountDatabase[databaseIndex].accountNum << endl;
        cout << bankAccountDatabase[databaseIndex].password << endl;
    }
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     findAccountNumber()
PURPOSE:           Looks for account # that is passed in
RETURNS:           the index of the record in the database the contains that
RETURNS:           record or -1 if not found
NOTES:             Put important usage notes here ...
----------------------------------------------------------------------------- */
int findAccountNumber(Record bankAccountDatabase [], char accountNumber [])
{
    int i = 0;
    
//    for (int j = 0; j < 100; j++)
//    {
//        cout << bankAccountDatabase[j].firstName << endl;
//        cout << bankAccountDatabase[j].lastName << endl;
//        cout << bankAccountDatabase[j].middleInitial << endl;
//        cout << bankAccountDatabase[j].ssNum << endl;
//        cout << bankAccountDatabase[j].phoneNumAreaCode << endl;
//        cout << bankAccountDatabase[j].phoneNum << endl;
//        cout << bankAccountDatabase[j].balance << endl;
//        cout << bankAccountDatabase[j].accountNum << endl;
//        cout << bankAccountDatabase[j].password << endl;
//    }
    while (bankAccountDatabase[i].accountNum[0] != 0)
    {
        if (strcmp(bankAccountDatabase[i].accountNum, accountNumber) == 0)
            return i;
        //cout << i << endl;
        i++;
    }
    cout << "The account number: " << accountNumber << " was not found";
    exit(1);
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     verifyInDatabase()
PURPOSE:           verifies the passed in argument is contained in the database
RETURNS:
RETURNS:
NOTES:             Put important usage notes here ...
----------------------------------------------------------------------------- */

/* -----------------------------------------------------------------------------
FUNCTION NAME:     validAccountNumberPassword()
PURPOSE:           checks that passed in account number and password match a 
                    single record in the database
RETURNS:            true if a valid account number and password combination
RETURNS:            displays error message and exits, if not
NOTES:
----------------------------------------------------------------------------- */
bool validateAccountNumberPassword(char accountNumber [], char password [], Record bankAccountDatabase [])
{
    int databaseIndex; // Index of database records that contains account #
    
    databaseIndex = findAccountNumber(bankAccountDatabase, accountNumber);
    if (strcmp(bankAccountDatabase[databaseIndex].password, password) == 0)
        return true;
    else
    {
        cout << "\nThat account number and password combination was not valid\n";
        exit(2);
    }
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     parseArguments()
PURPOSE:           
RETURNS:
RETURNS:
NOTES:             Put important usage notes here ...
----------------------------------------------------------------------------- */

void parseArguments(int argc, char * argv[], CommandLineParameters &params)
{
    bool foundFirstAccountNumber = false;
    bool foundFirstPassword = false;
    
    for (int i = 1; i < argc; i++)
    {
        char * argument = argv[i];
        
        if (argument[1] == '?')
            if (argument[2] != 0)
                displayErrorMessage();
        if (argument[1] == 'A')
            strcpy(params.A, &argument[2]);
        if (argument[1] == 'D')
            strcpy(params.D, &argument[2]);

        if (argument[1] == 'F')
            strcpy(params.F, &argument[2]);
        if (argument[1] == 'H')
            strcpy(params.H, &argument[2]);
        if (argument[1] == 'I')
            if (argument[2] != 0)
                displayErrorMessage();
        if (argument[1] == 'L')
            strcpy(params.L, &argument[2]);
        if (argument[1] == 'M')
            strcpy(params.M, &argument[2]);
        if (argument[1] == 'N')
        {
            if (foundFirstAccountNumber)
                strcpy(params.N2, &argument[2]);
            else
            {
                strcpy(params.N1, &argument[2]);
                foundFirstAccountNumber = true;
            }
            
        }
        if (argument[1] == 'P')
        {
            if (foundFirstPassword)
                strcpy(params.P2, &argument[2]);
            else
            {
                strcpy(params.P1, &argument[2]);
                foundFirstPassword = true;
            }
            
        }
        if (argument[1] == 'R')
            strcpy(params.R, &argument[2]);
        if (argument[1] == 'S')
            strcpy(params.S, &argument[2]);
        if (argument[1] == 'T')
            strcpy(params.T, &argument[2]);
        if (argument[1] == 'W')
            strcpy(params.W, &argument[2]);
    }
    
}
