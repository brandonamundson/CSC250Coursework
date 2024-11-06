#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <cstring>
#include <ctime>
#include <io.h>
#include <direct.h>
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
using namespace std;

struct args
{
    bool create;
    bool modify;
    string dir;
    string pattern;
};

int changeDir(int argc, char *argv[], ofstream &fout, args arg);
int closeFiles(ofstream &fout);
void findDir(ofstream &fout, args arg);
void findFile(ofstream &fout, args arg);

int main(int argc, char *argv[])
{
    ofstream fout;
    int error;
    string dir;
    string pattern;
    args arg;
    error = changeDir(argc, argv, fout, (args)arg);
    if (error != 0)
    {
        return(1);
    }
    findDir(fout, (args)arg);

    closeFiles(fout);
    return(0);
}


int changeDir(int argc, char *argv[], ofstream &fout, args arg)
{
    arg.create = false;
    arg.modify = false;
    fout.open("dir.xml");
    if (!fout)
    {
        cout << "Error opening output file";
        return(12);
    }
    else
    {
        fout << "<?xml version = \"1.0\"?>" << endl;
    }
    if (argc < 3 || argc > 5)
    {
        cout << "Please run as prog3.exe, -m or -c, a directory, and pattern.";
        return(10);
    }
    else
    {
        if (argc == 3)
        {
            if (strcmp(_getcwd(NULL, 0), argv[1]) != 0)
            {
                arg.dir = argv[1];
                arg.pattern = argv[2];
                if (_chdir(argv[1]) == 0)
                {
                    cout << "Program changed directories successfully" << endl;
                }
                else
                {
                    cout << "Unable to change to directory " << argv[1] << endl;
                    return(11);
                }
            }
        }
        if (argc == 4)
        {
            if (strcmp(_getcwd(NULL, 0), argv[2]) != 0)
            {
                arg.dir = argv[2];
                arg.pattern = argv[3];
                if (argv[1][1] == 'M' || argv[1][1] == 'm')
                {
                    cout << "modification date for files.\n";
                    arg.modify = true;
                }
                if (argv[1][1] == 'C' || argv[1][1] == 'c')
                {
                    cout << "creation date for files.\n";
                    arg.create = true;
                }
                if (_chdir(argv[2]) == 0)
                {
                    cout << "Program changed directories successfully" << endl;
                }
                else
                {
                    cout << "Unable to change to directory " << argv[2] << endl;
                    return(11);
                }
            }
        }
        if (argc == 5)
        {
            arg.dir = argv[3];
            arg.pattern = argv[4];
            if (argv[2][1] == 'M' || argv[2][1] == 'm')
            {
                cout << "modification date for files.\n";
                arg.modify = true;
            }
            if (argv[2][1] == 'C' || argv[2][1] == 'c')
            {
                cout << "creation date for files.\n";
                arg.create = true;
            }
            if (strcmp(_getcwd(NULL, 0), argv[3]) != 0)
            {
                if (_chdir(argv[3]) == 0)
                {
                    cout << "Program changed directories successfully" << endl;
                }
                else
                {
                    cout << "Unable to change to directory " << argv[3] << endl;
                    return(11);
                }
            }
        }
    }
    return(0);
}


int closeFiles(ofstream &fout)
{
    fout.close();
    return(0);
}


void findDir(ofstream &fout, args arg)
{
    _finddata_t afile;
    intptr_t dir_handle;

    arg.dir = _getcwd(NULL, 0);

    fout << "<folder name = \"";
    fout << arg.dir;
    fout << "\">";
    fout << endl;
    dir_handle = _findfirst(arg.pattern.c_str(), &afile);
    if (dir_handle == -1)
    {
        return;
    }
    do
    {
        if ((strcmp(afile.name, ".") != 0) && (strcmp(afile.name, "..") != 0))
        {
            if (afile.attrib & _A_SUBDIR)
            {
                arg.dir = _getcwd(NULL, 0);
                arg.dir.push_back((char)"\\");
                arg.dir.push_back((char)&afile.name);
                if (_chdir(arg.dir.c_str()) != 0)
                {
                    cout << "Unable to change to the directory" << arg.dir << endl;
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


void findFile(ofstream &fout, args arg)
{
    char timeModify[256] = "";
    char timeCreate[256] = "";
    intptr_t dir_handle;
    _finddata_t afile;

    dir_handle = _findfirst(arg.pattern.c_str(), &afile);
    if (dir_handle == -1)
    {
        return;
    }

    do
    {
        if (!(afile.attrib & _A_SUBDIR))
        {
            fout << "file name=\"" << afile.name << "\" ";
            if (arg.modify)
            {
                strcpy(timeModify, ctime(&afile.time_write));
                timeModify[strlen(timeModify) - 1] = '\0';
                fout << "DateModified=\"" << timeModify << "\" ";
            }
            if (arg.create)
            {
                strcpy(timeCreate, ctime(&afile.time_create));
                timeModify[strlen(timeModify) - 1] = '\0';
                fout << "DateCreated=\"" << timeCreate << "\" ";
            }
            fout << "/>" << endl;
        }
    } while (_findnext(dir_handle, &afile) == 0);
    _findclose(dir_handle);
}
