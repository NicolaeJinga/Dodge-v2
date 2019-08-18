#include<iostream>
#include<math.h>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <cstdlib>
#include<ctime>
#include <stdlib.h>

#include "GameItself.h"

using namespace std;
int main()
{
	GameItself game;
	game.init();
	sf::Clock clock;
	float dt=0.0f;
	cout <<"Character = "<< sizeof(Character) << " bytes" << endl;
	cout <<"Enemies = "<< sizeof(Enemy) << " bytes" << endl;
	cout <<"Premiu = "<< sizeof(Premiu) << " bytes" << endl;
	cout <<"Power = "<< sizeof(Power) << " bytes" << endl;
	cout <<"GameItself = "<< sizeof(GameItself) << " bytes" << endl;
	cout <<"Math = "<< sizeof(Math) << " bytes" << endl;

	while (game.m_window.isOpen())
	{
		sf::Event event;
		while (game.m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				game.m_window.close();
		}
		dt=clock.getElapsedTime().asSeconds();
		clock.restart();
		game.update(dt);
		game.draw();    
	}
	return 0;
}