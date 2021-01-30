//----------------------------------------
//	   CS 315 Project 4
//----------------------------------------
#include <iostream>
#include <fstream>
#include "family.h"
#include <string>
#include "list.h"

using namespace std;

// returns the family number that two individuals are related through
// two cases for parent family and two for marriage family
int familyFinder(int personID1, int personID2, person * people[100]) {
	if (people[personID1]->parent == people[personID2]->parent) {
		return people[personID1]->parent->ID;
	}
	if (people[personID1]->parent == people[personID2]->marriage) {
                return people[personID1]->parent->ID;
        }
	if (people[personID1]->marriage == people[personID2]->parent) {
		return people[personID1]->marriage->ID;
	}
	if (people[personID1]->marriage == people[personID2]->marriage) {
		return people[personID1]->marriage->ID;
	}
}

// small UI to get user's choice of file
string chooseFile() {
        string fileChoice; // string for getting user's choice of file

        // outputs instructions for user
        cout << "Please enter the text file you would like to use." << endl;
        cout << "For my data, enter myData.txt." << endl;
        cout << "For Dr. Finkel's data, enter finkelData.txt." << endl;
        cout << "Choice: ";

        cin >> fileChoice; // gets user input for the file

        // outputs more instructions
        cout << endl;
        cout << "Thank you for choosing. To continue, press enter." << endl;
        cin.get();
        cin.get();

        return fileChoice; // sends back the file choice
}


