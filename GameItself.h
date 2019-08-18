#ifndef __GAMEITSELF_H__
#define __GAMEITSELF_H__

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Character.h"
#include "Premiu.h"
#include "Enemy.h"
#include "Power.h"
#include "Player.h"
#include "HUD.h"
#include "Snipe.h"

class GameItself
{
public:
	sf::RenderWindow m_window;
	Character m_characters[2];
	Player m_players[2];
	Premiu m_premiu;
	int m_nrPremiiLuate;
	Enemy m_enemies[200];
	int m_nrEnemies;
	bool m_fullscreen;
	sf::Texture m_splashscreenTexture;
	sf::Sprite m_splashscreenSprite;
	float m_globalTimeAmplification;
	sf::Music m_music;
	sf::SoundBuffer m_edgeBuffer;
	sf::Sound m_edgeSound;
	sf::Font m_myFont;
	HUD m_HUD;
	Snipe m_snipe;

	enum GameState
	{
		INIT = 0,
		SPLASHSCREEN,
		MENIU,
		GAME,
		GAMEOVER,
		COUNT
	};

	int m_stareCurenta;
	
	/*
	0 - init(default)
	1 - splashscreen
	2 - meniu
	3 - game
	4 - gameover
	...
	*/

	void init();
	void spawnPremiu();
	void spawnEnemy();
	void gameReset();
	void update(float dt);
	void draw();

};

#endif //__GAMEITSELF_H__