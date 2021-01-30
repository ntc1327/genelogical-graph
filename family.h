//------------------------------------
//	    family class
//------------------------------------
// Describes a family in the
// genelogical graph
//------------------------------------
#include <iostream>

// similar to person class, person must be declared first for use here
// they are dependent on each other
class person;

class family {
friend class person;

public:
	family();
	person * husband;
	person * wife;
	person * child[10];
	int ID;
};
