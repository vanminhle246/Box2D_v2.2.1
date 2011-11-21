#pragma once
#include <Box2D\Dynamics\b2Body.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include "freeglut/freeglut.h"
#endif

class Ball
{
public:
	b2Body* m_body;
	float m_radius;
	bool m_contacting;
	Ball(void);
	Ball(b2World* world, float radius);
	~Ball(void);
	void render();
	void renderAtBodyPosition();
	void startContact();
	void endContact();
};
