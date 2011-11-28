#pragma once
#include "..\framework\test.h"
extern int numFootContacts;
class TestJumpingEvent :
	public Test
{
public:
	b2Body* m_body;
	TestJumpingEvent(void);
	~TestJumpingEvent(void);
	void Step(Settings*);
	static Test* Create()
	{
		return new TestJumpingEvent;
	}
};
