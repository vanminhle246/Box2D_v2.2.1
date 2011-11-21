#pragma once
#include "..\framework\test.h"
#include "Ball.h"
#include <vector>
using namespace std;

class TestDrawObject :
	public Test
{
public:
	std::vector<Ball *> balls;
	TestDrawObject(void);
	~TestDrawObject(void);
	static Test* Create()
	{
		return new TestDrawObject;
	}
	void Step(Settings*);
};
