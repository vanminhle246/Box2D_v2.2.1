#pragma once
#include "..\framework\test.h"

class TestRevolute :
	public Test
{
public:
	b2Body* m_bodyA;
	b2Body* m_bodyB;
	b2RevoluteJoint* m_joint;
	TestRevolute(void);
	~TestRevolute(void);
	void Step(Settings*);
	static Test* Create()
	{
		return new TestRevolute;
	}
};
