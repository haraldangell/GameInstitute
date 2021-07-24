// Monster.cpp

#include <iostream>
#include <string>
#include "Monster.h"
#include "Player.h"
#include "Random.h"
using namespace std;

Monster::Monster()
{
	mName = "";
	mHitPoints = 0;
	mAccuracy = 0;
	mExpReward = 0;
	mGold = 0;
	mArmor.mName = "";
	mArmor.armorValue = 0;
	mWeapon.mName = "";
	mWeapon.mDamageRange.mLow = 0;
	mWeapon.mDamageRange.mHigh = 0;
}

Monster::Monster(const std::string& name, int hp, int acc,	int xpReward, int gold, std::string armorName, int armorValue, const std::string& weaponName, int lowDamage, int highDamage)
{
	mName      = name;
	mHitPoints = hp;
	mAccuracy  = acc;
	mExpReward = xpReward;
	mGold = gold;
	mArmor.mName = armorName;
	mArmor.armorValue = armorValue;
	mWeapon.mName = weaponName;
	mWeapon.mDamageRange.mLow  = lowDamage;
	mWeapon.mDamageRange.mHigh = highDamage;
}
Monster::~Monster()
{

}

bool Monster::isDead()
{
	return mHitPoints <= 0;
}

int Monster::getXPReward()
{
	return mExpReward;
}
int Monster::getGold()
{
	return mGold;
}
std::string Monster::getName()
{
	return mName;
}

int Monster::getArmor()
{
	return mArmor.armorValue;
}

void Monster::attack(Player& player)
{
	cout << "A " << mName << " attacks you " << "with a " << mWeapon.mName << endl;

	// Test to see if the monster hit the player.
	if( Random(0, 20) < mAccuracy )
	{
		// Generate a damage value based on the weapons range.
		int damage = Random(mWeapon.mDamageRange);

		// Subtract the player's armor from damage to
		// simulate armor weakening the attack.  Note that
		// if the armor > damage this results in a negative
		// number.
		int totalDamage = damage - player.getArmor();

		// If totalDamage <= 0, then we say that, although
		// the attack hit, it did not penetrate the armor.
		if( totalDamage <= 0 )
		{
			cout << "The monster's attack failed to " << "penetrate your armor." << endl;
		}
		else
		{
			cout << "You are hit for " << totalDamage << " damage!" << endl;

			// Subtract from players hitpoints.
			player.takeDamage(totalDamage);
		}
	}
	else
	{
		cout << "The " << mName << " missed!" << endl;
	}
	cout << endl;
}

void Monster::takeDamage(int damage)
{
	mHitPoints -= damage;
}

void Monster::displayHitPoints()
{
	cout << mName << "'s hitpoints = " << mHitPoints << endl;
}