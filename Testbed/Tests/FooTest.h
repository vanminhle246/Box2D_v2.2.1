
#pragma once
#include "..\framework\test.h"
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

class FooTest :
	public Test
{
public:
	b2Body* dynamicBody;
	FooTest(void);
	~FooTest(void);
	void Step(Settings*);
	static Test* Create()
	{
		return new FooTest;
	}
};
