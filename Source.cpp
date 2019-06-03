#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <random>
#include <sstream>
#include <ctime>
#include <vector>
using namespace sf;
struct point
{
	int x, y;
};

int main()
{

	srand(time(0));

	RenderWindow app(VideoMode(400, 533), "Jimmy Jump!");
	app.setFramerateLimit(60);

	Texture t1, t2, t3;
	t1.loadFromFile("D:/Doodle Jump/Fon1.png");
	t2.loadFromFile("D:/Doodle Jump/platforma33.png");
	t3.loadFromFile("D:/Doodle Jump/player.png");
	

	Sprite sBackground(t1), sPlat(t2), sPers(t3);

	point plat[20];
	
	RectangleShape gameoverBackground(Vector2f(400, 533));
	gameoverBackground.setFillColor(Color::White);

	Font font;
	font.loadFromFile("D:/Doodle Jump/CENTAUR.ttf.");
	Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(50);
	scoreText.setFillColor(Color::Red);
	Text gameoverText;
	gameoverText.setFont(font);
	gameoverText.setString("Game Over!");
	gameoverText.setCharacterSize(80);
	gameoverText.setFillColor(Color::Red);


	for (int i = 0; i < 10; i++)
	{
		plat[i].x = rand() % 400;
		plat[i].y = rand() % 533;
	}

	int x = 100, y = 100, h = 200;
	float dx = 0, dy = 0;

	while (app.isOpen())
	{
		Event e;
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Right)) x += 3;  //  управление 
		if (Keyboard::isKeyPressed(Keyboard::Left)) x -= 3;

		dy += 0.2;                                         //  вертикальное ускорение 
		y += dy;
		if (y > 800)  dy = -10;

		if (y < h)
			for (int i = 0; i < 10; i++)
			{
				y = h;
				plat[i].y = plat[i].y - dy;
				if (plat[i].y > 533) { plat[i].y = 0; plat[i].x = rand() % 400; }
			}

		for (int i = 0; i < 10; i++)
			if ((x + 50 > plat[i].x) && (x + 20 < plat[i].x + 68)
				&& (y + 70 > plat[i].y) && (y + 70 < plat[i].y + 14) && (dy > 0))  dy = -10;

		sPers.setPosition(x, y);

		app.draw(sBackground);
		app.draw(sPers);
		for (int i = 0; i < 10; i++)  //рисуем платформы
		{
			sPlat.setPosition(plat[i].x, plat[i].y);
			app.draw(sPlat);
		}

		/*
	* - - - - - –азмер изображений----
	* фон.png размер: 400 * 533
	* игрок.png размер: 80 * 80
	* платформа.png размер: 68 * 14/*/
		

	// проигрыш
		if (y > 800)
		{
			gameoverText.setPosition(30, 100);
			scoreText.setPosition(100, 300);
			goto gameover;
		}
		app.draw(scoreText);
		app.display();
	}

	// проигрыш
	gameover:
	while (app.isOpen())
	{
		sf::Event event;
		while (app.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				app.close();
		}
		app.draw(gameoverBackground);
		app.draw(gameoverText);
		app.draw(scoreText);
		app.display();
		
	}
	return 0;
}