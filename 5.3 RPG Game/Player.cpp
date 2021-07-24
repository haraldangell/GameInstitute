// Player.cpp

#include <iostream>
#include "Player.h"
#include "Random.h"
#include <string>
using namespace std;

Player::Player()
{
	mName = "Default";
	mClassName = "Default";
	mRace = "Default";
	mAccuracy = 0;
	mHitPoints = 0;
	mMaxHitPoints = 0;
	mExpPoints = 0;
	mNextLevelExp = 0;
	mLevel = 0;
	mArmor.mName = "Default";
	mArmor.armorValue = 0;
	mMagicPoints = 0;
	mMaxMagicPoints = 0;
	mWeapon.mName = "Default Weapon Name";
	mWeapon.mDamageRange.mLow = 0;
	mWeapon.mDamageRange.mHigh = 0;

}



bool Player::isDead() const
{
	return mHitPoints <= 0;
}

int Player::getArmor() const
{
	return mArmor.armorValue;
}

int Player::getGold() const
{
	return mGold;
}

int Player::getLevel() const
{
	return mLevel;
}
std::string Player::getName() const
{
	return mName;
}
void Player::takeDamage(int damage)
{
	mHitPoints -= damage;
}

void Player::createCharater()
{
	//dwarf, human,	elf, halfling.
	// accuracy, hitpoints
	cout << "CHARACTER RACE GENERATION" << endl;
	cout << "==========================" << endl;

	// Input character's name.
	cout << "Enter your character's name: ";
	getline(cin, mName);

	cout << "Please select a character race number..." << endl;
	cout << "1) Dwarf 2) Human 3) Elf 4) Halfling : ";

	auto raceNum = 0;
	cin >> raceNum;

	switch (raceNum)
	{
	case 1: //Dwarf
		mRace = "Dwarf";
		mAccuracy = 2;
		mHitPoints = 8;
		break;
	case 2: //Human
		mRace = "Human";
		mAccuracy = 5;
		mHitPoints = 5;
		break;
	case 3: //Elf
		mRace = "Elf";
		mAccuracy = 7;
		mHitPoints = 3;
		break;
	case 4: //Hafling
		mRace = "Hafling";
		mAccuracy += 8;
		mHitPoints += 8;
		break;
	}


	cout << "CHARACTER CLASS GENERATION" << endl;
	cout << "==========================" << endl;


	// Character selection.
	cout << "Please select a character class number..." << endl;
	cout << "1) Fighter 2) Wizard 3) Cleric 4) Thief : ";

	int characterNum = 1;
	cin >> characterNum;

	switch (characterNum)
	{
	case 1:  // Fighter
		mClassName = "Fighter";
		mAccuracy += 10;
		mHitPoints += 20;
		mMaxHitPoints = 20;
		mExpPoints = 0;
		mNextLevelExp = 1000;
		mLevel = 1;
		mArmor.mName = "SquirePlate";
		mArmor.armorValue = 4;
		mGold = 0;
		mMagicPoints = 20;
		mMaxMagicPoints = 20;
		mWeapon.mName = "Long Sword";
		mWeapon.mDamageRange.mLow = 1;
		mWeapon.mDamageRange.mHigh = 8;
		break;
	case 2:  // Wizard
		mClassName = "Wizard";
		mAccuracy += 5;
		mHitPoints += 1000; //Set back to 10
		mMaxHitPoints = 10;
		mExpPoints = 0;
		mNextLevelExp = 1000;
		mLevel = 1;
		mArmor.mName = "Dirty Old Linen Cloth";
		mArmor.armorValue = 1;
		mGold = 25000; //remember to set back to 0
		mWeapon.mName = "Staff";
		mWeapon.mDamageRange.mLow = 1;
		mWeapon.mDamageRange.mHigh = 4;
		mMagicPoints = 20;
		mMaxMagicPoints = 20;
		addSpell("Fireball", 3, 12, 3);
		break;
	case 3:  // Cleric
		mClassName = "Cleric";
		mAccuracy += 5;
		mHitPoints += 15;
		mMaxHitPoints = 15;
		mExpPoints = 0;
		mNextLevelExp = 1000;
		mLevel = 1;
		mArmor.mName = "Clerical clothing";
		mArmor.armorValue = 3;
		mGold = 0;
		mWeapon.mName = "Flail";
		mWeapon.mDamageRange.mLow = 1;
		mWeapon.mDamageRange.mHigh = 6;
		mMagicPoints = 20;
		mMaxMagicPoints = 20;
		addSpell("HolyWaterBall", 3, 12, 3);
		break;
	default: // Thief
		mClassName = "Thief";
		mAccuracy += 7;
		mHitPoints += 12;
		mMaxHitPoints = 12;
		mExpPoints = 0;
		mNextLevelExp = 1000;
		mLevel = 1;
		mArmor.mName = "Black Scarf";
		mArmor.armorValue = 2;
		mGold = 0;
		mWeapon.mName = "Short Sword";
		mWeapon.mDamageRange.mLow = 1;
		mWeapon.mDamageRange.mHigh = 6;
		mMagicPoints = 20;
		mMaxMagicPoints = 20;
		break;
	}
}

