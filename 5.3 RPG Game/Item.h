#ifndef ITEM_H
#define ITEM_H

#include <string>

struct Item
{
	std::string mName;
	std::string mType;
	Range mPotion;
	int mAmount;
};

#endif
