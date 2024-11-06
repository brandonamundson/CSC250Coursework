/***************************************************************************//**
 * @file 
 * @brief This file calls the function to open the neccessary files for this,
 * program
 * in the database file.
 * 
 * @mainpage Program 1 - Database Checker
 *
 * @section course_section Course Information
 *
 * @authors Brandon Amundson
 *
 * @date February 27, 2014
 *
 * @par Instructor:
 *         Roger Schrader
 *
 * @par Course:
 *         CSC 250 - Section 1 - 11:00 am
 *
 * @par Location:
 *         Classrom Building - Room 204W
 *
 * @section program_section Program Information
 *
 * @details
 * This program takes a database file and opens it up for reading.  Then the
 * program processes each record in the database file and checks for errors.
 * If there are any errors, they are output to a text file.  If there are no
 * errors, they are output to a seperate file.
 * 
 * To keep track of all errors, there is a string variable called checkFalse
 * where each portion is changed to a one for any errors, if there are no
 * errors in that part of the record, it is changed to a zero.  This program
 * checks the record structure that consists of a name, address, city, state,
 * zipcode, birthdate, license date, expiration date, radio class, and a
 * callsign.  This program was create essentially to check the database of the
 * FCC's licensed ham radio operators for errors as they transistion from an
 * older system that did not do errorchecking upon entry to a new system that
 * will.
 *
 * @section compile_section Compiling and Usage
 *
 * @par Compiling Instructions:
 *      None
 *
 * @par Usage:
   @verbatim
   c:\> prog1.exe data.bin good.bin bad.txt
             data.bin is the database file that needs to be checked for errors.
             good.bin is the binary file to output the correct records to.
             bad.txt is the text file to output all records that have errors.
   @endverbatim
 *
 * @section todo_bugs_modifications_section Todo, Bugs, and Modifications
 *
 *
 * @par Modifications and Developing Timeline:
   @verbatim
   Date          Modification
   ------------  ---------------------------------------------------------------
   February 10   Have ability to open and close files and begin to read in
                 structure
   February 14   Be able to check the name and city fields for errors as well
                 as check the address for errors.
   February 18   Be able to successfully extract date and zipcode and check
                 them for errors.
   February 20   Check the Call Sign for errors
   February 25   Output all errors and all good records.
   February 26   Fix all bugs.
   February 27   Document Program
   March 21      Fix Program--finding errors in zip, day portion of date, chars
                 in callsign, uppercase in callsign, & proper error messages(done)
                 add in comments to cover the algorithm if code was removed.
   @endverbatim
 *
 ******************************************************************************/

#pragma pack(1)
#include "functions.h"

/***************************************************************************//**
 * @author Brandon Amundson
 *
 * @par Description:
 * This is the main function of the program.  It calls the functions to read
 * and write from, and to files, it also calls the function that calls the
 * function that checks for errors in all portions of the records in the
 * database file.
 *
 * @param[in]        argc - argument count from when the program was started.
 * @param[in]        argv - contains the arguments from when the program was
 *                          started.
 *
 * @returns 0 - program ran successfully.
 * @returns 10 - Not enough command line arguments.
 *
 ******************************************************************************/
int main(int argc, char *argv[])
{
    ifstream fin;
    ofstream good, bad;
    Record record;
    string countFalse = {0};
    if (argc == 4)
    {
        openFiles(fin, good, bad, argv);
    }
    else
    {
        cout << "Please run as prog1.exe, database file, good file, bad file.";
        return(10);
    }

    while (fin.read((char*)&record, sizeof(Record)))
    {
        callFunctions(record, countFalse);
        errorCheck(countFalse, good, bad, record);
        countFalse.clear();
    }

    closeFiles(fin, good, bad);
    return(0);
}
