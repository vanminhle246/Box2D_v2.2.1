#pragma once
#include "..\framework\test.h"
#include <Box2D\Dynamics\b2Body.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include "freeglut/freeglut.h"
#endif
class BallUserData
{
public:
	b2Color m_color;
	bool m_contacting;
	int m_numContacts;
	float m_radius;
	b2Vec2 m_position;
	float m_angle;
	b2Vec2 m_linearVelocity;
	BallUserData(void);
	BallUserData(b2World* world, float radius);
	~BallUserData(void);
	void render();
	void renderAtBodyPosition();
	void startContact();
	void endContact();
	BallUserData(b2World* world, float radius, b2Color color, uint16 categoryBits, uint16 maskBits);
};
