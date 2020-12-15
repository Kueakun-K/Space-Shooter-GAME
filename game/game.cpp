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
#include <fstream>

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
void enemybossshotwave4();
void enemybossmoveRL();
void enemybossmoveRLwave4();
void enemymoveRLwave3();
void itemmove();
int chk_1[6] = { 0 };  //bullet
int chk_3[19] = { 0 };  //enemy
int chk_4[19] = { 0 };  //enemyBullet
int chk_5[6] = { 0 };  //enemyboss
int chk_6[18] = { 0 };  //enemybossBullet
int hpboss[4] = { 10,10,10,10 };
int hpenemy[14] = {2,2,2,2,2,2,2,2,2,2,2,2,2,2};
int hpbulletboss[12] = { 2,2,2,2,2,2,2,2,2,2,2,2 };
int enemyCount = 0;
int wave = 1;
int waveend = 0;
int sd = 5;
int HP = 3;
int cnt;
int score = 0;
float debounce = 0;
float deltatime = 0.0f;
bool shieldcheckplayer = false;
bool enemymove1 = true;
bool enemymove2[19] = {};
bool bossmove = false;
bool right = true;
bool left = false;
bool bossright = true;
bool bossleft = false;
bool itemcheck = false;
bool healcheck = false;
bool shieldcheck = false;
bool speedcheck = false;


int startgame = 0;
clock_t start = -0.5, end = 0;
clock_t start1 = -0.5, end1 = 0;
clock_t start2 = -0.5, end2 = 0;
clock_t start3 = -0.5, end3 = 0;
clock_t start4 = -0.5, end4 = 0;

Texture BULLET;
Texture enemyTexture;
Texture bulletenemy;
Texture enemybossTexture;
Texture bulletenemyboss;
Texture heal;
Texture shield;
Texture boot;
Texture shield1;


SoundBuffer soundbullet;
SoundBuffer soundenemybomb;
SoundBuffer soundenemybossbomb;

class Player
{
public:
	Sprite shape;
	Texture* texture;

	Player(Texture* texture)
	{
		this->texture = texture;
		this->shape.setTexture(*texture);
		this->shape.setPosition(300, 600);
	}
	~Player() {}
};


class Bullet {
public:
	sf::Sprite bullet;
	void set(int x, int y)
	{
		BULLET.loadFromFile("img/bullet.png");
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
		bulletenemy.loadFromFile("img/bulletenemy.png");
		enemybullet.setTexture(bulletenemy);
		enemybullet.setTextureRect(sf::IntRect(0, 0, 20, 25));
		enemybullet.setPosition(x, y);
	}
};

class enemybossBullet {
public:
	sf::Sprite enemybossbullet;
	void set(int x, int y)
	{
		bulletenemyboss.loadFromFile("img/bulletenemyboss.png");
		enemybossbullet.setTexture(bulletenemyboss);
		enemybossbullet.setTextureRect(sf::IntRect(0, 0, 20, 25));
		enemybossbullet.setPosition(x, y);
	}
};

class itemheal {
public:
	sf::Sprite itemheal;
	void set(int x, int y)
	{
		heal.loadFromFile("img/heal.png");
		itemheal.setTexture(heal);
		itemheal.setTextureRect(sf::IntRect(0, 0, 40, 40));
		itemheal.setPosition(x, y);
	}
};

class itemshield {
public:
	sf::Sprite itemshield;
	void set(int x, int y)
	{
		shield.loadFromFile("img/shield.png");
		itemshield.setTexture(shield);
		itemshield.setTextureRect(sf::IntRect(0, 0, 40, 40));
		itemshield.setPosition(x, y);
	}
};

class itemspeed {
public:
	sf::Sprite itemspeed;
	void set(int x, int y)
	{
		boot.loadFromFile("img/boot.png");
		itemspeed.setTexture(boot);
		itemspeed.setTextureRect(sf::IntRect(0, 0, 40, 40));
		itemspeed.setPosition(x, y);
	}
};

class shieldplayer {
public:
	sf::Sprite shieldplayer;
	void set(int x, int y)
	{
		shield1.loadFromFile("img/shieldplayer.png");
		shieldplayer.setTexture(shield1);
		shieldplayer.setTextureRect(sf::IntRect(0, 0, 90, 90));
		shieldplayer.setPosition(x, y);
	}
};

class bulletsound {
public:
	sf::Sound bulletsound;
	void playsound(){
		soundbullet.loadFromFile("sound/bullet.wav");
		bulletsound.setBuffer(soundbullet);
		bulletsound.play();
	}
	void pausesound() {
		bulletsound.pause();
	}
};

