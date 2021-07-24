
#include "Spell.h"
#include <iostream>

Spell::Spell()
{
	mName = "Default";
	mDamageRange.mLow = 0;
	mDamageRange.mHigh = 0;
	mMagicPointsRequired = 0;
}

Spell::Spell(std::string name, int low, int high, int required)
{
	mName = name;
	mDamageRange.mLow = low;
	mDamageRange.mHigh = high;
	mMagicPointsRequired = required;
}

Spell::~Spell()
{
}

std::string Spell::getName() const
{
	return mName;
}

Range Spell::getRange() const
{
	return mDamageRange;
}

int Spell::getMagicPointsRequired() const
{
	return mMagicPointsRequired;
}

void Spell::setName(std::string name)
{
	mName = name;
}

void Spell::setDamageRange(int low, int high)
{
	mDamageRange.mLow = low;
	mDamageRange.mHigh = high;
}

void Spell::setMagicPointsRequired(int required)
{
	mMagicPointsRequired = required;
}


