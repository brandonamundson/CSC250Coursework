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
#include "functions.h"


/***************************************************************************//**
 * @author Brandon Amundson
 *
 * @par Description:
 * This is the function that opens the files for writing the good records to a
 * specified binary file and the bad records to a specified text file.  All
 * records are read in from a specified binary database file.  If this function
 * is unable to open any file, it exits with a code one.
 * 
 * 
 * @param[in, out]       fin - Input File Stream to be opened.
 *                             Used to read in contents from binary file to be  
 *                             checked for accuracy.
 * @param[in, out]      good - Output File Stream to be opened.  Used to output
 *                             good records to a binary file.
 * @param[in, out]       bad - Output File Stream to be opened.  Used to output
 *                             bad records to a text file.
 * @param[in]    commandline - commandline arguments of what filenames to use
 *                             are to be opened.
 ******************************************************************************/
void openFiles(ifstream &fin, ofstream &good, ofstream &bad, char **commandline)
{
        fin.open(commandline[1], ios::in | ios::binary);
        if (!fin)
        {
            cout << "Unable to open " << commandline[1] << ".  Closing Program Now"
               ;
            exit(1);
        }
        good.open(commandline[2], ios::out | ios::trunc | ios::binary);
        if (!good)
        {
            cout << "Unable to open " << commandline[2] << ".  Closing Program Now"
               ;
            exit(1);
        }
        bad.open(commandline[3], ios::out | ios::trunc);
        if (!bad)
        {
            cout << "Unable to open " << commandline[3] << ".  Closing Program Now"
               ;
            exit(1);
        }
}


/***************************************************************************//**
 * @author Brandon Amundson
 *
 * @par Description:
 * This is the function that calls all of the other functions that do not
 * involve opening or closing files and do not deal with outputting the good or
 * bad records that are read in from a file.
 *
 * @param[in]         record - This is passed in to allow access to the records
 *                             that were read into the structure in main.
 *                             Program breaks if this is declared as a local
 *                             variable.
 * @param[in,out] countFalse - This is the string that keeps track of all
 *                             errors found in the database file.  Each portion
 *                             is set to a 1 if there are any errors.
 *******************************************************************************/
void callFunctions(Record record, string &countFalse)
{
    int i = 0;
    string birth;
    string license;
    string expire;
    countFalse.resize(30);
    nameCheck(record.name, countFalse, i);
    i += 2;
    numCheck(record.address, countFalse);
    nameCheck(record.city, countFalse, i);
    state(record.state, countFalse);
    zipCheck(record.zipCode, countFalse);
    i = 7;
    extractDate(record.birthDate, countFalse, i, birth);
    extractDate(record.licensedDate, countFalse, i, license);
    extractDate(record.expirationDate, countFalse, i, expire);
    checkIfAfter(countFalse, license, expire);
    classCheck((char*) &record.radioClass, countFalse);
    sign(record.callSign, countFalse);
}


/***************************************************************************//**
 * @author Brandon Amundson
 *
 * @par Description:
 * This is the function that checks for the correct set of characters, 
 * (ie. letters a-z both uppercase and lowercase, and spaces or periods) in the
 * name field and is used on the name and city portion of the record.
 *
 * @param[in]           name - This typecasts the name and city portions of the
 *                             record from a character array to a string
 *                             allowing the usage of the string class member
 *                             functions.
 * @param[in,out] countFalse - This is the string that keeps track of all
 *                             errors found in the database file.  Each portion
 *                             is set to a 1 if there are any errors.
 * @param[in]              i - This variable is used to keep track of how many
 *                             times a function is called and to help keep
 *                             track of all errors.
 ******************************************************************************/
void nameCheck(string name, string &countFalse, int i)
{
    int idx;

    idx = name.find_first_not_of(validNames);
    if (idx != name.npos)
    {
        countFalse[i] = 1;
    }
    else
        countFalse[i] = 0;
}


/***************************************************************************//**
 * @author Brandon Amundson
 *
 * @par Description:
 * This is the function that checks for the correct set of characters,
 * (ie. letters a-z both uppercase and lowercase,numbers, and spaces, periods
 * or the pound symbol) in the address field and is used on the address portion
 * of the record.
 *
 * @param[in]        address - This typecasts the address portion of the
 *                             record from a character array to a string
 *                             allowing the usage of the string class member
 *                             functions.
 * @param[in,out] countFalse - This is the string that keeps track of all
 *                             errors found in the database file.  Each portion
 *                             is set to a 1 if there are any errors.
 ******************************************************************************/
