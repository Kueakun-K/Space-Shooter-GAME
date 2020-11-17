#pragma once
#include <SFML/Graphics.hpp>
#define MAX_ITEMS 3

class Menu
{
public:
	Menu(float width, float hight);
	~Menu();

	void Draw(sf::RenderWindow& window);
	void moveUp();
	void moveDown();
	int GetPressedItem() { return mainMenuSelected; }

/*	
	int mainMenuPressed()
	{
		return mainMenuSelected;
	}
*/	

private:
	int mainMenuSelected = 0;
	sf::Font font;
	sf::Text menu[MAX_ITEMS];
};