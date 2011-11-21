#pragma once
#include <Box2D\dynamics\b2worldcallbacks.h>
#include <vector>
#include <Box2D\Dynamics\b2Fixture.h>

class MyQueryCallback :
	public b2QueryCallback
{
public:
	std::vector<b2Body*> foundBodies;
	MyQueryCallback(void);
	~MyQueryCallback(void);
	bool ReportFixture(b2Fixture* fixture);
};
