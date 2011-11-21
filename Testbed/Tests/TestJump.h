#pragma once
#include "..\framework\test.h"
#include "TestMovingConstantSpeed.h"

class TestJump :
	public Test
{
public:
	b2Body* body;
	_moveState moveState;
	int remainingJumpSteps;
	TestJump(void);
	~TestJump(void);
	void Step(Settings*);
	static Test* Create()
	{
		return new TestJump;
	}
	void Keyboard(unsigned char key);
};
