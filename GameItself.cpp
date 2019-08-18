#include "GameItself.h"
#include <iostream>
#include "PlayerPanel.h"
#include "Snipe.h"

//Init Game ------------------------------------------------------------------------------------------------------INIT GAME -----------------------------------------------------------------
void GameItself::init()
{
	//initialize main window
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	m_stareCurenta = INIT;
	srand((unsigned)time(0));
	m_fullscreen = true;
	if(m_fullscreen)
		m_window.create(sf::VideoMode::getDesktopMode(), "Dodge", sf::Style::Fullscreen, settings);
	else
		m_window.create(sf::VideoMode(300,300), "Dodge", sf::Style::Default, settings);
	m_characters[0].init(sf::Color::White, 25,sf::Vector2f(),((sf::Vector2f)m_window.getSize())*0.5f);
	spawnPremiu();
	m_nrEnemies = 0;
	m_nrPremiiLuate = 0;
	if (m_music.openFromFile("Resources/Music.wav")==false)
		std::cout<<"could not open Music.wav. error in gameitself.init"<<std::endl;
	m_music.setLoop(true);
	m_music.setVolume(100.0f);
	if (!m_edgeBuffer.loadFromFile("Resources/ding.wav"))
		std::cout<<"could not load ding.wav. error in gameitself.init"<<std::endl;
	m_edgeSound.setBuffer(m_edgeBuffer);
	m_edgeSound.setPitch(0.9f);
	m_edgeSound.setVolume(100.0f);
	if(m_splashscreenTexture.loadFromFile("Resources/splashscreen.png")==false)
		std::cout<<"could not load splashscreen.png. error in gameitself.draw"<<std::endl;
	m_splashscreenSprite.setTexture(m_splashscreenTexture);
	m_splashscreenSprite.setPosition(0.0f, 0.0f);
	m_splashscreenSprite.setScale(1.0f/m_splashscreenTexture.getSize().x*m_window.getSize().x, 1.0f/m_splashscreenTexture.getSize().y*m_window.getSize().y);
	m_globalTimeAmplification = 1.0f;
	m_snipe.init(20,Snipe::SNIPE,sf::Vector2f(),2,3,1,false);
	m_snipe.setPointer2Char(&m_characters[0]);
}

void GameItself::spawnPremiu()
{
	Premiu::PremiuType type = Premiu::STATIC;
	if(m_nrPremiiLuate > 2)
		type=Premiu::RUNNING;
	do
	{
		m_premiu.init(15.0f,type,sf::Vector2f(),sf::Vector2f((float)(rand() % (int)((m_window.getSize().x*4.0f/5.0f-(int)m_premiu.getHitboxRadius())+10)),(float)(rand() % (int)((m_window.getSize().y-(int)m_premiu.getHitboxRadius()-5)+10))));
	}while(Math::Distanta(m_premiu.getPosition(),m_characters[0].getPosition())<100);	
	m_premiu.setPointer2Char(&m_characters[0]);
}

//spawn enemy at random position
void GameItself::spawnEnemy()
{
	Enemy::EnemyType type=Enemy::STATIC;
	if (m_nrEnemies < 3)
		type = Enemy::STATIC;
	else if (m_nrEnemies < 8)
		type = Enemy::REFLECT;
	else
		type = Enemy::CHASE;
				
	do
	{
		m_enemies[m_nrEnemies].init(type,0,sf::Vector2f(),sf::Vector2f());
		m_enemies[m_nrEnemies].setPosition(sf::Vector2f((float)(rand() % (int)((m_window.getSize().x*4.0f/5.0f-(int)m_enemies[m_nrEnemies].getRadiusFromType(type))+5)),
														(float)(rand()%((m_window.getSize().y-(int)m_enemies[m_nrEnemies].getRadiusFromType(type)-5)+10))));
	}while(Math::Distanta(m_enemies[m_nrEnemies].getPosition(),m_characters[0].getPosition())<100+m_enemies[m_nrEnemies].getHitboxRadius());
	m_enemies[m_nrEnemies].setPointer2Char(&m_characters[0]);
	if((type == Enemy::REFLECT) || (type == Enemy::UNPREDICTABLE))
	{
		m_enemies[m_nrEnemies].setVelocity((float)rand() / (float)RAND_MAX * 360, 50.0f+25.0f*(type%10));
	}
	
	m_nrEnemies++;
}

