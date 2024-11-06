/***************************************************************************//**
 * @file 
 * 
 * @brief This file contains all the functions required to read and write from 
 * files and also contains the functions that check for errors in the database 
 * file.
 *
 * @author Brandon Amundson
 * 
 ******************************************************************************/

#pragma pack(1)
#ifndef __FUNCTIONS__H__
#define __FUNCTIONS__H__
#define _CRT_SECURE_NO_DEPRICATE
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <string>
#include <cctype>
using namespace std;

/**
 * @brief Structure to hold all of the client data.
 */
struct Record
{
    char name[30];              /*!< the name of the client*/
    char address[30];           /*!< the address of the client*/
    char city[28];              /*!< the city the client lives in*/
    char state[2];              /*!< the state the client lives in*/
    unsigned int zipCode;       /*!< the zipcode of the area the client lives*/
    unsigned int birthDate;     /*!< the birthdate of the client*/
    unsigned int licensedDate;  /*!< the license date of the client*/
    unsigned int expirationDate;/*!< the expiration date of the client's record*/
    char radioClass;            /*!< the classification of the client*/
    char callSign[5];           /*!< the callSign of the client*/
};

/**
 * @brief The valid States that can be in the state field of the Record Structure
 */
const string validStates[50] = {"AL", "AK", "AZ", "AR", "CA", "CO", "CT", "DE",
                                "FL", "GA", "HI", "ID", "IL", "IN", "IA", "KS", 
                                "KY", "LA", "ME", "MD", "MA", "MI", "MN", "MS",
                                "MO", "MT", "NE", "NV", "NH", "NJ", "NM", "NY",
                                "NC", "ND", "OH", "OK", "OR", "PA", "RI", "SC",
                                "SD", "TN", "TX", "UT", "VT", "VA", "WA", "WV",
                                "WI", "WY" };

/**
* @brief The valid characters that can be in the address field of the Record
*        Structure
*/
const string validAddress = 
       { "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz#. " };

/**
* @brief The valid characters that can be in the name and city field of the
*        Record Structure
*/
const string validNames = 
                  { "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz. " };

/**
* @brief The valid days for each month that can be in the date field of the
*        Record Structure
*/
const int validDay[20] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, 31,
                           31, 31, 31 };

/**
* @brief The valid characters that can be in the radioClass field of the
*        Record Structure
*/
const string validClass = {"npatgxNPATGX"};

/**
* @brief The valid characters that can be in the callSign field of the
*        Record Structure
*/
const string validChar = {"KWN"};

/**
* @brief The valid characters that can be in the 2nd, 4th, and 5th spot in the
*        call sign portion of the record.
*/
const string upper = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };

/**
 * @brief The mask used to extract the four digit portion of the Zip Code from 
 *        the zipCode field of the record structure.
 */
const int DIG4MASK = 16383;

/**
* @brief The mask used to extract the five digit portion of the Zip Code from
*        the zipCode field of the record structure.
*/
const int DIG5MASK = 262143;

/**
 * @brief This is the mask that is used to extract the day portion of the date
 *        from the date portions of the Record structure.
 */
const int dayMask = 63;

/**
* @brief This is the mask that is used to extract the month portion of the date
*        from the date portions of the Record structure.
*/
const int monthMask = 15;

/**
* @brief This is the mask that is used to extract the year portion of the date
*        from the date portions of the Record structure.
*/
const int yearMask = 4095;

void openFiles(ifstream &fin, ofstream &good, ofstream &bad, char **commandline);
void callFunctions(Record record, string &countFalse);
void nameCheck(string name, string &countFalse, int i);
void numCheck(string address, string &countFalse);
void state(string state, string &countFalse);
void zipCheck(unsigned int zip, string &countFalse);
void extractDate(unsigned int date, string &countFalse, int &i, string &format);
void monthCheck(int month, string &countFalse, int i);
void dayCheck(int day, int month, string &countFalse, int i);
void yearCheck(int year, string &countFalse, int i);
void checkIfAfter(string &countFalse, string license, string expire);
void classCheck(string radio, string &countFalse);
void sign(string sign, string &countFalse);
void errorCheck(string &countFalse, ofstream &good, ofstream &bad, Record record);
void outputError(string &countFalse, ofstream &bad, Record record);
void outputGood(ofstream &good, Record record);
void closeFiles(ifstream &fin, ofstream &good, ofstream &bad);
void outputBadStruct(ofstream &bad, Record record);
#endif