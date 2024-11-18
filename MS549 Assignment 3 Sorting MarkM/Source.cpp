/* Mark Montenieri
   Fall 2024
   MS549

   Bubble Sort and Insertion Sort project
   References: I used the sort functions from a previous project
   */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <random>
#include <chrono>
#include<vector>
#include <wtypes.h>
#include <winuser.h>

using namespace std;

template<class T>// Template def

struct Node // Node structure
{
	T data; // Template data
	Node* next; // Previous node
	Node* prev; // Next node
};

/* Declare head/tail, of type <int> */
Node<int>* head;
Node<int>* tail;

/* Init booleans for type of sort to perform */
bool bBubbleSort = false;
bool bInsertionSort = false;
 
void DeleteList(Node<int>** headref)
{	 
	Node<int>* current = *headref;// Init current and set = to headref
	Node<int>* next = NULL;// Init a new node for next

	while (current)// While current is a valid node	 
	{		 
		next = current->next;// Set next to current node's next node ref		 
		free(current);// Free memory for current node
		current = next;// Set current to the next node to be deleted	
		
	}
	*headref = NULL;// Set head to null	 

	/* 
	Since tree is deleted, new nodes must be 
	created/allocated and values set
	*/

	/* Init nodes (allocate memory) */
	head = new Node<int>;
	tail = new Node<int>;

	/* Init data values to NULL */
	head->data = NULL;
	tail->data = NULL;;
}

void DisplayList()
{	 
	Node<int>* current;// Create a local node var			

	if (head->next == nullptr)//Only a single node in list
	{
		current = head;// Make current = head
		cout << current->data << " ";
	}
	else// Multiple nodes in list
	{
		current = head;
		while (current != nullptr)// While current val isn't nullptr
		{
			cout << current->data << " ";
			current = current->next;// Assign to next in list				
		}
	}	 
}

void InsertDataAtEnd(int value)// Insert at end
{	 
	Node<int>* node = new Node<int>;// Init a new node of type int
	node->data = value;// Assign value to the newly created node

	if (head->data == NULL)// Is there a list yet?
	{
		/* Create first node of a new list */
		head = node;// Assign node to head
		tail = node;// Assign node to tail

		head->next = nullptr;// Next item in list is nullptr
		head->prev = nullptr;// Previous item in list is nullptr
		tail->next = nullptr;// Next item in list is nullptr
		tail->prev = nullptr;// Previous item in list is nullptr
	}
	else
	{
		if (head->next == nullptr)// Only a single item in list?
		{
			head->next = node;// Head next is our new node
		}

		Node<int>* oldTail = tail;
		oldTail->next = node; //Assign the new node to the old one's next
		tail->next = node;// Previous tail's next is now this node
		tail = node;// Make this node the new tail
		tail->next = nullptr;// This new node becomes the end of list	
		tail->prev = oldTail;// Set new tail's prev val to that of the old tail		  
	}	 
} 

bool ImportFileContents(string fileName)// Read the file, if valid
{
	ifstream in(fileName.c_str());// Open the File	 
	if (!in)// Is valid?
	{
		cerr << "Cannot open the File : " << fileName << endl;
		return false;
	}
	string str;// String var	
	while (getline(in, str))// Read each line until the end
	{
		if (str.size() > 0)// Line has data?
		{
			int value = stoi(str);// Convert to int
			InsertDataAtEnd(value);// Insert to Linked list
		}		 
	}
	in.close();//Close The File
	return true;// Success!
}

void BubbleSortList()
{	
	bool bSwapped;// bool to check if values have been swapped
	struct Node<int>* current;// Current node ref
	struct Node<int>* next = NULL;// Next node ref
	 
	if (head == NULL)// Is list empty?
	{
		return;
	}		

	do// Loop and swap as needed
	{
		bSwapped = false;// Init var to false
		current = head;// Set current = to root node(head)

		while (current->next != next)// Is node current(next) different than next? (checking to see if we are at end of list)
		{
			if (current->data > current->next->data)// Is current node data larger than current next node data?
			{
				swap(current->data, current->next->data);// Swap to put smaller value to left
				bSwapped = true;// Indicate swapped = true
			}
			current = current->next;// Set current = to its next node ref
		}
		next = current;// Set next to current
	} while (bSwapped);// Do while swapped = true
	cout << "DONE!" << endl;
}

void InsertionSwap(Node<int>* first, Node<int>* second)// Swap values if necessary
{
	int temp = first->data;// Create a temp value containing the first node's data
	first->data = second->data;// Set first nodes data to second node value
	second->data = temp;// Now set the second node value to the temp value (formerly first)
}
 
