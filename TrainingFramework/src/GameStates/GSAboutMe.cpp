#include "GSAboutMe.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GSAboutMe::GSAboutMe()
{

}


GSAboutMe::~GSAboutMe()
{
	
}



void GSAboutMe::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");

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

	//exit button
	texture = ResourceManagers::GetInstance()->GetTexture("button_X2");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(50, screenHeight - 100);
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		ResourceManagers::GetInstance()->StopAllSound();
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
		});
	m_listButton.push_back(button);

	//Text Info

	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("timesi");

	std::shared_ptr<Text> text = std::make_shared< Text>(shader, font, "GAMELOFT - LEAP2021", TEXT_COLOR::WHILE, 2.0);
	text->Set2DPosition(Vector2(screenWidth/2-360, screenHeight + 50));
	m_listText.push_back(text);

	text = std::make_shared< Text>(shader, font, "BAHAMUT", TEXT_COLOR::WHILE, 1.5);
	text->Set2DPosition(Vector2(screenWidth / 2-340, screenHeight + 100));
	m_listText.push_back(text);

	text = std::make_shared< Text>(shader, font, "Nguyen Van Truong", TEXT_COLOR::WHILE, 1.5);
	text->Set2DPosition(Vector2(screenWidth / 2- 340, screenHeight + 150));
	m_listText.push_back(text);

	text = std::make_shared< Text>(shader, font, "01/09/1999 - Thai Binh", TEXT_COLOR::WHILE, 1.5);
	text->Set2DPosition(Vector2(screenWidth / 2 - 340, screenHeight + 200));
	m_listText.push_back(text);

	text = std::make_shared< Text>(shader, font, "Hoc Vien Cong Nghe Buu Chinh Vien Thong", TEXT_COLOR::WHILE, 1.5);
	text->Set2DPosition(Vector2(screenWidth / 2 - 340, screenHeight + 250));
	m_listText.push_back(text);

	text = std::make_shared< Text>(shader, font, "Em cam on anh Hoang, anh Hung da giup do em", TEXT_COLOR::WHILE, 1.5);
	text->Set2DPosition(Vector2(screenWidth / 2 - 340, screenHeight + 350));
	m_listText.push_back(text);

	text = std::make_shared< Text>(shader, font, "trong suot qua trinh thuc tap tai Gameloft.", TEXT_COLOR::WHILE, 1.5);
	text->Set2DPosition(Vector2(screenWidth / 2 - 340, screenHeight + 400));
	m_listText.push_back(text);

	text = std::make_shared< Text>(shader, font, "Em cung cam on chi Thao da giup do em trong", TEXT_COLOR::WHILE, 1.5);
	text->Set2DPosition(Vector2(screenWidth / 2 - 340, screenHeight + 500));
	m_listText.push_back(text);

	text = std::make_shared< Text>(shader, font, "qua trinh tuyen chon.", TEXT_COLOR::WHILE, 1.5);
	text->Set2DPosition(Vector2(screenWidth / 2 - 340, screenHeight + 550));
	m_listText.push_back(text);

	text = std::make_shared< Text>(shader, font, "Cam on cong ty Gameloft da to chuc", TEXT_COLOR::WHILE, 1.5);
	text->Set2DPosition(Vector2(screenWidth / 2 - 340, screenHeight + 650));
	m_listText.push_back(text);

	text = std::make_shared< Text>(shader, font, "chuong trinh thuc tap cho bon em. ", TEXT_COLOR::WHILE, 1.5);
	text->Set2DPosition(Vector2(screenWidth / 2 - 340, screenHeight + 700));
	m_listText.push_back(text);

	text = std::make_shared< Text>(shader, font, "Thanks For All!!! ", TEXT_COLOR::RED, 2.5);
	text->Set2DPosition(Vector2(screenWidth / 2 - 340, screenHeight + 800));
	m_listText.push_back(text);
}

void GSAboutMe::Exit()
{
}


void GSAboutMe::Pause()
{

}

void GSAboutMe::Resume()
{

}


void GSAboutMe::HandleEvents()
{

}

void GSAboutMe::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSAboutMe::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSAboutMe::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	menu_BackGround->Update(deltaTime);
	m_GameLogo->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	MoveInfo(deltaTime);
	m_currentTime += deltaTime;
	if (m_currentTime >= 30) {
		ResourceManagers::GetInstance()->StopAllSound();
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
	}
}

void GSAboutMe::Draw()
{
	m_BackGround->Draw();
	//menu_BackGround->Draw();
	m_GameLogo->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	for (auto it : m_listText)
	{
		it->Draw();
	}
}

void GSAboutMe::MoveInfo(float deltaTime) {
	for (auto it : m_listText) {
		it->Set2DPosition(it->Get2DPosition().x, it->Get2DPosition().y - 40 * deltaTime);
	}
}