bool Player::attack(Monster& monster)
{
	// Combat is turned based: display an options menu.  You can,
	// of course, extend this to let the player use an item,
	// cast a spell, and so on.
	int selection = 1;
	cout << "1) Attack, 2) Spell ";
	if (!mBag.empty())
		cout << "3)Use item ";
	cout << "4) Run: ";
	cin >> selection;
	cout << endl;

	switch (selection)
	{
	case 1:
		cout << "You attack an " << monster.getName() << " with a " << mWeapon.mName << endl;

		if (Random(0, 20) < mAccuracy)
		{
			int damage = Random(mWeapon.mDamageRange);

			int totalDamage = damage - monster.getArmor();

			if (totalDamage <= 0)
			{
				cout << "Your attack failed to penetrate " << "the armor." << endl;
			}
			else
			{
				cout << "You attack for " << totalDamage << " damage!" << endl;

				// Subtract from monster's hitpoints.
				monster.takeDamage(totalDamage);
			}
		}
		else
		{
			cout << "You miss!" << endl;
		}
		cout << endl;
		break;
	case 2:
		if (!mSpellBook.empty())
		{
			auto answer = 0;
			cout << "Spells available:" << endl;

			for (auto i = 0; i < mSpellBook.size(); ++i)
				if (mSpellBook[i].getMagicPointsRequired() <= mMagicPoints)
					cout << i << ") " << mSpellBook[i].getName() << endl;

			cout << "Choose your Spell: ";
			cin >> answer;
			if (0 <= answer && mSpellBook.size() > answer)
			{
				cout << "You attack an " << monster.getName() << " with a " << mSpellBook[answer].getName() << endl;
				if (Random(0, 10) < mAccuracy)
				{
					int damage = Random(mSpellBook[answer].getRange());
					mMagicPoints = mSpellBook[answer].getMagicPointsRequired();

					int totalDamage = damage - monster.getArmor();

					if (totalDamage <= 0)
					{
						cout << "Your attack failed to penetrate " << "the armor." << endl;
					}
					else
					{
						cout << "Your spell attack caused " << totalDamage << " damage!" << endl;

						// Subtract from monster's hitpoints.
						monster.takeDamage(totalDamage);
					}
				}
			}
		}
		break;
	case 3:
	{
		auto answer = 0;
		cout << "Items available:" << endl;

		for (auto i = 0; i < mBag.size(); ++i)
			cout << i << ") " << mBag[i].mAmount << "stk of " << mBag[i].mName<< endl;

		cout << "Choose your Item: ";
		cin >> answer;
		if (0 <= answer && mBag.size() > answer && mBag[answer].mAmount != 0)
		{
			if (mBag[answer].mPotion.mHigh > 0)
			{
				cout << "You attack an " << monster.getName() << " with a " << mBag[answer].mName << endl;

				int damage = mBag[answer].mPotion.mHigh;

				if (mBag[answer].mAmount == 0)
					if (mBag.size() > 1)
						mBag.erase(mBag.begin() + answer);
					else
						mBag.clear();

				int totalDamage = damage - monster.getArmor();

				if (totalDamage <= 0)
				{
					cout << "Your attack failed to penetrate " << "the armor." << endl;
				}
				else
				{
					cout << "Your " << mBag[answer].mName << " attack caused " << totalDamage << " damage!" << endl;

					// Subtract from monster's hitpoints.
					monster.takeDamage(totalDamage);
				}
			}
			if(mBag[answer].mPotion.mLow > 0)
			{
				cout << "You use the " << mBag[answer].mName << " to heal " << mBag[answer].mPotion.mLow << "of your health!!";
				mHitPoints = mBag[answer].mPotion.mLow;
				mBag[answer].mAmount -= 1;

				if (mBag[answer].mAmount == 0)
					if (mBag.size() > 1)
						mBag.erase(mBag.begin() + answer);
					else
						mBag.clear();
			}


		}
		break;

	}
	case 4:
		// 25 % chance of being able to run.
		int roll = Random(1, 4);

		if (roll == 1)
		{
			cout << "You run away!" << endl;
			return true;//<--Return out of the function.
		}
		else
		{
			cout << "You could not escape!" << endl;
			break;
		}
	}

	return false;
}