class enemybombsound {
public:
	sf::Sound enemybombsound;
	void playsound() {
		soundenemybomb.loadFromFile("sound/enemybomb.wav");
		enemybombsound.setBuffer(soundenemybomb);
		enemybombsound.play();
	}
	void pausesound() {
		enemybombsound.pause();
	}
};

class enemybossbombsound {
public:
	sf::Sound enemybossbombsound;
	void playsound() {
		soundenemybossbomb.loadFromFile("sound/enemybossbomb.wav");
		enemybossbombsound.setBuffer(soundenemybossbomb);
		enemybossbombsound.play();
	}
	void pausesound() {
		enemybossbombsound.pause();
	}
};


Enemy enemy[19];
Bullet bullet[6];
enemyBullet enemybullet[19];
EnemyBoss enemyboss[4];
enemybossBullet enemybossbullet[18];
itemheal healitem;
itemshield shielditem;
itemspeed speeditem;
shieldplayer shield2;

bulletsound soundbulletplay;
enemybombsound soundenemybombplay;
enemybossbombsound soundenemybossbombplay;

int main()
{
	RenderWindow window(sf::VideoMode(1000, 800), "MENU MODE", sf::Style::Close | sf::Style::Resize);
	Menu menu(window.getSize().x, window.getSize().y);

	Texture texture;
	if (!texture.loadFromFile("img/background.png")) {
	}
	Sprite backgroundmenu;
	backgroundmenu.setTexture(texture);

	//leaderboard
	Texture leaderboardbackground;
	leaderboardbackground.loadFromFile("img/backgroundleaderboard.png");
	Sprite backgroundleaderborad;
	backgroundleaderborad.setTexture(leaderboardbackground);

	//leaderboard
	Texture backgroundover;
	backgroundover.loadFromFile("img/back.png");
	Sprite back;
	back.setTexture(backgroundover);

	//clock
	sf::Clock clock3,clock2;

	


	sf::Music music;
	// Open it from an audio file
	if (!music.openFromFile("sound/backgroundsound.ogg"))
	{
		// error...
	}
	// Change some parameters
	music.setPosition(0, 1, 10); // change its 3D position
	music.setPitch(2);           // increase the pitch
	music.setVolume(50);         // reduce the volume
	music.setLoop(true);         // make it loop
	// Play it
	music.play();

	//font
	Font font;
	if (!font.loadFromFile("Pixeboy.ttf"))
	{
		return -1;
	}

	Text scoreboard;
	scoreboard.setFont(font);
	scoreboard.setString("SCOREBOARD");
	scoreboard.setFillColor(sf::Color::White);
	scoreboard.setCharacterSize(50);
	scoreboard.setPosition(380, 110);

	std::vector<std::pair<int, std::string>> ScoreBoard;


	//name 
	sf::Text name;
	name.setFont(font);
	name.setString("Name : ");
	name.setFillColor(sf::Color::White);
	name.setPosition(200, 300);
	name.setCharacterSize(80);
	sf::String nameplayer;

	//high score
	Text hname, hscore, HighScoreText;
	HighScoreText.setFont(font);
	HighScoreText.setFillColor(sf::Color::White);
	HighScoreText.setCharacterSize(50);
	HighScoreText.setPosition(300, 300);

	hscore.setFont(font);
	hscore.setCharacterSize(40);
	hscore.setFillColor(sf::Color::White);
	hname.setFont(font);
	hname.setCharacterSize(40);
	hname.setFillColor(sf::Color::White);

	//gameover
	sf::Text gameover;
	gameover.setFont(font);
	gameover.setString("GAME OVER");
	gameover.setFillColor(sf::Color::White);
	gameover.setPosition(200, 200);
	gameover.setCharacterSize(160);

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
			
			float x, y, z;
			x = player.shape.getPosition().x;
			y = player.shape.getPosition().y;
			z = enemyboss[0].enemyboss.getPosition().y;

			end = clock();
			float dif1 = (float)(end - start) / CLOCKS_PER_SEC;

			//player control
			if (Keyboard::isKeyPressed(Keyboard::W))
				player.shape.move(0, -sd);
			if (Keyboard::isKeyPressed(Keyboard::A))
				player.shape.move(-sd, 0);
			if (Keyboard::isKeyPressed(Keyboard::S))
				player.shape.move(0, sd);
			if (Keyboard::isKeyPressed(Keyboard::D))
				player.shape.move(sd, 0);
			if (Keyboard::isKeyPressed(Keyboard::Space) && dif1 > 0.5)
				for (int i = 0; i < 6; i++) {
					if (chk_1[i] == 0) {
						bullet[i].set(x + 20, y - 15);
						chk_1[i] = 1;
						soundbulletplay.playsound();
						start = clock();
						break;
					}
					soundbulletplay.pausesound();
				}

			if (shieldcheckplayer == true) {
				shield2.set(player.shape.getPosition().x - 12, player.shape.getPosition().y - 10);

			}

			//collision bullet&enemybullet
			for (int i = 0; i < 6; i++) {
				for (int k = 0; k < 19; k++) {
					if (bullet[i].bullet.getGlobalBounds().intersects(enemybullet[k].enemybullet.getGlobalBounds())) {
						bullet[i].bullet.setPosition(sf::Vector2f(-40, -40));
						chk_4[k] = 0;
						enemybullet[k].enemybullet.setPosition(sf::Vector2f(-800, -800));
						score -= 100;
					}
				}
			}
			
			//collision bullet&enemybossbullet
			for (int i = 0; i < 6; i++) {
				for (int k = 0; k < 18; k++) {
					if (bullet[i].bullet.getGlobalBounds().intersects(enemybossbullet[k].enemybossbullet.getGlobalBounds())) {
						bullet[i].bullet.setPosition(sf::Vector2f(-40, -40));
						if (hpbulletboss[k] == 1) {
							chk_6[k] = 0;
							enemybossbullet[k].enemybossbullet.setPosition(sf::Vector2f(-800, -800));
							score -= 100;
						}
						if (hpbulletboss[k] == 2) {
							hpbulletboss[k] -= 1;
							score -= 100;
						}
					}
				}
			}
			
			//collision player&enemybullet
			for (int k = 0; k < 19; k++) {
				if (player.shape.getGlobalBounds().intersects(enemybullet[k].enemybullet.getGlobalBounds())) {
					enemybullet[k].enemybullet.setPosition(sf::Vector2f(-800, -800));
					chk_4[k] = 0;
					if (shieldcheckplayer == true) {
						shieldcheckplayer = false;
					}
					else {
						HP--;
						score -= 300;
					}
				}
			}

			//collision player&enemybossbullet
			for (int k = 0; k < 18; k++) {
				if (player.shape.getGlobalBounds().intersects(enemybossbullet[k].enemybossbullet.getGlobalBounds())) {
					enemybossbullet[k].enemybossbullet.setPosition(sf::Vector2f(-800, -800));
					chk_6[k] = 0;
					if (shieldcheckplayer == true) {
						shieldcheckplayer = false;
					}
					else {
						HP--;
						score -= 500;
					}
				}
			}

			//collision bullet&enemy
			for (int i = 0; i < 6; i++) {
				for (int k = 0; k < 19; k++) {
					if (enemy[k].enemy.getGlobalBounds().intersects(bullet[i].bullet.getGlobalBounds())) {
						bullet[i].bullet.setPosition(sf::Vector2f(-40, -40));
						if (hpenemy[k] == 1) {
							enemy[k].enemy.setPosition(sf::Vector2f(-8000, -800));
							enemybullet[k].enemybullet.setPosition(sf::Vector2f(-8000, -800));
							soundenemybombplay.playsound();
							scoreCount++;
							enemymove2[k] == false;
							//chk_3[k] = 0;
							chk_4[k] = 0;
							enemyCount++;
							score += 1000;
						}

						if (hpenemy[k] == 2) {
							hpenemy[k] -= 1;
						}
						
					}
				}
			}

			//collision player&enemy
			for (int k = 0; k < 19; k++) {
				if (player.shape.getGlobalBounds().intersects(enemy[k].enemy.getGlobalBounds())) {
					enemy[k].enemy.setPosition(sf::Vector2f(-8000, -800));
					enemybullet[k].enemybullet.setPosition(sf::Vector2f(-8000, -800));
					//chk_3[k] = 0;
					chk_4[k] = 0;
					scoreCount++;
					enemyCount++;
					//HP--;
				}
			}

			//collision bullet&enemyboss
			for (int i = 0; i < 6; i++) {
				for (int k = 0; k < 6; k++) {
					if (enemyboss[k].enemyboss.getGlobalBounds().intersects(bullet[i].bullet.getGlobalBounds()) && scoreCount == 14) {
						bullet[i].bullet.setPosition(sf::Vector2f(-40, -40));
						if (hpboss[0] == 1) {
							enemyboss[0].enemyboss.setPosition(Vector2f(-8000, -800));
							enemybossbullet[0].enemybossbullet.setPosition(sf::Vector2f(-8000, -800));
							enemybossbullet[1].enemybossbullet.setPosition(sf::Vector2f(-8000, -800));
							enemybossbullet[2].enemybossbullet.setPosition(sf::Vector2f(-8000, -800));
							soundenemybossbombplay.playsound();
							chk_6[0] = 0;
							chk_6[1] = 0;
							chk_6[2] = 0;
							enemyCount++;
							score += 3000;
							hpboss[0] = 0;
							
						}
						if (hpboss[1] == 1) {
							enemyboss[1].enemyboss.setPosition(Vector2f(-8000, -800));
							enemybossbullet[3].enemybossbullet.setPosition(sf::Vector2f(-8000, -800));
							enemybossbullet[4].enemybossbullet.setPosition(sf::Vector2f(-8000, -800));
							enemybossbullet[5].enemybossbullet.setPosition(sf::Vector2f(-8000, -800));
							soundenemybossbombplay.playsound();
							chk_6[3] = 0;
							chk_6[4] = 0;
							chk_6[5] = 0;
							score += 3000;
							hpboss[1] = 0;
						}
						if (hpboss[2] == 1) {
							enemyboss[2].enemyboss.setPosition(Vector2f(-8000, -800));
							enemybossbullet[6].enemybossbullet.setPosition(sf::Vector2f(-8000, -800));
							enemybossbullet[7].enemybossbullet.setPosition(sf::Vector2f(-8000, -800));
							enemybossbullet[8].enemybossbullet.setPosition(sf::Vector2f(-8000, -800));
							soundenemybossbombplay.playsound();
							chk_6[6] = 0;
							chk_6[7] = 0;
							chk_6[8] = 0;
							score += 3000;
							hpboss[2] = 0;
						}
						if (hpboss[3] == 1) {
							enemyboss[3].enemyboss.setPosition(Vector2f(-800, -800));
							enemybossbullet[9].enemybossbullet.setPosition(sf::Vector2f(-8000, -800));
							enemybossbullet[10].enemybossbullet.setPosition(sf::Vector2f(-8000, -800));
							enemybossbullet[11].enemybossbullet.setPosition(sf::Vector2f(-8000, -800));
							soundenemybossbombplay.playsound();
							chk_6[9] = 0;
							chk_6[10] = 0;
							chk_6[11] = 0;
							score += 3000;
							hpboss[3] = 0;
						}
						if (hpboss[0] > 1) {
							hpboss[0] -= 1;
						}
						if (wave == 4)
							hpboss[k] -= 1;
						
					}
				}
			}

			//collision player&item
			if (player.shape.getGlobalBounds().intersects(healitem.itemheal.getGlobalBounds())) {
				healitem.itemheal.setPosition(-800, -800);
				HP += 1;
				healcheck = false;
				wave += 1;
			}
			if (player.shape.getGlobalBounds().intersects(shielditem.itemshield.getGlobalBounds())) {
				shielditem.itemshield.setPosition(-800, -800);
				shieldcheckplayer = true;
				shieldcheck = false;
				wave += 1;
			}
			if (player.shape.getGlobalBounds().intersects(speeditem.itemspeed.getGlobalBounds())) {
				speeditem.itemspeed.setPosition(-800, -800);
				sd += 3;
				speedcheck = false;
				wave += 1;
			}

			//collision item&window
			if (healitem.itemheal.getPosition().y > 800) {
				healitem.itemheal.setPosition(-800, -800);
				healcheck = false;
				wave += 1;
			}
			if (shielditem.itemshield.getPosition().y > 800) {
				shielditem.itemshield.setPosition(-800, -800);
				shieldcheck = false;
				wave += 1;
			}
			if (speeditem.itemspeed.getPosition().y > 800) {
				speeditem.itemspeed.setPosition(-800, -800);
				speedcheck = false;
				wave += 1;
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
						enemy[i].set(((200 * i ) + 65), -90);
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

			if (waveend == 1) {
				itemmove();
				end1 = clock();
				float dif3 = (float)(end1 - start1) / CLOCKS_PER_SEC;
				if (dif3 > 2) {
					if (itemcheck == true) {
						x = rand() % 3;
						if (x == 0) {
							healitem.set(480, -200);
							healcheck = true;
						}
						if (x == 1) {
							shielditem.set(480, -200);
							shieldcheck = true;
						}
						if (x == 2) {
							speeditem.set(480, -200);
							speedcheck = true;
						}
						start1 = clock();
					}
					itemcheck = false;
				}
			}

			if (wave == 2) {
				enemymovewave2();
				enemyshotwave12();
				enemymoveRL();
				//enemy
				for (int i = 5; i < 10; i++) {
					if (chk_3[i] == 0) {
						enemy[i].set(((200 * (i -5)) + 65), -90);
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
							//soundbulletenemyplay.playsound();
						}
						start1 = clock();
					}dif3 = 0;
				}
			}

			if (waveend == 2) {
				itemmove();
				end1 = clock();
				float dif3 = (float)(end1 - start1) / CLOCKS_PER_SEC;
				if (dif3 > 2) {
					if (itemcheck == true) {
						x = rand() % 3;
						if (x == 0) {
							healitem.set(480, -200);
							healcheck = true;
						}
						/*if (x == 1) {
							shielditem.set(480, -200);
							shieldcheck = true;
						}*/
						if (x == 2 || x==1) {
							speeditem.set(480, -200);
							speedcheck = true;
						}
						start1 = clock();
					}
					itemcheck = false;
				}
			}

			if (wave == 3) {
				enemymovewave3();
				enemyshotwave345();
				enemybossmove();
				enemybossshot();
				enemybossmoveRL();
				enemymoveRLwave3();
				//enemymoveRL();
				//enemy
				for (int i = 10; i < 14; i++) {
					if (chk_3[i] == 0) {
						if (i ==10) {
							enemy[i].set(85, -90);
							chk_3[i] = 1;
							break;
						}
						if (i == 11) {
							enemy[i].set(265, -90);
							chk_3[i] = 1;
							break;
						}
						if (i == 12) {
							enemy[i].set(665, -90);
							chk_3[i] = 1;
							break;
						}
						if (i == 13) {
							enemy[i].set(845, -90);
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
						break;
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
								hpbulletboss[i] = 2;
							}

							if (i == 2) {
								enemybossbullet[i].set(enemyboss[0].enemyboss.getPosition().x + 85, enemyboss[i].enemyboss.getPosition().y + 100);
								chk_6[i] = 1;
								hpbulletboss[i] = 2;
							}
							
						}
						start2 = clock();
					}dif4 = 0;
				}

				//enemybossbullet2
				end3 = clock();
				float dif5 = (float)(end3 - start3) / CLOCKS_PER_SEC;
				if (dif5 > 2) {
					if (chk_6[1] == 0 && enemyboss[0].enemyboss.getPosition().y == 30) {
						enemybossbullet[1].set(enemyboss[0].enemyboss.getPosition().x + 53.5, enemyboss[0].enemyboss.getPosition().y + 135);
						chk_6[1] = 1;
						hpbulletboss[1] = 2;
						start3 = clock();
					}dif5 = 0;
				}
			}

			if (waveend == 3) {
				itemmove();
				end1 = clock();
				float dif3 = (float)(end1 - start1) / CLOCKS_PER_SEC;
				if (dif3 > 2) {
					if (itemcheck == true) {
						x = rand() % 3;
						if (x == 0) {
							healitem.set(480, -200);
							healcheck = true;
						}
						if (x == 1) {
							shielditem.set(480, -200);
							shieldcheck = true;
						}
						if (x == 2) {
							speeditem.set(480, -200);
							speedcheck = true;
						}
						start1 = clock();
					}
					itemcheck = false;
				}
			}

			if (wave == 4) {
				enemybossmove();
				enemybossshotwave4();
				enemybossmoveRLwave4();
				//enemyboss
				for (int i = 1; i < 4; i++) {
					if (chk_5[i] == 0) {
						if (i == 1) {
							enemyboss[i].set(100, -200);
							chk_5[i] = 1;
						}
						if (i == 2) {
							enemyboss[i].set(430, -200);
							chk_5[i] = 1;
						}
						if (i == 3) {
							enemyboss[i].set(760, -200);
							chk_5[i] = 1;
						}
					}
				}
				//enemybossbullet
				end2 = clock();
				float dif4 = (float)(end2 - start2) / CLOCKS_PER_SEC;
				if (dif4 > 3) {
					for (int i = 3; i < 12; i++) {
						if (chk_6[i] == 0 && (enemyboss[3].enemyboss.getPosition().y == 30 || enemyboss[2].enemyboss.getPosition().y == 30 || enemyboss[1].enemyboss.getPosition().y == 30)) {
							if (i == 3) {
								enemybossbullet[i].set(enemyboss[1].enemyboss.getPosition().x + 21, enemyboss[1].enemyboss.getPosition().y + 70);
								chk_6[i] = 1;
								hpbulletboss[i] = 2;
							}

							if (i == 5) {
								enemybossbullet[i].set(enemyboss[1].enemyboss.getPosition().x + 85, enemyboss[1].enemyboss.getPosition().y + 70);
								chk_6[i] = 1;
								hpbulletboss[i] = 2;
							}
							if (i == 6) {
								enemybossbullet[i].set(enemyboss[2].enemyboss.getPosition().x + 21, enemyboss[2].enemyboss.getPosition().y + 70);
								chk_6[i] = 1;
								hpbulletboss[i] = 2;
							}

							if (i == 8) {
								enemybossbullet[i].set(enemyboss[2].enemyboss.getPosition().x + 85, enemyboss[2].enemyboss.getPosition().y + 70);
								chk_6[i] = 1;
								hpbulletboss[i] = 2;
							}
							if (i == 9) {
								enemybossbullet[i].set(enemyboss[3].enemyboss.getPosition().x + 21, enemyboss[3].enemyboss.getPosition().y + 70);
								chk_6[i] = 1;
								hpbulletboss[i] = 2;
							}

							if (i == 11) {
								enemybossbullet[i].set(enemyboss[3].enemyboss.getPosition().x + 85, enemyboss[3].enemyboss.getPosition().y + 70);
								chk_6[i] = 1;
								hpbulletboss[i] = 2;
							}
							
						}
						start2 = clock();
						
					}dif4 = 0;
					
				}
				//enemybossbullet2
				end3 = clock();
				float dif5 = (float)(end3 - start3) / CLOCKS_PER_SEC;
				if (dif5 > 2) {
					for (int i = 3; i < 12; i++) {
						if (chk_6[i] == 0 && (enemyboss[3].enemyboss.getPosition().y == 30 || enemyboss[2].enemyboss.getPosition().y == 30 || enemyboss[1].enemyboss.getPosition().y == 30)) {
							if (i == 4) {
								enemybossbullet[i].set(enemyboss[1].enemyboss.getPosition().x + 53.5, enemyboss[1].enemyboss.getPosition().y + 135);
								chk_6[i] = 1;
								hpbulletboss[i] = 2;
								start3 = clock();
							}
							if (i == 7) {
								enemybossbullet[i].set(enemyboss[2].enemyboss.getPosition().x + 53.5, enemyboss[2].enemyboss.getPosition().y + 135);
								chk_6[i] = 1;
								hpbulletboss[i] = 2;
								start3 = clock();
							}
							if (i == 10) {
								enemybossbullet[i].set(enemyboss[3].enemyboss.getPosition().x + 53.5, enemyboss[3].enemyboss.getPosition().y + 135);
								chk_6[i] = 1;
								hpbulletboss[i] = 2;
								start3 = clock();
							}
							
						}
						
					}dif5 = 0;
					

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

			//item
			if (healcheck == true)
				window.draw(healitem.itemheal);
			if (shieldcheck == true)
				window.draw(shielditem.itemshield);
			if (speedcheck == true)
				window.draw(speeditem.itemspeed);
			//shield
			if (shieldcheckplayer == true) {
				window.draw(shield2.shieldplayer);
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

			if (HP == 0 || HP < 0) {
				//write files
				std::string name;
				name = nameplayer;
				std::ofstream highscore;
				highscore.open("score/Score.txt", std::ios::out | std::ios::app);
				highscore << "\n" << name << " " << score;
				highscore.close();

				//read files
				ScoreBoard.clear();

				std::ifstream loadFile;
				loadFile.open("score/Score.txt");
				while (!loadFile.eof()) {
					std::string tempName;
					int tempScore;
					loadFile >> tempName >> tempScore;
					std::cout << tempName << " " << tempScore << std::endl;
					ScoreBoard.push_back({ tempScore,tempName });
				}
				loadFile.close();

				std::sort(ScoreBoard.begin(), ScoreBoard.end(), std::greater<std::pair< int, std::string>>());
				std::cout << ScoreBoard.data();
				std::vector<std::pair<int, std::string >>::iterator k = ScoreBoard.begin();
				HighScoreText.setString("HIGH SCORE : " + std::to_string(k->first));
				startgame = 4;
				goto gameover;
				window.close();
			}

			//score
			scoreText.setString(std::to_string(score));
			window.draw(scoreText);

			//wave
			waveText.setString(std::to_string(wave));
			window.draw(waveText);

			//testposition
			position.setString(std::to_string(HP));
			window.draw(position);


			window.display();
		}
		return 0;
	}
strgame1:
	if (startgame == 2) {
			sf::RenderWindow window(sf::VideoMode(1000, 800), "LEDERBOARD", sf::Style::Close | sf::Style::Resize);
			while (window.isOpen())
			{
				sf::Event event;
				while (window.pollEvent(event))
				{
					switch (event.type)
					{

					case sf::Event::Closed:
						window.close();
						break;
					}
				}
				ScoreBoard.clear();
				
				std::ifstream loadFile;
				loadFile.open("score/Score.txt");
				while (!loadFile.eof())
				{
					std::string tempName;
					int tempScore;
					loadFile >> tempName >> tempScore;
					ScoreBoard.push_back({ tempScore,tempName });
				}
				loadFile.close();
				
				sort(ScoreBoard.begin(), ScoreBoard.end(), std::greater<std::pair< int, std::string>>());

				window.draw(backgroundleaderborad);

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					window.close();
				}

				
				cnt = 0;
				for (std::vector<std::pair<int, std::string>>::iterator k = ScoreBoard.begin(); k != ScoreBoard.end(); ++k)
				{
					++cnt;
					if (cnt > 5)
						break;
					std::cout << cnt << std::endl;
					
					hscore.setPosition(300, 250 + (50 * cnt));
					hname.setPosition(600, 250 + (50 * cnt));
					hscore.setString(std::to_string(k->first));
					hname.setString(k->second);
					window.draw(hscore);
					window.draw(hname);
					
				}
				
				window.draw(scoreboard);
				window.display();

			}
		}
