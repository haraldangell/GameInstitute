// Monster.h

#ifndef MONSTER_H
#define MONSTER_H

#include "Weapon.h"
#include "Armor.h"
#include <string>


// "Forward class declaration" so that we can use the Player
// class without having defined it yet.  This idea is 
// similar to a function declaration.

class Player;

class Monster
{
public:
	Monster();
	Monster(const std::string& name, int hp, int acc, int xpReward, int gold, std::string armorName,  int armorValue, const std::string& weaponName, int lowDamage, int highDamage);
	~Monster();

	bool isDead();

	

	int         getXPReward();
	int			getGold();
	std::string getName();
	int         getArmor();

	void attack(Player& player);
	void takeDamage(int damage);
	void displayHitPoints();

private:

	std::string mName;
	int         mHitPoints;
	int         mAccuracy;
	int         mExpReward;
	int			mGold;
	Armor       mArmor;
	Weapon      mWeapon;
};

#endif //MONSTER_H