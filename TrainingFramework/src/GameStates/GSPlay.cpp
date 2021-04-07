#include "GSPlay.h"
#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GSPlay::GSPlay()
{
	//BG_Sound
	ResourceManagers::GetInstance()->PlaySound("bg_Play_Sound.wav", true);
}


GSPlay::~GSPlay()
{
	ResourceManagers::GetInstance()->StopAllSound();
}


void GSPlay::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	//BackGround 1
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_play1");
	m_BackGround1 = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround1->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround1->SetSize(screenWidth, screenHeight);
	//BackGround 2
	texture = ResourceManagers::GetInstance()->GetTexture("bg_play1");
	m_BackGround2 = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround2->Set2DPosition(screenWidth / 2, screenHeight / 2 - screenHeight);
	m_BackGround2->SetSize(screenWidth, screenHeight);

	//Main Character
	texture = ResourceManagers::GetInstance()->GetTexture("MainCharacter");
	m_MainCharacter = std::make_shared<MainCharacter>(model, shader, texture, 500, 3);
	SpawnCharacter();
	//text game
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_txtHeartMainC = std::make_shared<Text>(shader, font,"x " + std::to_string(m_MainCharacter->GetHeart()), TEXT_COLOR::RED, 1.0);
	m_txtHeartMainC->Set2DPosition(Vector2(90, 130));
	m_txtCoin = std::make_shared<Text>(shader, font, "x " + std::to_string(m_MainCharacter->GetHeart()), TEXT_COLOR::YELLOW, 1.0);
	m_txtCoin->Set2DPosition(Vector2(90, 60));
	m_txtYouDied = std::make_shared<Text>(shader, font, "YOU DIED! ", TEXT_COLOR::RED, 4.0);
	m_txtYouDied->Set2DPosition(screenWidth / 4, -100);
	m_txtVictory = std::make_shared<Text>(shader, font, "VICTORY!", TEXT_COLOR::GREEN, 4.0);
	m_txtVictory->Set2DPosition(screenWidth / 4, -100);

	//exit button
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	texture = ResourceManagers::GetInstance()->GetTexture("button_X2");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Vector2(screenWidth - 50, 50));
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		ResourceManagers::GetInstance()->StopAllSound();
		//GameStateMachine::GetInstance()->PopState();
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
		});
	m_listButton.push_back(button);

	//reset button
	texture = ResourceManagers::GetInstance()->GetTexture("button_reset");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Vector2(screenWidth - 120, 50));
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		ResourceManagers::GetInstance()->StopAllSound();
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
		});
	m_listButton.push_back(button);
	
	//Animation Heart
	auto animshader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	texture = ResourceManagers::GetInstance()->GetTexture("heart");
	std::shared_ptr<Animation2D> anim = std::make_shared<Animation2D>(model, animshader, texture, 8, 0.2f);
	anim->Set2DPosition(Vector2(50, 110));
	anim->SetSize(50, 50);
	m_listAnim.push_back(anim);

	//Animation Coin
	texture = ResourceManagers::GetInstance()->GetTexture("coin");
	anim = std::make_shared<Animation2D>(model, animshader, texture, 6, 0.1f);
	anim->Set2DPosition(Vector2(50, 50));
	anim->SetSize(50, 50);
	m_listAnim.push_back(anim);
}

void GSPlay::Exit()
{

}


void GSPlay::Pause()
{

}

void GSPlay::Resume()
{

}


void GSPlay::HandleEvents()
{

}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{

	m_MainCharacter->HandleKeyEvents(key, bIsPressed);
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
	m_MainCharacter->HandleTouchEvents(x, y, bIsPressed);

	//Bullet
	if((bIsPressed))
	{
		if (m_MainCharacter->GetIsAlive()) {
			m_listBulletMainC.push_back(m_MainCharacter->Fire());
		}
	}

}

