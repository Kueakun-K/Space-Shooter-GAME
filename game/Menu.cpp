#include "Menu.h"
Menu::Menu(float width, float hight)
{
	if (!font.loadFromFile("Pixeboy.ttf"))
	{

	}
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Play");
	//menu[0].setOrigin(menu[0].getLocalBounds().width / 2), menu[0].getLocalBounds().hight / 2);
	menu[0].setPosition(sf::Vector2f((width / 2), hight / (MAX_ITEMS + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Leaderboard");
	menu[1].setPosition(sf::Vector2f(width / 2, hight / (MAX_ITEMS + 1) * 2));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Exit");
	menu[2].setPosition(sf::Vector2f(width / 2, hight / (MAX_ITEMS + 1) * 3));

}
Menu::~Menu()
{

}

void Menu::Draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}

void Menu::moveUp()
{
	if (mainMenuSelected - 1 >= 0)
	{
		menu[mainMenuSelected].setFillColor(sf::Color::White);
			mainMenuSelected--;
			menu[mainMenuSelected].setFillColor(sf::Color::Red);
	}
}

void Menu::moveDown()
{
	if (mainMenuSelected + 1 < MAX_ITEMS)
	{
		menu[mainMenuSelected].setFillColor(sf::Color::White);
		mainMenuSelected++;
		menu[mainMenuSelected].setFillColor(sf::Color::Red);
	}
}