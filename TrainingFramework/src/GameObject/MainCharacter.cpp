#include "MainCharacter.h"
#include "Shaders.h"
#include "Models.h"
#include "Camera.h"
#include "Texture.h"

extern GLint screenWidth;
extern GLint screenHeight;


MainCharacter::MainCharacter(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, float HP, int Heart)
	: Sprite2D(model, shader, texture)
{
	m_HP = HP;
	m_heart = Heart;
	//m_pModel = model;
	//m_pShader = shader;
	//m_pCamera = nullptr;
	//m_pTexture = texture;

	//m_Vec3Position = Vector3(0, 0, 0);
	//m_iHeight = 50;
	//m_iWidth = 100;
	//m_Vec3Scale = Vector3((float)m_iWidth / screenWidth, (float)m_iHeight / screenHeight, 1);
}

MainCharacter::MainCharacter(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, Vector4 color)
	: Sprite2D(model, shader, color)
{
	m_pModel = model;
	m_pShader = shader;
	m_pCamera = nullptr;
	m_pTexture = nullptr;
	m_Color = color;

	m_Vec3Position = Vector3(0, 0, 0);
	m_iHeight = 50;
	m_iWidth = 100;
	m_Vec3Scale = Vector3((float)m_iWidth / screenWidth, (float)m_iHeight / screenHeight, 1);
}

MainCharacter::~MainCharacter()
{
}

void MainCharacter::SetHP(int HP)
{
	m_HP = HP;
}

int MainCharacter::GetHP()
{
	return m_HP;
}

void MainCharacter::SetHeart(int Heart)
{
	m_heart = Heart;
}

bool MainCharacter::GetIsAlive()
{
	if (m_heart <= 0) {
		isAlive = false;
	}
	return isAlive;
}

void MainCharacter::SetIsAlive(bool IsAlive)
{
	isAlive = IsAlive;
}

bool MainCharacter::GetIsCanDash()
{
	return m_isCanDash;
}

void MainCharacter::SetIsCanDash(bool IsCanDash)
{
	m_isCanDash = IsCanDash;
}

int MainCharacter::GetHeart()
{
	return m_heart;
}

float MainCharacter::GetDamage()
{
	return m_damage;
}

void MainCharacter::Update(GLfloat deltatime)
{
	if (isMovingRight && isAlive) {
		MainCharacter::MoveRight(h, deltatime);
	}
	if (isMovingUp && isAlive) {
		MainCharacter::MoveUp(v, deltatime);
	}
}


void MainCharacter::HandleKeyEvents(unsigned char key, bool bIsPresseded)
{
	switch (key) {
	case KEY_MOVE_RIGHT:
		if (bIsPresseded) {
			h = 1;
			isMovingRight = true;
		}
		else {
			isMovingRight = false;
		}
		break;
	case KEY_MOVE_LEFT:
		if (bIsPresseded) {
			h = -1;
			isMovingRight = true;
		}
		else {
			isMovingRight = false;
		}
		break;
	case KEY_MOVE_FORWARD:
		if (bIsPresseded) {
			v = -1;
			isMovingUp = true;
		}
		else {
			isMovingUp = false;
		}
		break;
	case KEY_MOVE_BACKWARD:
		if (bIsPresseded) {
			v = 1;
			isMovingUp = true;
		}
		else {
			isMovingUp = false;
		}
		break;
	case KEY_RIGHT:
		if (bIsPresseded) {
			h = 1;
			isMovingRight = true;
		}
		else {
			isMovingRight = false;
		}
		break;
	case KEY_LEFT:
		if (bIsPresseded) {
			h = -1;
			isMovingRight = true;
		}
		else {
			isMovingRight = false;
		}
		break;
	case KEY_UP:
		if (bIsPresseded) {
			v = -1;
			isMovingUp = true;
		}
		else {
			isMovingUp = false;
		}
		break;
	case KEY_DOWN:
		if (bIsPresseded) {
			v = 1;
			isMovingUp = true;
		}
		else {
			isMovingUp = false;
		}
		break;
	case KEY_SPACEBAR:
		if (bIsPresseded) {

			isDash = true;
		}
		else {
			isDash = false;
		}
		break;
	}
}

void MainCharacter::HandleTouchEvents(GLint x, GLint y, bool bIsPressed) {
	if (bIsPressed) {
		MainCharacter::SetRotationZ(MainCharacter::Rotation(x, y));
		MainCharacter::SpeedforBullet(x, y);
	}
	else {

	}

}