void GSPlay::Update(float deltaTime)
{
	
	//Background
	if (m_BackGround1->Get2DPosition().y > (screenHeight / 2 + screenHeight)) {
		m_BackGround1->Set2DPosition(screenWidth / 2, screenHeight / 2);
		m_BackGround2->Set2DPosition(screenWidth / 2, screenHeight / 2 - screenHeight);
	}
	m_BackGround1->Set2DPosition(screenWidth / 2, m_BackGround1->Get2DPosition().y + 100.0f * deltaTime);
	m_BackGround2->Set2DPosition(screenWidth / 2, m_BackGround2->Get2DPosition().y + 100.0f * deltaTime);

	//Text
	m_txtHPMainC->setText(std::to_string(m_MainCharacter->GetHP()));
	//for (auto it : m_listTxtHPEnemy) {
	//	m_txtHPEnemy->setText(std::to_string(m_Enemy->GetHP()));
	//}


	//m_txtHPEnemy->Set2DPosition(Vector2(m_Enemy->Get2DPosition().x, m_Enemy->Get2DPosition().y + 50));
	m_txtHPMainC->Set2DPosition(Vector2(m_MainCharacter->Get2DPosition().x + 10, m_MainCharacter->Get2DPosition().y + 80));
	m_HPTitleMainC->Set2DPosition(Vector2(m_MainCharacter->Get2DPosition().x - 40, m_MainCharacter->Get2DPosition().y + 80));

	//Phase Control
	currentTime += deltaTime;
	if (!clear) {
		if (currentTime >= TimePerPhase) {
			PhaseByTime();
			currentTime -= TimePerPhase;
		}
	}
	PhaseControl();


	//Character
		//Main
	m_MainCharacter->Update(deltaTime);
	m_txtCoin->setText("x " + std::to_string(score));

		//Enemy
	for (int i = 0; i < m_listEnemy.size(); i++) {
		m_listEnemy[i]->Update(deltaTime);
		if (m_listEnemy[i]->GetIsCanFire()) {
			m_listBulletEnemy.push_back(m_listEnemy[i]->Fire(m_MainCharacter->Get2DPosition().x, m_MainCharacter->Get2DPosition().y));
			m_listEnemy[i]->SetIsCanFire(false);
		}
		if (!(m_listEnemy[i]->GetIsAlive())) {
			m_listExplosion.push_back(m_listEnemy[i]->Explosion(m_listEnemy[i]->Get2DPosition().x, m_listEnemy[i]->Get2DPosition().y));
			m_listEnemy.erase(m_listEnemy.begin() + i);
			score++;
			phase++;
		}
	}

	for (int i = 0; i < m_listSecondEnemy.size(); i++) {
		m_listSecondEnemy[i]->Update(deltaTime);
		if (m_listSecondEnemy[i]->GetIsCanFire()) {
			m_listBulletEnemy.push_back(m_listSecondEnemy[i]->Fire2A(m_MainCharacter->Get2DPosition().x, m_MainCharacter->Get2DPosition().y));
			m_listBulletEnemy.push_back(m_listSecondEnemy[i]->Fire2B(m_MainCharacter->Get2DPosition().x, m_MainCharacter->Get2DPosition().y));
			m_listSecondEnemy[i]->SetIsCanFire(false);
		}
		if (!(m_listSecondEnemy[i]->GetIsAlive())) {
			m_listExplosion.push_back(m_listSecondEnemy[i]->Explosion(m_listSecondEnemy[i]->Get2DPosition().x, m_listSecondEnemy[i]->Get2DPosition().y));
			m_listSecondEnemy.erase(m_listSecondEnemy.begin() + i);
			score+=2;
			phase++;
		}
	}

	for (int i = 0; i < m_listEnemyPerTime.size(); i++) {
		m_listEnemyPerTime[i]->Update(deltaTime);
		if (m_listEnemyPerTime[i]->GetIsCanFire()) {
			m_listBulletEnemy.push_back(m_listEnemyPerTime[i]->Fire(m_MainCharacter->Get2DPosition().x, m_MainCharacter->Get2DPosition().y));
			m_listEnemyPerTime[i]->SetIsCanFire(false);
		}
		if (!(m_listEnemyPerTime[i]->GetIsAlive())) {
			m_listExplosion.push_back(m_listEnemyPerTime[i]->Explosion(m_listEnemyPerTime[i]->Get2DPosition().x, m_listEnemyPerTime[i]->Get2DPosition().y));
			m_listEnemyPerTime.erase(m_listEnemyPerTime.begin() + i);
		}
	}

		//Boss
	for (int i = 0; i < m_listBoss.size(); i++) {
		m_listBoss[i]->Update(deltaTime);
		if (m_listBoss[i]->GetIsCanFire()) {
			m_listBulletEnemy.push_back(m_listBoss[i]->Fire1(m_MainCharacter->Get2DPosition().x, m_MainCharacter->Get2DPosition().y));
			m_listBulletEnemy.push_back(m_listBoss[i]->Fire2A(m_MainCharacter->Get2DPosition().x, m_MainCharacter->Get2DPosition().y));
			m_listBulletEnemy.push_back(m_listBoss[i]->Fire2B(m_MainCharacter->Get2DPosition().x, m_MainCharacter->Get2DPosition().y));
			m_listBulletEnemy.push_back(m_listBoss[i]->Fire3A(m_MainCharacter->Get2DPosition().x, m_MainCharacter->Get2DPosition().y));
			m_listBulletEnemy.push_back(m_listBoss[i]->Fire3B(m_MainCharacter->Get2DPosition().x, m_MainCharacter->Get2DPosition().y));
			m_listBoss[i]->SetIsCanFire(false);
		}
		if (!(m_listBoss[i]->GetIsAlive())) {
			m_listExplosion.push_back(m_listBoss[i]->Explosion(m_listBoss[i]->Get2DPosition().x-rand()%150, m_listBoss[i]->Get2DPosition().y-rand() % 150));
			m_listExplosion.push_back(m_listBoss[i]->Explosion(m_listBoss[i]->Get2DPosition().x+rand()% 20, m_listBoss[i]->Get2DPosition().y+ rand() % 150));
			m_listExplosion.push_back(m_listBoss[i]->Explosion(m_listBoss[i]->Get2DPosition().x+ rand()% 150, m_listBoss[i]->Get2DPosition().y- rand() % 150));
			m_listBoss.erase(m_listBoss.begin() + i);
			score += 5;
			phase++;
		}
	}
	

	//List
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	for (auto it : m_listAnim)
	{
		it->Update(deltaTime);
	}

	for (int i = 0; i < m_listBulletMainC.size(); i++) {
		m_listBulletMainC[i]->Update(deltaTime);
		if (!(m_listBulletMainC[i]->GetActive())) {
			m_listBulletMainC.erase(m_listBulletMainC.begin() + i);
		}
	}

	for (int i = 0; i < m_listShield.size(); i++) {
		m_listShield[i]->Update(deltaTime);
		if (!(m_listShield[i]->GetActive())) {
			m_listShield.erase(m_listShield.begin() + i);
		}
	}

	for (int i = 0; i < m_listBulletEnemy.size(); i++) {
		m_listBulletEnemy[i]->Update(deltaTime);
		if (!(m_listBulletEnemy[i]->GetActive())) {
			m_listBulletEnemy.erase(m_listBulletEnemy.begin() + i);
		}
	}

	for (int i = 0; i < m_listBulletImpact.size(); i++) {
		m_listBulletImpact[i]->Update(deltaTime);
		if (!(m_listBulletImpact[i]->GetActive())) {
			m_listBulletImpact.erase(m_listBulletImpact.begin() + i);
		}
	}

	for (int i = 0; i < m_listExplosion.size(); i++) {
		
		m_listExplosion[i]->Update(deltaTime);
		if (!(m_listExplosion[i]->GetActive())) {
			m_listExplosion.erase(m_listExplosion.begin() + i);
		}
	}
	//Check Collider
	GSPlay::CheckCollider(deltaTime);

	//Check Is Clear
	CheckIsClear();

	//Die
	if (m_MainCharacter->GetHP() <= 0) {
		m_MainCharacter->SetHeart((m_MainCharacter->GetHeart() - 1));
		m_listExplosion.push_back(m_MainCharacter->Explosion(m_MainCharacter->Get2DPosition().x, m_MainCharacter->Get2DPosition().y));
		if (m_MainCharacter->GetHeart() > 0) {
			GSPlay::SpawnCharacter();
			m_txtHeartMainC->setText("x " + std::to_string(m_MainCharacter->GetHeart()));
		}
		else {
			m_txtHeartMainC->setText("x " + std::to_string(m_MainCharacter->GetHeart()));
			m_MainCharacter->Set2DPosition(screenWidth /2, screenHeight + 200);
			m_MainCharacter->SetHP(30);
			m_MainCharacter->SetIsAlive(false);
			phase = 99;
			m_ChangeState = true;
		}
	}

	if (m_win && m_ChangeState) {
		if (m_txtVictory->Get2DPosition().y <= screenHeight / 6) {
			m_txtVictory->Set2DPosition(m_txtVictory->Get2DPosition().x, m_txtVictory->Get2DPosition().y + 100 * deltaTime);
		}
	}
	else if(!m_win && m_ChangeState) {
		if (m_txtYouDied->Get2DPosition().y <= screenHeight / 6) {
			m_txtYouDied->Set2DPosition(m_txtYouDied->Get2DPosition().x, m_txtYouDied->Get2DPosition().y + 100 * deltaTime);
		}
	}

	//Change State when Die or Victory
	if (m_ChangeState) {
		m_timeToChangeState += deltaTime;
		if (m_timeToChangeState >= TimeChangeState) {
			if (m_win) {
				ResourceManagers::GetInstance()->StopAllSound();
				GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Victory);
			}else
				GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_PlayAgainMenu);
		}
	}
}

