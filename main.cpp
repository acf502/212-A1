/*
Name: Aaron Colin Foote
user: acf502 / 4258770
Last Modified Date: 25/3/13
File Description: main.cpp file for Assignment 1 of CSCI212
*/

#include <iostream>
#include <cstdlib>
#include "linkedlist.h"

using namespace std;

int main(int argc, char* argv[])
{
	LinkedList List;
	char *Option = argv[1];
	string ch[10];			//string array of data from ls -l command
	string permissions;
	int files;			//variables to hold pieces of data from ls -l command
	string user;
	string usertype;
	float totsize;
	int year;
	int month;
	int day;
	string time;
	string filename;
		while (cin.good())
		{
			getline(cin, ch[0], ' ');
			cout << ch[0] << endl;
			if (ch[0][0] == '-')	//check that start of line consists of 10 characters and starts with a '-', to eliminate listings of directories
				{ 
					cin >> ch[1];				//load each part of line into corresponding array elements.
					cin.ignore();
					getline(cin, ch[2],' ');
					getline(cin, ch[3],' ');
					cin >> ch[4];
					cin.ignore();
					getline(cin, ch[5],'-');
					getline(cin, ch[6],'-');
					getline(cin, ch[7],' ');
					getline(cin, ch[8],' ');
					getline(cin, ch[9],'\n');

					permissions = ch[0];			//move array elements to variables from beginning of main function
					files = atoi(ch[1].c_str());		//convert to integer where necessary
					user = ch[2];
					usertype = ch[3];
					totsize = atoi(ch[4].c_str());
					year = atoi(ch[5].c_str());
					if (ch[6][0] == '0')
						ch[6].erase(0,1);
					month = atoi(ch[6].c_str());
					if (ch[7][0] == '0')			//if string begins with 0, remove 0 before conversion to integer
						ch[7].erase(0,1);
					day = atoi(ch[7].c_str());
					time = ch[8];
					filename = ch[9];

					List.SetIterator();
					List.AddToTail(permissions, files, user, usertype, totsize, year, month, day, time, filename);
					
				}
			else
			getline(cin,ch[0],'\n');		//if line isn't suitable, skip line
			
		}

		List.Insert();
	return 0;
}