void numCheck(string address, string &countFalse)
{
    int idx;

    idx = address.find_first_not_of(validAddress);
    if (idx != address.npos)
    {
        countFalse[1] = 1;
        return;
    }
    else
        countFalse[1] = 0;
}


/***************************************************************************//**
 * @author Brandon Amundson
 *
 * @par Description:
 * This is the function that checks if the 1st character of the state is
 * capitalized and if the state is a valid state.  If the 1st character is not
 * capitalized or if the, the state is not valid variable countFalse is
 * incremented to a 1 accordingly.
 *
 * @param[in]          state - This typecasts the state portion of the record
 *                             from a character array to a string allowing the
 *                             use of the string class member functions,
 *                             specifically the find_first_not_of function.
 *
 * @param[in,out] countFalse - This is the string that keeps track of all
 *                             errors found in the database file.  Each portion
 *                             is set to a 1 if there are any errors.
 ******************************************************************************/
void state(string state, string &countFalse)
{
    int size = 0;
    int i;
    int idx;

    size = state.size();
    if (size > 2)
        state.erase(2);
    if (state[0] >= 65 && state[0] <= 90)
        countFalse[4] = 0;
    else
        countFalse[4] = 1;
    for (i = 0; i < 2; i++)
    {
        state[i] = toupper(state.at(i));
    }
    for (i = 0; i < 50; i++)
    {
        idx = state.compare(validStates[i]);
        if (idx != 0)
        {
            countFalse[3] = 1;
        }
        else
        {
            countFalse[3] = 0;
            return;
        }
    }
}


/***************************************************************************//**
 * @author Brandon Amundson
 *
 * @par Description:
 * This is the function that checks if the four digit and five digit portions
 * of the zipcode are valid.  If the 5 digit portion or the four digit portion
 * of the zip code is not valid variable countFalse is incremented to a 1
 * accordingly
 * @param[in]            zip - This is the zipcode portion of the record that
 *                             is to be extracted.  
 * @param[in,out] countFalse - This is the string that keeps track of all
 *                             errors found in the database file.  Each portion
 *                             is set to a 1 if there are any errors.
 ******************************************************************************/
void zipCheck(unsigned int zip, string &countFalse)
{
    unsigned int fourDigit;
    unsigned int fiveDigit;
    unsigned int temp;

    fourDigit = zip & DIG4MASK;
    temp = zip >> 14;
    fiveDigit = temp & DIG5MASK;

    if (fiveDigit >= 10000 && fiveDigit <= 99999)
        countFalse[5] = 0;
    else
    {
        countFalse[5] = 1;
    }
    if (fourDigit >= 1000 && fourDigit <= 9999)
        countFalse[6] = 0;
    else
    {
        countFalse[6] = 1;
    }
}


/***************************************************************************//**
 * @author Brandon Amundson
 *
 * @par Description:
 * This is the function that extracts the date in its portions of month, day,
 * and year.  The function then checks to find if the month, day, and year are
 * valid.  If any part of the date is not valid, the  variable countFalse is
 * incremented to a 1 accordingly.
 * 
 * @param[in]           date - This is the date portion of the record that
 *                             is to be extracted into its seperate parts.
 * @param[in,out] countFalse - This is the string that keeps track of all
 *                             errors found in the database file.  Each portion
 *                             is set to a 1 if there are any errors.
 * @param[in,out]          i - This variable keeps count of where in the string
 *                             to change to a 1 or 0 depending on whether there
 *                             is an error or not.
 * @param[in,out]     format - This keeps track of the date which is put in as
 *                             year/month/day.  This allows the program to
 *                             compare the dates in another function.
 ******************************************************************************/
void extractDate(unsigned int date, string &countFalse, int &i, string &format)
{
    int day;
    int month;
    int year;
    unsigned int shift1;
    unsigned int shift2;

    day = date & dayMask;
    shift1 = date >> 6;
    month = shift1 & monthMask;
    shift2 = shift1 >> 6;
    year = shift2 & yearMask;

    format.push_back(year);
    format.push_back('/');
    format.push_back(month);
    format.push_back('/');
    format.push_back(day);

    monthCheck(month, countFalse, i);
    i++;
    dayCheck(day, month, countFalse, i);
    i++;
    yearCheck(year, countFalse, i);
    i++;
}