void GSPlay::Draw()
{
	m_BackGround1->Draw();
	m_BackGround2->Draw();
	for (auto it : m_listBulletMainC) {
		it->Draw();
	}
	for (auto it : m_listBulletEnemy) {
		it->Draw();
	}
	m_MainCharacter->Draw();
	for (auto it : m_listEnemyPerTime) {
		it->Draw();
	}
	for (auto it : m_listEnemy) {
		it->Draw();
	}
	for (auto it : m_listSecondEnemy) {
		it->Draw();
	}
	for (auto it : m_listBoss) {
		it->Draw();
	}

	for (auto it : m_listShield) {
		it->Draw();
	}

	for (auto it : m_listBulletImpact) {
		it->Draw();
	}
	for (auto it : m_listExplosion) {
		it->Draw();
	}
	for (auto it : m_listAnim)
	{
		it->Draw();
	}

	m_HPTitleMainC->Draw();
	m_txtHPMainC->Draw();
	m_txtHeartMainC->Draw();
	m_txtCoin->Draw();
	m_txtYouDied->Draw();
	m_txtVictory->Draw();

	for (auto it : m_listButton)
	{
		it->Draw();
	}
}

void GSPlay::CheckCollider(float deltaTime) {
	//Collider Spaceship
		
	for (auto it : m_listEnemy) {
		distX = m_MainCharacter->Get2DPosition().y - it->Get2DPosition().y;
		distY = m_MainCharacter->Get2DPosition().x - it->Get2DPosition().x;
		dist = abs(sqrt(distX * distX + distY * distY));
		if (dist <= EnemySize/2 + MainSize/2) {
			m_MainCharacter->Collider(deltaTime);
			m_listShield.push_back(m_MainCharacter->Shield(m_MainCharacter->Get2DPosition().x, m_MainCharacter->Get2DPosition().y));
		}
	}
	for (auto it : m_listEnemyPerTime) {
		distX = m_MainCharacter->Get2DPosition().y - it->Get2DPosition().y;
		distY = m_MainCharacter->Get2DPosition().x - it->Get2DPosition().x;
		dist = abs(sqrt(distX * distX + distY * distY));
		if (dist <= EnemyPTSize / 2 + MainSize/2) {
			m_MainCharacter->Collider(deltaTime);
			m_listShield.push_back(m_MainCharacter->Shield(m_MainCharacter->Get2DPosition().x, m_MainCharacter->Get2DPosition().y));
		}
	}
	for (auto it : m_listSecondEnemy) {
		distX = m_MainCharacter->Get2DPosition().y - it->Get2DPosition().y;
		distY = m_MainCharacter->Get2DPosition().x - it->Get2DPosition().x;
		dist = abs(sqrt(distX * distX + distY * distY));
		if (dist <= SecondEnemySize/2 + MainSize / 2) {
			m_MainCharacter->Collider(deltaTime);
			m_listShield.push_back(m_MainCharacter->Shield(m_MainCharacter->Get2DPosition().x, m_MainCharacter->Get2DPosition().y));
		}
	}

	for (auto it : m_listBoss) {
		distX = m_MainCharacter->Get2DPosition().y - it->Get2DPosition().y;
		distY = m_MainCharacter->Get2DPosition().x - it->Get2DPosition().x;
		dist = abs(sqrt(distX * distX + distY * distY));
		if (dist <= BossSize/2 + MainSize / 2) {
			m_MainCharacter->Collider(deltaTime);
			m_listShield.push_back(m_MainCharacter->Shield(m_MainCharacter->Get2DPosition().x, m_MainCharacter->Get2DPosition().y));
		}
	}

	

	//Collider Bullet Enemy
	for (auto bullet : m_listBulletEnemy) {
		distX = m_MainCharacter->Get2DPosition().y - bullet->Get2DPosition().y;
		distY = m_MainCharacter->Get2DPosition().x - bullet->Get2DPosition().x;
		dist = abs(sqrt(distX * distX + distY * distY));
		if (dist <= MainSize/2 && m_MainCharacter->GetIsAlive()) {
			m_MainCharacter->SetHP(m_MainCharacter->GetHP() - bullet->GetDamage());
			m_listBulletImpact.push_back(m_MainCharacter->BulletImpact(bullet->Get2DPosition().x, bullet->Get2DPosition().y));
			bullet->SetActive(false);
		}
	}

	//Collider Bullet Main
	for (auto bullet : m_listBulletMainC) {
		//Enemy
		for (int enemy = 0; enemy < m_listEnemy.size(); enemy++) {
			distX = m_listEnemy[enemy]->Get2DPosition().y - bullet->Get2DPosition().y;
			distY = m_listEnemy[enemy]->Get2DPosition().x - bullet->Get2DPosition().x;
			dist = abs(sqrt(distX * distX + distY * distY));
			if (dist <= EnemySize/2) {
				m_listEnemy[enemy]->SetHP(m_listEnemy[enemy]->GetHP() - bullet->GetDamage());
				m_listBulletImpact.push_back(m_listEnemy[enemy]->BulletImpact(bullet->Get2DPosition().x, bullet->Get2DPosition().y));
				bullet->SetActive(false);
			}
		}
		for (int sEnemy = 0; sEnemy < m_listSecondEnemy.size(); sEnemy++) {
			distX = m_listSecondEnemy[sEnemy]->Get2DPosition().y - bullet->Get2DPosition().y;
			distY = m_listSecondEnemy[sEnemy]->Get2DPosition().x - bullet->Get2DPosition().x;
			dist = abs(sqrt(distX * distX + distY * distY));
			if (dist <= SecondEnemySize/2) {
				m_listSecondEnemy[sEnemy]->SetHP(m_listSecondEnemy[sEnemy]->GetHP() - bullet->GetDamage());
				m_listBulletImpact.push_back(m_listSecondEnemy[sEnemy]->BulletImpact(bullet->Get2DPosition().x, bullet->Get2DPosition().y));
				bullet->SetActive(false);
			}
		}
		//Enemy Per Time
		for (int enemypertime = 0; enemypertime < m_listEnemyPerTime.size(); enemypertime++) {
			distX = m_listEnemyPerTime[enemypertime]->Get2DPosition().y - bullet->Get2DPosition().y;
			distY = m_listEnemyPerTime[enemypertime]->Get2DPosition().x - bullet->Get2DPosition().x;
			dist = abs(sqrt(distX * distX + distY * distY));
			if (dist <= EnemyPTSize/2) {
				m_listEnemyPerTime[enemypertime]->SetHP(m_listEnemyPerTime[enemypertime]->GetHP() - bullet->GetDamage());
				m_listBulletImpact.push_back(m_listEnemyPerTime[enemypertime]->BulletImpact(bullet->Get2DPosition().x, bullet->Get2DPosition().y));
				bullet->SetActive(false);
			}
		}
		//Boss
		for (int boss = 0; boss < m_listBoss.size(); boss++) {
			distX = m_listBoss[boss]->Get2DPosition().y - bullet->Get2DPosition().y;
			distY = m_listBoss[boss]->Get2DPosition().x - bullet->Get2DPosition().x;
			dist = abs(sqrt(distX * distX + distY * distY));
			if (dist <= BossSize/2) {
				m_listBoss[boss]->SetHP(m_listBoss[boss]->GetHP() - bullet->GetDamage());
				m_listBulletImpact.push_back(m_listBoss[boss]->BulletImpact(bullet->Get2DPosition().x, bullet->Get2DPosition().y));
				bullet->SetActive(false);
			}
		}
	}
}

