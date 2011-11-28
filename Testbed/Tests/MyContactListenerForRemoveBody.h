#pragma once
#include <Box2D/Dynamics/b2worldcallbacks.h>

class MyContactListenerForRemoveBody :
	public b2ContactListener
{
public:
	MyContactListenerForRemoveBody(void);
	~MyContactListenerForRemoveBody(void);
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
};
