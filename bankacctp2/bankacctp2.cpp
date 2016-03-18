/* -----------------------------------------------------------------------------

FILE:              bankacctp2.cpp

DESCRIPTION:       A brief description of this source code file ...

COMPILER:          Xcode, GCC

NOTES:             Put other information here ...

MODIFICATION HISTORY: added argument validation

Author                  Date               Version
---------------         ----------         --------------
Nathan Bertram          2016-03-18         Version 13.0

----------------------------------------------------------------------------- */

#include <iostream>
#include <cstring>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include "bankacctp2.hpp"

using std::cout;
using std::endl;
using std::setw;

// Function Protypes
void helpScreen();
void checkForNoArgs(int);
void checkForSlashes(int, char * []);
void collectFirstCharArgs(int, char * [], char []);
void sortArgCollection(char [], int);
void matchArgCombination(int, char * [], char [],  Record [],
                         CommandLineParameters);
void displayErrorMessage();
void readFromDatabaseFile(Record [], char []);
void displayInfo(Record [], CommandLineParameters);
int findAccountNumber(Record [], char []);
void parseArguments(int, char * [], CommandLineParameters&);
bool validateAccountNumberPassword(char [], char [], Record []);
void changeFirstName(Record [], CommandLineParameters);
void changeLastName(Record [], CommandLineParameters);
void changeMiddleIntial(Record [], CommandLineParameters);
void changeSSN(Record [], CommandLineParameters);
void changeAreaCode(Record [], CommandLineParameters);
void changePhoneNumber(Record [], CommandLineParameters);
void changePassword(Record [], CommandLineParameters);
void transfer(Record [], CommandLineParameters);
void produceReport(Record [], CommandLineParameters);
void saveDatabase(Record [], CommandLineParameters);

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
    matchArgCombination(argc, argv, argCollection, bankAccountDatabase, params);
    saveDatabase(bankAccountDatabase, params);
    /*
    for (int j = 0; j < 3; j++)
        {
            cout << bankAccountDatabase[j].lastName << endl;
            cout << bankAccountDatabase[j].firstName << endl;
            cout << bankAccountDatabase[j].middleInitial << endl;
            cout << bankAccountDatabase[j].ssNum << endl;
            cout << bankAccountDatabase[j].phoneNumAreaCode << endl;
            cout << bankAccountDatabase[j].phoneNum << endl;
            cout << bankAccountDatabase[j].balance << endl;
            cout << bankAccountDatabase[j].accountNum << endl;
            cout << bankAccountDatabase[j].password << endl;
        }
    */
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

    std::ifstream helpFile;
    helpFile.open("helpFile.txt");
    
    char getdata[10000];
    helpFile.read(getdata, sizeof getdata);
    if (helpFile.eof())
    {
        // got the whole file...
        //size_t bytes_really_read = helpFile.gcount();
        
    }
    else if (helpFile.fail())
    {
        // some other error...
    }
    else
    {
        // getdata must be full, but the file is larger...
        
    }
    cout << getdata;
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
void matchArgCombination(int argc, char * argv[], char argCollection [],
                         Record bankAccountDatabase [], CommandLineParameters params)
{
    if (strcmp(argCollection, HELP) == 0)
        helpScreen();
    else if (strcmp(argCollection, DISPLAY_INFO) == 0)
    {
        if (validateAccountNumberPassword(params.N1, params.P1, bankAccountDatabase))
            displayInfo(bankAccountDatabase, params);
    }
    else if (strcmp(argCollection, CHANGE_FIRST_NAME) == 0)
    {
        if (validateAccountNumberPassword(params.N1, params.P1, bankAccountDatabase))
            changeFirstName(bankAccountDatabase, params);
    }
    else if (strcmp(argCollection, CHANGE_LAST_NAME) == 0)
    {
        if (validateAccountNumberPassword(params.N1, params.P1, bankAccountDatabase))
            changeLastName(bankAccountDatabase, params);
    }
    else if (strcmp(argCollection, CHANGE_MIDDLE_INTIAL) == 0)
    {
        if (validateAccountNumberPassword(params.N1, params.P1, bankAccountDatabase))
            changeMiddleIntial(bankAccountDatabase, params);
    }
    else if (strcmp(argCollection, CHANGE_SSN) == 0)
    {
        if (validateAccountNumberPassword(params.N1, params.P1, bankAccountDatabase))
            changeSSN(bankAccountDatabase, params);
    }
    else if (strcmp(argCollection, CHANGE_AREA_CODE) == 0)
    {
        if (validateAccountNumberPassword(params.N1, params.P1, bankAccountDatabase))
            changeAreaCode(bankAccountDatabase, params);
    }
    else if (strcmp(argCollection, CHANGE_PHONE_NUMBER) == 0)
    {
        if (validateAccountNumberPassword(params.N1, params.P1, bankAccountDatabase))
            changePhoneNumber(bankAccountDatabase, params);
    }
    else if (strcmp(argCollection, TRANSFER) == 0)
    {
        if (validateAccountNumberPassword(params.N1, params.P1, bankAccountDatabase))
            if (validateAccountNumberPassword(params.N2, params.P2, bankAccountDatabase))
                transfer(bankAccountDatabase, params);
    }
    else if (strcmp(argCollection, CHANGE_PASSWORD) == 0)
    {
        if (validateAccountNumberPassword(params.N1, params.P1, bankAccountDatabase))
            changePassword(bankAccountDatabase, params);
    }
    else if (strcmp(argCollection, PRODUCE_REPORT) == 0)
        produceReport(bankAccountDatabase, params);
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
    std::ifstream dataFile;
    int i = 0; // counter
    
    dataFile.open(databaseName);
    if (dataFile)
    {
        while (dataFile >> bankAccountDatabase[i].lastName)
        {
            dataFile >> bankAccountDatabase[i].firstName;
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
void displayInfo(Record bankAccountDatabase [], CommandLineParameters params)
{
    int databaseIndex;

    databaseIndex = findAccountNumber(bankAccountDatabase, params.N1);
    cout << "Name: " << bankAccountDatabase[databaseIndex].firstName << " "
    << bankAccountDatabase[databaseIndex].middleInitial << " "
    << bankAccountDatabase[databaseIndex].lastName << endl;
    cout << "Social Security Number: " << bankAccountDatabase[databaseIndex].ssNum << endl;
    cout << "Phone Number: (" << bankAccountDatabase[databaseIndex].phoneNumAreaCode
    << ") " << bankAccountDatabase[databaseIndex].phoneNum << endl;
    cout.precision(2);
    cout << "Balance: $" << std::fixed << bankAccountDatabase[databaseIndex].balance << endl;
    cout << "Account #: " << bankAccountDatabase[databaseIndex].accountNum << endl;
    cout << "Password: " << bankAccountDatabase[databaseIndex].password << endl;
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
        
        // If second character in argument is 'A'
        if (argument[1] == 'A')
        {
            // Check to make sure argument is exactly 5 characters
            if (strlen(argument) != 5)
                displayErrorMessage();
            // check to see if all characters are digits
            for (int i = 2; i < strlen(argument); i++)
            {
                if (!isdigit(argument[i]))
                    displayErrorMessage();
            }
            // Argument is valid, copy to params struct
            strcpy(params.A, &argument[2]);
        }
        
        // If second character in argument is 'D'
        if (argument[1] == 'D')
        {
            // Check to make sure argument is less than 99 characters
            if (strlen(argument) > 99)
                displayErrorMessage();
            // Argument is valid, copy to params struct
            strcpy(params.D, &argument[2]);
        }
        
        // If second character in argument is 'F'
        if (argument[1] == 'F')
        {
            // Check to make sure argument is less than 99 characters
            if (strlen(argument) > 99)
                displayErrorMessage();
            // check to see if all characters are letters
            for (int i = 2; i < strlen(argument); i++)
            {
                if (!isalpha(argument[i]))
                    displayErrorMessage();
            }
            // Argument is valid, copy to params struct
            strcpy(params.F, &argument[2]);
        }
        
        // If second character in argument is 'H'
        if (argument[1] == 'H')
        {
            // Check to make sure argument is exactly 9 characters
            if (strlen(argument) != 9)
                displayErrorMessage();
            // check to see if all characters are digits
            for (int i = 2; i < strlen(argument); i++)
            {
                if (!isdigit(argument[i]))
                    displayErrorMessage();
            }
            // Argument is valid, copy to params struct
            strcpy(params.H, &argument[2]);
        }
        
        // If second character in argument is 'I'
        if (argument[1] == 'I')
        {
            // Check to make sure argument is exactly 2 characters
            if (argument[2] != 0)
                displayErrorMessage();
        }
        
        // If second character in argument is 'L'
        if (argument[1] == 'L')
        {
            // Check to make sure argument is less than 99 characters
            if (strlen(argument) > 99)
                displayErrorMessage();
            // check to see if all characters are letters
            for (int i = 2; i < strlen(argument); i++)
            {
                if (!isalpha(argument[i]))
                    displayErrorMessage();
            }
            // Argument is valid, copy to params struct
            strcpy(params.L, &argument[2]);
        }
        
        // If second character in argument is 'M'
        if (argument[1] == 'M')
        {
            // Check to make sure argument is exactly 3 characters
            if (strlen(argument) != 3)
                displayErrorMessage();
            // check to see if all characters are letters
            for (int i = 2; i < strlen(argument); i++)
            {
                if (!isalpha(argument[i]))
                    displayErrorMessage();
            }
            // Argument is valid, copy to params struct
            params.M = argument[2];
        }
        
        // If second character in argument is 'N'
        if (argument[1] == 'N')
        {
            
            if (foundFirstAccountNumber)
            {
                // Check to make sure argument is exactly (5 + 2) characters
                if (strlen(argument) != (5 + 2))
                    displayErrorMessage();
                strcpy(params.N2, &argument[2]);
            }
            else
            {
                // Check to make sure argument is exactly (5 + 2) characters
                if (strlen(argument) != (5 + 2))
                    displayErrorMessage();
                strcpy(params.N1, &argument[2]);
                foundFirstAccountNumber = true;
            }
            
        }
        
        // If second character in argument is 'P'
        if (argument[1] == 'P')
        {
            if (foundFirstPassword)
            {
                // Check to make sure argument is exactly (6 + 2) characters
                if (strlen(argument) != (6 + 2))
                    displayErrorMessage();
                strcpy(params.P2, &argument[2]);
            }
            else
            {
                // Check to make sure argument is exactly (6 + 2) characters
                if (strlen(argument) != (6 + 2))
                    displayErrorMessage();
                strcpy(params.P1, &argument[2]);
                foundFirstPassword = true;
            }
            
        }
        
        // If second character in argument is 'R'
        if (argument[1] == 'R')
        {
            // Check to make sure argument is less than 99 characters
            if (strlen(argument) > 99)
                displayErrorMessage();
            strcpy(params.R, &argument[2]);
        }
        
        // If second character in argument is 'S'
        if (argument[1] == 'S')
        {
            // Check to make sure argument is exactly 9 + 2 characters
            if (strlen(argument) != (9 + 2))
                displayErrorMessage();
            // check to see if all characters are digits
            for (int i = 2; i < strlen(argument); i++)
            {
                if (!isdigit(argument[i]))
                    displayErrorMessage();
            }
            // Argument is valid, copy to params struct
            strcpy(params.S, &argument[2]);
        }
        
        // If second character in argument is 'T'
        if (argument[1] == 'T')
        {
            bool foundAPeriod = false;
            // check to see if all characters are digits or a '.'
            for (int i = 2; i < strlen(argument); i++)
            {
                if (argument[i] != '.')
                {
                    // if haven't found a period yet
                    if (!foundAPeriod)
                        foundAPeriod = true;
                    else
                        displayErrorMessage();
                }
                else if (!isdigit(argument[i]))
                    displayErrorMessage();
            }
            params.T = atof(&argument[2]);
        }
        
        // If second character in argument is 'W'
        if (argument[1] == 'W')
        {
            // Check to make sure argument is exactly 6 + 2 characters
            if (strlen(argument) != (6 + 2))
                displayErrorMessage();
            // check to see if all characters are digits or uppercase letters
            for (int i = 2; i < strlen(argument); i++)
            {
                // if character is a letter
                if (isalpha(argument[i]))
                {
                    // if character is not uppercase
                    if (!isupper(argument[i]))
                        displayErrorMessage();
                }
                // if character in not a digit
                else if (!isdigit(argument[i]))
                    displayErrorMessage();
            }
            // Argument is valid, copy to params struct
            strcpy(params.W, &argument[2]);
        }
    } // end of for loop
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     changeFirstName()
PURPOSE:           Purpose of function ...
RETURNS:           What the function returns ... or ...
RETURNS:           Nothing (void function)
NOTES:             Put important usage notes here ...
----------------------------------------------------------------------------- */
void changeFirstName(Record bankAccountDatabase [], CommandLineParameters params)
{
    int databaseIndex = findAccountNumber(bankAccountDatabase, params.N1);
    //if (strlen(params.F < 1
    strcpy(bankAccountDatabase[databaseIndex].firstName, params.F);
}

/* -----------------------------------------------------------------------------
 FUNCTION NAME:     changeLastName()
 PURPOSE:           Purpose of function ...
 RETURNS:           What the function returns ... or ...
 RETURNS:           Nothing (void function)
 NOTES:             Put important usage notes here ...
 ----------------------------------------------------------------------------- */
void changeLastName(Record bankAccountDatabase [], CommandLineParameters params)
{
    int databaseIndex = findAccountNumber(bankAccountDatabase, params.N1);
    strcpy(bankAccountDatabase[databaseIndex].lastName, params.L);
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     changeMiddleIntial()
PURPOSE:           Purpose of function ...
RETURNS:           What the function returns ... or ...
RETURNS:           Nothing (void function)
NOTES:             Put important usage notes here ...
----------------------------------------------------------------------------- */
void changeMiddleIntial(Record bankAccountDatabase [], CommandLineParameters params)
{
    int databaseIndex = findAccountNumber(bankAccountDatabase, params.N1);
    bankAccountDatabase[databaseIndex].middleInitial = params.M;
}

/* -----------------------------------------------------------------------------
 FUNCTION NAME:     changeSSN()
 PURPOSE:           Purpose of function ...
 RETURNS:           What the function returns ... or ...
 RETURNS:           Nothing (void function)
 NOTES:             Put important usage notes here ...
 ----------------------------------------------------------------------------- */
void changeSSN(Record bankAccountDatabase [], CommandLineParameters params)
{
    int databaseIndex = findAccountNumber(bankAccountDatabase, params.N1);
    strcpy(bankAccountDatabase[databaseIndex].ssNum, params.S);
}

/* -----------------------------------------------------------------------------
 FUNCTION NAME:     changeAreaCode()
 PURPOSE:           Purpose of function ...
 RETURNS:           What the function returns ... or ...
 RETURNS:           Nothing (void function)
 NOTES:             Put important usage notes here ...
 ----------------------------------------------------------------------------- */
void changeAreaCode(Record bankAccountDatabase [], CommandLineParameters params)
{
    int databaseIndex = findAccountNumber(bankAccountDatabase, params.N1);
    strcpy(bankAccountDatabase[databaseIndex].phoneNumAreaCode, params.A);
}
/* -----------------------------------------------------------------------------
 FUNCTION NAME:     changeAreaCode()
 PURPOSE:           Purpose of function ...
 RETURNS:           What the function returns ... or ...
 RETURNS:           Nothing (void function)
 NOTES:             Put important usage notes here ...
 ----------------------------------------------------------------------------- */
void changePhoneNumber(Record bankAccountDatabase [], CommandLineParameters params)
{
    int databaseIndex = findAccountNumber(bankAccountDatabase, params.N1);
    strcpy(bankAccountDatabase[databaseIndex].phoneNum, params.H);
}
/* -----------------------------------------------------------------------------
 FUNCTION NAME:     changeAreaCode()
 PURPOSE:           Purpose of function ...
 RETURNS:           What the function returns ... or ...
 RETURNS:           Nothing (void function)
 NOTES:             Put important usage notes here ...
 ----------------------------------------------------------------------------- */
void changePassword(Record bankAccountDatabase [], CommandLineParameters params)
{
    int databaseIndex = findAccountNumber(bankAccountDatabase, params.N1);
    strcpy(bankAccountDatabase[databaseIndex].password, params.W);
}

/* -----------------------------------------------------------------------------
 FUNCTION NAME:     changeAreaCode()
 PURPOSE:           Purpose of function ...
 RETURNS:           What the function returns ... or ...
 RETURNS:           Nothing (void function)
 NOTES:             Put important usage notes here ...
 ----------------------------------------------------------------------------- */
void transfer(Record bankAccountDatabase [], CommandLineParameters params)
{
    if (strcmp(params.N1, params.N2) == 0)
    {
        cout << "\n\nCan't transfer money to the same account silly!\n";
        exit(1);
    }
    int databaseIndexFrom = findAccountNumber(bankAccountDatabase, params.N1);
    // If the transfer amount is less than 0 or greater than the balance
    // Display error
    if (params.T < 0 || params.T > bankAccountDatabase[databaseIndexFrom].balance)
    {
        cout << "\n\nInvalid transfer amount!\n";
        exit(1);
    }
    int databaseIndexTo = findAccountNumber(bankAccountDatabase, params.N2);
    bankAccountDatabase[databaseIndexFrom].balance -= params.T;
    bankAccountDatabase[databaseIndexTo].balance += params.T;
    cout << "\n\n$" << params.T << " successfully transfered from account #: "
    << params.N1 << ", to account #: " << params.N2
    << "\n\nThe new balance in the first account is: $"
    << bankAccountDatabase[databaseIndexFrom].balance
    << "\n\nThe new balance in the second account is: $"
    << bankAccountDatabase[databaseIndexTo].balance;
}

/* -----------------------------------------------------------------------------
 FUNCTION NAME:     produceReport()
 PURPOSE:           Purpose of function ...
 RETURNS:           What the function returns ... or ...
 RETURNS:           Nothing (void function)
 NOTES:             Put important usage notes here ...
 ----------------------------------------------------------------------------- */
void produceReport(Record bankAccountDatabase [], CommandLineParameters params)
{
    std::ofstream reportFile;
    
    reportFile.open(params.R);
    if (reportFile) // If the reportFile succesfully opens
    {
        int i = 0;
        
        reportFile
        << "-------    ----        -----     --    ---------    ------------    -------\n"
        << "Account    Last        First     MI    SS           Phone           Account\n"
        << "Number     Name        Name            Number       Number          Balance\n"
        << "-------    ----        -----     --    ---------    ------------    -------\n";
        
        while (bankAccountDatabase[i].accountNum[0] != 0)
        {
            reportFile << std::left;
            reportFile << std::setw(11) << bankAccountDatabase[i].accountNum;
            reportFile << std::setw(12) << bankAccountDatabase[i].lastName;
            reportFile << std::setw(10) << bankAccountDatabase[i].firstName;
            reportFile << std::setw(6) << bankAccountDatabase[i].middleInitial;
            reportFile << std::setw(13) << bankAccountDatabase[i].ssNum;
            reportFile << "(" << bankAccountDatabase[i].phoneNumAreaCode << ")" << std::setw(12) << bankAccountDatabase[i].phoneNum;
            reportFile << bankAccountDatabase[i].balance;
            reportFile << endl;
            i++;
        }
        reportFile.close();
    }
    else // If the files fails to open
        cout << "\n\nThe report file failed to open\n";
}

/* -----------------------------------------------------------------------------
FUNCTION NAME:     saveDatabase()
PURPOSE:           Purpose of function ...
RETURNS:           What the function returns ... or ...
RETURNS:           Nothing (void function)
NOTES:             Put important usage notes here ...
----------------------------------------------------------------------------- */
void saveDatabase(Record bankAccountDatabase [], CommandLineParameters params)
{
    std::ofstream dataFile;
    int i = 0;
    
    dataFile.open(params.D);
    
    while (bankAccountDatabase[i].lastName[0] != 0)
    {
        dataFile << bankAccountDatabase[i].lastName << endl;
        dataFile << bankAccountDatabase[i].firstName << endl;
        dataFile << bankAccountDatabase[i].middleInitial << endl;
        dataFile << bankAccountDatabase[i].ssNum << endl;
        dataFile << bankAccountDatabase[i].phoneNumAreaCode << endl;
        dataFile << bankAccountDatabase[i].phoneNum << endl;
        dataFile << bankAccountDatabase[i].balance << endl;
        dataFile << bankAccountDatabase[i].accountNum << endl;
        dataFile << bankAccountDatabase[i].password << endl << endl;
        i++;
    }
    dataFile.close();
}

/* -----------------------------------------------------------------------------
FUNCTION:          validateArgument()
DESCRIPTION:       check arguments for valid input
RETURNS:           Void function
NOTES:
----------------------------------------------------------------------------- */
/*
void validateArguments(Record bankAccountDatabase [],
                       CommandLineParameters params)
{
    // Check Length
    
    for
            if (inputType == FIRST || inputType == LAST || inputType == MIDDLE)
                std::cout << INDENT << "Only letters, no spaces, ";
            if (inputType == SS_NUM || inputType == AREA_CODE || inputType == PHONE_NUM)
                std::cout << INDENT << "Only numbers allowed,";
            if (inputType == ACCOUNT_NUM || inputType == PASSWORD)
                std::cout << INDENT << "Only numbers and upper case letters,";
            
            std::cout << "not longer then " << (inputType == LAST ? LAST - 1 : inputType) << " characters.\n\n";
        }
        if (inputType == FIRST)
            std::cout << INDENT << "Please enter your first name: ";
        if (inputType == LAST)
            std::cout << INDENT << "Please enter your last name: ";
        if (inputType == MIDDLE)
            std::cout << INDENT << "Please enter your middle intial: ";
        if (inputType == SS_NUM)
            std::cout << INDENT << "Please enter your social security number [no dashes]: ";
        if (inputType == AREA_CODE)
            std::cout << INDENT << "Please enter your phone number area code: ";
        if (inputType == PHONE_NUM)
            std::cout << INDENT << "Please enter your 7 digit phone number: ";
        if (inputType == ACCOUNT_NUM)
            std::cout << INDENT << "Please choose an account number [Length 5: A-Z,0-9]: ";
        if (inputType == PASSWORD)
            std::cout << INDENT << "Please choose a password [Length 6: A-Z,0-9]: " ;
        
        std::cin >> inputArray;
        
        // Check Length of Input
        inputLength = strlen(inputArray);
        if (inputType == FIRST || inputType == LAST)
        {
            if (inputLength < 1 || inputLength > 20)
            {
                isValid = false;
            }
        }
        if (inputType == MIDDLE)
        {
            if (inputLength > 1)
            {
                isValid = false;
            }
        }
        if (inputType == SS_NUM || inputType == AREA_CODE || inputType == PHONE_NUM)
        {
            if (inputLength != inputType)
            {
                isValid = false;
            }
        }
 
        
        // Check Validity of input Characters
        int i = 0;
        
        if (inputType == FIRST || inputType == LAST || inputType == MIDDLE)
        {
            while (inputArray[i] != 0  && isValid == true)
            {
                isValid = isalpha(inputArray[i]);
                i++;
            }
        }
        if (inputType == SS_NUM || inputType == AREA_CODE || inputType == PHONE_NUM)
        {
            while (inputArray[i] != 0  && isValid == true)
            {
                isValid = isdigit(inputArray[i]);
                i++;
            }
        }
        if (inputType == ACCOUNT_NUM || inputType == PASSWORD)
        {
            while (inputArray[i] != 0  && isValid == true)
            {
                char character = inputArray[i];
                isValid = isalnum(character);
                if (isalpha(character))
                    isValid = isupper(character);
                i++;
            }
        }
    } while (!isValid); // Keep looping as long as input is not valid
}
*/