/***************************************************************************//**
 * @author Brandon Amundson
 *
 * @par Description:
 * This function takes the month that is sent in and checks
 * to make sure that it is a valid month.  If the month is not valid,
 * countFalse is incremented to reflect the error.  Otherwise it is set to 0 if
 * it is valid.
 *
 * @param[in]          month - This is the month that has been extracted from
 *                             the date field of the Record structure.  It is
 *                             compared against the valid months to see if it
 *                             is true or false.
 * @param[in,out] countFalse - This is the string that keeps track of all
 *                             errors found in the database file.  Each portion
 *                             is set to a 1 if there are any errors.
 * @param[in]              i - This variable keeps count of where in the string
 *                             to change to a 1 or 0 depending on whether there
 *                             is an error or not.
 ******************************************************************************/
void monthCheck(int month, string &countFalse, int i)
{
    if (month > 0 && month <= 12)
        countFalse[i] = 0;
    else
        countFalse[i] = 1;
}


/***************************************************************************//**
 * @author Brandon Amundson
 *
 * @par Description:
 * This function takes the month that is sent in and checks to make sure that
 * it is a valid month.  If the month is not valid, countFalse is incremented
 * to reflect the error.  Otherwise it is set to 0 if it is valid.
 *
 * @param[in]          month - This is the month that has been extracted from
 *                             the date field of the Record structure.  It is
 *                             used to see if the day portion of the date field
 *                             is valid.
 * @param[in,out] countFalse - This is the string that keeps track of all
 *                             errors found in the database file.  Each portion
 *                             is set to a 1 if there are any errors.
 * @param[in]              i - This variable keeps count of where in the string
 *                             to change to a 1 or 0 depending on whether there
 *                             is an error or not.
 * @param[in]            day - This is the day that has been extracted from the
 *                             date portion of the record structure.  It is
 *                             compared against the valid days of the
 *                             particular month that has been extracted from
 *                             the date field.  If it is not valid, the
 *                             countFalse variable is incremented accordingly.
 ******************************************************************************/
void dayCheck(int day, int month, string &countFalse, int i)
{
    int maxDay;
    if (month == 0)
    {
        maxDay = validDay[month];
    }
    else
        maxDay = validDay[month - 1];
    if (day > 0 && day <= maxDay)
        countFalse[i] = 0;
    else
        countFalse[i] = 1;
}


/***************************************************************************//**
 * @author Brandon Amundson
 *
 * @par Description:
 * This function takes the month that is sent in and checks to make  sure that
 * it is a valid month.  If the month is not valid, countFalse is incremented
 * to reflect the error.  Otherwise it is set to 0 if it is valid.
 *
 * @param[in]           year - This is the year that has been extracted from
 *                             the date field of the Record structure.  It is
 *                             used to see if the year portion of the date
 *                             field is valid.  A valid year is between 1900
 *                             and 2015.
 * @param[in,out] countFalse - This is the string that keeps track of all
 *                             errors found in the database file.  Each portion
 *                             is set to a 1 if there are any errors.
 * @param[in]              i - This variable keeps count of where in the string
 *                             to change to a 1 or 0 depending on whether there
 *                             is an error or not.
 ******************************************************************************/
void yearCheck(int year, string &countFalse, int i)
{
    if (year >= 1900 && year <= 2015)
    {
        countFalse[i] = 0;
    }
    else
    {
        countFalse[i] = 1;
    }
}


/***************************************************************************//**
 * @author Brandon Amundson
 *
 * @par Description:
 * 
 *
 * @param[in]        license - This is the license date part of the structure
 *                             and is in the format of year/month/day and is
 *                             checked to see if it is before the expire date.
 * @param[in,out] countFalse - This is the string that keeps track of all
 *                             errors found in the database file.  Each portion
 *                             is set to a 1 if there are any errors.
 * @param[in]         expire - This is the expiration date part of the
 *                             structure and is in the format of year/month/day
 *                             and is checked to see if it is after the license
 *                             date.
 ******************************************************************************/
void checkIfAfter(string &countFalse, string license, string expire)
{
    int expireAfter;
    expireAfter = license.compare(expire);
    if (expireAfter >= 0)
        countFalse[16] = 1;
    else
        countFalse[16] = 0;
}


