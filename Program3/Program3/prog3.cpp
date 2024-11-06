/***************************************************************************//**
 * @file 
 * @brief This file is the code that runs the program and will search the
 *        a given directory looking for a specific file pattern.
 * 
 * @mainpage Program 3 - Recursive Directory Search
 *
 * @section course_section Course Information
 *
 * @authors Brandon Amundson
 *
 * @date March 13, 2015
 *
 * @par Instructor:
 *         Roger Schrader
 *
 * @par Course:
 *         CSC 250 - Section 1 - 11:00 am
 *
 * @par Location:
 *         Classroom Building - Room 204W
 *
 * @section program_section Program Information
 *
 * @details
 *      This program recursively searches a specific directory for a specific
 * file pattern and will output all of the found files and folders within the
 * specified directory.  This program is run with a command that specifies
 * whether the creation date, the modify date or both are outputted to an XML
 * formatted file.  The next command that is required is a valid directory to
 * search and a search pattern to find specific files.  If you want all files,
 * use the pattern "*.*".
 *
 *      This program then takes the given command line arguments and searches
 * the given directory and all of the files within each directory outputting
 * each in MLA fomrat to an XML file.  When searching each subdirectory for
 * for files, it checks to make sure that it matches the specific file pattern
 * that is specified when running the program.  When this program is done, it
 * then exits with code 0.
 *
 * @section compile_section Compiling and Usage
 *
 * @par Compiling Instructions:
 *      None
 *
 * @par Usage:
   @verbatim
   c:\> prog3.exe -c, -m, or both -c -m, directory, pattern
                  -c is for outputting the creation date.
                  -m is for outputting the modify date.
                  directory is the directory that is to be searched - must have.
                  pattern is the pattern of the files to search for - must have.
   @endverbatim
 *
 * @section todo_bugs_modifications_section Todo, Bugs, and Modifications
 *
 *
 * @par Modifications and Developing Timeline:
   @verbatim
   Date          Modification
   ------------  ---------------------------------------------------------------
   March 26      Have the command line arguments parsed
   March 30      Have error checked the dir.xml file for opening and that the
                 specified directory exists.
   April 2       Output a valid XML file without doing a recursive call for the
                 inner files.  This includes files that match the specified
                 pattern.
   April 7       Be able to recursively traverse the directory structure
                 outputting XML tags.
   April 10      Have tested and debugged your program
   April 13      Program due by 11:50PM
   @endverbatim
 *
 ******************************************************************************/
#define _CRT_SECURE_NO_DEPRECATE
#include "prog3.h"


/***************************************************************************//**
 * @author Brandon Amundson
 *
 * @par Description:
 * This is the main function of the program.  It calls the functions that
 * recursively search the directory after verifing that the directory exists.
 *
 * @param[in]        argc - argument count from when the program was started.
 * @param[in]        argv - contains the arguments from when the program was
 *                          started.
 *
 * @returns 0 - program ran successfully.
 * @returns 1 - Unable to change directory or unable to open file for output.
 *
 ******************************************************************************/
int main(int argc, char *argv[])
{
    ofstream fout;
    int error;
    args arg;
    error = openOutput(fout);
    if (error != 0)
    {
        return(1);
    }
    findMorC(arg, argc, argv);
    error = changeDir(argc, argv, fout, arg);
    if (error != 0)
    {
        return(1);
    }
    findDir(fout, arg);

    closeFiles(fout);
    return(0);//exits program
}


/***************************************************************************//**
 * @author Brandon Amundson
 *
 * @par Description:
 * This is the function that opens the files for writing the XML tags to an
 * XML formatted file.  If this function is unable to open any file, it exits
 * with a code twelve.
 * 
 * 
 * @param[in, out]      fout - Output File Stream to be opened.  Used to output
 *                             the directory in XML format.
 * @return 12           Error opening file.
 * @return 0            Succefully opend file.
 ******************************************************************************/
