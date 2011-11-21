#pragma once
#include "..\framework\test.h"
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
class TestFriction :
	public Test
{
public:
	TestFriction(void);
	~TestFriction(void);
	void Step(Settings*);
	static Test* Create()
	{
		return new TestFriction;
	}
};
