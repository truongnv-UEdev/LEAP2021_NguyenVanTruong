#pragma once
#include "baseobject.h"

class Sprite2D : public BaseObject
{
private:
	std::string		m_Text;
	bool			m_active = true;
	float			m_currentTime = 0;
	float			m_deleteTime = 0;
	void			CaculateWorldMatrix();
protected:
	Vector2			m_Vec2DPos;
	GLint			m_iHeight;
	GLint			m_iWidth;

public:
	Sprite2D(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
	Sprite2D(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, Vector4 color);
	~Sprite2D();

	void		Init() override;
	void		Draw() override;
	void		Update(GLfloat deltatime) override;

	void		SetText(std::string text);
	void		SetDeleteTime(float delTime);
	float		GetDeleteTime();
	std::string	GetText();
	void		SetActive(bool active);
	bool		GetActive();


	void		Set2DPosition(GLfloat x, GLfloat y);
	void		SetRotationZ(GLfloat z);
	void		Set2DPosition(Vector2 pos);

	Vector2		Get2DPosition();
	void		SetSize(GLint width, GLint height);

};

