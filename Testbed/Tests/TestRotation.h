#pragma once
#include "..\framework\test.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include "freeglut/freeglut.h"
#endif
class TestRotation :
	public Test
{
public:
	b2Body* body;
	b2Vec2 clickedPoint;
	TestRotation(void);
	~TestRotation(void);
	void Step(Settings*);
	static Test* Create()
	{
		return new TestRotation;
	}
	void MouseDown(const b2Vec2& p);
};
