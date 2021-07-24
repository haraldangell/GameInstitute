#ifndef INVENTORY_H
#define INVENTORY_H


#include <string>
#include "Range.h"
#include "Weapon.h"
#include "Armor.h"
#include "Spell.h"
#include "Item.h"

struct InventoryWeapon
{
	InventoryWeapon(std::string name, int low, int high, int price) { mWeapon.mName = name; mWeapon.mDamageRange.mLow = low; mWeapon.mDamageRange.mHigh = high; mPrice = price; };
	Weapon mWeapon;
	int mPrice;
};
struct InventoryArmor
{
	InventoryArmor(std::string name, int value, int price) { mArmor.mName = name; mArmor.armorValue, mPrice = price; };
	Armor mArmor;
	int mPrice;
};
struct InventorySpell
{
	InventorySpell(std::string name, int low, int high, int price) { mSpell.setName(name); mSpell.setDamageRange(low, high); mPrice = price; };
	Spell mSpell;
	int mPrice;
};
struct InventoryItem
{
	InventoryItem(std::string name, std::string type, int low, int high, int amount, int price) { mItem.mName = name; mItem.mType = type; mItem.mPotion.mLow = low;	mItem.mPotion.mHigh = high;	mItem.mAmount = amount;	mPrice = price; };
	Item mItem;
	int mPrice;
};
#endif