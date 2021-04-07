#include "Enemy.h"
#include "Shaders.h"
#include "Models.h"
#include "Camera.h"
#include "Texture.h"

extern GLint screenWidth;
extern GLint screenHeight;


Enemy::Enemy(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, float HP, float damage, float TimetoFire, const char *bulletTexture)
	: Sprite2D(model, shader, texture)
{
	m_HP = HP;
	m_damage = damage;
	m_timeToFire = TimetoFire;
	m_bulletTexture = bulletTexture;
	//m_pModel = model;
	//m_pShader = shader;
	//m_pCamera = nullptr;
	//m_pTexture = texture;

	//m_Vec3Position = Vector3(0, 0, 0);
	//m_iHeight = 50;
	//m_iWidth = 100;
	//m_Vec3Scale = Vector3((float)m_iWidth / screenWidth, (float)m_iHeight / screenHeight, 1);
}


Enemy::~Enemy()
{
	std::cout << "Enemy deleted!" << std::endl;
}

int Enemy::GetHP()
{
	return Enemy::m_HP;
}

void Enemy::SetHP(float HP)
{
	m_HP = HP;
}

float Enemy::GetDamage()
{
	return m_damage;
}

float Enemy::GetTimeToFire()
{
	return m_timeToFire;
}

void Enemy::Collider(GLfloat deltaTime)
{
	Enemy::m_HP -= 20 * deltaTime;
}

void Enemy::SetIsAlive(bool alive) {
	m_isAlive = alive;
}
bool Enemy::GetIsAlive() {
	return m_isAlive;
}

void Enemy::SetIsCanFire(bool fire) {
	m_isCanFire = fire;
}
bool Enemy::GetIsCanFire() {
	return m_isCanFire;
}

void Enemy::IsAlive() {
	if (m_HP <= 0) {
		Enemy::SetIsAlive(false);
	}
}

void Enemy::Update(GLfloat deltatime)
{
	m_currentTime += deltatime;
	//Fire
	if (m_currentTime >= m_timeToFire) {
		m_isCanFire = true;
		m_currentTime -= m_timeToFire;
	}
	
	//Moving
	if (Enemy::Get2DPosition().x > screenWidth) h = -1; else if (Enemy::Get2DPosition().x < 10) h = 1;
	if (Enemy::Get2DPosition().y > screenHeight) v = -1; else if (Enemy::Get2DPosition().y < 10) v = 1;
	Enemy::Move(h, v, deltatime);

	//IsAlive
	Enemy::IsAlive();
}


void Enemy::HandleKeyEvents(unsigned char key, bool bIsPresseded)
{

}

void Enemy::HandleTouchEvents(GLint x, GLint y, bool bIsPressed) {

}

void Enemy::Move(float H, float V, GLfloat deltaTime) {
	Enemy::Set2DPosition(Enemy::Get2DPosition().x + (rand() % EnemyMovementSpeed) * H * deltaTime, Enemy::Get2DPosition().y + (rand() % EnemyMovementSpeed) * V * deltaTime);
}


float Enemy::Rotation(GLint x, GLint y) {
	a = Enemy::Get2DPosition().y - y;
	b = x - Enemy::Get2DPosition().x;
	if (a <= 0 && b >= 0) {
		return sin(PI / 2) - abs(a) / abs(sqrt(a * a + b * b));
	}
	else if (a <= 0 && b <= 0) return -(sin(PI / 2) - abs(a) / abs(sqrt(a * a + b * b)));
	else if (a >= 0 && b <= 0) return -(abs(a) / abs(sqrt(a * a + b * b)) + PI / 2);
	else return abs(a) / abs(sqrt(a * a + b * b)) + PI / 2;
}

void Enemy::SpeedforBullet(GLint x, GLint y)
{
	float a = Enemy::Get2DPosition().y - y;
	float b = x - Enemy::Get2DPosition().x;
	if (a >= 0) vb = -1; else vb = 1;
	if (b >= 0) hb = 1; else hb = -1;
	SpeedBulletX = BulletSpeed * abs(b) / abs(sqrt(a * a + b * b));
	SpeedBulletY = BulletSpeed * abs(a) / abs(sqrt(a * a + b * b));
}

std::shared_ptr<Bullet> Enemy::Fire(GLint x, GLint y) {
	Enemy::SetRotationZ(Enemy::Rotation(x, y));
	Enemy::SpeedforBullet(x, y);
	//create Bullet
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture(m_bulletTexture);

	std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(model, shader, texture, SpeedBulletX, hb, SpeedBulletY, vb, Enemy::GetDamage(), "laser2.mp3");
	bullet->Set2DPosition(Vector2(Enemy::Get2DPosition().x, Enemy::Get2DPosition().y));
	bullet->SetSize(20, 20);
	return bullet;
}

std::shared_ptr<Bullet> Enemy::Fire2A(GLint x, GLint y) {
	Enemy::SetRotationZ(Enemy::Rotation(x, y));
	Enemy::SpeedforBullet(x-20, y);
	//create Bullet
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture(m_bulletTexture);

	std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(model, shader, texture, SpeedBulletX, hb, SpeedBulletY, vb, Enemy::GetDamage(), "laser2.mp3");
	bullet->Set2DPosition(Vector2(Enemy::Get2DPosition().x-20, Enemy::Get2DPosition().y));
	bullet->SetSize(20, 20);
	return bullet;
}

std::shared_ptr<Bullet> Enemy::Fire2B(GLint x, GLint y) {
	Enemy::SetRotationZ(Enemy::Rotation(x, y));
	Enemy::SpeedforBullet(x+20, y);
	//create Bullet
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture(m_bulletTexture);

	std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(model, shader, texture, SpeedBulletX, hb, SpeedBulletY, vb, Enemy::GetDamage(), "laser2.mp3");
	bullet->Set2DPosition(Vector2(Enemy::Get2DPosition().x + 20, Enemy::Get2DPosition().y));
	bullet->SetSize(20, 20);
	return bullet;
}
std::shared_ptr<Sprite2D> Enemy::BulletImpact(GLint x, GLint y) {
	//create Impact
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("impact");
	std::shared_ptr<Sprite2D> impact = std::make_shared<Sprite2D>(model, shader, texture);
	impact->SetDeleteTime(0.15);
	impact->Set2DPosition(Vector2(x, y));
	impact->SetSize(40, 40);
	ResourceManagers::GetInstance()->PlaySound("bullet_Impact_main.wav", false);
	return impact;
}

std::shared_ptr<Animation2D> Enemy::Explosion(GLint x, GLint y) {
	//create Explosion
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("explosion");
	std::shared_ptr<Animation2D> explosion = std::make_shared<Animation2D>(model, shader, texture, 6, 0.15f);
	explosion->SetDeleteTime(1);
	explosion->Set2DPosition(Vector2(x, y));
	explosion->SetSize(120, 120);
	ResourceManagers::GetInstance()->PlaySound("explosion.wav", false);
	return explosion;
}

