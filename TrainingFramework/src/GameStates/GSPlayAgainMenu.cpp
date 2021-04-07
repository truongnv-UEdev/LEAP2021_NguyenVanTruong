#include "GSPlayAgainMenu.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GSPlayAgainMenu::GSPlayAgainMenu()
{

}


GSPlayAgainMenu::~GSPlayAgainMenu()
{
}



void GSPlayAgainMenu::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	
	
	//Sound
	ResourceManagers::GetInstance()->PlaySound("bg_PlayAgain_Sound.wav", true);

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_play1");
	m_BackGround1 = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround1->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround1->SetSize(screenWidth, screenHeight);
	m_BackGround2 = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround2->Set2DPosition(screenWidth / 2, screenHeight / 2 - screenHeight);
	m_BackGround2->SetSize(screenWidth, screenHeight);


	//play button
	texture = ResourceManagers::GetInstance()->GetTexture("button_newgame");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, screenHeight / 2);
	button->SetSize(250, 60);
	button->SetOnClick([]() {
		ResourceManagers::GetInstance()->StopAllSound();
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
		});
	m_listButton.push_back(button);

	//exit button
	texture = ResourceManagers::GetInstance()->GetTexture("button_menu");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, (screenHeight / 2) + 75);
	button->SetSize(250, 60);
	button->SetOnClick([]() {
		ResourceManagers::GetInstance()->StopAllSound();
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
		});
	m_listButton.push_back(button);

	//text
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_Text = std::make_shared<Text>(shader, font, "YOU DIED!", TEXT_COLOR::RED, 4.0);
	m_Text->Set2DPosition(Vector2(screenWidth / 4, screenHeight / 6));

}

void GSPlayAgainMenu::Exit()
{
}


void GSPlayAgainMenu::Pause()
{

}

void GSPlayAgainMenu::Resume()
{

}


void GSPlayAgainMenu::HandleEvents()
{

}

void GSPlayAgainMenu::HandleKeyEvents(int key, bool bIsPressed)
{
	
}

void GSPlayAgainMenu::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSPlayAgainMenu::Update(float deltaTime)
{

	//Background
	MoveBackground(deltaTime);


	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSPlayAgainMenu::Draw()
{
	m_BackGround1->Draw();
	m_BackGround2->Draw();
	m_Text->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
}

void GSPlayAgainMenu::MoveBackground(GLfloat deltaTime) {
	//Background
	if (m_BackGround1->Get2DPosition().y > (screenHeight / 2 + screenHeight)) {
		m_BackGround1->Set2DPosition(screenWidth / 2, screenHeight / 2);
		m_BackGround2->Set2DPosition(screenWidth / 2, screenHeight / 2 - screenHeight);
	}
	m_BackGround1->Set2DPosition(screenWidth / 2, m_BackGround1->Get2DPosition().y + 100.0f * deltaTime);
	m_BackGround2->Set2DPosition(screenWidth / 2, m_BackGround2->Get2DPosition().y + 100.0f * deltaTime);
}

