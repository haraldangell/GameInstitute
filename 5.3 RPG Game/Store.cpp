#include "Store.h"
#include "Inventory.h"
#include <iostream>
using namespace std;

Store::Store()
{
}

void Store::enter(Player& player, std::string name)
{

	bool leave = false;

	vector<InventoryWeapon> weapons;
	weapons.push_back(InventoryWeapon("Excalibur",  1, 20,5000 ));
	weapons.push_back(InventoryWeapon("Zulfiqar", 1, 15, 2500));
	weapons.push_back(InventoryWeapon("Joyeuse", 1, 12, 1800));

	vector<InventoryArmor> armors;
	armors.push_back(InventoryArmor("Crusader armour", 10, 4000));
	armors.push_back(InventoryArmor("Plate armour", 8, 3000));
	armors.push_back(InventoryArmor("Lights armour", 6, 2000));
	
	vector<InventorySpell> spells;
	spells.push_back(InventorySpell("Death Nova",2, 45,3500));
	spells.push_back(InventorySpell("Ice Tempest",2, 35, 2500));
	spells.push_back(InventorySpell("Soul Bomb", 2, 25, 1500));

	vector<InventoryItem> items;
	items.push_back(InventoryItem("Water of life", "Healing", 45, 0, 50, 750));
	items.push_back(InventoryItem("Purifing water", "Healing", 25, 0, 50, 500));
	items.push_back(InventoryItem("FireBomb", "Damage", 0, 25, 50, 350));

	while (!leave)
	{
		mName = name;
		auto pick = 0;
		cout << "-----------------------------" << endl;
		cout << "Welcome to " << mName << endl;
		cout << "-----------------------------" << endl;

		cout << endl;

		cout << "What do you like to buy today?" << endl;

		cout << "You have " << player.getGold() << " gold" << endl;		
		cout << " 1) Weapon 2) Armor 3) Spells 4) Items 99) Leave Store: ";

		cin >> pick;
		switch (pick)
		{
		case 1:
		{
			WEAPONS:
			auto answer = 0;
			
			cout << "Would you like to buy a weapon today?" << endl;
			for (auto i = 0; i < 3; ++i)
				cout << i << " " << weapons[i].mWeapon.mName << " " << weapons[i].mPrice << " gold" << endl;
			cout << "Choose the number in front of the weapon to choose it or 99 to leave: ";
			cin >> answer;
			if (answer == 99) break;
			if(0 <= answer && answer <= weapons.size())
				if (player.getGold() >= weapons[answer].mPrice)
				{
					player.changeWeapon(weapons[answer].mWeapon);
					player.useGold(weapons[answer].mPrice);
					cout << "You just bought " << weapons[answer].mWeapon.mName;
				}
				else
				{
					cout << "You don't have enough gold" << endl;
				}
			goto WEAPONS;
			break;
			

		}

		case 2:
		{
			ARMORS:
			auto answer = 0;


			cout << "Would you like to buy a armor today?" << endl;
			for (auto i = 0; i < 3; ++i)
				cout << i << " " << armors[i].mArmor.mName << " " << armors[i].mPrice << " gold" << endl;
			cout << "Choose the number in front of the armor to choose it or 99 to leave: ";
			cin >> answer;
			if (answer == 99) break;
			if (0 <= answer && answer <= armors.size())
				if (player.getGold() >= armors[answer].mPrice)
				{
					player.changeArmor(armors[answer].mArmor);
					player.useGold(armors[answer].mPrice);
					cout << "You just bought " << armors[answer].mArmor.mName << endl;
				}
				else
				{
					cout << "You don't have enough gold" << endl;
				}
			goto ARMORS;
			break;
		}
		case 3:
		{
			SPELLS:
			auto answer = 0;


			cout << "Would you like to buy a spell today?" << endl;
			for (auto i = 0; i < 3; ++i)
				cout << i << " " << spells[i].mSpell.getName() << " " << spells[i].mPrice << " gold" << endl;
			cout << "Choose the number in front of the spell to choose it or 99 to leave: ";
			cin >> answer;
			if (answer == 99) break;
			if (0 <= answer && answer <= spells.size())
				if (player.getGold() >= spells[answer].mPrice)
				{
					player.addSpell(spells[answer].mSpell);
					player.useGold(spells[answer].mPrice);
					cout << "You just bought " << spells[answer].mSpell.getName() << endl;
				}
				else
				{
					cout << "You don't have enough gold" << endl;
				}
			goto SPELLS;
			break;

		}
		case 4:
		{
			ITEMS:
		 	int answer = 0;
			int amount = 0;


			cout << "Would you like to buy a potions today?" << endl;
			for (auto i = 0; i < 3; ++i)
				cout << i << " " << items[i].mItem.mName << " " << items[i].mPrice << " gold" << endl;

			cout << "Choose the number in front of the spell to choose it or 99 to leave: ";
			cin >> answer;
			if (answer == 99) break;

			if (0 <= answer && answer <= items.size())
			{
				if (player.getGold() >= items[answer].mPrice)
				{

					auto abletobuy = player.getGold() / items[answer].mPrice;
					cout << "You can afford " << abletobuy << "stk and there is " << items[answer].mItem.mAmount << "stk availible" <<   endl;
					cout << "How many potions do you want to buy?";
					cin >> amount;

					InventoryItem * tempItem = new InventoryItem(
						items[answer].mItem.mName,
						items[answer].mItem.mType, 
						items[answer].mItem.mPotion.mLow, 
						items[answer].mItem.mPotion.mHigh, 
						amount,
						items[answer].mPrice
					);

					
					if (abletobuy >= amount && items[answer].mItem.mAmount >= amount)
					{
						if (player.getName() == tempItem->mItem.mName)
							player.addItems(tempItem->mItem.mName, amount);
						else
							player.addItems(tempItem->mItem);

						player.useGold(tempItem->mPrice * amount);
						items[answer].mItem.mAmount -= amount;
					}
					
					cout << "You just bought " << tempItem->mItem.mAmount << "stk of" << tempItem->mItem.mName << endl;
					delete tempItem;
					tempItem = nullptr;
				}
				else
				{
					cout << "You don't have enough gold" << endl;
				}
				goto ITEMS;
			}



			break;

		}
		case 99:
			leave = true;
			break;
		}
	}

}
