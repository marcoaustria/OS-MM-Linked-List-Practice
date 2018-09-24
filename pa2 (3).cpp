//Marco Austria

#include <iostream>
#include<math.h>
#include <string>
using namespace std;

class LinkedList {

private:
	struct Node {
		string name;
		Node*nextNodePtr=NULL;
	};
	Node*head;
	Node*newNode;
	Node*temp;
	Node*start;
	Node*tempStart;

public:
	LinkedList();
	void addNode();
	void printList();
	int addProgram(string programName, string fit, int pages);
	int removeProgram(string programName);
	int findNumFragments();

};

LinkedList::LinkedList() {
	tempStart=new Node();
	start=new Node();
	head = new Node();
	head->name = "Header";//debug
	newNode = new Node();
	temp = new Node();
	temp->name = "Temp";//debug
	head->nextNodePtr = newNode;
	for (int i = 0; i < 32; i++) {
		temp = newNode;
		newNode = new Node();
		newNode->name = "Free";
		temp->nextNodePtr = newNode;
	}
}

//choice 1
int LinkedList::addProgram(string programName, string fit, int pages) {
	temp = head->nextNodePtr;

	//check if program name already exists
	while (true) {
		if (temp->name == programName) {
			cout << "Error, Program " << programName << " already running."
					<< endl;
			return 0;
		}
		if (temp->nextNodePtr != NULL) {
			temp = temp->nextNodePtr;
		} else {
			break;
		}
	}

	//to find lowest count size that fits the pages
	//set to 33 so that first hole always counts as min
	int min = 33;

	//to find biggest count size that fits the pages
	//set to 0 so that first hole always counts as max
	int max = 0;

	//to count number of free spaces
	int count = 0;

	//assigned to smallest space
	//will be where the program starts to fill
//start
	/*to know the start of free space
	 to potentially give value to "real" start
	 if space is smallest*/
//tempStart

	temp = head->nextNodePtr;
	//finds spaces and size to determine best fit
	while (true) {

		//if free space found
		if (temp->name == "Free") {
			//if free space found is the first
			//will assign tempStart to that node
			if (count == 0) {
				tempStart = temp;
			}
			count++;
		}

		//worst fit
		if (fit.compare("worst") == 0) {
			//if space is completely found and holds least necessary pages
			//min is least number of spaces, resets count, potential start will be tempStart
			if (count != 0 && temp->name != "Free" && count >= pages
					&& count > max) {
				max = count;
				count = 0;
				start = tempStart;
			}
			//if done finding a space but space is too small or not smaller than others
			//resets count
			if ((count != 0) && (temp->name != "Free")
					&& (count < pages || count <= max)) {
				count = 0;
			}
		}

		//best fit
		if (fit.compare("best") == 0) {
			//if space is completely found and holds least necessary pages
			//min is least number of spaces, resets count, potential start will be tempStart
			if (count != 0 && temp->name != "Free" && count >= pages
					&& count < min) {
				min = count;
				count = 0;
				start = tempStart;
			}
			//if done finding a space but space is too small or not smaller than others
			//resets count
			if ((count != 0) && (temp->name != "Free")
					&& (count < pages || count >= min)) {
				count = 0;
			}
		}
		if (temp->nextNodePtr != NULL) {
			temp = temp->nextNodePtr;
		} else {
			break;
		}
	}			//while loop
	temp = start;
	//fill with program
	while (pages != 0) {
		temp->name = programName;
		pages--;
		if (temp->nextNodePtr != NULL) {
			temp = temp->nextNodePtr;
		} else {
			break;
		}

	}			//while loop

	return 0;
}			//function

//choice 2
//traverse nodes and find programs with correct name
//count number of pages reclaimed and return
int LinkedList::removeProgram(string programName) {
	temp = head->nextNodePtr;
	int pages = 0;
	while (true) {
		if (temp->name == programName) {
			temp->name = "Free";
			pages++;
		}
		if (temp->nextNodePtr != NULL) {
			temp = temp->nextNodePtr;
		} else {
			break;
		}
	}
	return pages;
}

