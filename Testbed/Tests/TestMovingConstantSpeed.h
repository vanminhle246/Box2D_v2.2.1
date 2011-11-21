#pragma once
#include "..\framework\test.h"
enum _moveState{
	MS_STOP,
	MS_LEFT,
	MS_RIGHT,
	MS_JUMP
};

class TestMovingConstantSpeed :
	public Test
{
public:
	b2Body* body;
	_moveState moveState;
	TestMovingConstantSpeed(void);
	~TestMovingConstantSpeed(void);
	void Step(Settings*);
	static Test* Create()
	{
		return new TestMovingConstantSpeed;
	}
	void Keyboard(unsigned char key);
};