/***************************************************************************//**
 * @author Brandon Amundson
 *
 * @par Description:
 * This is the function that checks for the correct set of characters in the
 * Radio Class field and is used on the Radio Class portion of the record to
 * check that it is a valid class.  If the class is not valid, countFalse is
 * incremented accordingly.
 *
 * @param              radio - This is the radio class portion of the record
 *                             that is typecasted from a character array to a
 *                             string when it is passed in.  It is compared
 *                             against all of the valid classes and countFalse
 *                             is incremented accordingly if the class is not
 *                             valid.
 * @param[in,out] countFalse - This is the string that keeps track of all
 *                             errors found in the database file.  Each portion
 *                             is set to a 1 if there are any errors.
 ******************************************************************************/
void classCheck(string radio, string &countFalse)
{
    radio.erase(1);
    int idx;

    idx = radio.find_first_not_of(validClass);
    if (idx != radio.npos)
    {
        countFalse[17] = 1;
    }
    else
        countFalse[17] = 0;
}


/***************************************************************************//**
 * @author Brandon Amundson
 *
 * @par Description:
 * This is the function that checks to see if the callSign portion of the
 * record is valid.  To be valid, the sign must start with a K, W, or N, the
 * second, fourth, and fifth characters must be any letter A-Z and the third
 * character must be any single digit number 0-9.  All letters must be
 * capitalized.  If any portion of the call sign is invalid, countFalse is
 * incremented accordingly.
 *
 * @param[in]           sign - this is the callSign portion of the record
 *                             that is read from file.  It is typecasted to a
 *                             string as it is passed into the function and
 *                             it is then checked to make sure that it meets
 *                             all the requirements given.  If any part of the
 *                             callSign is invalid, the valid countFalse is
 *                             incremented accordingly.
 * @param[in,out] countFalse - This is the string that keeps track of all
 *                             errors found in the database file.  Each portion
 *                             is set to a 1 if there are any errors.
 ******************************************************************************/
void sign(string sign, string &countFalse)
{
    string first;
    int idx[10];


    sign.erase(5);

    if (isdigit(sign[2]))
        countFalse[20] = 0;
    else
        countFalse[20] = 1;

    idx[1] = isalpha(sign[0]);
    idx[2] = isalpha(sign[1]);
    idx[3] = isalpha(sign[3]);
    idx[4] = isalpha(sign[4]);
    if (idx[1] != 0)
    {
        idx[5] = isupper(sign[0]);
    }
    if (idx[2] != 0)
    {
        idx[6] = isupper(sign[1]);
    }
    if (idx[3] != 0)
    {
        idx[7] = isupper(sign[3]);
    }
    if (idx[4] != 0)
    {
        idx[8] = isupper(sign[4]);
    }

    if (idx[1] != 0)
    {
        first = toupper(sign[0]);
        idx[0] = first.find_first_not_of(validChar);
    }
    if (idx[0] == first.npos)
    {
        countFalse[18] = 0;
    }
    else
        countFalse[18] = 1;
    if (idx[1] == 0 || idx[2] == 0 || idx[3] == 0 || idx[4] == 0)
    {
        countFalse[19] = 1;
    }
    else
        countFalse[19] = 0;
    if (idx[5] == 0 || idx[6] == 0 || idx[7] == 0 || idx[8] == 0)
    {
        countFalse[21] = 1;
    }
    else
        countFalse[21] = 0;
}


/***************************************************************************//**
 * @author Brandon Amundson
 *
 * @par Description:
 * This function processes the countFalse string looking to see if there are
 * any errors in the string, and if there are, the outputError function is
 * called to output the errors.  If there are no errors, the outputGood 
 * function which will output the good records that do not have any errors.
 * 
 * @param[in, out]      good - Output File Stream that has been opened.  Used
 *                             to output good records to a binary file.
 * @param[in, out]       bad - Output File Stream that has been opened.  Used
 *                             to output bad records to a text file.
 * @param[in,out] countFalse - This is the string that keeps track of all
 *                             errors found in the database file.  Each portion
 *                             is set to a 1 if there are any errors.
 * @param[in]         record - This is passed in to allow access to the records
 *                             that were read into the structure in main.
 *                             Program breaks if this is declared as a local
 *                             variable.
 ******************************************************************************/
void errorCheck(string &countFalse, ofstream &good, ofstream &bad, Record record)
{
    int idx;
    idx = countFalse.find_first_of(1);
    if (idx != countFalse.npos)
    {
        outputError(countFalse, bad, record);
        bad << endl;
    }
    else
        outputGood(good, record);
}


