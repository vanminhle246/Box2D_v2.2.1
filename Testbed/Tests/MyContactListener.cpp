#include "MyContactListener.h"
#include <Box2D\Dynamics\Contacts\b2Contact.h>
#include "BallUserData.h"

void handleContact(BallUserData* b1, BallUserData* b2)
{
	int temp = b1->m_numContacts;
	b1->m_numContacts = b2->m_numContacts;
	b2->m_numContacts = temp;
}
MyContactListener::MyContactListener(void)
{
}

MyContactListener::~MyContactListener(void)
{
}

void MyContactListener::BeginContact(b2Contact* contact)
{
	/**
	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	if (bodyUserData)
		static_cast<BallUserData*>(bodyUserData)->startContact();
	bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserData)
		static_cast<BallUserData*>(bodyUserData)->startContact();
	/**/
	/**/
	void* bodyAUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	void* bodyBUserData = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyAUserData && bodyBUserData)
		handleContact(static_cast<BallUserData*>(bodyAUserData), static_cast<BallUserData*>(bodyBUserData));
	/**/
}
void MyContactListener::EndContact(b2Contact* contact)
{
	//check if fixture A was a ball
	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	if (bodyUserData)
		static_cast<BallUserData*>(bodyUserData)->endContact();
	
	//check if fixture B was a ball
	bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserData)
		static_cast<BallUserData*>(bodyUserData)->endContact();
}
