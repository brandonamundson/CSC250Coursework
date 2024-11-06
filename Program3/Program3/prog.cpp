#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <cstring>
#include <ctime>
#include <io.h>
#include <direct.h>
using namespace std;

int changeDir(int argc, char *argv[], ofstream &fout, string &dir, string &pattern);
int closeFiles(ofstream &fout);
void recursion(ofstream &fout, string &dir, string &pattern);

int main(int argc, char *argv[])
{
    ofstream fout;
    int error;
    string dir;
    string pattern;
    error = changeDir(argc, argv, fout, dir, pattern);
    if (error != 0)
    {
        return(1);
    }
    recursion(fout, dir, pattern);

    closeFiles(fout);
    return(0);
}


int changeDir(int argc, char *argv[], ofstream &fout, string &dir, string &pattern)
{
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
    if (argc < 3)
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
                dir = argv[1];
                pattern = argv[2];
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
                dir = argv[2];
                pattern = argv[3];
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
            dir = argv[3];
            pattern = argv[4];
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

void recursion(ofstream &fout, string &dir, string &pattern)
{
    _finddata_t afile;
    intptr_t dir_handle;
    string dir;
    dir = _getcwd(NULL, 0);
    fout << "<folder name = \"" << dir << "\">" << endl;
    dir_handle = _findfirst(pattern.c_str(), &afile);
    if (dir_handle == -1)
    {
        return;
    }
    do
    {
        if ((strcmp(afile.name, ".") != 0) || (strcmp(afile.name, "..") != 0))
        {
            if (afile.attrib & _A_SUBDIR)
            {
                dir = _getcwd(NULL, 0);
                dir.push_back((char)"\\");
                dir.push_back((char)&afile.name);
                if (_chdir(dir.c_str()) != 0)
                {
                    cout << "Unable to change to the directory" << dir << endl;
                }
                recursion(fout, dir, pattern);
                if (_chdir("..") != 0)
                {
                    cout << "Error, cant backtrack" << endl;
                }
            }
        }
    } while (_findnext(dir_handle, &afile) == 0);
    _findclose(dir_handle);
    recursion(fout, dir, pattern);
    fout << "</folder>" << endl;
}