/***************************************************************************//**
 * @author Brandon Amundson
 *
 * @par Description:
 * This function outputs any errors to a text file.
 * 
 * @param[in, out]       bad - Output File Stream that has been opened.  Used
 *                             to output bad records to a text file.
 * @param[in,out] countFalse - This is the string that keeps track of all
 *                             errors found in the database file.  Each portion
 *                             is set to a 1 if there are any errors.
 * @param[in]         record - This is passed in to allow access to the records
 *                             that were read into the structure in main.
 *                             Program breaks if this is declared as a local
 *                             variable.
 ******************************************************************************/
void outputError(string &countFalse, ofstream &bad, Record record)
{
    //bad.write((char*)&record, sizeof(Record));
    outputBadStruct(bad, record);
    if (countFalse[0] == 1)
        bad << "     Invalid character in the name field" << endl;
    if (countFalse[1] == 1)
        bad << "     Invalid character in the address field" << endl;
    if (countFalse[2] == 1)
        bad << "     Invalid character in the city field" << endl;
    if (countFalse[3] == 1)
        bad << "     Invalid State Code" << endl;
    if (countFalse[4] == 1)
        bad << "     First character of State Code not capitalized" << endl;
    if (countFalse[5] == 1)
        bad << "     Invalid 5 digit zip code" << endl;
    if (countFalse[6] == 1)
        bad << "     Invalid 4 digit zip code" << endl;
    if (countFalse[7] == 1)
        bad << "     Invalid month in Birthday" << endl;
    if (countFalse[8] == 1)
        bad << "     Invalid day in Birthday" << endl;
    if (countFalse[9] == 1)
        bad << "     Invalid year in Birthday" << endl;
    if (countFalse[10] == 1)
        bad << "     Invalid month in License" << endl;
    if (countFalse[11] == 1)
        bad << "     Invalid day in License" << endl;
    if (countFalse[12] == 1)
        bad << "     Invalid year in License" << endl;
    if (countFalse[13] == 1)
        bad << "     Invalid month in Expiration" << endl;
    if (countFalse[14] == 1)
        bad << "     Invalid day in Expiration" << endl;
    if (countFalse[15] == 1)
        bad << "     Invalid year in Expiration" << endl;
    if (countFalse[16] == 1)
        bad << "     Expiration Date is not after the License Date" << endl;
    if (countFalse[17] == 1)
        bad << "     Radio Class code is invalid" << endl;
    if (countFalse[18] == 1)
        bad << "     Invalid first character in call sign" << endl;
    if (countFalse[19] == 1)
        bad << "     Invalid second, fourth, or fifth character in call sign"
            << endl;
    if (countFalse[20] == 1)
        bad << "     Invalid digit in call sign" << endl;
    if (countFalse[21] == 1)
        bad << "     Call Sign not uppercase" << endl;
}


void outputBadStruct(ofstream &bad, Record record)
{
    bad << record.name << endl << record.address << endl << record.city << ", "
        << record.state << " " << record.zipCode << endl << record.birthDate
        << endl << record.licensedDate << endl << record.expirationDate << endl
        << record.radioClass << " - " << record.callSign << endl;
}


/***************************************************************************//**
 * @author Brandon Amundson
 *
 * @par Description:
 * This function is called by outputError function to output all good records.
 * 
 *
 * @param[in]         record - This is passed in to allow access to the records
 *                             that were read into the structure in main.
 *                             Program breaks if this is declared as a local
 *                             variable.
 * @param[in, out]      good - Output File Stream that has been opened.  Used
 *                             to output good records to a binary file.
 ******************************************************************************/
void outputGood(ofstream &good, Record record)
{
    good.write((char*)&record, sizeof(Record));
}


/***************************************************************************//**
 * @author Brandon Amundson
 *
 * @par Description:
 * This is the function that opens the files for writing the good records to a
 * specified binary file and the bad records to a specified text file.  All
 * records are read in from a specified binary database file.  If this function
 * is unable to open any file, it exits with a code one.
 * 
 * 
 * @param[in, out]       fin - Input File Stream to be closed.
 *                             Used to read in contents from binary file to be  
 *                             checked for accuracy.
 * @param[in, out]      good - Output File Stream to be closed.  Used to output
 *                             good records to a binary file.
 * @param[in, out]       bad - Output File Stream to be closed.  Used to output
 *                             bad records to a text file.
 ******************************************************************************/
void closeFiles(ifstream &fin, ofstream &good, ofstream &bad)
{
    good.close();
    bad.close();
    fin.close();
}
