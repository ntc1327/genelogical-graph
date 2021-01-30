//----------------------------------
//          list class
//----------------------------------
// Describes a list to store the 
// people in the graph for Relate
//----------------------------------
#include "person.h"

class list {
friend class person;

public:
        list();
        void pushBack(person * givenPerson);
        person * popFront();
        bool isEmpty();
        person * head;
        person * rear;
};

