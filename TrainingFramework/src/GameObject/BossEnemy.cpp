#include "BossEnemy.h"
#include "Shaders.h"
#include "Models.h"
#include "Camera.h"
#include "Texture.h"

extern GLint screenWidth;
extern GLint screenHeight;


BossEnemy::BossEnemy(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, float HP, float damage, float TimetoFire, const char* bulletTexture)
	: Enemy(model, shader, texture, HP, damage, TimetoFire, bulletTexture)
{
	m_bulletTexture = bulletTexture;
	ResourceManagers::GetInstance()->PlaySound("boss_Start.wav", false);
}


BossEnemy::~BossEnemy()
{
	std::cout << "Enemy deleted!" << std::endl;
}


void BossEnemy::Update(GLfloat deltatime)
{
	Enemy::Update(deltatime);
}


void BossEnemy::HandleKeyEvents(unsigned char key, bool bIsPresseded)
{

}

void BossEnemy::HandleTouchEvents(GLint x, GLint y, bool bIsPressed) {

}

void BossEnemy::SpeedforBullet(GLint x, GLint y)
{
	float a = Enemy::Get2DPosition().y - y;
	float b = x - Enemy::Get2DPosition().x;
	if (a >= 0) vb = -1; else vb = 1;
	if (b >= 0) hb = 1; else hb = -1;
	SpeedBulletX = BulletSpeed * abs(b) / abs(sqrt(a * a + b * b));
	SpeedBulletY = BulletSpeed * abs(a) / abs(sqrt(a * a + b * b));
}

std::shared_ptr<Bullet> BossEnemy::Fire1(GLint x, GLint y) {
	BossEnemy::SetRotationZ(BossEnemy::Rotation(x, y));
	BossEnemy::SpeedforBullet(x, y);
	//create Bullet
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture(m_bulletTexture);

	std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(model, shader, texture, SpeedBulletX, hb, SpeedBulletY, vb, Enemy::GetDamage(), "enemy_shot.mp3");
	bullet->Set2DPosition(Vector2(BossEnemy::Get2DPosition().x, BossEnemy::Get2DPosition().y));
	bullet->SetSize(20, 20);
	return bullet;
}

std::shared_ptr<Bullet> BossEnemy::Fire2A(GLint x, GLint y) {
	BossEnemy::SetRotationZ(BossEnemy::Rotation(x, y));
	BossEnemy::SpeedforBullet(x - 40, y);
	//create Bullet
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture(m_bulletTexture);

	std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(model, shader, texture, SpeedBulletX, hb, SpeedBulletY, vb, Enemy::GetDamage(), "enemy_shot.mp3");
	bullet->Set2DPosition(Vector2(Enemy::Get2DPosition().x - 20, Enemy::Get2DPosition().y));
	bullet->SetSize(20, 20);
	return bullet;
}
std::shared_ptr<Bullet> BossEnemy::Fire2B(GLint x, GLint y) {
	BossEnemy::SetRotationZ(BossEnemy::Rotation(x, y));
	BossEnemy::SpeedforBullet(x + 40, y);
	//create Bullet
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture(m_bulletTexture);

	std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(model, shader, texture, SpeedBulletX, hb, SpeedBulletY, vb, Enemy::GetDamage(), "enemy_shot.mp3");
	bullet->Set2DPosition(Vector2(Enemy::Get2DPosition().x + 20, Enemy::Get2DPosition().y));
	bullet->SetSize(20, 20);
	return bullet;
}

std::shared_ptr<Bullet> BossEnemy::Fire3A(GLint x, GLint y) {
	BossEnemy::SetRotationZ(BossEnemy::Rotation(x, y));
	BossEnemy::SpeedforBullet(x - 70, y);
	//create Bullet
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture(m_bulletTexture);

	std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(model, shader, texture, SpeedBulletX, hb, SpeedBulletY, vb, Enemy::GetDamage(), "enemy_shot.mp3");
	bullet->Set2DPosition(Vector2(BossEnemy::Get2DPosition().x - 40, BossEnemy::Get2DPosition().y));
	bullet->SetSize(20, 20);
	return bullet;
}
std::shared_ptr<Bullet> BossEnemy::Fire3B(GLint x, GLint y) {
	BossEnemy::SetRotationZ(BossEnemy::Rotation(x, y));
	BossEnemy::SpeedforBullet(x + 70, y);
	//create Bullet
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture(m_bulletTexture);

	std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(model, shader, texture, SpeedBulletX, hb, SpeedBulletY, vb, Enemy::GetDamage(), "enemy_shot.mp3");
	bullet->Set2DPosition(Vector2(BossEnemy::Get2DPosition().x + 40, BossEnemy::Get2DPosition().y));
	bullet->SetSize(20, 20);
	return bullet;
}


std::shared_ptr<Animation2D> BossEnemy::Explosion(GLint x, GLint y) {
	//create Explosion
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("explosion");
	std::shared_ptr<Animation2D> explosion = std::make_shared<Animation2D>(model, shader, texture, 6, 0.15f);
	explosion->SetDeleteTime(2);
	explosion->Set2DPosition(Vector2(x, y));
	explosion->SetSize(200, 200);
	ResourceManagers::GetInstance()->PlaySound("base_explosion.mp3", false);
	return explosion;
}

