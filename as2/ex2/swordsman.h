//=======================
//		swordsman.h
//=======================

// Derived from base class player
// For the job Swordsman
#include <iostream>
#include "player.h"
class swordsman : public player	// subclass swordsman publicly inherited from base player
{
public:
	swordsman(int lv_in=1, std::string name_in="Not Given");	
		// constructor with default level of 1 and name of "Not given"
	void isLevelUp();
	bool attack (player &p);
	bool specialatt(player &p);
		/* These three are derived from the pure virtual functions of base class
		   The definition of them will be given in this subclass. */
	void AI(player &p);				// Computer opponent
};
