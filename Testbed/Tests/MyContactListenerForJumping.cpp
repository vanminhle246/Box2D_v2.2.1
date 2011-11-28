#include "MyContactListenerForJumping.h"
#include <Box2D\Dynamics\b2Fixture.h>
#include <Box2D\Dynamics\Contacts\b2Contact.h>

MyContactListenerForJumping::MyContactListenerForJumping(void)
{
}

MyContactListenerForJumping::~MyContactListenerForJumping(void)
{
}
void MyContactListenerForJumping::BeginContact(b2Contact* contact)
{
	void* fixtureUserData = contact->GetFixtureA()->GetUserData();
	if ( (int)fixtureUserData == 3)
	{
		numFootContacts++;
	}
	fixtureUserData = contact->GetFixtureB()->GetUserData();
	if ( (int)fixtureUserData == 3)
	{
		numFootContacts++;
	}
}
void MyContactListenerForJumping::EndContact(b2Contact* contact)
{
	void* fixtureUserData = contact->GetFixtureA()->GetUserData();
	if ( (int)fixtureUserData == 3)
	{
		numFootContacts--;
	}
	fixtureUserData = contact->GetFixtureB()->GetUserData();
	if ( (int)fixtureUserData == 3)
	{
		numFootContacts--;
	}
}