// Player.h

#ifndef PLAYER_H
#define PLAYER_H

#include "Weapon.h"
#include "Monster.h"
#include "Spell.h"
#include "Armor.h"
#include "Item.h"
#include <string>
#include <vector>


class Player
{
public:
	// Constructor.
	Player();

	// Methods
	bool isDead() const;

	int getArmor() const;
	int getGold() const;
	int getLevel() const;
	std::string getName()const;

	void takeDamage(int damage);
	void createCharater();
	bool attack(Monster& monster);
	void levelUp();
	void rest();
	void viewStats() const;
	void victory(int xp, int gold);
	void gameover();
	void displayHitPoints() const;
	void addSpell(std::string name, int low, int high, int required);
	void addSpell(Spell spell);
	void addItems(Item item);
	void addItems(std::string name,int amount);
	void changeArmor(Armor armor);
	void changeWeapon(Weapon weapon);
	void useGold(int gold);
	

 
private:
	// Data members.
	std::string mName;
	std::string mClassName;
	std::string mRace;
	int         mAccuracy;
	int         mHitPoints;
	int         mMaxHitPoints;
	int         mExpPoints;
	int         mNextLevelExp;
	int         mLevel;
	Armor       mArmor;
	int			mGold;
	int		    mMagicPoints;
	int			mMaxMagicPoints;
	Weapon      mWeapon;
	std::vector<Spell> mSpellBook;
	std::vector<Item> mBag;
};

#endif //PLAYER_H