#ifndef STORE_H
#define STORE_H

#include "Player.h"
#include <string>
#include <iostream>

class Store 
{
public:
	Store();
	void enter(Player& player, std::string name);
	

private:
	std::string mName;
};

#endif