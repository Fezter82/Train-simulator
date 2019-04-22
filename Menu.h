//--------------------------------------
//Menu.h
//Headerfile for class Menu
//Andreas Lind, anli1606@student.miun.se
//--------------------------------------
#ifndef MenuH
#define MenuH
#include "MenuItem.h"
#include <vector>
#include <string>

class Menu
{
private:
	vector<MenuItem> menuItems;
	string menuHeadline;

public:
	//-----------------------Constructor
	Menu();
	Menu(string pText);

	//-----------------------Set and Get-functions
	void setMenuText(string pText);
	void addItem(string pText, bool pBool);
	void setAvailable(int idx);
	void disable(int idx);
	string getMenuHead() const { return menuHeadline; }
	int getMenuChoice();
	void editMenuItem(int idx, string tmp, bool choice);
	void setMenuItemOption(int idx, int pOpt);
	int getMenuItemOption(int idx) const;

	//-----------------------Print
	void printMenuItems() const;
	
};

#endif
