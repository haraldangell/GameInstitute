/*

Exercises

Gold Modification **Done**

Add an integer data member to the Player class that keeps track of the player’s amount of gold. After
each battle, generate a random gold reward that the player receives, in addition to the experience point
award. It would make sense for harder enemies (ogres, Orc lords) to provide a larger gold reward then
orcs and goblins. Be sure to also modify the Player::viewStats() method to display the current
amount of gold the player owns.

Character Races  **Done**

Modify the character creation process so that the user can choose a character race 
(e.g., dwarf, human,elf, halfling). 

Additionally, give statistical pros and cons to each race. For example, an elf may start the
game with a higher accuracy rating than a dwarf, but lower hit points. Conversely, a dwarf may start out
with more hit points than an elf, but less accuracy.

Leveling Up **Done**
The leveling up process we implemented in Section 5.3 does not take the player’s class into
consideration. Modify the leveling up process to reflect the class of the character. For example, a
“fighter” should gain more hit points than a “wizard.”

"Fighter"
"Wizard"
"Cleric"
"Thief"

Magic Points **Done**
Add an integer data member to the Player class that describes the number of magic points the player
currently has. Additionally, add a “max magic points” data member that describes the maximum
number of magic points the player can have at his/her current level. Be sure to also modify the
Player::viewStats() method to display the current amount of magic points the player has. Also,
be sure to increase the amount of magic points when the character levels up—and a “wizard” should
gain more hit points than a “fighter.”
After you have added magic points to the system, create a Spell structure and then instantiate a few
types of spell objects, such as
“magic missile,” “fireball,” and “shield.” You may want to implement the
Spell structure like so:
struct Spell
{
std::string mName;
Range mDamageRange;
int mMagicPointsRequired;
};
· mName: The name of the spell (e.g., “Fireball”).
· mDamageRange: The range of damage the spell inflicts.
· mMagicPointsRequired: The number of magic points required to cast the spell.

Finally, add a “cast spell” option to the combat menu, which allows the player to select and cast a spell
from a list of spells in his/her spell book. Be sure to verify that the player has enough magic points to
cast the spell. And also be sure to deduct the magic points required to cast the spell from the player’s
magic point count, after a spell is cast.


Random Encounters During Rest **Done**
In the current implementation, a player can rest to full hit points after every battle with no risk. Since
there is no such thing as a free lunch, add random encounters when resting– maybe a 25% chance of an
attack during rest.

A Store **Done**
Add a store to the map at some location. That is, in the main game loop do something like:
if( gameMap.getPlayerXPos() == 2 && gameMap.getPlayerYPos() == 3 )
{
Store store;
store.enter(gamePlayer);
}

Thus, if the player lands on the point (2, 4), the player enters the store. And Store is a class you define
which contains methods for displaying the store’s inventory, and for buying/selling weapons, armor, and
items. Note that you may want to write a small armor structure so that you can name armor:
struct Armor
{
std::string mName;
int armorValue;
};

Items
Allow the player to buy and carry healing potions, which can be used to heal the player during combat.

Moreover, allow the user to carry magic fireball potions, which can be used against enemies in battle.

You can add an Item array (you define the Item class) to the Player class for storing these items, or
use a std::vector to store them.
So that the player can use an item during combat, add a “use item” option to the combat menu.


Multiple Enemies
Modify the game so that the player can encounter several enemies at once. For example,
Map::checkRandomEncounter() can return a pointer to an array of enemies. Then update
Player::attack(Monster& monster) to instead take an array of monsters: Player::attack(Monster
monsters[]).



*/