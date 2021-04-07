#pragma once
#include "Sprite2D.h"
#include "GameManager/ResourceManagers.h"

class Bullet :
    public Sprite2D
{
private:
	bool m_active = true;
	float m_damage;
	int v = 1, h = 1;
	GLint a, b, fx, fy;
	float SpeedX, SpeedY;
	std::string		m_Text;

	
protected:
	Vector2			m_Vec2DPos;
	GLint			m_iHeight;
	GLint			m_iWidth;

public:
	
	Bullet::Bullet(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, float SpeedX, int h, float SpeedY, int v, float damage, const char* sound);
	~Bullet();
	void		Update(GLfloat deltaTime) override;
	void		SetActive(bool Active);
	bool		GetActive();
	void		IsActive();
	float		GetDamage();
	void		Exit();

	void		Move(GLfloat deltaTime);
	void		Hit();
};