strgame2: //name
	if (startgame == 3) {
		sf::RenderWindow window(sf::VideoMode(1000, 800), "NAME", sf::Style::Close | sf::Style::Resize);
		while (window.isOpen())
		{

			deltatime = clock3.restart().asSeconds();

			sf::Event event;
			while (window.pollEvent(event))
			{
				switch (event.type)
				{

				case sf::Event::Closed:
					window.close();
					break;
				}
			}
			window.draw(backgroundleaderborad);

			if (event.type == sf::Event::TextEntered and debounce < clock2.getElapsedTime().asSeconds())
			{

				debounce = clock2.getElapsedTime().asSeconds() + 0.2;
				if (event.text.unicode >= 33 && event.text.unicode <= 126 && nameplayer.getSize() <= 13 && event.text.unicode != 44)
				{
					nameplayer += event.text.unicode;
				}
				else if (event.text.unicode == 8)//backspace
				{
					nameplayer = nameplayer.substring(0, nameplayer.getSize() - 1);
				}
				else if (event.text.unicode == 13 && nameplayer.getSize() > 0)//enter
				{
					startgame = 1;
					printf("play");
					window.close();
					goto strgame;
					break;
				}
			}


			name.setString("Name : " + nameplayer);

			window.draw(name);
			window.display();
		}
	}
