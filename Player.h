#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Character.h"

class Player
{
public:

	//Input Device
	int m_inputDevice;

	//Character
	Character* m_character;

	//Score
	int m_score;
};

#endif //__PLAYER_H__