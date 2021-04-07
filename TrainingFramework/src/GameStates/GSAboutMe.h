#pragma once
#include "gamestatebase.h"
#include "GameButton.h"

class GSAboutMe :
	public GameStateBase
{
public:
	GSAboutMe();
	~GSAboutMe();

	void Init();
	void Exit();

	void Pause();
	void Resume();

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);
	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void Update(float deltaTime);
	void Draw();

	void MoveInfo(float deltaTime);

private:
	std::shared_ptr<Sprite2D> m_BackGround;
	std::shared_ptr<Sprite2D> menu_BackGround;
	std::shared_ptr<Sprite2D> m_GameLogo;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::vector<std::shared_ptr<Text>> m_listText;

	float m_currentTime = 0;
};