gameover:
	if (startgame == 4) {
		sf::RenderWindow window(sf::VideoMode(1000, 800), "NAME", sf::Style::Close | sf::Style::Resize);
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
					case sf::Keyboard::Enter:
						startgame = 0;
						window.close();
						goto menu;
						break;
					}
					break;
				}
			}

			window.draw(back);
			window.draw(gameover);
			//Window.draw(window);

			window.display();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
			}
		}
	}
menu:
	if(startgame==0) {

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
							startgame = 3;
							window.close();
							goto strgame2;
							break;
						case 1:
							startgame = 2;
							window.clear();
							window.close();
							goto strgame1;
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
		
		if (bullet[i].bullet.getPosition().y < 10) {
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
		if (enemy[5].enemy.getPosition().y == 80) {
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
		if (chk_6[i] == 1 && enemyboss[0].enemyboss.getPosition().y == 30) {
			enemybossbullet[i].enemybossbullet.move(0, 5);
		}
		if (enemybossbullet[i].enemybossbullet.getPosition().y > 800) {
			hpbulletboss[i] = 2;
			chk_6[i] = 0;
		}
	}
}

void enemybossshotwave4()
{
	for (int i = 0; i < 18; i++) {
		if (chk_6[i] == 1 && (enemyboss[3].enemyboss.getPosition().y == 30 || enemyboss[2].enemyboss.getPosition().y == 30 || enemyboss[1].enemyboss.getPosition().y == 30)) {
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
		waveend += 1;
		itemcheck = true;
		//bossmove = true;
	}
}

void enemymoveRL()
{
	srand(time(NULL));
	for (int i = 5; i < 10; i++) {
		if (enemymove2[i] == true) {
			int x = rand() % 2;
			if (x == 0) {
				if(enemy[i].enemy.getPosition().x < ((200 * (i - 5)) + 120))
					enemy[i].enemy.move(1, 0);
				else
					enemy[i].enemy.move(-1, 0);
			}
			if (x == 1) {
				if (enemy[i].enemy.getPosition().x > ((200 * (i - 5)) +15))
					enemy[i].enemy.move(-1, 0);
				else
					enemy[i].enemy.move(1, 0);
			}
		}
	}
}

void enemymoveRLwave3()
{
	srand(time(NULL));
	for (int i = 10; i < 14; i++) {
		if (enemymove2[i] == true) {
			int x = rand() % 2;
			if (x == 0) {
				if (i == 10) {
					if (enemy[i].enemy.getPosition().x < 135)
						enemy[i].enemy.move(1, 0);
					else
						enemy[i].enemy.move(-1, 0);
				}
				if (i == 11) {
					if (enemy[i].enemy.getPosition().x < 315)
						enemy[i].enemy.move(1, 0);
					else
						enemy[i].enemy.move(-1, 0);
				}
				if (i == 12) {
					if (enemy[i].enemy.getPosition().x < 715)
						enemy[i].enemy.move(1, 0);
					else
						enemy[i].enemy.move(-1, 0);
				}
				if (i == 13) {
					if (enemy[i].enemy.getPosition().x < 895)
						enemy[i].enemy.move(1, 0);
					else
						enemy[i].enemy.move(-1, 0);
				}
			}
			if (x == 1) {
				if (i == 10) {
					if (enemy[i].enemy.getPosition().x > 15)
						enemy[i].enemy.move(-1, 0);
					else
						enemy[i].enemy.move(1, 0);
				}
				if (i == 11) {
					if (enemy[i].enemy.getPosition().x > 215)
						enemy[i].enemy.move(-1, 0);
					else
						enemy[i].enemy.move(1, 0);
				}
				if (i == 12) {
					if (enemy[i].enemy.getPosition().x > 605)
						enemy[i].enemy.move(-1, 0);
					else
						enemy[i].enemy.move(1, 0);
				}
				if (i == 13) {
					if (enemy[i].enemy.getPosition().x > 795)
						enemy[i].enemy.move(-1, 0);
					else
						enemy[i].enemy.move(1, 0);
				}

			}
		}
	}
}

void enemybossmoveRL()
{
	srand(time(NULL));
	if (enemyCount == 4 && wave == 3) {
		for (int i = 0; i < 1; i++) {
			int x = rand() % 2;
			if (x == 0) {
				if (enemyboss[i].enemyboss.getPosition().x < 800)
					enemyboss[i].enemyboss.move(1, 0);
				else
					enemyboss[i].enemyboss.move(-1, 0);
			}
			if (x == 1) {
				if (enemyboss[i].enemyboss.getPosition().x > 100)
					enemyboss[i].enemyboss.move(-1, 0);
				else
					enemyboss[i].enemyboss.move(1, 0);
				
			}
		}
	}
}

void enemybossmoveRLwave4()
{
	srand(time(NULL));
	if (wave == 4 && (enemyboss[3].enemyboss.getPosition().y == 30 || enemyboss[2].enemyboss.getPosition().y == 30 || enemyboss[1].enemyboss.getPosition().y == 30)) {
		
		for (int i = 1; i < 4; i++) {
			int x = rand() % 2;
			if (x == 0) {
				if (i == 1) {
					if (enemyboss[i].enemyboss.getPosition().x <190)
						enemyboss[i].enemyboss.move(1, 0);
					else
						enemyboss[i].enemyboss.move(-1, 0);
				}
				if (i == 2) {
					if (enemyboss[i].enemyboss.getPosition().x < 520)
						enemyboss[i].enemyboss.move(1, 0);
					else
						enemyboss[i].enemyboss.move(-1, 0);
				}
				if (i == 3) {
					if (enemyboss[i].enemyboss.getPosition().x < 850)
						enemyboss[i].enemyboss.move(1, 0);
					else
						enemyboss[i].enemyboss.move(-1, 0);
				}
			}
			if (x == 1) {
				if (i == 1) {
					if (enemyboss[i].enemyboss.getPosition().x > 10)
						enemyboss[i].enemyboss.move(-1, 0);
					else
						enemyboss[i].enemyboss.move(1, 0);
				}
				if (i == 2) {
					if (enemyboss[i].enemyboss.getPosition().x > 340)
						enemyboss[i].enemyboss.move(-1, 0);
					else
						enemyboss[i].enemyboss.move(1, 0);
				}
				if (i == 3) {
					if (enemyboss[i].enemyboss.getPosition().x > 670)
						enemyboss[i].enemyboss.move(-1, 0);
					else
						enemyboss[i].enemyboss.move(1, 0);
				}
			}
		}
	}
}

void itemmove()
{
	if (healcheck == true)
		healitem.itemheal.move(0, 3);
	if (shieldcheck == true)
		shielditem.itemshield.move(0, 3);
	if (speedcheck == true)
		speeditem.itemspeed.move(0, 3);
}
