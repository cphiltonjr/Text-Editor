#define PDC_DLL_BUILD 1
#ifdef _WIN32
//Windows includes
#include "curses.h"
#include "panel.h"
#include "curspriv.h"
#else
//Linux / MacOS includes
#include <curses.h>
#endif
#include <string>
#include <sstream>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "curses.h"

using namespace std;

void PrintFile(vector<char> lines, WINDOW* winptr)
{
	typedef vector<char> Lines;
	int maxlength = 205;
	int loop_counter = 0;
	int counter_len = 3;
	int counter_row = 3;

	for (Lines::const_iterator i = lines.begin(); i != lines.end(); ++i)
	{
		if (loop_counter < maxlength)//looking at the wrong thing
		{
			mvaddch(counter_row, counter_len, *i);
			counter_len++;
			loop_counter++;
		}
		else
		{
			counter_row++;
			counter_len = 3;
			loop_counter = 0;
			mvaddch(counter_row, counter_len, *i);
			i--;
		}

	}
}

void CheckFile(string file, WINDOW* winptr)
{ // use getline to push into a temp place holder then push in into the vector
	typedef vector<char> Doc;
	char ch;
	Doc doc;
	string line;
	ifstream myfile;
	myfile.open(file);

	if (myfile.is_open())
	{
		while (!myfile.eof())
		{
			getline(myfile, line);
			for (int i = 0; i < line.length(); i++)
			{
				doc.push_back(line.at(i));
			}
		}
	}
	else
	{
		PrintError("file/open", winptr);
		MakeFile(file, winptr);
	}

	myfile.close();
	PrintFile(doc, winptr);
}

void MakeFile(string file, WINDOW* winptr)
{
	ofstream newfile(file);
}