#include "Bullet.h"
#include "Shaders.h"
#include "Models.h"
#include "Camera.h"
#include "Texture.h"


extern GLint screenWidth;
extern GLint screenHeight;


Bullet::Bullet(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture,float speedX,int H, float speedY, int V, float damage, const char *sound)
	: Sprite2D(model, shader, texture)
{
	ResourceManagers::GetInstance()->PlaySound(sound, false);
	SpeedX = speedX;
	SpeedY = speedY;
	h = H;
	v = V;
	m_damage = damage;
}


Bullet::~Bullet()
{
}

void Bullet::Update(GLfloat deltatime)
{
	Bullet::Move(deltatime);
	Bullet::IsActive();
}

//void Bullet::HandleKeyEvents(unsigned char key, bool bIsPresseded)
//{
//
//}
//
//void Bullet::HandleTouchEvents(GLint x, GLint y, bool bIsPressed) {
//
//}

void Bullet::Move(GLfloat deltaTime) {
	Bullet::Set2DPosition(Bullet::Get2DPosition().x + SpeedX * h * deltaTime, Bullet::Get2DPosition().y + SpeedY * v * deltaTime);
}

void Bullet::SetActive(bool Active) {
	m_active = Active;
}
bool Bullet::GetActive() {
	return m_active;
}

void Bullet::IsActive() {
	if (Bullet::Get2DPosition().x >= screenWidth || Bullet::Get2DPosition().x < 0 || Bullet::Get2DPosition().y  < 0 || Bullet::Get2DPosition().y > screenHeight) {
		m_active = false;
	}
}

float Bullet::GetDamage() {
	return m_damage;
}
