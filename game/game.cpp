#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <math.h>
#include <cstdlib>

using namespace sf;

class Player
{
public:
	Sprite shape;
	Texture *texture;
	int HP;
	int HPMax;

	Player(Texture *texture)
	{
		this->HPMax = 10;
		this->HP = this->HPMax;

		this->texture = texture;
		this->shape.setTexture(*texture);
	}
	~Player(){}
};

class Enemy
{

};

class Bullet
{

};

int main()
{
	srand(time(NULL));

	RenderWindow window(sf::VideoMode(1080, 720), "Thunder Stike",Style::Default);
	window.setFramerateLimit(60);

	Texture playerTex;
	playerTex.loadFromFile("img/spaceship.png");

	Texture enemyTex;
	playerTex.loadFromFile("img/rock.png");

	Texture bulletTex;
	playerTex.loadFromFile("img/bullet.png");

	Player player(&playerTex);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear();

		window.draw(player.shape);
		
		window.display();
	}
	return 0;
}