void GSPlay::SpawnCharacter()
{
	//Main Character
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_MainCharacter->Set2DPosition(Vector2(screenWidth / 2, screenHeight - 100));
	m_MainCharacter->SetSize(MainSize, MainSize);
	m_MainCharacter->SetHP(500);
	m_MainCharacter->SetIsAlive(true);
	//text game
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");

	//HP MainChar
	m_HPTitleMainC = std::make_shared<Text>(shader, font, "HP: ", TEXT_COLOR::GREEN, 1.0);
	m_HPTitleMainC->Set2DPosition(Vector2(m_MainCharacter->Get2DPosition().x - 40, m_MainCharacter->Get2DPosition().y + 50));
	m_txtHPMainC = std::make_shared<Text>(shader, font, std::to_string(m_MainCharacter->GetHP()), TEXT_COLOR::GREEN, 1.0);
	m_txtHPMainC->Set2DPosition(Vector2(m_MainCharacter->Get2DPosition().x, m_MainCharacter->Get2DPosition().y + 50));
}

void GSPlay::Phase1() {
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("EnemyCharacter");
	std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(model, shader, texture, 300, 20, 1,"bulletT_Enemy2");
	enemy->Set2DPosition(Vector2(screenWidth / 2, (rand() % 1000) * -1));
	enemy->SetSize(EnemySize, EnemySize);
	m_listEnemy.push_back(enemy);
}

