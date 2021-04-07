/*
#include "GSIntro.h"
#include "GSMenu.h"
*/
#include "GSPlay.h"
#include "GSIntro.h"
#include "GSMenu.h"
#include "GSPlayAgainMenu.h"
#include "GSVictory.h"
#include "GSAboutMe.h"

#include "GameStatebase.h"

std::shared_ptr<GameStateBase> GameStateBase::CreateState(StateTypes stt)
{
	std::shared_ptr<GameStateBase> gs = nullptr;
	switch (stt)
	{
	case STATE_INVALID:
		break;
	case STATE_Intro:
		gs = std::make_shared<GSIntro>();
		break;
	case STATE_Menu:
		gs = std::make_shared<GSMenu>();
		break;
	case STATE_Play:
		gs = std::make_shared<GSPlay>();
		break;
	case STATE_PlayAgainMenu:
		gs = std::make_shared<GSPlayAgainMenu>();
		break;
	case STATE_Victory:
		gs = std::make_shared<GSVictory>();
		break;
	case STATE_AboutMe:
		gs = std::make_shared<GSAboutMe>();
		break;
	default:
		break;
	}
	return gs;
}