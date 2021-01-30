//------------------------------
//	   list class
//------------------------------
#include "list.h"

// constructor
list::list() {
	head = NULL;
	rear = NULL;
}

// removes the head person from the list
person * list::popFront() {
	// creates a storage person variable
	person * giveBack;
	
	// cases for only one person and more than one
	if (head == rear) {
		giveBack = head;
		head = NULL;
		rear = NULL;
		return giveBack;
	}
	else {
		giveBack = head;
		head = head->next;
		giveBack->next = NULL;
		return giveBack;
	}
}

// checks if list is empty or not
bool list::isEmpty() {
	if (head == NULL) {
		return true;
	}
	else {
		return false;
	}
}

// adds person to back of list
void list::pushBack(person * givenPerson) {
	// sets visited status to true since they are in the list
	givenPerson->visited = true;

	// cases for if no one is in list and if someone is
	if (head == NULL) {
		head = givenPerson;
		rear = givenPerson;
	}
	else {
		rear->next = givenPerson;
		rear = givenPerson;
	}
}

