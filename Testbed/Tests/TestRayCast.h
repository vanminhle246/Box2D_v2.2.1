#pragma once
#include "..\framework\test.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include "freeglut/freeglut.h"
#endif

class TestRayCast :
	public Test
{
public:
	b2Vec2 mouseDownPos, mouseUpPos;
	TestRayCast(void);
	~TestRayCast(void);
	static Test* Create()
	{
		return new TestRayCast;
	}
	void Step(Settings*);
	/**/
	void MouseDown(const b2Vec2& p);
	void MouseUp(const b2Vec2& p);
	/**/
};
