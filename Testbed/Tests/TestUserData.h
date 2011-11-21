#pragma once
#include "..\framework\test.h"
#include "BallUserData.h"
#include "MyContactListener.h"

class TestUserData :
	public Test
{
public:
	TestUserData(void);
	~TestUserData(void);
	static Test* Create()
	{
		return new TestUserData;
	}
	void Step(Settings*);
};
