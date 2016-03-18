/* -----------------------------------------------------------------------------

FILE:              bankacctp2.cpp

DESCRIPTION:       A brief description of this source code file ...

COMPILER:          Xcode, GCC

NOTES:             Put other information here ...

MODIFICATION HISTORY: fixed DisplayInfo

Author                  Date               Version
---------------         ----------         --------------
Nathan Bertram          2016-03-17         Version 11.0

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
void saveDatabase(Record []);

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
        size_t bytes_really_read = helpFile.gcount();
        
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
            params.T = atof(&argument[2]);
        if (argument[1] == 'W')
            strcpy(params.W, &argument[2]);
    }
    
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
    bankAccountDatabase[databaseIndex].middleInitial = params.M[0];
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

/* -----------------------------------------------------------------------------
FUNCTION NAME:     saveDatabase()
PURPOSE:           Purpose of function ...
RETURNS:           What the function returns ... or ...
RETURNS:           Nothing (void function)
NOTES:             Put important usage notes here ...
----------------------------------------------------------------------------- */
void saveDatabase(Record bankAccountDatabase [])
{
    
}