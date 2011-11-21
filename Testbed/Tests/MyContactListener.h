#pragma once
#include <Box2D\dynamics\b2worldcallbacks.h>

class MyContactListener :
	public b2ContactListener
{
public:
	MyContactListener(void);
	~MyContactListener(void);
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
};
