//--------------------------------------
//MenuItem.h
//Headerfil for class MenuItem
//Andreas Lind, anli1606@student.miun.se
//--------------------------------------
#ifndef MenuItemH
#define MenuItemH

#include <string>
using namespace std;

class MenuItem
{
private:
	string menuText;
	bool enabled;
	int option;

public:
	//-----------------------Construktor
	MenuItem();

	//-----------------------Set och Get-functions
	void setMenuText(string pText, bool pBool);
	void setEnabled();
	void setDisabled();
	string getMenuText() const { return menuText; }
	bool getEnabled() const;
	int getOption() const { return option; }
	void setOption(int pOpt) { option = pOpt; }
};

#endif
