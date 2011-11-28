#pragma once
#include <Box2d\dynamics\b2worldcallbacks.h>

extern int numFootContacts;
class MyContactListenerForJumping :
	public b2ContactListener
{
public:
	MyContactListenerForJumping(void);
	~MyContactListenerForJumping(void);
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
};
