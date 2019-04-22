//------------------------------------------------------
//MenuItem.cpp
//Definition file of member functions for class MenuItem
//Andreas Lind, anli1606@student.miun.se
//------------------------------------------------------
#include "MenuItem.h"
//-------------------------------------------------------------------------------------------
// Default constructor
//-------------------------------------------------------------------------------------------
MenuItem::MenuItem()
{
	menuText = "";
}
//-------------------------------------------------------------------------------------------
// Initializing constructor
//-------------------------------------------------------------------------------------------
void MenuItem::setMenuText(string pText, bool pBool)
{
	menuText = pText;
	enabled = pBool;
	option = 1;
}
//-------------------------------------------------------------------------------------------
// setEnabled
// Set menu selection to be enabled (= selectable)
//-------------------------------------------------------------------------------------------
void MenuItem::setEnabled()
{
	enabled = true;
}
//-------------------------------------------------------------------------------------------
// setDisabled
// Set menu selection to be disabled(= false = not selectable)
//-------------------------------------------------------------------------------------------
void MenuItem::setDisabled()
{
	enabled = false;
}
//-------------------------------------------------------------------------------------------
// getEnabled
// Read if menu selection is true or false (= selectable or not selectable)
//-------------------------------------------------------------------------------------------
bool MenuItem::getEnabled() const
{
	if (enabled == true)
		return true;
	else
		return false;
}