void GameItself::gameReset()
{
	m_nrPremiiLuate = 0;
	m_characters[0].init(sf::Color::White, 25,sf::Vector2f(),((sf::Vector2f)m_window.getSize())*0.5f);
	spawnPremiu();
	m_nrEnemies=0;
	m_HUD.clearAll();
}

//----------------------------------------------------------------------------------------------------------FULL UPDATE-----------------------------------------------------------------------------------------
void GameItself::update(float dt)
{
	//UpdateGameLogic

	//General requirements
	sf::Joystick::update();

		
	switch(m_stareCurenta)
	{
	//init
	case INIT:
		{
			m_stareCurenta = SPLASHSCREEN;
			break;
		}

	//splashscreen
	case SPLASHSCREEN:
		{
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{
				m_stareCurenta = GAME;
				gameReset();
				PlayerPanel* p0 = new PlayerPanel(&m_players[0]);
				p0->setPosition(sf::Vector2f(m_window.getSize().x * 4.0f / 5.0f + 20.0f, 20.0f));
				m_HUD.addPanel(p0);
				m_HUD.init();
				m_snipe.setPosition(sf::Vector2f(m_window.getSize().x * 2.0f / 10.0f, m_window.getSize().y * 2.0f / 10.0f));
				m_snipe.setHit(false);
				m_players[0].m_character = &m_characters[0];
				m_players[0].m_inputDevice = 0;
				m_players[0].m_score = 0;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				m_window.close();
			break;
		}

	//meniu
	case MENIU:
		{
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
			{
				//m_music.play();
				m_stareCurenta = GAME;
				
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				m_window.close();

			break;
		}

	//game
	case GAME:
		{
			//														---------------------------------  game update ------------------------------
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
			{
				// set game state to main menu
				m_stareCurenta = MENIU;
				// ignore the current input
				break;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				m_window.close();

			//game time amplification
			dt *= m_globalTimeAmplification;
			
			//update all the powers of the characters
			m_characters[0].updatePowers(dt);

			//update characters
			m_characters[0].update(dt);

			//update premiu
			m_premiu.update(dt);

			//update snipe
			m_snipe.update(dt);
		

			if(m_snipe.hasHitTarget() == true)
			{
				m_stareCurenta = GAMEOVER;
			}
																		//------------------------ enemies.collision() -----------------------------
			//update enemies
			for(int i=0; i<m_nrEnemies;i++)
			{
				//collision enemy with player;
				if(Math::Collision(m_enemies[i].getPosition(),m_enemies[i].getHitboxRadius()-1,m_characters[0].getPosition(),m_characters[0].getHitboxRadius()-1))
				{	
					m_stareCurenta = GAMEOVER;
					
				}
				//----------------------------------------------------------------------collision enemies with borders-----------------------------------------
				//collision with borderLeft
				if(Math::Collision(m_enemies[i].getPosition(),m_enemies[i].getHitboxRadius(),sf::Vector2f(5.0f,1.0f),sf::Vector2f(5.0f,0.0f)))
				{
					m_enemies[i].setPosition(sf::Vector2f(5+m_enemies[i].getHitboxRadius(),m_enemies[i].getPosition().y));
					m_enemies[i].reflect(sf::Vector2f(1.0f,0.0f));
				}
				//collision with borderRight
				if(Math::Collision(m_enemies[i].getPosition(),m_enemies[i].getHitboxRadius(),sf::Vector2f(m_window.getSize().x*4.0f/5.0f,0.0f),sf::Vector2f(m_window.getSize().x*4.0f/5.0f,1.0f)))
				{
					m_enemies[i].setPosition(sf::Vector2f(m_window.getSize().x*4.0f/5.0f-m_enemies[i].getHitboxRadius(),m_enemies[i].getPosition().y));
					m_enemies[i].reflect(sf::Vector2f(-1.0f,0.0f));
				}
				//collision with borderTop
				if(Math::Collision(m_enemies[i].getPosition(),m_enemies[i].getHitboxRadius(),sf::Vector2f(0.0f,5.0f),sf::Vector2f(1.0f,5.0f)))
				{
					m_enemies[i].setPosition(sf::Vector2f(m_enemies[i].getPosition().x,5+m_enemies[i].getHitboxRadius()));
					m_enemies[i].reflect(sf::Vector2f(0.0f,-1.0f));
				}
				//collision with borderBottom
				if(Math::Collision(m_enemies[i].getPosition(),m_enemies[i].getHitboxRadius(),sf::Vector2f(1.0f,m_window.getSize().y-5.0f),sf::Vector2f(0.0f,m_window.getSize().y-5.0f)))
				{
					m_enemies[i].setPosition(sf::Vector2f(m_enemies[i].getPosition().x,m_window.getSize().y-5.0f-m_enemies[i].getHitboxRadius()));
					m_enemies[i].reflect(sf::Vector2f(0.0f,1.0f));
				}
				//now moving enemy
				m_enemies[i].update(dt);
			}

			//--------------------------------------------------------------------- collisions player with borders-------------------------------------------
			//collision with borderLeft
			bool hasCollided = false;
			if(Math::Collision(m_characters[0].getPosition(),m_characters[0].getHitboxRadius(),sf::Vector2f(5.0f,1.0f),sf::Vector2f(5.0f,0.0f)))
			{
				hasCollided = true;
				m_characters[0].setPosition(sf::Vector2f(5.0f+m_characters[0].getHitboxRadius(),m_characters[0].getPosition().y));
			}
			//collision with borderRight
			if(Math::Collision(m_characters[0].getPosition(),m_characters[0].getHitboxRadius(),sf::Vector2f(m_window.getSize().x*4.0f/5.0f,0.0f),sf::Vector2f(m_window.getSize().x*4.0f/5.0f,1.0f)))
			{
				hasCollided = true;
				m_characters[0].setPosition(sf::Vector2f(m_window.getSize().x*4.0f/5.0f-m_characters[0].getHitboxRadius(),m_characters[0].getPosition().y));
			}
			//collision with borderTop
			if(Math::Collision(m_characters[0].getPosition(),m_characters[0].getHitboxRadius(),sf::Vector2f(0.0f,5.0f),sf::Vector2f(1.0f,5.0f)))
			{
				hasCollided = true;
				m_characters[0].setPosition(sf::Vector2f(m_characters[0].getPosition().x,5.0f+m_characters[0].getHitboxRadius()));
			}
			//collision with borderBottom
			if(Math::Collision(m_characters[0].getPosition(),m_characters[0].getHitboxRadius(),sf::Vector2f(1.0f,m_window.getSize().y-5.0f),sf::Vector2f(0.0f,m_window.getSize().y-5.0f)))
			{
				hasCollided = true;
				m_characters[0].setPosition(sf::Vector2f(m_characters[0].getPosition().x,m_window.getSize().y-5.0f-m_characters[0].getHitboxRadius()));
			}
	
			//----------------------------------------------------------------------collision premiu cu borders-----------------------------------------
			//collision with borderLeft
			if(Math::Collision(m_premiu.getPosition(),m_premiu.getHitboxRadius(),sf::Vector2f(5.0f,1.0f),sf::Vector2f(5.0f,0.0f)))			
				m_premiu.setPosition(sf::Vector2f(5.0f+m_premiu.getHitboxRadius(),m_premiu.getPosition().y));
			//collision with borderRight
			if(Math::Collision(m_premiu.getPosition(),m_premiu.getHitboxRadius(),sf::Vector2f(m_window.getSize().x*4.0f/5.0f,0.0f),sf::Vector2f(m_window.getSize().x*4.0f/5.0f,1.0f)))
				m_premiu.setPosition(sf::Vector2f(m_window.getSize().x*4.0f/5.0f-m_premiu.getHitboxRadius(),m_premiu.getPosition().y));
			//collision with borderTop
			if(Math::Collision(m_premiu.getPosition(),m_premiu.getHitboxRadius(),sf::Vector2f(0.0f,5.0f),sf::Vector2f(1.0f,5.0f)))
				m_premiu.setPosition(sf::Vector2f(m_premiu.getPosition().x,5.0f+m_premiu.getHitboxRadius()));
			//collision with borderBottom
			if(Math::Collision(m_premiu.getPosition(),m_premiu.getHitboxRadius(),sf::Vector2f(1.0f,m_window.getSize().y-5.0f),sf::Vector2f(0.0f,m_window.getSize().y-5.0f)))
				m_premiu.setPosition(sf::Vector2f(m_premiu.getPosition().x,m_window.getSize().y-5.0f-m_premiu.getHitboxRadius()));
				

			//----------------------------------------------------------------------collision char with premiu --------------------------------------------
			if(Math::Collision(m_characters[0].getPosition(),m_characters[0].getHitboxRadius(),m_premiu.getPosition(),m_premiu.getHitboxRadius()))
			{
				spawnEnemy();
				m_nrPremiiLuate++;
				m_players[0].m_score++;
				spawnPremiu();
			}
			
			if(hasCollided==true)
			{
				if(m_edgeSound.getStatus() == sf::SoundSource::Status::Stopped)
					m_edgeSound.play();
			}

			m_HUD.update(dt);

			break;

		}


	//gameover
	case GAMEOVER:
		{
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{
				m_stareCurenta = SPLASHSCREEN;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				m_window.close();
			break;
		}

	}
} 
//------------------------------------------------------------------------------------------------------------------DRAW FULL----------------------------------------------------------------------------------
void GameItself::draw()
{
	// clear the window with black color
	m_window.clear(sf::Color::Black);
	auto x=5.0f;
	sf::Texture texture;
	sf::Sprite sprite;
	//Draw Everything Here
	switch(m_stareCurenta)
	{

	//init
	case INIT:
		break;

	//splash screen
	case SPLASHSCREEN:
		m_window.draw(m_splashscreenSprite);
		break;

	//meniu
	case MENIU:
		m_window.clear(sf::Color::Blue);
		break;

	//game
	case GAME:
		{
			//create borders
			sf::RectangleShape borderTop(sf::Vector2f((float)m_window.getSize().x,5.0f));
			sf::RectangleShape borderBottom(sf::Vector2f((float)m_window.getSize().x,5.0f));
			sf::RectangleShape borderLeft(sf::Vector2f(5.0f,(float)m_window.getSize().y));
			sf::RectangleShape borderRight(sf::Vector2f(5.0f,(float)m_window.getSize().y));
			sf::RectangleShape borderRight2(sf::Vector2f(5.0f,(float)m_window.getSize().y));
			//position borders
			borderTop.setPosition(0.0f,0.0f);
			borderBottom.setPosition(0.0f,m_window.getSize().y-5.0f);
			borderLeft.setPosition(0.0f,0.0f);
			borderRight.setPosition(m_window.getSize().x*4.0f/5.0f,0.0f);
			borderRight2.setPosition(m_window.getSize().x-5.0f,0.0f);
			//draw borders
			m_window.draw(borderTop);
			m_window.draw(borderBottom);
			m_window.draw(borderLeft);
			m_window.draw(borderRight);
			m_window.draw(borderRight2);

			//draw premiu
			m_premiu.draw(m_window);
			
			//draw enemies
			for(int i =0;i<m_nrEnemies;i++)
				m_enemies[i].draw(m_window);
			

			//draw character
			m_characters[0].draw(m_window);

			//draw HUD
			m_HUD.draw(m_window);

			//draw snipe
			m_snipe.draw(m_window);

			break;
		}

	//gameover
	case GAMEOVER:
		m_window.clear(sf::Color::White);
		sf::Text gameOverText;
		gameOverText.setFont(m_myFont);
		int x = 5;
		char xAsString[20];
		_itoa_s(x,xAsString,10);
		gameOverText.setString(xAsString);
		gameOverText.setOrigin(gameOverText.getLocalBounds().width/2.0f, gameOverText.getLocalBounds().height/2.0f);
		gameOverText.setPosition(m_window.getSize().x/2.0f, m_window.getSize().y/2.0f);
		gameOverText.setFillColor(sf::Color::Black);
		m_window.draw(gameOverText);
		break;

	}
	//end the current frame
	m_window.display();
}
