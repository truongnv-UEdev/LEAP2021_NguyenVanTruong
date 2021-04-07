#pragma once
#include "Enemy.h"
class BossEnemy :
    public Enemy
{
private:
	float v = 1, h = 1, vb = 1, hb = 1;
	float SpeedBulletX, SpeedBulletY;
	const char* m_bulletTexture;
public:
	BossEnemy(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, float HP, float damage, float TimetoFire, const char *bulletTexture);
	~BossEnemy();

	void		Update(GLfloat deltaTime);
	void		HandleKeyEvents(unsigned char key, bool bIsPresseded);
	void		HandleTouchEvents(GLint x, GLint y, bool bIsPressed);
	void		Exit();

	std::shared_ptr<Bullet>		Fire1(GLint x, GLint y);
	std::shared_ptr<Bullet>		Fire2A(GLint x, GLint y);
	std::shared_ptr<Bullet>		Fire2B(GLint x, GLint y);
	std::shared_ptr<Bullet>		Fire3A(GLint x, GLint y);
	std::shared_ptr<Bullet>		Fire3B(GLint x, GLint y);
	std::shared_ptr<Animation2D>	Explosion(GLint x, GLint y);
	void		SpeedforBullet(GLint x, GLint y);
};

