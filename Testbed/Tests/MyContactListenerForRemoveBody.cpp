#include "MyContactListenerForRemoveBody.h"
#include <Box2D/Dynamics/Contacts/b2Contact.h>
#include "BallForRemoveBody.h"
#include <set>

extern std::set<BallForRemoveBody*> ballsScheduledForRemoval;
void handleContact(BallForRemoveBody* b1, BallForRemoveBody* b2)
{
	/**
	bool temp = b1->m_seed;
	b1->m_seed = b2->m_seed;
	b2->m_seed = temp;
	/**/
	if (b1->m_seed)
	{
		ballsScheduledForRemoval.insert(b1);
		b2->m_seed = true;
	}
	else if (b2->m_seed)
	{
		ballsScheduledForRemoval.insert(b2);
		b1->m_seed = true;
	}
}
MyContactListenerForRemoveBody::MyContactListenerForRemoveBody(void)
{
}

MyContactListenerForRemoveBody::~MyContactListenerForRemoveBody(void)
{
}
void MyContactListenerForRemoveBody::BeginContact(b2Contact* contact)
{
	void* bodyAUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	void* bodyBUserData = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyAUserData && bodyBUserData)
		handleContact(static_cast<BallForRemoveBody*>(bodyAUserData), static_cast<BallForRemoveBody*>(bodyBUserData));
}
void MyContactListenerForRemoveBody::EndContact(b2Contact* contact)
{

}