void MainCharacter::MoveRight(float m, GLfloat deltaTime) {
	if (h > 0) {
		if (MainCharacter::Get2DPosition().x < screenWidth-50) {
			MainCharacter::Set2DPosition((MainCharacter::Get2DPosition().x + (MovementSpeed * m) * deltaTime), MainCharacter::Get2DPosition().y);
		}
	}
	else {
		if (MainCharacter::Get2DPosition().x > 50) {
			MainCharacter::Set2DPosition((MainCharacter::Get2DPosition().x + (MovementSpeed * m) * deltaTime), MainCharacter::Get2DPosition().y);
		}
	}
}

void MainCharacter::MoveUp(float m, GLfloat deltaTime) {
	if (v > 0) {
		if (MainCharacter::Get2DPosition().y < screenHeight - 50) {
			MainCharacter::Set2DPosition(MainCharacter::Get2DPosition().x, MainCharacter::Get2DPosition().y + (MovementSpeed * m) * deltaTime);
		}
	}
	else {
		if (MainCharacter::Get2DPosition().y > 50) {
			MainCharacter::Set2DPosition(MainCharacter::Get2DPosition().x, MainCharacter::Get2DPosition().y + (MovementSpeed * m) * deltaTime);
		}
	}	
}

void MainCharacter::Dash(float m, float n, GLfloat deltaTime) {
	if (MainCharacter::Get2DPosition().y < screenHeight - 50 && MainCharacter::Get2DPosition().y > 0 && MainCharacter::Get2DPosition().x < screenWidth - 50 && MainCharacter::Get2DPosition().x > 0) {
		MainCharacter::Set2DPosition(MainCharacter::Get2DPosition().x + (DashSpeed * m) * deltaTime, MainCharacter::Get2DPosition().y + (DashSpeed * n) * deltaTime);
	}
}

float MainCharacter::Rotation(GLint x, GLint y) {
	a = MainCharacter::Get2DPosition().y - y;
	b = x - MainCharacter::Get2DPosition().x;

	if (a >= 0 && b <= 0) {
		return sin(PI / 2) - abs(a) / abs(sqrt(a * a + b * b));
	}
	else if (a >= 0 && b >= 0) return -(sin(PI / 2) - abs(a) / abs(sqrt(a * a + b * b)));
	else if (a <= 0 && b >= 0) return -(abs(a) / abs(sqrt(a * a + b * b)) + PI / 2);
	else return abs(a) / abs(sqrt(a * a + b * b)) + PI / 2;
}

std::shared_ptr<Bullet> MainCharacter::Fire() {
	//create Bullet
		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
		auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
		auto texture = ResourceManagers::GetInstance()->GetTexture("bulletT_Main");
		std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(model, shader, texture, SpeedBulletX, hb, SpeedBulletY, vb, MainCharacter::GetDamage(), "laser.mp3");
		bullet->Set2DPosition(Vector2(MainCharacter::Get2DPosition().x, MainCharacter::Get2DPosition().y));
		bullet->SetSize(20, 20);
		return bullet;
}

void MainCharacter::SpeedforBullet(GLint x, GLint y)
{
	float a = MainCharacter::Get2DPosition().y - y;
	float b = x - MainCharacter::Get2DPosition().x;
	if (a >= 0) vb = -1; else vb = 1;
	if (b >= 0) hb = 1; else hb = -1;
	SpeedBulletX = BulletSpeed * abs(b) / abs(sqrt(a * a + b * b));
	SpeedBulletY = BulletSpeed * abs(a) / abs(sqrt(a * a + b * b));
}

std::shared_ptr<Sprite2D> MainCharacter::BulletImpact(GLint x, GLint y) {
	//create Impact
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("impact");
	std::shared_ptr<Sprite2D> impact = std::make_shared<Sprite2D>(model, shader, texture);
	impact->SetDeleteTime(0.15);
	impact->Set2DPosition(Vector2(x, y));
	impact->SetSize(40, 40);
	ResourceManagers::GetInstance()->PlaySound("bullet_Impact.wav", false);
	return impact;
}

void MainCharacter::Collider(GLfloat deltaTime)
{
	MainCharacter::m_HP -= DPS*deltaTime;


}

std::shared_ptr<Animation2D> MainCharacter::Explosion(GLint x, GLint y) {
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

std::shared_ptr<Sprite2D> MainCharacter::Shield(GLint x, GLint y) {
	//creatShield
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("shield");
	std::shared_ptr<Sprite2D> shield = std::make_shared<Sprite2D>(model, shader, texture);
	shield->SetDeleteTime(0.01);
	shield->Set2DPosition(Vector2(x, y));
	shield->SetSize(MainSize + 20, MainSize + 20);
	return shield;
}