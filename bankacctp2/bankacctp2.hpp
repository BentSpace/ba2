/* -----------------------------------------------------------------------------
 
 FILE:              bankacctp2.hpp
 
 DESCRIPTION:       A brief description of this source code file ...
 
 COMPILER:          Xcode, GCC
 
 NOTES:             Put other information here ...
 
 MODIFICATION HISTORY: created matchArgCombination() function
 
 Author                  Date               Version
 ---------------         ----------         --------------
 Nathan Bertram          2016-03-04         Version 5.0
 
 ----------------------------------------------------------------------------- */

#ifndef bankacctp2_hpp
#define bankacctp2_hpp

#include <iostream>

#define CLEAR_SCREEN \
    std::cout << "\033[2J\033[1;1H"

struct Record
{
    char firstName[21];
    char lastName[21];
    char middleInitial;
    char ssNum[10];
    char phoneNumAreaCode[4];
    char phoneNum[8];
    double balance;
    char accountNum[6];
    char password[7];
};



#endif /* Header_h */
