#pragma once
#include <cstdlib>
#include "Sprite2D.h"
#include "Bullet.h" 
#include "Animation2D.h"

class Enemy :
	public Sprite2D
{
private:
	int m_HP;
	float m_damage;
	float m_currentTime = 0;
	float m_timeToFire;
	const char* m_bulletTexture;
	bool m_isCanFire = false;
	bool m_isAlive = true;
	GLfloat a, b, fx, fy;
	float v = 1, h = 1, vb = 1, hb =1;
	float SpeedBulletX, SpeedBulletY;
	bool isFire = false;
	std::string		m_Text;
	std::vector<std::shared_ptr<Bullet>> m_listBullet;

protected:
	Vector2			m_Vec2DPos;
	GLint			m_iHeight;
	GLint			m_iWidth;

public:
	Enemy(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, float HP, float damage, float TimetoFire, const char* bulletTexture);
	~Enemy();

	void		Update(GLfloat deltaTime);
	void		HandleKeyEvents(unsigned char key, bool bIsPresseded);
	void		HandleTouchEvents(GLint x, GLint y, bool bIsPressed);
	void		Exit();

	int			GetHP();
	void		SetHP(float HP);
	float		GetDamage();
	float		GetTimeToFire();
	void		Move(float H, float V, GLfloat deltaTime);
	void		SetIsAlive(bool alive);
	void		SetIsCanFire(bool fire);
	bool		GetIsCanFire();
	bool		GetIsAlive();
	void		IsAlive();
	void		Collider(GLfloat deltaTime);
	float		Rotation(GLint x, GLint y);
	std::shared_ptr<Bullet>		Fire(GLint x, GLint y);
	std::shared_ptr<Bullet>		Fire2A(GLint x, GLint y);
	std::shared_ptr<Bullet>		Fire2B(GLint x, GLint y);
	std::shared_ptr<Sprite2D>	BulletImpact(GLint x, GLint y);
	std::shared_ptr<Animation2D>	Explosion(GLint x, GLint y);
	void		SpeedforBullet(GLint x, GLint y);
};

