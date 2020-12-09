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

using namespace sf;

void shot();
void enemymovewave1();
void enemymovewave2();
void enemymovewave3();
void enemyshotwave12();
void enemyshotwave345();
void check();
void enemymoveRL();
void enemybossmove();
void enemybossshot();
int chk_1[6] = { 0 };  //bullet
int chk_3[19] ={ 0 };  //enemy
int chk_4[19] ={ 0 };  //enemyBullet
int chk_5[6] = { 0 };  //enemyboss
int chk_6[18] ={ 0 };  //enemybossBullet
int enemyCount = 0;
int wave = 3;
bool enemymove1 = true;
bool enemymove2[19] = {};
bool right = true;
bool left = false;
bool bossmove = false;

int startgame = 0;
clock_t start = -0.5, end = 0;
clock_t start1 = -0.5, end1 = 0;
clock_t start2 = -0.5, end2 = 0;

Texture BULLET;
Texture enemyTexture;
Texture enemybossTexture;

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
		}
		~Player() {}
	};


class Bullet {
public:
	sf::Sprite bullet;
	void set(int x, int y)
	{
		//BULLET.loadFromFile("img/bullet.png");
		bullet.setTexture(BULLET);
		bullet.setTextureRect(sf::IntRect(0, 0, 20, 20));
		bullet.setPosition(x, y);
	}
};

class Enemy
{
public:
	Sprite enemy;
	int enemyhp = 2;
	void set(int x, int y)
	{
		enemyTexture.loadFromFile("img/space_enemy.png");
		enemy.setTexture(enemyTexture);
		enemy.setTextureRect(sf::IntRect(0, 0, 70, 70));
		enemy.setPosition(x, y);
	}
};

class EnemyBoss
{
public:
	Sprite enemyboss;
	//int hit = 0;
	void set(int x, int y)
	{
		enemybossTexture.loadFromFile("img/enemyboss.png");
		enemyboss.setTexture(enemybossTexture);
		enemyboss.setTextureRect(sf::IntRect(0, 0, 130, 130));
		enemyboss.setPosition(x, y);
	}
};

class enemyBullet {
public:
	sf::Sprite enemybullet;
	void set(int x, int y)
	{
		//BULLET.loadFromFile("img/bullet.png");
		enemybullet.setTexture(BULLET);
		enemybullet.setTextureRect(sf::IntRect(0, 0, 20, 20));
		enemybullet.setPosition(x, y);
	}
};

class enemybossBullet {
public:
	sf::Sprite enemybossbullet;
	void set(int x, int y)
	{
		//BULLET.loadFromFile("img/bullet.png");
		enemybossbullet.setTexture(BULLET);
		enemybossbullet.setTextureRect(sf::IntRect(0, 0, 20, 20));
		enemybossbullet.setPosition(x, y);
	}
};

Enemy enemy[19];
Bullet bullet[6];
enemyBullet enemybullet[19];
EnemyBoss enemyboss[6];
enemybossBullet enemybossbullet[18];

