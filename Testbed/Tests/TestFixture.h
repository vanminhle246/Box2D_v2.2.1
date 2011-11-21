#pragma once
#include "..\framework\test.h"

class TestFixture :
	public Test
{
public:
	TestFixture(void);
	~TestFixture(void);
	void Step(Settings*);
	static Test* Create()
	{
		return new TestFixture;
	}
};
