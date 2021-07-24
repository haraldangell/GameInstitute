
#ifndef SPELL_H
#define SPELL_H

#include <string>
#include "Range.h"

struct Spell
{
	std::string mName;
	Range mDamageRange;
	int mMagicPointsRequired;
};

#endif