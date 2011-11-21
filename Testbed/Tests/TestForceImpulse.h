#pragma once
#include "..\framework\test.h"

class TestForceImpulse :
	public Test
{
public:
	b2Body* bodies[3];
	bool forceOn;
	TestForceImpulse(void);
	~TestForceImpulse(void);
	void Step(Settings*);
	static Test* Create()
	{
		return new TestForceImpulse;
	}
	void Keyboard(unsigned char key);
};
