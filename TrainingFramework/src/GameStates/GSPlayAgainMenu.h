#pragma once
#include "gamestatebase.h"
#include "GameButton.h"

class GSPlayAgainMenu :
	public GameStateBase
{
public:
	GSPlayAgainMenu();
	~GSPlayAgainMenu();
	
	void Init();
	void Exit();

	void Pause();
	void Resume();

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);
	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void Update(float deltaTime);
	void Draw();

	void MoveBackground(GLfloat deltaTime);

private:
	std::shared_ptr<Sprite2D> m_BackGround1;
	std::shared_ptr<Sprite2D> m_BackGround2;
	std::shared_ptr<Sprite2D> menu_BackGround;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::shared_ptr<Text>  m_Text;
	float cur = 0;

};

