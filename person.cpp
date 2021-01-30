//--------------------------
//	person class
//--------------------------
#include "person.h"

// constructor
person::person() {
	parent = NULL;
	marriage = NULL;
	next = NULL;
	ID = -1;
	visited = false;
}