int openOutput(ofstream &fout)
{
    fout.open("dir.xml");//function that opens the xml file
    if (!fout)
    {
        cout << "Error opening output file";
        return(12);
    }
    else
    {
        fout << "<?xml version = \"1.0\"?>" << endl;
    }
    return(0);
}


/***************************************************************************//**
 * @author Brandon Amundson
 *
 * @par Description:
 * This is the function that parses the directory portion of the command line
 * arguments and changes to the directory provided in the command line arguments.
 * 
 * 
 * @param[in]        argc - argument count from when the program was started.
 * @param[in]        argv - contains the arguments from when the program was
 *                          started.
 * @param[in, out]   fout - Output File Stream for outputting.  Used to
 *                          output the directory in XML format.
 * @param[in, out]    arg - Structure to hold all of the information of
 *                          command line arguments.
 ******************************************************************************/
int changeDir(int argc, char *argv[], ofstream &fout, args &arg)
{
    if (argc < 3 || argc > 5)//checks argument count
    {
        runState();
    }
    else //changes the directory based on argument count
    {
        if (argc == 3)
        {
            if (strcmp(_getcwd(NULL, 0), argv[1]) != 0)
            {
                arg.pattern = argv[2];
                if (_chdir(argv[1]) == 0)
                {
                }
                else
                {
                    cout << "Unable to change to directory " << argv[1] << endl;
                    return(11);
                }
            }
        }
        if (argc > 3)
        {
            if (strcmp(_getcwd(NULL, 0), argv[argc - 2]) != 0)
            {
                if (_chdir(argv[argc - 2]) == 0)
                {
                }
                else
                {
                    cout << "Unable to change to directory " << argv[2] << endl;
                    return(11);
                }
            }
        }
    }
    return(0);
}


/***************************************************************************//**
 * @author Brandon Amundson
 *
 * @par Description:
 * This is the function that checks the command line arguments for a m or c or
 * both and sets the modify or create portions of the args structure to true or
 * false as required.
 * 
 * @param[in]        argc - argument count from when the program was started.
 * @param[in]        argv - contains the arguments from when the program was
 *                          started.
 * @param[in, out]    arg - Structure to hold all of the information of
 *                          command line arguments.
 ******************************************************************************/
void findMorC(args &arg, int argc, char *argv[])
{
    arg.create = false; //function that checks valid option if given
    arg.modify = false;
    char c;
    char m;
    if (argc == 3)
        return;
    if (argc == 5)
    {
        c = argv[argc - 3][1];
        c = toupper(c);
        m = argv[argc - 2][1];
        m = toupper(m);

        if ((c == 'M' && m == 'C') || (c == 'C' && m == 'M'))
        {
            arg.pattern = argv[argc - 1];
            arg.modify = true;
            arg.create = true;
        }
        else
        {
            runState();
        }
    }
    else
    {
        arg.pattern = argv[argc - 1];
        c = argv[argc - 3][1];
        c = toupper(c);
        if (c == 'M' || c == 'C')
        {
            if (c == 'M')
            {
                arg.modify = true;
            }
            if (c == 'C')
            {
                arg.create = true;
            }
        }
        else
            runState();
    }
}


/***************************************************************************//**
 * @author Brandon Amundson
 *
 * @par Description:
 * This is the function that closes the file for writing the XML tags to an
 * XML formatted file.
 * 
 * 
 * @param[in, out]      fout - Output File Stream to be used for outputting.
 *                             Used to output the directory in XML format.
 * @return 0            Succefully closed file.
 ******************************************************************************/
int closeFiles(ofstream &fout)
{
    fout.close();
    return(0);
}


/***************************************************************************//**
 * @author Brandon Amundson
 *
 * @par Description:
 * This is the function that recursively searches the directory for other
 * subdirectories.  Then this functions calls the findFile function that outputs
 * the files that match the pattern and also outputs the date created or date
 * modified depending on the users choice.
 * 
 * 
 * @param[in, out]      fout - Output File Stream to be used for outputting.
 *                             Used to output the directory in XML format.
 * @param[in, out]       arg - Structure to hold all of the information of
 *                             command line arguments.
 ******************************************************************************/
