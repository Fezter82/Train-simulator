//------------------------------------------------------
// Menu.cpp
// Definition file of class Menu
// Andreas Lind, anli1606@student.miun.se
//------------------------------------------------------
#include "Menu.h"
#include <iostream>
using namespace std;
//-------------------------------------------------------------------------------------------
// Default constructor
//-------------------------------------------------------------------------------------------
Menu::Menu()
{
	menuHeadline = "";
}
//-------------------------------------------------------------------------------------------
// Initializing constructor
//-------------------------------------------------------------------------------------------
Menu::Menu(string pText)
{
	menuHeadline = pText;
}
//-------------------------------------------------------------------------------------------
// setMenuText
// Set data member menuHeadline to the value of pText
//-------------------------------------------------------------------------------------------
void Menu::setMenuText(string pText)
{
	menuHeadline = pText;
}
//-------------------------------------------------------------------------------------------
// addItem
// add menu-object to menu
//-------------------------------------------------------------------------------------------
void Menu::addItem(string pText, bool pBool)
{
	MenuItem newItem;
	newItem.setMenuText(pText, pBool); //sätt datamedlemmars värden
	menuItems.push_back(newItem); //pusha in det i menyvectorn
}
//-------------------------------------------------------------------------------------------
// setAvailable
// 
// If menu selection is inactive, it will be activated
//-------------------------------------------------------------------------------------------
void Menu::setAvailable(int idx)
{
	menuItems[idx].setEnabled();
}
//-------------------------------------------------------------------------------------------
// setAvailable
// If menu selection is active, it is set to inactive
//-------------------------------------------------------------------------------------------
void Menu::disable(int idx)
{
	menuItems[idx].setDisabled();
}
//-------------------------------------------------------------------------------------------
// printMenuItems
// print menus
//-------------------------------------------------------------------------------------------
void Menu::printMenuItems() const
{
	int count = 0;

	cout << endl << menuHeadline << endl;

	for (auto idx : menuItems)
	{
			count++;
			cout << count << ". ";
			cout << idx.getMenuText() << endl;
	}
}
//-------------------------------------------------------------------------------------------
// getMenuChoice
// Read the user's menu choice and give error message if choice is not active / selectable
//-------------------------------------------------------------------------------------------
int Menu::getMenuChoice()
{
	int tmp;
	bool again = true;

	do {
		cout << endl << "My choice: ";
		cin >> tmp;
		cin.get();
		
		if (tmp > menuItems.size())
			throw(string("Menu choice is not available!!"));

		if (menuItems[tmp-1].getEnabled() == true) //Om menyval är valbart avslutas loopen
			again = false;
		else
		{
			cout << endl << "Menu option is not available. Try again!" << endl;
		}

	} while (again == true);

	return tmp;
}
//-------------------------------------------------------------------------------------------
// editMenuItem
// change text in menuItem
//-------------------------------------------------------------------------------------------
void Menu::editMenuItem(int idx, string tmp, bool choice)
{
	menuItems[idx].setMenuText(tmp, choice);
}
//-------------------------------------------------------------------------------------------
// setMenuItemOption
// set data member 'option'
//-------------------------------------------------------------------------------------------
void Menu::setMenuItemOption(int idx, int pOpt)
{
	menuItems[idx].setOption(pOpt);
}
//-------------------------------------------------------------------------------------------
// getMenuItemOption
// get data member 'option'
//-------------------------------------------------------------------------------------------
int Menu::getMenuItemOption(int idx) const
{
	return menuItems[idx].getOption();
}