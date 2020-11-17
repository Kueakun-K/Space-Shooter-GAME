#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <math.h>
#include <cstdlib>
#include <vector>
#include <SFML/OpenGL.hpp>
#include "Menu.h"
#include <time.h>
#include<sstream>

using namespace sf;

void shot();
void erase();
int chk_1[6] = { 0 };
int chk_2[6] = { 0 };
clock_t start = -0.5, end = 0;

Texture monsterTexture;
//Texture playerTexture;
Texture BULLET;
//Sprite shapeSprite;
//Vector2f spawnPoint = { 0.f, 0.f };

class Player
	{
public:
		Sprite shape;
		Texture *texture;
		
	
		Player(Texture *texture)
		{
			
	
			this->texture = texture;
			this->shape.setTexture(*texture);
			this->shape.setPosition(300,600);
			//this->shape.setScale(50.f, 50.f);
		}
	
		~Player() {}
	
	};
	

class Monster
{
public:
	Sprite monster;
	int hit = 0;

	void set(int x, int y)
	{
		monsterTexture.loadFromFile("img/rock.png");
		monster.setTexture(monsterTexture);
		monster.setTextureRect(sf::IntRect(0, 0, 50, 50));
		monster.setPosition(x, y);
	}
	
};


class Bullet {
public:
	sf::Sprite bullet;
	void set(int x, int y)
	{
		BULLET.loadFromFile("img/bullet.png");
		bullet.setTexture(BULLET);
		bullet.setTextureRect(sf::IntRect(0, 0, 50, 50));
		bullet.setPosition(x, y);
	}
};


Bullet bullet[6];
Monster monster[6];

