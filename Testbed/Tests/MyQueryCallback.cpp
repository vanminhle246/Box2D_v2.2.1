#include "MyQueryCallback.h"

MyQueryCallback::MyQueryCallback(void)
{
}

MyQueryCallback::~MyQueryCallback(void)
{
}
bool MyQueryCallback::ReportFixture(b2Fixture* fixture)
{
	foundBodies.push_back(fixture->GetBody());
	return true;
}