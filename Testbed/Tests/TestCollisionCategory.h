#pragma once
#include "..\framework\test.h"
#include <vector>
#include "BallForCollisionCategory.h"


class TestCollisionCategory :
	public Test
{
public:
	std::vector<BallForCollisionCategory *> balls;
	TestCollisionCategory(void);
	~TestCollisionCategory(void);
	static Test* Create()
	{
		return new TestCollisionCategory;
	}
	void Step(Settings*);
};