void findDir(ofstream &fout, args &arg)
{
    _finddata_t afile; /*recursive function that outputs folder tags and handles
                       / the sub directories.*/
    intptr_t dir_handle; 
    int idx = arg.dir.npos;

    arg.dir = _getcwd(NULL, 0);

    fout << "<folder name = \"";
    idx = arg.dir.find('&');
    while (idx != arg.dir.npos)
    {
        arg.dir.erase(idx, 1);
        arg.dir.insert(idx, "&amp;");
        idx = arg.dir.find('&', idx + 1);
    }
    fout << arg.dir << "\">" << endl;
    dir_handle = _findfirst("*.*", &afile);
    if (dir_handle == -1)
    {
        fout << "</folder>" << endl;
        return;
    }
    do
    {
        if ((strcmp(afile.name, ".") != 0) && (strcmp(afile.name, "..") != 0))
        {
            if (afile.attrib & _A_SUBDIR)
            {
                arg.dir = _getcwd(NULL, 0);
                arg.dir.push_back('\\');
                arg.dir += afile.name;
                if (_chdir(arg.dir.c_str()) != 0)
                {
                    cout << "Unable to change to the directory " << arg.dir
                         << endl;
                    continue;
                }
                findDir(fout, arg);
                if (_chdir("..") != 0)
                {
                    cout << "Error, cant backtrack" << endl;
                }
            }
        }
    } while (_findnext(dir_handle, &afile) == 0);
    _findclose(dir_handle);
    findFile(fout, arg);
    fout << "</folder>" << endl;
}


/***************************************************************************//**
 * @author Brandon Amundson
 *
 * @par Description:
 * This is the function that searches the current directory and outputs the
 * files that match the pattern and also outputs the date created or date
 * modified depending on the users choice.
 * 
 * 
 * @param[in, out]      fout - Output File Stream to be used for outputting.
 *                             Used to output the directory in XML format.
 * @param[in, out]       arg - Structure to hold all of the information of
 *                             command line arguments.
 ******************************************************************************/
void findFile(ofstream &fout, args &arg)
{
    string timeModify;/*the function that outputs the files within directories
                      / that match the given pattern*/
    string timeCreate;
    intptr_t dir_handle;
    _finddata_t afile;
    string name;
    int idx = name.npos;

    dir_handle = _findfirst(arg.pattern.c_str(), &afile);
    if (dir_handle == -1)
    {
        return;
    }
    do
    {
        if (!(afile.attrib & _A_SUBDIR))
        {
            fout << "<file name=\"";
            name = afile.name;
            idx = name.find('&');
            while (idx!=name.npos)
            {
                name.erase(idx, 1);
                name.insert(idx, "&amp;");
                idx = name.find('&', idx + 1);
            }
            fout << name;
            fout << "\" ";
            if (arg.modify)
            {
                timeModify = ctime(&afile.time_write);
                timeModify.erase((timeModify.size() - 1));
                fout << "DateModified=\"" << timeModify << "\" ";
            }
            if (arg.create)
            {
                timeCreate = ctime(&afile.time_create);
                timeCreate.erase((timeCreate.size() - 1));
                fout << "DateCreated=\"" << timeCreate << "\" ";
            }
            fout << "/>" << endl;
        }
    } while (_findnext(dir_handle, &afile) == 0);
    _findclose(dir_handle);
}


/***************************************************************************//**
 * @author Brandon Amundson
 *
 * @par Description:
 * This is the function that is called when the program is not run with valid
 * command line arguments.  This exits the program with a code 5.
 ******************************************************************************/
void runState()
{
    cout << "Please run as prog3.exe, -m or -c, a valid directory, and a pattern."
         << endl;
    exit(5);
}
