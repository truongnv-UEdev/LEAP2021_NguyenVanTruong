#pragma once
#include "Sprite2D.h"
#include "Bullet.h" 
#include "Animation2D.h"
class MainCharacter :
	public Sprite2D
{
private:
	int m_HP;
	int m_heart;
	float m_damage = 20;
	float m_currentTime = 0;
	float m_TimeToFire = 3;
	float v = 0, h = 0, vb = 0, hb = 0, f;
	GLfloat a, b, fx, fy;
	float SpeedBulletX, SpeedBulletY;
	bool isMovingUp = false;
	bool isMovingRight = false;
	float TimeDashCooldown = 0;
	bool isAlive = true;
	bool isDash = false;
	bool m_isCanDash = true;
	std::string		m_Text;
	std::vector<std::shared_ptr<Bullet>> m_listBullet;

protected:
	Vector2			m_Vec2DPos;
	GLint			m_iHeight;
	GLint			m_iWidth;

public:
	MainCharacter(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, float HP, int Heart);
	MainCharacter(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, Vector4 color);
	~MainCharacter();

	void		Update(GLfloat deltaTime) override;
	void		HandleKeyEvents(unsigned char key, bool bIsPresseded);
	void		HandleTouchEvents(GLint x, GLint y, bool bIsPressed);
	void		Exit();


	void		MoveRight(float m, GLfloat deltaTime);
	void		MoveUp(float m, GLfloat deltaTime);
	void		Dash(float m, float n, GLfloat deltaTime);
	void		Collider(GLfloat deltaTime);

	int			GetHP();
	void		SetHP(int HP);
	void		SetHeart(int Heart);
	int			GetHeart();
	float		GetDamage();
	void		SetIsAlive(bool IsAlive);
	bool		GetIsAlive();
	void		SetIsCanDash(bool IsCanDash);
	bool		GetIsCanDash();

	float		Rotation	(GLint x, GLint y);
	std::shared_ptr<Bullet>		Fire();
	void		SpeedforBullet(GLint x, GLint y);
	std::shared_ptr<Sprite2D>		BulletImpact(GLint x, GLint y);
	std::shared_ptr<Sprite2D>		Shield(GLint x, GLint y);
	std::shared_ptr<Animation2D>	Explosion(GLint x, GLint y);
};

