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
void erase();
void enemymove();
void enemyshot();
void check();
void enemymoveRL();
void enemybossmove();
int chk_1[6] = { 0 };
int chk_2[6] = { 0 };
int chk_3[6] = { 0 };  //enemy
int chk_4[6] = { 0 };  //enemyBullet
int chk_5 = 0;         //enemyboss
int enemyCount = 0;
bool enemymove1 = true;
bool enemymove2[6] = {};
bool right = true;
bool left = false;
bool bossmove = false;

int startgame = 0;
clock_t start = -0.5, end = 0;
clock_t start1 = -0.5, end1 = 0;

Texture monsterTexture;
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
		enemyboss.setTextureRect(sf::IntRect(0, 0, 180, 180));
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

Enemy enemy[6];
Bullet bullet[6];
Monster monster[6];
enemyBullet enemybullet[6];
EnemyBoss enemyboss;

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
			erase();
			enemymove();
			enemyshot();
			check();
			enemymoveRL();
			enemybossmove();
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
			end = clock();
			float dif2 = (float)(end - start) / CLOCKS_PER_SEC;
			//monster 
			/*for (int i = 0; i < 6; i++) {
				if (chk_2[i] == 0 && dif2 > 1) {
					monster[i].set(rand() % 600, -30);
					chk_2[i] = 1;
					start = clock();
					break;
				}
			}*/

			//enemy
			for (int i = 0; i < 6; i++) {
				if (chk_3[i] == 0) {
					enemy[i].set(((115 * i) + 160), -90);
					chk_3[i] = 1;
					break;
				}
			}
			
			end1 = clock();
			float dif3 = (float)(end1 - start1) / CLOCKS_PER_SEC;
			//enemyBullet 
			if (dif3 > 3) {
				for (int i = 0; i < 6; i++) {
					if (chk_4[i] == 0 && enemy[i].enemy.getPosition().y == 80) {
						enemybullet[i].set(enemy[i].enemy.getPosition().x + 23, enemy[i].enemy.getPosition().y + 58);
						chk_4[i] = 1;
					}
					start1 = clock();
				}dif3 = 0;
			}

			//enemyboss
			if (chk_5 == 0) {
				enemyboss.set(400, -200);
				chk_5 = 1;
				//break;
			}

			//collision bullet&enemybullet
			for (int i = 0; i < 6; i++) {
				for (int k = 0; k < 6; k++) {
					if (bullet[i].bullet.getGlobalBounds().intersects(enemybullet[k].enemybullet.getGlobalBounds())) {
						bullet[i].bullet.setPosition(sf::Vector2f(-40, -40));
						enemybullet[k].enemybullet.setPosition(sf::Vector2f(-80, 150));
						chk_4[k] = 0;
					}
				}
			}

			//collision player&enemybullet
			
				for (int k = 0; k < 6; k++) {
					if (player.shape.getGlobalBounds().intersects(enemybullet[k].enemybullet.getGlobalBounds())) {
						
						enemybullet[k].enemybullet.setPosition(sf::Vector2f(-80, 150));
						chk_4[k] = 0;
						//HP--;
					}
				}
			

			//collision bullet&enemy
				for (int i = 0; i < 6; i++) {
					for (int k = 0; k < 6; k++) {
						if (enemy[k].enemy.getGlobalBounds().intersects(bullet[i].bullet.getGlobalBounds())) {
							bullet[i].bullet.setPosition(sf::Vector2f(-40, -40));
							enemy[k].enemy.setPosition(sf::Vector2f(-80, 150));
							scoreCount++;
							enemymove2[k] == false;
							chk_3[k] = 0;
							chk_4[k] = 0;
							enemyCount++;
						}
					}
				}
			
			//collision player&monster
			for (int i = 0; i < 6; i++) {
				if (monster[i].monster.getGlobalBounds().intersects(player.shape.getGlobalBounds())) {
					monster[i].monster.setPosition(sf::Vector2f(-100, 200));
					HP--;
				}
			}

			//collision bullet&monster
			for (int i = 0; i < 6; i++) {
				for (int k = 0; k < 6; k++) {
					if (monster[k].monster.getGlobalBounds().intersects(bullet[i].bullet.getGlobalBounds())) {
						monster[k].monster.setPosition(sf::Vector2f(rand() % 600, -100));
						bullet[i].bullet.setPosition(sf::Vector2f(-40, -40));
						scoreCount++;
					}
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

			//monster
			/*for (int i = 0; i < 6; i++) {
				if (chk_2[i] == 1) {
					window.draw(monster[i].monster);
				}
			}*/

			//enemy
			for (int i = 0; i < 6; i++) {
				if (chk_3[i] == 1) {
					window.draw(enemy[i].enemy);
				}
			}

			//enemyboss
			if (chk_5 == 1) {
				window.draw(enemyboss.enemyboss);
			}

			//enemybullet
			for (int i = 0; i < 6; i++) {
				if (chk_4[i] == 1) {
					window.draw(enemybullet[i].enemybullet);
				}
			}

			//score
			scoreText.setString(std::to_string(scoreCount));
			window.draw(scoreText);

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

void erase()
{
	for (int i = 0; i < 6; i++) {
		if (chk_2[i] == 1) {
			monster[i].monster.move(0, 2.2);
		}
		if (monster[i].monster.getPosition().y > 800) {
			chk_2[i] = 0;
		}
	}
}

void enemymove()
{
	for (int i = 0; i < 6; i++) {
		if (enemy[i].enemy.getPosition().y < 80 && chk_3[i] == 1 && enemymove1 == true) {
			enemy[i].enemy.move(0, 2.5);
		}
		if (enemy[5].enemy.getPosition().y == 80 ) {
			enemymove1 = false;
		}
		if (enemy[i].enemy.getPosition().y == 80) {
			enemymove2[i] = true;
		}
	}
}

void enemybossmove()
{
	if (bossmove == true && enemyboss.enemyboss.getPosition().y < 30 && chk_5 == 1) {
		enemyboss.enemyboss.move(0, 2.5);
	}
}

void enemyshot()
{
	for (int i = 0; i < 6; i++) {
		if (chk_4[i] == 1 && enemy[i].enemy.getPosition().y == 80) {
			enemybullet[i].enemybullet.move(0, 5);
		}
		if (enemybullet[i].enemybullet.getPosition().y > 800) {
			chk_4[i] = 0;

		}
	}
}

void check()
{
	if (enemyCount == 6) {
		//enemymove1 = true;
		//enemyCount = 0;
		bossmove = true;
	}
}

void enemymoveRL()
{
	for (int i = 0; i < 6; i++) {
		if (enemymove2[i] == true) {
			if (right == true) {
				if (enemy[i].enemy.getPosition().x < ((115 * i) + 250)) {
					enemy[i].enemy.move(1, 0);

				}
				if (enemy[i].enemy.getPosition().x == ((115 * i) + 250)) {
					right = false;
					left = true;
				}
			}
			if (left == true) {
				if (enemy[i].enemy.getPosition().x > ((115 * i) + 100)) {
					enemy[i].enemy.move(-1, 0);
				}
				if (enemy[i].enemy.getPosition().x == ((115 * i) + 100)) {
					left = false;
					right = true;
				}
			}
		}
	}
}