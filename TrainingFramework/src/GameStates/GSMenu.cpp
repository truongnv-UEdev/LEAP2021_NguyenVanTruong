#include "GSMenu.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GSMenu::GSMenu()
{

}


GSMenu::~GSMenu()
{
}



void GSMenu::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	
	//BG_Sound
	ResourceManagers::GetInstance()->PlaySound("bg_MainMenu_Sound.wav", true);

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_main_menu");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	//Game Logo
	texture = ResourceManagers::GetInstance()->GetTexture("game_logo");
	m_GameLogo = std::make_shared<Sprite2D>(model, shader, texture);
	m_GameLogo->Set2DPosition(screenWidth / 2, 120);
	m_GameLogo->SetSize(600, 200);

	//Background_menu
	texture = ResourceManagers::GetInstance()->GetTexture("bg_menu");
	menu_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	menu_BackGround->Set2DPosition(screenWidth / 2, (screenHeight / 2) + 100);
	menu_BackGround->SetSize(600, 400);

	//play button
	texture = ResourceManagers::GetInstance()->GetTexture("button_play");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth - 150, screenHeight - 175);
	button->SetSize(250, 60);
	button->SetOnClick([]() {
		ResourceManagers::GetInstance()->StopAllSound();
		GameStateMachine::GetInstance()->PushState(StateTypes::STATE_Play);
		});
	m_listButton.push_back(button);

	//About Me button
	texture = ResourceManagers::GetInstance()->GetTexture("button_aboutme");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(50, screenHeight - 100);
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PushState(StateTypes::STATE_AboutMe);
		});
	m_listButton.push_back(button);


	//exit button
	texture = ResourceManagers::GetInstance()->GetTexture("button_quit");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth -150, screenHeight - 100);
	button->SetSize(250, 60);
	button->SetOnClick([]() {
		exit(0);
		});
	m_listButton.push_back(button);


	////text game title
	//shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	//std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	//m_Text_gameName = std::make_shared< Text>(shader, font, "SAMPLE NAME", TEXT_COLOR::GREEN, 1.0);
	//m_Text_gameName->Set2DPosition(Vector2(screenWidth / 2 - 80, 120));
}

void GSMenu::Exit()
{
}


void GSMenu::Pause()
{

}

void GSMenu::Resume()
{

}


void GSMenu::HandleEvents()
{

}

void GSMenu::HandleKeyEvents(int key, bool bIsPressed)
{
	
}

void GSMenu::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSMenu::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	menu_BackGround->Update(deltaTime);
	m_GameLogo->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSMenu::Draw()
{
	m_BackGround->Draw();
	//menu_BackGround->Draw();
	m_GameLogo->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
}
