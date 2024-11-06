/***************************************************************************//**
 * @file 
 * 
 * @brief This file contains all the functions required to read and write from 
 * files and also contains the functions that traverse the file system from the
 * given directory.
 *
 * @author Brandon Amundson
 * 
 ******************************************************************************/

#pragma pack(1)
#ifndef _PROG3__H______
#define _PROG3__H______
#define _CRT_SECURE_NO_DEPRECATE
    #include <iostream>
    #include <fstream>
    #include <algorithm>
    #include <string>
    #include <cstring>
    #include <ctime>
    #include <io.h>
    #include <direct.h>
    using namespace std;

    /**
    * @brief Structure to hold all of the information of command line arguments.
    */
	struct args
	{
		bool create;      /*!< a flag to set to true if the user specifies -c*/
		bool modify;      /*!< a flag to set to true if the user specifies -m*/
		string dir;       /*!< the specified directory to search*/
		string pattern;   /*!< the search pattern*/
	};
	int openOutput(ofstream &fout);
	int changeDir(int argc, char *argv[], ofstream &fout, args &arg);
	int closeFiles(ofstream &fout);
	void findDir(ofstream &fout, args &arg);
	void findFile(ofstream &fout, args &arg);
	void findMorC(args &arg, int argc, char *argv[]);
	void runState();
#endif