int main()
{
	
	srand(time(NULL));
	
	RenderWindow window(sf::VideoMode(650, 720),"Game" );
	window.setFramerateLimit(60);

	Texture BackgroundTexture;
	Sprite background;
	Vector2u TextureSize;
	Vector2u WindowSize;

	//Texture playerTexture;
	//RectangleShape player(sf::Vector2f(50.0f, 50.0f));
	//playerTexture.loadFromFile("img/spaceship1.png");
	//spriteSizeX = playerTexture.getSize().x / 2;
	//spriteSizeY = playerTexture.getSize().y / 4;
	//shapeSprite.setTexture(playerTexture);
	//shapeSprite.setTextureRect(sf::IntRect(0, 0, 58, 98));
	//shapeSprite.setTextureRect(sf::IntRect(0, 0, spriteSizeX, spriteSizeY));
	//shapeSprite.setPosition(spawnPoint);

	if (!BackgroundTexture.loadFromFile("img/spae.png"))
	{
		return -1;
	}
	else
	{
		TextureSize = BackgroundTexture.getSize(); //Get size of texture.
		WindowSize = window.getSize();             //Get size of window.

		float ScaleX = (float)WindowSize.x / TextureSize.x;
		float ScaleY = (float)WindowSize.y / TextureSize.y;     //Calculate scale.

		background.setTexture(BackgroundTexture);
		background.setScale(ScaleX, ScaleY);      //Set scale.   
	}


	


	//icon
	Image icon;
	if (!icon.loadFromFile("img/icon.png"))
	{
		return -1;
	}
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	Texture playerTex;
	playerTex.loadFromFile("img/spaceship1.png");

	Texture enemyTex;
	enemyTex.loadFromFile("img/rock.png");

	//Player init
	Player player(&playerTex);
	

	while (window.isOpen())
	{
		shot();
		erase();
		Event event;
		while (window.pollEvent(event))
		{
			
			if (event.type == Event::Closed)
				window.close();
		}
		float x, y;
		x = player.shape.getPosition().x;
		y = player.shape.getPosition().y;

		
		float dif1 = (float)(end - start) / CLOCKS_PER_SEC;
		
		//player
		if (Keyboard::isKeyPressed(Keyboard::W))
			player.shape.move(0.f, -8.f);
		if (Keyboard::isKeyPressed(Keyboard::A))
			player.shape.move(-8.f, 0.f);
		if (Keyboard::isKeyPressed(Keyboard::S))
			player.shape.move(0.f, 8.f);
		if (Keyboard::isKeyPressed(Keyboard::D))
			player.shape.move(8.f, 0.f);
		if (Keyboard::isKeyPressed(Keyboard::Space) && dif1 > 0.5)
			for (int i = 0; i < 6; i++) {
				if (chk_1[i] == 0) {
					bullet[i].set(x + 20, y - 20);
					chk_1[i] = 1;
					start = clock();
					break;
				}
				
			}
		end = clock();
		float dif2 = (float)(end - start) / CLOCKS_PER_SEC;
		//monster
		for (int i = 0; i < 6; i++) {
			if (chk_2[i] == 0 && dif2 > 1) {
				monster[i].set(rand() % 600, -30);
				chk_2[i] = 1;
				start = clock();
				break;
			}
		}
			

		//collision
		for (int i = 0; i < 6; i++) {
			if (monster[i].monster.getGlobalBounds().intersects(player.shape.getGlobalBounds())) {
				monster[i].monster.setPosition(sf::Vector2f(0, 0));
			}
		}
			/*
			//Bullets
			for (size_t i = 0; i < player.bullets.size(); i++)
			{
				//Move
				player.bullets[i].shape.move(20.f, 0.f);

				//Out of window bounds
				if (player.bullets[i].shape.getPosition().x > window.getSize().x)
				{
					player.bullets.erase(player.bullets.begin() + i);
					break;
			}
			*/
				/*
				//Enemy collision
				for (size_t k = 0; k < enemies.size(); k++)
				{
					if (player.bullets[i].shape.getGlobalBounds().intersects(enemies[k].shape.getGlobalBounds()))
					{
						if (enemies[k].HP <= 1)
						{
							//score += enemies[k].HPMax;					
							enemies.erase(enemies.begin() + k);
						}
						else
							enemies[k].HP--; //ENEMY TAKE DAMAGE

						player.bullets.erase(player.bullets.begin() + i);
						break;
					}
				}
			}
		*/

		
				
		
			

		//Collision with window
		if (player.shape.getPosition().x <= 0) //Left
			player.shape.setPosition(0.f, player.shape.getPosition().y);
		if (player.shape.getPosition().x >= window.getSize().x - player.shape.getGlobalBounds().width) //Right
			player.shape.setPosition(window.getSize().x - player.shape.getGlobalBounds().width, player.shape.getPosition().y);
		if (player.shape.getPosition().y <= 0) //Top
			player.shape.setPosition(player.shape.getPosition().x, 0.f);
		if (player.shape.getPosition().y >= window.getSize().y - player.shape.getGlobalBounds().height) //Bottom
			player.shape.setPosition(player.shape.getPosition().x,window.getSize().y - player.shape.getGlobalBounds().height);

		//Draw
		window.clear();

		//menu
		//menu.Draw(window);

		
		window.draw(background);
		//player
		window.draw(player.shape);

		for (int i = 0; i < 6; i++) {
			if (chk_1[i] == 1) {
				window.draw(bullet[i].bullet);
			}
		}
		
		//enemy
		
		for (int i = 0; i < 6; i++) {
			if (chk_2[i] == 1) {
				window.draw(monster[i].monster);
			}
		
		}

		
		
		window.display();
	}
	return 0;
}

void shot()
{
	for (int i = 0; i < 6; i++) {
		if (chk_1[i] == 1) {
			bullet[i].bullet.move(0, -5);
		}
		if (bullet[i].bullet.getPosition().y <0) {
			chk_1[i] = 0;
		}
	}
}

void erase()
{
	for (int i = 0; i < 6; i++) {
		if (chk_2[i] == 1) {
			monster[i].monster.move(0, 2.2);
		}
		if (monster[i].monster.getPosition().y > 700) {
			chk_2[i] = 0;
		}
	}
	
}
