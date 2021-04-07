#pragma once
#include "gamestatebase.h"
#include "GameButton.h"
#include "Animation2D.h"
#include "MainCharacter.h"
#include "Enemy.h"
#include "BossEnemy.h"

class Sprite2D;
class Sprite3D;
class Text;

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void Init();
	void Exit();

	void Pause();
	void Resume();

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);

	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void Update(float deltaTime);
	void Draw();
	void SpawnCharacter();
	void CheckCollider(float deltaTime);

	//Phase
	void Phase1();
	void Phase2();
	void Phase3();
	void Phase4();
	void Phase5();
	void PhaseByTime();
	void PhaseControl();
	void CheckIsClear();


private:
	std::shared_ptr<Sprite2D> m_BackGround1;
	std::shared_ptr<Sprite2D> m_BackGround2;
	std::shared_ptr<MainCharacter> m_MainCharacter;
	std::vector<std::shared_ptr<Enemy>> m_listEnemy;
	std::vector<std::shared_ptr<Enemy>> m_listSecondEnemy;
	std::vector<std::shared_ptr<BossEnemy>> m_listBoss;
	std::vector<std::shared_ptr<Enemy>> m_listEnemyPerTime;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::vector<std::shared_ptr<Animation2D>> m_listAnim;
	std::vector<std::shared_ptr<Bullet>> m_listBulletMainC;
	std::vector<std::shared_ptr<Bullet>> m_listBulletEnemy;
	std::vector<std::shared_ptr<Sprite2D>> m_listBulletImpact;
	std::vector<std::shared_ptr<Sprite2D>> m_listExplosion;
	std::vector<std::shared_ptr<Sprite2D>> m_listShield;
	std::shared_ptr<Text>  m_txtYouDied;
	std::shared_ptr<Text>  m_txtVictory;
	std::shared_ptr<Text>  m_HPTitleMainC;
	std::shared_ptr<Text>  m_txtHPMainC;
	std::shared_ptr<Text>  m_txtHeartMainC;
	std::shared_ptr<Text>  m_txtCoin;


	float distX, distY, dist;
	bool phase1 = false, phase2 = false, phase3 = false, phase4 = false, phase5 = false, bossDie = false, clear = false;
	bool m_win = false;
	bool m_PlaySoundDie = false;
	bool m_PlaySoundVictory = false;
	bool m_ChangeState = false;
	float currentTime = 0;
	float m_timeToChangeState = 0;
	int phase = 0;
	int score = 0;
};

