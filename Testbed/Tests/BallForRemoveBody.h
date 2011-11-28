#pragma once
#include "..\framework\test.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include "freeglut/freeglut.h"
#endif
class BallForRemoveBody
{
public:
	b2Body* m_body;
	b2World* m_world;
	b2Color m_color;
	float m_radius;
	bool m_contacting;
	bool m_seed;
	BallForRemoveBody(void);
	~BallForRemoveBody(void);
	BallForRemoveBody(b2World* world, float radius, b2Color color, uint16 categoryBits, uint16 maskBits);
	void render();
	void renderAtBodyPosition();
	BallForRemoveBody(b2World* world, float radius);
};