void InsertionSortList()
{
	Node<int>* currentList = head;// Make a new current (working) list from the existing one
	Node<int>* next;// Make a new Next node	 
	 
	while (currentList != NULL)// Is current list valid?
	{
		next = currentList->next;// Next node = current node's next ptr
		while (next != NULL && next->prev != NULL)// While next is NOT null and next previous node is NOT null
		{
			if (next->data < next->prev->data)// Is the next node's value smaller than the next->prev node's data?
			{
				InsertionSwap(next, next->prev);// Swap the values
				next = next->prev;
			}
			else 
			{
				break;// Break out to the outer while loop
			}
		}
		currentList = currentList->next;// Step to the next node
	}	 
}

void MenuChooseFile()
{
	Node<int>* insertList = NULL;// Insertion sort list
	int num = 0;// File choice
	string fileName;// File name to open
	cout << "Choose which file to run." << endl;
	cout << "1 = num10.dat" << endl;
	cout << "2 = num100.dat" << endl;
	cout << "3 = num1000.dat" << endl;
	cout << "4 = num10000.dat" << endl;
	cout << "5 = num100000.dat" << endl;
	cout << "6 = num1000000.dat" << endl;
	cout << "Your choice: ";
	cin >> num;	

	switch (num)// User choice selects one of these files
	{
	case 1:
	{
		fileName = "SortDatasets\\num10.dat";
		break;
	}
	case 2:
	{
		fileName = "SortDatasets\\num100.dat";
		break;
	}
	case 3:
	{
		fileName = "SortDatasets\\num1000.dat";
		break;
	}
	case 4:
	{
		fileName = "SortDatasets\\num10000.dat";
		break;
	}
	case 5:
	{
		fileName = "SortDatasets\\num100000.dat";
		break;
	}
	case 6:
	{
		fileName = "SortDatasets\\num1000000.dat";
		break;
	}
	default:
		fileName = "SortDatasets\\num10.dat";
		break;
	}
	 
	bool result = ImportFileContents(fileName);// Attempt to open file
	if (result)
	{
		//cout << "Unsorted list:" << endl;// DEBUG ONLY
		//DisplayList();
		auto start = chrono::high_resolution_clock::now();// Start high-res timer
		if (bBubbleSort == true)
		{
			BubbleSortList();// Sort the list
			bBubbleSort = false;
		}
		else
		{
			InsertionSortList();
			bInsertionSort = false;
		}	

		auto finish = chrono::high_resolution_clock::now();// Stop high-res timer
		auto microseconds = chrono::duration_cast<chrono::microseconds>(finish - start);// Get duration
		 
		/*Display in micro-milli-seconds */		 
		if (microseconds.count() < 1000)
		{
			cout << endl << endl << "Sort runtime: " << microseconds.count() << " Microseconds" << endl;
		}
		else if (microseconds.count() < 1000000)
		{
			cout << endl << endl << "Sort runtime: " << microseconds.count() << " Milliseconds" << endl;
		}
		else
		{
			cout << endl << endl << "Sort runtime: " << (microseconds.count() / 1000000) << " Seconds" << endl;
		}

		//cout << "Sorted List:" << endl;// DEBUG ONLY
		//DisplayList();// Display the current sorted list
		DeleteList(&head);// Delete the main list and free memory so we can run the function again		 
	}
}

int menu()
{
	cout << "Please choose from the options below." << endl << endl;
	int choice;
	cout << "1 = Bubble Sort Array" << endl;	
	cout << "2 = Insertion Sort Array" << endl;
	cout << "3 = Exit program" << endl;
	cin >> choice;// User input
	return choice;
}; // End of menu

int main()
{		
	cout << "Bubble sort & Insert Sort" << endl << endl;

	/* Init nodes (allocate memory) */
	head = new Node<int>;
	tail = new Node<int>;

	/* Init data values to NULL */
	head->data = NULL;
	tail->data = NULL;

	int choice = menu();// Show menu
	while (choice != 3)
	{
		if (choice == 1)// Bubble Sort
		{
			bBubbleSort = true;// Set bubble sort true
			MenuChooseFile();//
		}// end if choice == 1
		else if (choice == 2)// Insertion sort
		{
			bInsertionSort = true;// set insertion sort true
			MenuChooseFile();			
		}
		
		cout << endl;
		choice = menu();// Reopen menu
		cin.ignore();// clear input buffer
	};

	system("pause");// Pause to keep program open
	return 0;
}// end main