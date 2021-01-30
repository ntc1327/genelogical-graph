//-------------------------------
//	   person class
//-------------------------------
// Describes a person in the
// genelogical graph
//-------------------------------
#include <iostream>

// declares family so it can be used here
// is dependent on family so that is why
class family;

class person {
friend class family;

public:
	person();
	family * parent;
	family * marriage;
	person * next; // tracks next person in list
	int ID;
	bool visited; // tracks if person was visited in list
};