void GSPlay::Phase2() {
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("EnemyCharacter4");
	std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(model, shader, texture, 500, 25, 1.2, "bulletT_Enemy4");
	enemy->Set2DPosition(Vector2((rand() % screenWidth) * -1, (rand() % 1000)) * -1);
	enemy->SetSize(EnemySize, EnemySize);
	m_listSecondEnemy.push_back(enemy);

	texture = ResourceManagers::GetInstance()->GetTexture("EnemyCharacter2");
	enemy = std::make_shared<Enemy>(model, shader, texture, 700, 25, 1.5, "bulletT_Enemy3");
	enemy->Set2DPosition(Vector2(rand() % screenWidth, (rand() % 1000)) * -1);
	enemy->SetSize(EnemySize, EnemySize);
	m_listEnemy.push_back(enemy);
}

void GSPlay::Phase3() {
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("EnemyCharacter2");
	std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(model, shader, texture, 400, 20, 1, "bulletT_Enemy2");
	enemy->Set2DPosition(Vector2((rand() % screenWidth) * -1, (rand() % 1000)) * -1);
	enemy->SetSize(EnemySize, EnemySize);
	m_listEnemy.push_back(enemy);

	texture = ResourceManagers::GetInstance()->GetTexture("EnemyCharacter3");
	enemy = std::make_shared<Enemy>(model, shader, texture, 700, 25, 1.5, "bulletT_Enemy3");
	enemy->Set2DPosition(Vector2(rand() % screenWidth, (rand() % 1000)) * -1);
	enemy->SetSize(EnemySize, EnemySize);
	m_listEnemy.push_back(enemy);

	texture = ResourceManagers::GetInstance()->GetTexture("EnemyCharacter3");
	enemy = std::make_shared<Enemy>(model, shader, texture, 700, 25, 1.5, "bulletT_Enemy3");
	enemy->Set2DPosition(Vector2(rand() % screenWidth /2, (rand() % 1000)) * -1);
	enemy->SetSize(EnemySize, EnemySize);
	m_listEnemy.push_back(enemy);
}

