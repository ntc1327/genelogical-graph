//-----------------------------
//	  family class
//-----------------------------
#include "family.h"

// constructor
family::family() {
	husband = NULL;
	wife = NULL;
	for (int i = 0; i < 10; i++) {
		child[i] = NULL;
	}
	ID = -1;
}
