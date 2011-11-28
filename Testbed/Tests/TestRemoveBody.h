#pragma once
#include "..\framework\test.h"
#include "BallForRemoveBody.h"
#include <vector>

class TestRemoveBody :
	public Test
{
public:
	std::vector<BallForRemoveBody *> balls;
	TestRemoveBody(void);
	~TestRemoveBody(void);
	static Test* Create()
	{
		return new TestRemoveBody;
	}
	void Step(Settings*);
};