void GSPlay::Phase4() {
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("EnemyCharacter3");
	std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(model, shader, texture, 700, 15, 1.5, "bulletT_Enemy3");
	enemy->Set2DPosition(Vector2((rand() % screenWidth) * -1, (rand() % 1000)) * -1);
	enemy->SetSize(EnemySize, EnemySize);
	m_listEnemy.push_back(enemy);

	texture = ResourceManagers::GetInstance()->GetTexture("EnemyCharacter4");
	enemy = std::make_shared<Enemy>(model, shader, texture, 500, 20, 1.2, "bulletT_Enemy4");
	enemy->Set2DPosition(Vector2((rand() % screenWidth) * -1, (rand() % 1000)) * -1);
	enemy->SetSize(SecondEnemySize, SecondEnemySize);
	m_listSecondEnemy.push_back(enemy);

	texture = ResourceManagers::GetInstance()->GetTexture("EnemyCharacter4");
	enemy = std::make_shared<Enemy>(model, shader, texture, 500, 20, 1.2, "bulletT_Enemy4");
	enemy->Set2DPosition(Vector2((rand() % screenWidth) * -1, (rand() % 1000)) * -1);
	enemy->SetSize(SecondEnemySize, SecondEnemySize);
	m_listSecondEnemy.push_back(enemy);
}

