#ifndef SPELL_H
#define SPELL_H

#include <string>
#include "Range.h"

class Spell
{
public:
	Spell();
	Spell(std::string name, int low, int high, int required);
	~Spell();

	std::string getName()const;
	Range getRange()const;
	int getMagicPointsRequired()const;

	void setName(std::string name);
	void setDamageRange(int low, int high);
	void setMagicPointsRequired(int required);


private:
	std::string mName;
	Range mDamageRange;
	int mMagicPointsRequired;
};

#endif