int main()
{
	RenderWindow window(sf::VideoMode(1000, 800), "MENU MODE", sf::Style::Close | sf::Style::Resize);
	Menu menu(window.getSize().x, window.getSize().y);

	Texture texture;
	if (!texture.loadFromFile("img/spacee.png")) {
	}
	Sprite backgroundmenu;
	backgroundmenu.setTexture(texture);

strgame:
	if (startgame == 1) {
	srand(time(NULL));

	RenderWindow window(sf::VideoMode(1000, 800), "Game");
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);
	Menu menu(window.getSize().x, window.getSize().y);

	Texture BackgroundTexture;
	Sprite background;
	Vector2u TextureSize;
	Vector2u WindowSize;

	int HP = 3;

	//font
	Font font;
	if (!font.loadFromFile("Pixeboy.ttf"))
	{
		return -1;
	}

		//score
		int scoreCount = 0;
		Text scoreText;
		scoreText.setPosition(10, 0);
		scoreText.setFont(font);
		scoreText.setFillColor(Color::White);

		//wave
		Text waveText;
		waveText.setPosition(70, 0);
		waveText.setFont(font);
		waveText.setFillColor(Color::White);

		//testposition
		Text position;
		position.setPosition(150, 0);
		position.setFont(font);
		position.setFillColor(Color::White);

		if (!BackgroundTexture.loadFromFile("img/spacee.png"))
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

		//BG move
		BackgroundTexture.setRepeated(true);
		Shader parallaxShader;
		parallaxShader.loadFromMemory
		("uniform float offset;"

			"void main() {"
			"    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;"
			"    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;"
			"    gl_TexCoord[0].y = gl_TexCoord[0].y + offset;" // magic
			"    gl_FrontColor = gl_Color;"
			"}"
			, Shader::Vertex);
		float offset = 0.f;
		Clock clock1;

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
			check();
			Event event;
			while (window.pollEvent(event))
			{

				if (event.type == Event::Closed)
					window.close();
			}
			float x, y,z;
			x = player.shape.getPosition().x;
			y = player.shape.getPosition().y;
			z = enemyboss[0].enemyboss.getPosition().y;
			
			end = clock();
			float dif1 = (float)(end - start) / CLOCKS_PER_SEC;

			//player control
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
						bullet[i].set(x + 20, y - 15);
						chk_1[i] = 1;
						start = clock();
						break;
					}
				}

			
			//collision bullet&enemybullet
			for (int i = 0; i < 6; i++) {
				for (int k = 0; k < 19; k++) {
					if (bullet[i].bullet.getGlobalBounds().intersects(enemybullet[k].enemybullet.getGlobalBounds())) {
						bullet[i].bullet.setPosition(sf::Vector2f(-40, -40));
						enemybullet[k].enemybullet.setPosition(sf::Vector2f(-80, 150));
						chk_4[k] = 0;
					}
				}
			}

			//collision player&enemybullet
			for (int k = 0; k < 19; k++) {
				if (player.shape.getGlobalBounds().intersects(enemybullet[k].enemybullet.getGlobalBounds())) {
					enemybullet[k].enemybullet.setPosition(sf::Vector2f(-80, 150));
					chk_4[k] = 0;
					//HP--;
				}
			}


			//collision bullet&enemy
			for (int i = 0; i < 6; i++) {
				for (int k = 0; k < 19; k++) {
					if (enemy[k].enemy.getGlobalBounds().intersects(bullet[i].bullet.getGlobalBounds())) {
						bullet[i].bullet.setPosition(sf::Vector2f(-40, -40));
						enemy[k].enemy.setPosition(sf::Vector2f(-800, 150));
						scoreCount++;
						enemymove2[k] == false;
						//chk_3[k] = 0;
						chk_4[k] = 0;
						enemyCount++;
					}
				}
			}

			//collision player&enemy
			for (int k = 0; k < 19; k++) {
				if (player.shape.getGlobalBounds().intersects(enemy[k].enemy.getGlobalBounds())) {
					enemy[k].enemy.setPosition(sf::Vector2f(-800, 150));
					//chk_3[k] = 0;
					chk_4[k] = 0;
					scoreCount++;
					enemyCount++;
					//HP--;
				}
			}

			//Collision with window
			if (player.shape.getPosition().x <= 0) //Left
				player.shape.setPosition(0.f, player.shape.getPosition().y);
			if (player.shape.getPosition().x >= window.getSize().x - player.shape.getGlobalBounds().width) //Right
				player.shape.setPosition(window.getSize().x - player.shape.getGlobalBounds().width, player.shape.getPosition().y);
			if (player.shape.getPosition().y <= 0) //Top
				player.shape.setPosition(player.shape.getPosition().x, 0.f);
			if (player.shape.getPosition().y >= window.getSize().y - player.shape.getGlobalBounds().height) //Bottom
				player.shape.setPosition(player.shape.getPosition().x, window.getSize().y - player.shape.getGlobalBounds().height);


			if (wave == 1) {
				enemymovewave1();
				enemyshotwave12();
				//enemy
				for (int i = 0; i < 5; i++) {
					if (chk_3[i] == 0) {
						enemy[i].set(((140 * i) + 170), -90);
						chk_3[i] = 1;
						break;
					}
				}

				end1 = clock();
				float dif3 = (float)(end1 - start1) / CLOCKS_PER_SEC;
				//enemyBullet 
				if (dif3 > 3) {
					for (int i = 0; i < 5; i++) {
						if (chk_4[i] == 0 && enemy[i].enemy.getPosition().y == 80) {
							enemybullet[i].set(enemy[i].enemy.getPosition().x + 23, enemy[i].enemy.getPosition().y + 58);
							chk_4[i] = 1;
						}
						start1 = clock();
					}dif3 = 0;
				}
			}

			if (wave == 2) {
				enemymovewave2();
				enemyshotwave12();
				enemymoveRL();
				//enemy
				for (int i = 5; i < 10; i++) {
					if (chk_3[i] == 0) {
						enemy[i].set(((140 * (i%5)) + 170), -90);
						chk_3[i] = 1;
						break;
					}
				}

				end1 = clock();
				float dif3 = (float)(end1 - start1) / CLOCKS_PER_SEC;
				//enemyBullet 
				if (dif3 > 3) {
					for (int i = 5; i < 10; i++) {
						if (chk_4[i] == 0 && enemy[i].enemy.getPosition().y == 80) {
							enemybullet[i].set(enemy[i].enemy.getPosition().x + 23, enemy[i].enemy.getPosition().y + 58);
							chk_4[i] = 1;
						}
						start1 = clock();
					}dif3 = 0;
				}
			}

			if (wave == 3) {
				enemymovewave3();
				enemyshotwave345();
				enemybossmove();
				enemybossshot();
				//enemymoveRL();
				//enemy
				for (int i = 10; i < 14; i++) {
					if (chk_3[i] == 0) {
						if (i <12) {
							enemy[i].set(((140 * (i % 5)) + 190), -90);
							chk_3[i] = 1;
							break;
						}
						if (i >11) {
							enemy[i].set(((140 * (i % 5)) + 310), -90);
							chk_3[i] = 1;
							break;
						}
					}
				}

				end1 = clock();
				float dif3 = (float)(end1 - start1) / CLOCKS_PER_SEC;
				//enemyBullet 
				if (dif3 > 3) {
					for (int i = 10; i < 14; i++) {
						if (chk_4[i] == 0 && enemy[i].enemy.getPosition().y == 100) {
							enemybullet[i].set(enemy[i].enemy.getPosition().x + 23, enemy[i].enemy.getPosition().y + 58);
							chk_4[i] = 1;
						}
						start1 = clock();
					}dif3 = 0;
				}
				//enemyboss
				for (int i = 0; i < 1; i++) {
					if (chk_5[i] == 0) {
						enemyboss[i].set(430, -200);
						chk_5[i] = 1;
						//break;
					}
				}
				//enemybossbullet
				end2 = clock();
				float dif4 = (float)(end2 - start2) / CLOCKS_PER_SEC;
				if (dif4 > 3) {
					for (int i = 0; i < 3; i++) {
						if (chk_6[i] == 0 && enemyboss[0].enemyboss.getPosition().y == 30) {
							if (i == 0) {
								enemybossbullet[i].set(enemyboss[0].enemyboss.getPosition().x + 21, enemyboss[i].enemyboss.getPosition().y + 70);
								chk_6[i] = 1;
							}
							if (i == 1) {
								enemybossbullet[i].set(enemyboss[0].enemyboss.getPosition().x + 53.5, enemyboss[i].enemyboss.getPosition().y + 165);
								chk_6[i] = 1;
							}
							if (i == 2) {
								enemybossbullet[i].set(enemyboss[0].enemyboss.getPosition().x + 85, enemyboss[i].enemyboss.getPosition().y + 100);
								chk_6[i] = 1;
							}
						}
						start2 = clock();
					}dif4 = 0;
				}
			}
			
			
			//BG move
			parallaxShader.setUniform("offset", offset -= clock1.restart().asSeconds() / 50);

			//Draw
			window.clear();

			//menu
			//menu.Draw(window);

			//background
			window.draw(background, &parallaxShader);

			//player
			if (HP > 0) {
				window.draw(player.shape);
			}

			//bullet
			for (int i = 0; i < 6; i++) {
				if (chk_1[i] == 1) {
					window.draw(bullet[i].bullet);
				}
			}


			//enemy
			for (int i = 0; i < 19; i++) {
				if (chk_3[i] == 1) {
					window.draw(enemy[i].enemy);
				}
			}

			//enemyboss
			for (int i = 0; i < 6; i++) {
				if (chk_5[i] == 1) {
					window.draw(enemyboss[i].enemyboss);
				}
			}

			//enemybullet
			for (int i = 0; i < 19; i++) {
				if (chk_4[i] == 1) {
					window.draw(enemybullet[i].enemybullet);
				}
			}

			//enemybossbullet
			for (int i = 0; i < 18; i++) {
				if (chk_6[i] == 1) {
					window.draw(enemybossbullet[i].enemybossbullet);
				}
			}

			//score
			scoreText.setString(std::to_string(scoreCount));
			window.draw(scoreText);

			//wave
			waveText.setString(std::to_string(wave));
			window.draw(waveText);

			//testposition
			position.setString(std::to_string(z));
			window.draw(position);


			window.display();
		}
		return 0;
	}
	else {

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					menu.moveUp();
					break;
				case sf::Keyboard::Down:
					menu.moveDown();
					break;
				case sf::Keyboard::Enter:
					switch (menu.GetPressedItem())
					{
					case 0:
						startgame = 1;
						//printf("play");
						window.close();
						goto strgame;
						break;
					case 1:
						printf("leaderboard");
						break;
					case 2:
						window.close();
						break;
					}
					break;
				}
				break;
			}
		}
		window.draw(backgroundmenu);
		menu.Draw(window);
		window.display();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}
	}
	}
	return 0;
}