void GSPlay::Phase5() {
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("BossCharacter");
	std::shared_ptr<BossEnemy> boss = std::make_shared<BossEnemy>(model, shader, texture, 2500, 40, 1.5, "bulletT_Boss");
	boss->Set2DPosition(Vector2(screenWidth/ 2, (rand() % 500 * -1)));
	boss->SetSize(BossSize, BossSize);
	m_listBoss.push_back(boss);

	texture = ResourceManagers::GetInstance()->GetTexture("EnemyCharacter4");
	std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(model, shader, texture, 500, 20, 1.2, "bulletT_Enemy4");
	enemy->Set2DPosition(Vector2(screenWidth / 2 - 700, (rand() % 500) * -1));
	enemy->SetSize(SecondEnemySize, SecondEnemySize);
	m_listSecondEnemy.push_back(enemy);

	texture = ResourceManagers::GetInstance()->GetTexture("EnemyCharacter4");
	enemy = std::make_shared<Enemy>(model, shader, texture, 500, 20, 1.2, "bulletT_Enemy4");
	enemy->Set2DPosition(Vector2(screenWidth / 2 - 700, (rand() % 500) * -1));
	enemy->SetSize(SecondEnemySize, SecondEnemySize);
	m_listSecondEnemy.push_back(enemy);
}

void GSPlay::PhaseByTime() {
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("EnemyCharacter");
	std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(model, shader, texture, 100, 10, 1.2, "bulletT_EnemyPT");
	enemy->Set2DPosition(Vector2((rand() % screenWidth/2 * -1), (rand() % 1000)*-1));
	enemy->SetSize(EnemyPTSize, EnemyPTSize);
	m_listEnemyPerTime.push_back(enemy);

	std::shared_ptr<Enemy> enemy1 = std::make_shared<Enemy>(model, shader, texture, 100, 10, 1.2, "bulletT_EnemyPT");
	enemy1->Set2DPosition(Vector2((screenWidth + rand() % 500), (rand() % 1000) * -1));
	enemy1->SetSize(EnemyPTSize, EnemyPTSize);
	m_listEnemyPerTime.push_back(enemy1);
}

void GSPlay::PhaseControl() {
	switch (phase) {
	case 0:
		if (!phase1) {
			Phase1();
			phase1 = true;
			std::cout << "----------------- PHASE 1 -----------------" << score << std::endl;
		}
		break;
	case 1:
		if (!phase2) {
			Phase2();
			phase2 = true;
			std::cout << "----------------- PHASE 2 -----------------" << score << std::endl;
		}
		break;
	case 3:
		if (!phase3) {
			Phase3();
			phase3 = true;
			std::cout << "----------------- PHASE 3 -----------------" << score << std::endl;
		}
		break;
	case 6:
		if (!phase4) {
			Phase4();
			phase4 = true;
			std::cout << "----------------- PHASE 4 -----------------" << score << std::endl;
		}
		break;
	case 9:
		if (!phase5) {
			Phase5();
			phase5 = true;
			std::cout << "----------------- PHASE 5 -----------------" << score << std::endl;
		}
		break;
	case 12:
		if (!bossDie) {
			std::cout << "----------------- WIN -----------------" << score << std::endl;
			clear = true;
			bossDie = true;
		}
		break;
	case 88:
		if (!m_PlaySoundVictory) {
			ResourceManagers::GetInstance()->PlaySound("victory.mp3", false);
			m_win = true;
			m_PlaySoundVictory = true;
			phase = 999;
		}
		break;
	case 99:
		if (!m_PlaySoundDie) {
			ResourceManagers::GetInstance()->StopAllSound();
			ResourceManagers::GetInstance()->PlaySound("game_over.wav", false);
			m_win = false;
			m_PlaySoundDie = true;
			phase = 999;
		}
		break;
	default:
		break;
	}
}

void GSPlay::CheckIsClear() {
	if (m_listEnemyPerTime.size() == 0 && bossDie) {
		m_ChangeState = true;
		phase = 88;
	}
}