void Player::levelUp()
{
	if (mExpPoints >= mNextLevelExp)
	{
		cout << "You gained a level!" << endl;

		// Increment level.
		mLevel++;

		// Set experience points required for next level.
		mNextLevelExp = mLevel * mLevel * 1000;

		// Increase stats randomly.
		mAccuracy += Random(1, 3);
		mMaxHitPoints += Random(2, 6);
		mArmor.armorValue += Random(1, 2);
		mMaxMagicPoints += Random(1, 4);

		// Based on class
		if (mClassName == "Fighter")
		{
			mMaxHitPoints += Random(1, 4);
			mArmor.armorValue += Random(1, 2);
		}
		else if (mClassName == "Wizard")
		{
			mAccuracy += Random(1, 4);
			mMaxMagicPoints += Random(1, 4);
		}
		else if (mClassName == "Cleric")
		{
			mAccuracy += Random(1, 4);
			mMaxMagicPoints += Random(1, 4);
		}
		else
		{
			mArmor.armorValue += Random(1, 6);
		}

		// Give player full hitpoints when they level up.
		mHitPoints = mMaxHitPoints;
		mMagicPoints = mMaxMagicPoints;
	}
}

void Player::rest()
{
	cout << "Resting..." << endl;

	mHitPoints = mMaxHitPoints;
	mMagicPoints = mMaxMagicPoints;

	// TODO: Modify function so that random enemy encounters
	// are possible when resting.
}

void Player::viewStats() const
{
	cout << "PLAYER STATS" << endl;
	cout << "============" << endl;
	cout << endl;

	cout << "Name            = " << mName << endl;
	cout << "Race            = " << mRace << endl;
	cout << "Class           = " << mClassName << endl;
	cout << "Accuracy        = " << mAccuracy << endl;
	cout << "Hitpoints       = " << mHitPoints << endl;
	cout << "MaxHitpoints    = " << mMaxHitPoints << endl;
	cout << "XP              = " << mExpPoints << endl;
	cout << "XP for Next Lvl = " << mNextLevelExp << endl;
	cout << "Level           = " << mLevel << endl;
	cout << "Armor Name      = " << mArmor.mName << endl;
	cout << "Armor.armorValue = " << mArmor.armorValue << endl;
	cout << "Gold            = " << mGold << endl;
	cout << "Weapon Name     = " << mWeapon.mName << endl;
	cout << "Weapon Damage   = " << mWeapon.mDamageRange.mLow << "-" << mWeapon.mDamageRange.mHigh << endl;
	cout << endl;

	if (!mSpellBook.empty())
	{
		cout << "Spells available" << endl;
		for (int i = 0; i < mSpellBook.size(); ++i)
			cout << mSpellBook[i].getName() << endl;

	}
	if (!mBag.empty())
	{
		cout << "Own following potions" << endl;
		for (int i = 0; i < mBag.size(); ++i)
			cout << mBag[i].mAmount << " stk " << mBag[i].mName << endl;
	}


	cout << endl;
	cout << "END PLAYER STATS" << endl;
	cout << "================" << endl;
	cout << endl;


}

void Player::victory(int xp, int gold)
{
	cout << "You won the battle!" << endl;
	cout << "You win " << xp << " experience points!" << endl << endl;

	mExpPoints += xp;
	mGold += gold;
}

void Player::gameover(bool& done)
{
	cout << "You died in battle..." << endl;
	cout << endl;
	cout << "================================" << endl;
	cout << "GAME OVER!" << endl;
	cout << "================================" << endl;
	cout << "Press 'q' to quit: ";
	char q = 'q';
	cin >> q;
	cout << endl;
	done = true;
}

void Player::displayHitPoints() const
{
	cout << mName << "'s hitpoints = " << mHitPoints << endl;
}

void Player::addSpell(std::string name, int low, int high, int required)
{
	mSpellBook.push_back(Spell(name, low, high, required));
}

void Player::addSpell(Spell spell)
{
	mSpellBook.push_back(spell);
}

void Player::addItems(Item item)
{
	mBag.push_back(item);
}

void Player::addItems(std::string name, int amount)
{
	for (int i = 0; i < mBag.size(); ++i)
		if (mBag[i].mName == name)
			mBag[i].mAmount += amount;
}

void Player::changeArmor(Armor armor)
{
	mArmor.mName = armor.mName;
	mArmor.armorValue = armor.armorValue;
}

void Player::changeWeapon(Weapon weapon)
{
	mWeapon.mName = weapon.mName;
	mWeapon.mDamageRange.mLow = weapon.mDamageRange.mLow;
	mWeapon.mDamageRange.mHigh = weapon.mDamageRange.mHigh;
}

void Player::useGold(int gold)
{
	mGold -= gold;
}


