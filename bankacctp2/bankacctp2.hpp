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

// Holds anything user typed as part command line arguments
struct CommandLineParameters
{
    char A[100];
    char D[100];
    char F[100];
    char H[100];
    char L[100];
    char M[100];
    char N1[100];
    char N2[100];
    char P1[100];
    char P2[100];
    char R[100];
    char S[100];
    char T[100];
    char W[100];
};
/*
const char HELP_SCREEN [] =
"1.  bankacct /Dfilename /Nnumber /Ppassword /I\n\n
Read an input file that holds the bank account database, the name of which is\
"filename."\
Give all information for account with provided "account number" and "account\
password."\
The /I command line parameter must be accompanied by the /D, /N and /P command line\
parameters.\
Example:  bankacct /DBankDB.Txt /NA123B /PA23B42 /I\
2.  bankacct /Dfilename /Nnumber /Ppassword /Ffirstname\
Read an input file that holds the bank account database, the name of which is\
"filename."\
Change "first name" for account with provided "account number" and "account password."\
The /F command line parameter must be accompanied by the /D, /N and /P command line\
parameters.\
The new first name is the first name attached to the /F command line parameter.\
Example:  bankacct /DBankDB.Txt /NA123B /PA23B42 /FSteven\
3.  bankacct /Dfilename /Nnumber /Ppassword /Llastname\
Read an input file that holds the bank account database, the name of which is\
"filename."\
Change "last name" for account with provided "account number" and "account password."\
The /L command line parameter must be accompanied by the /D, /N and /P command line\
parameters.\
The new last name is the last name attached to the /L command line parameter.\
Example:  bankacct /DBankDB.Txt /NA123B /PA23B42 /LRichards\
4.  bankacct /Dfilename /Nnumber /Ppassword /Minitial\
Read an input file that holds the bank account database, the name of which is\
"filename."\
Change "middle initial" for account with provided "account number" and "account\
password."\
The /M command line parameter must be accompanied by the /D, /N and /P command line\
parameters.\
The new middle initial is the middle initial attached to the /M command line\
parameter.\
Example:  bankacct /DBankDB.Txt /NA123B /PA23B42 /MA\
5.  bankacct /Dfilename /Nnumber /Ppassword /Sssn\
Read an input file that holds the bank account database, the name of which is\
"filename."\
Change "social security number" for account with provided "account number" and\
"account password."\
The /S command line parameter must be accompanied by the /D, /N and /P command line\
parameters.\
The new social security number is the social security number attached to the /S\
command line parameter.\
Equivalent examples:  bankacct /DBankDB.Txt /NA123B /PA23B42 /S123894321\
bankacct /NA123B /PA23B42 /S123894321 /DBankDB.Txt\
bankacct /S123894321 /NA123B /PA23B42 /DBankDB.Txt\
bankacct /NA123B /S123894321 /PA23B42 /DBankDB.Txt\
bankacct /NA123B /S123894321 /DBankDB.Txt /PA23B42\
6.  bankacct /Dfilename /Nnumber /Ppassword /Aareacode\
Read an input file that holds the bank account database, the name of which is\
"filename."\
Change "phone number area code" for account with provided "account number" and\
"account password."\
The /A command line parameter must be accompanied by the /D, /N and /P command line\
parameters.\
The new phone number area code is the phone number area code attached to the /A\
command line parameter.\
Equivalent examples:  bankacct /DBankDB.Txt /NA123B /PA23B42 /A775\
bankacct /NA123B /DBankDB.Txt /PA23B42 /A775\
bankacct /NA123B /PA23B42 /DBankDB.Txt /A775\
bankacct /NA123B /PA23B42 /A775 /DBankDB.Txt\
7.  bankacct /Dfilename /Nnumber /Ppassword /Hphonenumber\
Read an input file that holds the bank account database, the name of which is\
"filename."\
Change "phone number" for account with provided "account number" and "account\
password."\
The /H command line parameter must be accompanied by the /D, /N and /P command line\
parameters.\
The new phone number is the phone number attached to the /H command line parameter.\
Equivalent examples:  bankacct /DBankDB.Txt /NA123B /PA23B42 /H3324581\
bankacct /NA123B /PA23B42 /DBankDB.Txt /H3324581\
8.  bankacct /Dfilename /Nnumber /Ppassword /Nnumber /Ppassword /Tamount
Read an input file that holds the bank account database, the name of which is
"filename."
Transfer "amount" from the first "account number" and "account password" pair to the
second "account number" and "account password" pair.
The /T command line parameter must be accompanied by the /D, /N and /P command line
parameters.
Two different accounts must be used.
Example:  bankacct /DBankDB.Txt /NA123B /PA23B42 /NC123A /PZ52C42 /T76809.20
Transfer from "account number" A123B with "password" A23B42 to "account number" C123A
with "password" Z52C42 an amount of $76809.20.
If the funds are not available, do not transfer anything.
The following examples show equivalent command lines that perform the same action.
Equivalent examples:  bankacct /DBankDB.Txt /T76809.20 /NA123B /PA23B42 /NC123A
/PZ52C42
bankacct /T76809.20 /NA123B /NC123A /PA23B42 /PZ52C42
bankacct /T76809.20 /NA123B /NC123A /DBankDB.Txt /PA23B42
bankacct /T76809.20 /DBankDB.Txt /NA123B /NC123A /PA23B42
/DBankDB.Txt
/PZ52C42
/PZ52C42
9.  bankacct /Dfilename /Nnumber /Ppassword /Wnewpassword
Read an input file that holds the bank account database, the name of which is
"filename."
Change "password" for account with provided "account number" and "account password."
The /W command line parameter must be accompanied by the /D, /N and /P command line
parameters.
The new password is the password attached to the /W command line parameter.
Equivalent examples:  bankacct /DBankDB.Txt /NA123B /PA23B42 /WZZSTOP
bankacct /NA123B /PA23B42 /WZZSTOP /DBankDB.Txt
Change the password of "account number" A123B with "password" A23B42 to have the new
password ZZSTOP.
10. bankacct /Dfilename1 /Rfilename2
Read an input file that holds the bank account database, the name of which is
"filename1."
The /R command line parameter must be accompanied by the /D command line parameter.
Produce a "report" file of the bank account database, put the report in a file named
"filename2."
Equivalent examples:  bankacct /DBankDB.Txt /RBankRpt.Txt
bankacct /RBankRpt.Txt /DBankDB.Txt"
*/
#endif /* Header_h */