void shot()
{
	for (int i = 0; i < 6; i++) {
		if (chk_1[i] == 1) {
			bullet[i].bullet.move(0, -5);
		}
		if (bullet[i].bullet.getPosition().y <10) {
			chk_1[i] = 0;
		}
	}
}


void enemymovewave1()
{
	for (int i = 0; i < 19; i++) {
		if (enemy[i].enemy.getPosition().y < 80 && chk_3[i] == 1 && enemymove1 == true) {
			enemy[i].enemy.move(0, 2.5);
		}
		if (enemy[5].enemy.getPosition().y == 80 ) {
			enemymove1 = false;
		}
	}
}

void enemymovewave2()
{
	for (int i = 0; i < 19; i++) {
		if (enemy[i].enemy.getPosition().y < 80 && chk_3[i] == 1 && enemymove1 == true) {
			enemy[i].enemy.move(0, 2.5);
		}
		if (enemy[10].enemy.getPosition().y == 80) {
			enemymove1 = false;
		}
		if (enemy[i].enemy.getPosition().y == 80) {
			enemymove2[i] = true;
		}
	}
}

void enemymovewave3()
{
	for (int i = 0; i < 19; i++) {
		if (enemy[i].enemy.getPosition().y < 100 && chk_3[i] == 1 && enemymove1 == true) {
			enemy[i].enemy.move(0, 2.5);
		}
		if (enemy[14].enemy.getPosition().y == 100) {
			enemymove1 = false;
		}
		if (enemy[i].enemy.getPosition().y == 100) {
			enemymove2[i] = true;
		}
	}
}

