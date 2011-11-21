#pragma once
#include "..\framework\test.h"
#include <vector>
#include "BallForSensor.h"
#include "BallForCollisionCategory.h"
#include "MyContactListenerForSensor.h"

class TestSensor :
	public Test
{
public:
	
	std::vector<BallForSensor *> balls;
	TestSensor(void);
	~TestSensor(void);
	static Test* Create()
	{
		return new TestSensor;
	}
	void Step(Settings*);
};