int main(){
	// declared and initialized person and family arrays
	person * people[100];
	family * families[100];
	for (int i = 0; i < 100; i++) {
		people[i] = new person;
		people[i]->ID = i;

		families[i] = new family;
		families[i]->ID = i;
	}

	// variables for opening and reading files
	ifstream file;
	string chosenFile;
	string fromFile;

	chosenFile = chooseFile(); // gets the user's choice

	// opens files based on the user's input
        if (chosenFile == "finkelData.txt") {
                file.open("finkelData.txt");
	}
	else if (chosenFile == "myData.txt") {
		file.open("myData.txt");
	}

	// makes sure file does not fail to open
	if (!file.fail()){
		// while there's input from the file
		while (file >> fromFile) {
			// used for goto loop to loop back
			family:
			// Family "function"
			if (fromFile == "Family") {
				// variables to store input from file
                                string storeString;
                                int familyID, husbandID, wifeID, childID[10];
				int childCount = 0;
				
				// takes in the needed IDs except children
                                file >> familyID >> storeString >> husbandID;
                                file >> storeString >> wifeID;

				// puts IDs into proper places
				families[familyID]->ID = familyID;
				people[husbandID]->ID = husbandID;
				people[wifeID]->ID = wifeID;
				
				// loop that takes in all children
				for (int i = 0; i < 10; i++) {
					file >> fromFile;
					
					// jumps to function if input is not "Child"
					if (fromFile != "Child") {
						goto function;
					}
					// stores child's ID and increments count
					else if (fromFile == "Child") {
						file >> childID[childCount];
						childCount++;	
					}
				}
				// used to jump out of for loop
                                function:

				// makes a variable for the current family
				// and points its pointers to proper places
				family * currFamily = families[familyID];
        			currFamily->husband = people[husbandID];
               			currFamily->wife = people[wifeID];
				// points child pointers using loop and count
        			if (childCount > 0) {
                			for (int i = 0; i < childCount; i++) {
                        			currFamily->child[i] = people[childID[i]];
                			}
        			}

				// output to user to show the storage of family
        			cout << "Family " << familyID << " has husband";
				cout << " " << husbandID << ", wife ";
        			cout << wifeID << ", and ";
				// output for the children again with loop
        			if (childCount > 0) {
                			cout << "children";
                			for (int i = 0; i < childCount; i++) {
                        			cout << " " << childID[i];
                			}
                			cout << "." << endl;
        			}
				// case for no children
        			else {
                			cout << "no children." << endl;
        			}

				// remembers what was stored in fromFile and
				// jumps back to this function if it was Family
				if (fromFile == "Family") {
					goto family;
				}
                        }	
			// Insert "function"
			if (fromFile == "Insert") {
				// creates variables needed for taking in IDs
				string storeString;
				int ID, parentFam, marriageFam;
				
				// takes in and stores IDs from file
				file >> ID >> storeString >> parentFam;
				file >> storeString >> marriageFam;

				// creates a new person and points its pointers
				// to proper families
				person * newPerson = people[ID];
        			newPerson->ID = ID;
        			newPerson->parent = families[parentFam];
        			newPerson->marriage = families[marriageFam];

				// output for user to see storage of individual
        			cout << "Individual ";
        			cout << ID << " has parent family ";
        			cout << parentFam<< " and ";
       			 	cout << "is married in family ";
			        cout << marriageFam << "." << endl;				
			}
			// Check "function"
			if (fromFile == "Check") {
				// used to tell if data was consistent or not
				bool consistency = true;
				
				// iterates through all possible families/people
				for (int i = 1; i < 100; i++) {
					// tracks backpointers to family for a child, needed because of a loop
                			bool isBackpoint = false;

					// all statements have NULL checks

					// checks family for same husband in marriage
					// checks husband ID so unknown parents do not cause a message
                			if (families[i]->husband != NULL) {
                               			if (families[i]->husband->ID != 0 && families[i]->husband->marriage != families[i]) {
                                               		cout << "Family " << families[i]->ID;
                                        		cout << " points to husband individual ";
                                        		cout << families[i]->husband->ID;
                                       			cout << " but there is no backpointer.";
                                       			cout << endl;
                                       			consistency = false;
                        			}
                			}
					// checks family for same wife in marriage
					// checks wife ID so unknown parents do not cause a message
                			if (families[i]->wife != NULL) {
                        			if (families[i]->wife->ID != 0 && families[i]->wife->marriage != families[i]) {
                                        		cout << "Family " << families[i]->ID;
                                        		cout << " points to wife individual ";
                           		                cout << families[i]->wife->ID;
                                       			cout << " but there is no backpointer.";
                                       			cout << endl;
                                       			consistency = false;
                        			}
                			}

					// checks family for same children as their parent family
                			for (int j = 0; j < 10; j++) {
                        			if (families[i]->child[j] != NULL) {
                                			if (families[i]->child[j]->parent != families[i]) {
                                        			cout << "Family " << families[i]->ID;
                                        			cout << " points to child individual ";
                                        			cout << families[i]->child[j]->ID;
                                        			cout << " but there is no backpointer.";
                                        			cout << endl;
                                        			consistency = false;
                                			}
						}
					}

					// checks an individual for same parent family for parents they claimed
					if (people[i]->parent != NULL) {
						// iterates through the person's pointed-to family
						// to check if they are claimed by that family
       				                for (int j = 0; j < 10; j++) {
							// if they were claimed, sets backpointer as true
                                			if (people[i]->parent->child[j] == people[i]) {
                                        			isBackpoint = true;
                                			}
                        			}
						// checks for unknown parents and if there was not a backpoiter
                         			if (people[i]->parent->ID != 0 && isBackpoint == false) {
                                		 	cout << "Individual " << people[i]->ID;
                               			 	cout << " points to parent family ";
                               			 	cout << people[i]->parent->ID;
                               			 	cout << " but there is no backpointer." << endl;
                               			 	consistency = false;
                         			}
                			}

					// checks an individual for the same marriage family as they claimed
					// also checks for unknown marriage
                			if (people[i]->marriage != NULL) {
                        			if (people[i]->marriage->ID != 0 && people[i]->marriage->husband != people[i] && people[i]->marriage->wife != people[i]) {
                                       			cout << "Individual " << people[i]->ID;
                                       			cout << " points to marriage family ";
                                       			cout << people[i]->marriage->ID;
                                       			cout << " but there is no backpointer.";
                                       			cout << endl;
                                       			consistency = false;
                               			}
                       			}
                		}

				// case for if the data was all consistent
				// don't put that grammar on me, Dr. Finkel has it like that
                		if (consistency == true) {
                       			cout << "The data are consistent." << endl;
               			}
			}

			// Relate "function"
			if (fromFile == "Relate") {
				// if people are connected, isConnected becomes true
        	                bool isConnected = false;
                	        // list for storing people for this version of BFS
                	        list visitNext;
				// source and destination stores "related" people
				// through is for storing the path of relation
				int source, destination, through[100];

				file >> destination;
				file >> source;
			
				// puts person into the list
				visitNext.pushBack(people[source]);
				
				// while there is someone in the list
				while (visitNext.isEmpty() == false) {
					person * temp  = visitNext.popFront();
					// If the destination person is found
					if (temp == people[destination]) {
						// establishes connection and break out of while loop
						isConnected = true;
						break;
					}
						// finds everyone in the current person's parent family
						if (temp->parent != NULL) {
							// finds family's husband
							if (temp->parent->husband != NULL && temp->parent->husband->visited == false) {
								// puts them in list and adds them to path
								visitNext.pushBack(temp->parent->husband);
								through[temp->parent->husband->ID] = temp->ID;
							}
							// finds family's wife
							if (temp->parent->wife != NULL && temp->parent->wife->visited == false) {
								// puts them in list and adds them to path
								visitNext.pushBack(temp->parent->wife);
								through[temp->parent->wife->ID] = temp->ID;
							}
							// iterates through family's children to find them
							for (int i = 0; i < 10; i++) {
								if (temp->parent->child[i] != NULL && temp->parent->child[i]->visited == false) {
									visitNext.pushBack(temp->parent->child[i]);
									through[temp->parent->child[i]->ID] = temp->ID;
								}
							}
						}
						// finds everyone in the current person's marriage family
						if (temp->marriage != NULL) {
							// finds family's husband
							if (temp->marriage->husband != NULL && temp->marriage->husband->visited == false) {
								// puts them in list and adds them to path
								visitNext.pushBack(temp->marriage->husband);
								through[temp->marriage->husband->ID] = temp->ID;
							}
							// finds family's wife
							if (temp->marriage->wife != NULL && temp->marriage->wife->visited == false) {
								visitNext.pushBack(temp->marriage->wife);
								through[temp->marriage->wife->ID] = temp->ID;
							}
							// iterate's through family's children to find them
							for (int i = 0; i < 10; i++) {
								if (temp->marriage->child[i] != NULL && temp->marriage->child[i]->visited == false) {
									visitNext.pushBack(temp->marriage->child[i]);
									through[temp->marriage->child[i]->ID] = temp->ID;
								}
							}
						}
				}
			
				// resets visited and next so there are no errors for next iteration of Relate
				for (int i = 0; i < 100; i++) {
					people[i]->visited = false;
					people[i]->next = NULL;
				}

				// displays the shortest path if there is a connection
				if (isConnected == true) {
					// starts the tracer at the "destination", actually source
					// destination and source had to be switched, more in documentation
					int tracer = destination;
			
					// starts output to user
					cout << "Individual " << destination;
					// goto loop used until the tracer equals the source
					loop:
	
					// outputs family based on the tracer and the next person in through
					cout << " family " << familyFinder(tracer, through[tracer], people);
					// outputs individual based on the tracer used as an index in through
					cout << " individual " << through[tracer];
					// updates tracer to trace to next connection
					tracer = through[tracer];
					
					// restarts loop if tracer is not at the "source"
					if (tracer != source) {
						goto loop;
					}

					cout << "." << endl;
				}
				// failure to connect message
				else {
					cout << "No connection was found between ";
					cout << destination << " and " << source << "." << endl;
				}
			}
		}
	}
	
	file.close();

	return 0;
}