void enemybossmove()
{
	for (int i = 0; i < 6; i++) {
		if (enemyboss[i].enemyboss.getPosition().y < 30 && chk_5[i] == 1) {
			enemyboss[i].enemyboss.move(0, 2.5);
		}
	}
}

void enemyshotwave12()
{
	for (int i = 0; i < 19; i++) {
		if (chk_4[i] == 1 && enemy[i].enemy.getPosition().y == 80) {
			enemybullet[i].enemybullet.move(0, 5);
		}
		if (enemybullet[i].enemybullet.getPosition().y > 800) {
			chk_4[i] = 0;

		}
	}
}

void enemyshotwave345()
{
	for (int i = 0; i < 19; i++) {
		if (chk_4[i] == 1 && enemy[i].enemy.getPosition().y == 100) {
			enemybullet[i].enemybullet.move(0, 5);
		}
		if (enemybullet[i].enemybullet.getPosition().y > 800) {
			chk_4[i] = 0;
		}
	}
}

void enemybossshot()
{
	for (int i = 0; i < 18; i++) {
		if (chk_6[i] == 1 & enemyboss[0].enemyboss.getPosition().y == 30) {
			enemybossbullet[i].enemybossbullet.move(0, 5);
		}
		if (enemybossbullet[i].enemybossbullet.getPosition().y > 800) {
			chk_6[i] = 0;
		}
	}
}

void check()
{
	if (enemyCount == 5) {
		//enemymove1 = true;
		enemyCount = 0;
		wave += 1;
		//bossmove = true;
	}
}

void enemymoveRL()
{
	for (int i = 5; i < 19; i++) {
		if (enemymove2[i] == true) {
			if (right == true) {
				if (enemy[i].enemy.getPosition().x < ((140 * (i%5)) + 250)) {
					enemy[i].enemy.move(1, 0);

				}
				if (enemy[i].enemy.getPosition().x == ((140 * (i % 5)) + 250)) {
					right = false;
					left = true;
				}
			}
			if (left == true) {
				if (enemy[i].enemy.getPosition().x > ((140 * (i % 5)) + 100)) {
					enemy[i].enemy.move(-1, 0);
				}
				if (enemy[i].enemy.getPosition().x == ((140 * (i % 5)) + 100)) {
					left = false;
					right = true;
				}
			}
		}
	}
}

