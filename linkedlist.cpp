/*
Name: Aaron Colin Foote
user: acf502 / 4258770
Last Modified Date: 25/3/13
File Description: linkedlist.cpp file for Assignment 1 of CSCI212
*/

#include <iostream>
#include <cstddef>
#include <string>
#include <iomanip>
#include "linkedlist.h"


// Compare function for LinkList class - ListDataType is defined in list.h

LinkedList::LinkedList()	//Constructor, Initiates Head of List to NULL
{
	Head = NULL;
}

LinkedList::~LinkedList()	// Destructor of List
{
	delete Head;
}

void LinkedList::AddToTail(string Fpermissions, int Ffiles, string Fuser, string Fusername, int Ftotsize, int Fyear, int Fmonth, int Fday, string Ftime, string Ffilename)	 // Loads data to nodes
{
	NodePtr NewNode = new node;

	NewNode->Permissions = Fpermissions;		//Each variable passed is loaded into  new node
	NewNode->Files = Ffiles;
	NewNode->Usertype = Fuser;
	NewNode->User = Fusername;
	NewNode->Latest.Year = Fyear;
	NewNode->Latest.Month = Fmonth;
	NewNode->Latest.Day = Fday;
	NewNode->TotSize = Ftotsize;
	NewNode->Time = Ftime;
	NewNode->Filename = Ffilename;
	NewNode->next = NULL;

	NodePtr Curr;		//Tracks current position in List
	if (Head != NULL)
	{
		Curr = Head;
		while (Curr->next)		//If Head exists, loop until end of list reached
			Curr = Curr->next;
		Curr->next = NewNode;
	}
	else
		Head = NewNode;	//If no Head, make Head this node

}

void LinkedList::SetIterator()	//Used for main.cpp, to begin from Head
{
	Current = Head;
}

void LinkedList::Insert()	//Nodes are prepared for printing, grouped together by user and to find values for All node
{
	int users = 1;
	NodePtr curr = Head;
	NodePtr tmp = new node;		//Re-used node to be passed on to Print, holds data on a user through each run
	NodePtr All = new node;		//Node that holds data relevant to all users in total, including total files and filesize etc
	All->User = "ALL";		//Initialized variables set to 0
	All->Files = 1;
	All->TotSize = 0;
	All->Oldest = Head->Latest;
	do
	{
		if (curr->User != curr->next->User)	//Calculate amount of users
			users++;
		curr = curr->next;	
	} while (curr->next != NULL);

	cout << "User\tFiles\tOldest\t\tLatest\t\tTotSize" << endl;	//Print out column labels before the loop of displaying user details

	for (int i = 0; i < users; i++)		//For each user:
	{
		curr = Head;
		tmp = curr;
		while (curr->next != NULL)	//While not at end of list
		{
			if (tmp->User == curr->next->User)	//If new user node's User is equal to next node's User:
			{
				tmp->Files += curr->next->Files;	//Add file count and filesize to new user node. Repeat for All node
				All->Files += curr->next->Files;
				tmp->TotSize += curr->next->TotSize;	
				All->TotSize += curr->next->TotSize;
				if (CalcDate(curr->next->Latest, tmp->Latest, curr->next->Time, tmp->Time))	//If next node is later date than current node:
				{
					tmp->Latest = curr->next->Latest;	//Change new user node's Latest time and date to next node's
					tmp->Time = curr->next->Time;
				}
				if (!CalcDate(curr->next->Latest, tmp->Latest, curr->next->Time, tmp->Time))	//If next node isn't later than current node
					tmp->Oldest = curr->next->Latest;	//Change new user's Old date to next node's date
			}
			curr = curr->next;
		}
		if (CalcDate(tmp->Latest, All->Latest, tmp->Time, All->Time))	//If new user node is later than All node's latest
		{
			All->Latest = tmp->Latest;	//Change All node's latest date and time to new user node's
			All->Time = tmp->Time;
		}
		if (CalcDate(All->Oldest, tmp->Oldest, tmp->Time, All->Time))	//If All node's oldest is newer than new user node's oldest
			All->Oldest = tmp->Oldest;	//Change All node's oldest date to new user node's
		
		Print(tmp);	//Pass new user node to Print for displaying. Repeat until all users are done
	}
	cout << "\n";	//Leaves empty line before All node
	Print(All);	//Pass All node to Print for displaying
	
}

void LinkedList::Print(NodePtr tmp)		//Nodes are displayed one at a time here
{
	cout << tmp->User << "\t" << tmp->Files << "\t";	//Output User then Files count
	PrintMonth(tmp->Oldest.Month);				//Output User's date of Oldest file
	cout << " " << tmp->Oldest.Day << "\t" << tmp->Oldest.Year << "\t";
	PrintMonth(tmp->Latest.Month);				//Output User's date (except year) of Latest file then time
	cout << " " << tmp->Latest.Day << "\t" << tmp->Time << "\t";
	
	int count = 0;
	long double filesize = CalcSize(tmp->TotSize, count);	//Calculates user's total filesize	
	cout << setprecision(4) << filesize;
	switch (count)						//Print filesize with Byte total abbreviated
	{
		case 0:
			cout << "Bytes" << endl;
			break;
		case 1:
			cout << "KB" << endl;
			break;
		case 2:
			cout << "MB" << endl;
			break;
		case 3:
			cout << "GB" << endl;
			break;
		case 4:
			cout << "TB" << endl;
			break;
		default:
			cout << "TB" << endl;
			break;
	};
}

int LinkedList::Find()	//??
{
	NodePtr curr = Head;
	
}

bool LinkedList::CalcDate(Date valx, Date valy, string timea, string timeb)	//Finds latest date, then by time if necessary
{
	long int datecalc1 = 0, datecalc2 = 0;
	datecalc1 = ((valx.Year*10000) + (valx.Month*100) + (valx.Day));	//Grouping year, month and day values into large value
	datecalc2 = ((valy.Year*10000) + (valy.Month*100) + (valy.Day));
	if (datecalc1 > datecalc2)						//Compare the 2 combined date values
		return true;
	else if ((datecalc1 >= datecalc2) && (timea >= timeb))			//If date and time greater, still return true		
		return true;
	else
		return false;			//Otherwise 2nd date is greater
}

void LinkedList::PrintMonth(int month)	//Depending on value of month, print different months
{
	switch (month)
	{
		case 1:
			cout << "Jan";
			break;
		case 2:
			cout << "Feb";
			break;
		case 3:
			cout << "Mar";
			break;
		case 4:
			cout << "Apr";
			break;
		case 5:
			cout << "May";
			break;
		case 6:
			cout << "Jun";
			break;
		case 7:
			cout << "Jul";
			break;
		case 8:
			cout << "Aug";
			break;
		case 9:
			cout << "Sep";
			break;
		case 10:
			cout << "Oct";
			break;
		case 11:
			cout << "Nov";
			break;
		case 12:
			cout << "Dec";
			break;
		default:
			cout << "?";
			break;
	};
}

long double LinkedList::CalcSize(float fsize,int &count)	//Divide filesize by 1024 to get appropriate filesize (e.g: KB, MB etc)
{
	while (fsize > 1023)
	{
		fsize /= 1024;
		count++;		//Tracks total amount of times divided to determine whether to use KB, MB etc
	}
	return fsize;
}
