/*
Name: Aaron Colin Foote
user: acf502 / 4258770
Last Modified Date: 25/3/13
File Description: linkedlist.h file for Assignment 1 of CSCI212
*/

#ifndef LIST_H_
#define LIST_H_

#include <cstddef>
#include <string>

using namespace std;

struct Date
	{
		int Day;
		int Month;
		int Year;
	};
struct node;
typedef node *NodePtr;
struct node{
			string Permissions;
			int Files;
			string Usertype;
			string User;
			Date Oldest, Latest;
			float TotSize;
			string Time;
			string Filename;
			NodePtr next;
		};

//typedef int ListDataType; 

class LinkedList
{
	public:
		LinkedList();                           // Constructor, Initiates Head of List to NULL
		~LinkedList();                          // Destructor of List
		void AddToTail(string, int, string, string, int, int, int, int, string, string);    // Loads data to nodes
		void SetIterator();			//Used for main.cpp, to begin from Head
		void Insert();				//Nodes are prepared for printing, grouped together by user and to find values for All node
		void Print(NodePtr);			//Nodes are displayed one at a time here
		int Find();				//??
		bool CalcDate(Date, Date, string, string);		//Finds latest date by grouping year, month and day values. Then by time if necessary
		void PrintMonth(int month);		//Depending on value of month, print different months
		long double CalcSize(float, int &);	//Divide filesize by 1024 to get appropriate filesize (e.g: KB, MB etc)
	private:
		
		NodePtr Head;
		NodePtr Current;                       // Iterator pointer
};

#endif