//choice 3
int LinkedList::findNumFragments() {
	temp = head->nextNodePtr;
	int numFragments = 0;
	int count = 0;
	while (true) {
		if (temp->name == "Free") {
			count++;
		}
		if (count != 0 && temp->name != "Free") {
			numFragments++;
			count = 0;
		}
		if (temp->nextNodePtr != NULL) {
			temp = temp->nextNodePtr;
		} else {
			break;
		}
	}
	numFragments++;
	return numFragments;
}

//choice 4
void LinkedList::printList() {
	temp = head->nextNodePtr;
	int counter = 0;
	while (true) {
		if (counter == 8) {
			cout << temp->name << " " << endl;
			counter = 1;
		} else {
			cout << temp->name << " ";
			counter++;
		}
		if (temp->nextNodePtr != NULL) {
			temp = temp->nextNodePtr;
		} else {
			break;
		}
	} //while loop
	cout << endl;
}

//take in argument for worst or best algorithm
int main( int argc, char ** argv) {

	//variable to be assigned for "worst fit" or "best fit"
	string fit(argv[1]);

	if (fit.compare("worst")==0) {
		cout << "Using worst fit algorithm" << endl;
		fit = "worst";
	}
	if (fit.compare("best")==0) {
		cout << "Using best fit algorithm" << endl;
		fit = "best";
	} else {
		cout<< "Please restart the program and enter an argument for the 'worst' or 'best' algorithm.\n Please use './a.out worst' or './a.out best'.";
		return 0;
	}

	LinkedList*L1 = new LinkedList();

	cout << "1. Add Program\n"
			"2. Kill Program\n"
			"3. Fragmentation\n"
			"4. Print Memory\n"
			"5. Exit\n" << endl;

	int choice;
	string programName;
	int programSize;
	int pages;
	int pagesReclaimed;
	int numFragments;

	//menu
	while (true) {
		cout << "choice - ";
		cin >> choice;
		cout << endl;

		//Add program
		if (choice == 1) {
			cout << "Program name - ";
			cin >> programName;
			cout << endl;
			if (programName.compare("Free") == 0) {
				cout << "Please choose an option other than 'Free'." << endl;
				continue;
			}
			cout << "Program size (KB) - ";
			cin >> programSize;
			cout << "\n";
			if (programSize % 4 == 0) {
				pages = programSize / 4;
			} else if (programSize % 4 != 0 && programSize > 4) {
				pages = (programSize / 4) + 1;
			} else if (programSize < 4) {
				pages = 1;
			} else if (programSize <= 0) {
				cout << "Size of program must be greater than zero." << endl;
				continue;
			}
			if (pages > 32) {
				cout << "Error, Not enough memory for Program " << programName
						<< endl;
				continue;
			}

			L1->addProgram(programName, fit, pages);
			cout << "Program " << programName << " added successfully: "
					<< pages << " page(s) used." << endl;
		}

		//Kill program
		else if (choice == 2) {
			cout << "Program name - ";
			cin >> programName;
			cout << endl;
			if (programName.compare("Free") == 0) {
				cout << "Please choose an option other than 'Free'.\n" << endl;
				continue;
			}

			pagesReclaimed = L1->removeProgram(programName);
			if (pagesReclaimed == 0) {
				cout << "The program you requested does not exist.\n" << endl;
				continue;
			}
			cout << "Program " << programName << " successfully killed, "
					<< pagesReclaimed << " page(s) reclaimed." << endl;
		}

		//Fragmentation
		else if (choice == 3) {
			numFragments = L1->findNumFragments();
			cout << "There are " << numFragments << " fragment(s).\n" << endl;
		}

		//Print memory
		else if (choice == 4) {
			L1->printList();
		}
		//Exit
		else if (choice == 5) {
			break;
		}

		//if choice is not a valid option
		else {
			cout << "Please enter a number choice from the menu." << endl;
		}
	} //while loop

//Exit
	cout << "Goodbye";

	return 0;
}

