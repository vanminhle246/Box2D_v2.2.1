#include "TestUserData.h"
MyContactListener myContactListenerInstance;

TestUserData::TestUserData(void)
{
	m_world->SetContactListener(&myContactListenerInstance);
	m_world->SetGravity(b2Vec2(0, 0));
	//a static body
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_staticBody;
	myBodyDef.position.Set(0, 0);
	b2Body* staticBody = m_world->CreateBody(&myBodyDef);

	//shape definition
	b2PolygonShape polygonShape;

	//fixture definition
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &polygonShape;

	//add four walls to the static body
	polygonShape.SetAsBox(20, 1, b2Vec2(0, 0), 0); //ground
	staticBody->CreateFixture(&myFixtureDef);
	polygonShape.SetAsBox(20, 1, b2Vec2(0, 40), 0); //ceiling
	staticBody->CreateFixture(&myFixtureDef);
	polygonShape.SetAsBox(1, 20, b2Vec2(-20, 20), 0); //left wall
	staticBody->CreateFixture(&myFixtureDef);
	polygonShape.SetAsBox(1, 20, b2Vec2(20, 20), 0); //right wall
	staticBody->CreateFixture(&myFixtureDef);

	for (int i=0; i<8; i++)
	{
		float radius = 1+ 2*(rand() / (float)RAND_MAX );
		BallUserData* ball = new BallUserData(m_world, radius);
		if (i == 0) ball->m_numContacts=10;
	}
}

TestUserData::~TestUserData(void)
{
}
void TestUserData::Step(Settings* settings)
{
	//run the default physics and rendering
	Test::Step(settings);

	//show some text in the main screen
	m_debugDraw.DrawString(5, m_textLine, "Now we have a ball restitution test");
	m_textLine += 15;

	b2Body* b = m_world->GetBodyList(); //get start of list
	while (b != NULL)
	{
		BallUserData* ball = static_cast<BallUserData*> (b->GetUserData());
		if (ball != NULL)
		{
			ball->m_position = b->GetPosition();
			ball->m_angle = b->GetAngle();
			ball->m_linearVelocity = b->GetLinearVelocity();
			ball->renderAtBodyPosition();
		}
		//continue to next body
		b = b->GetNext();
	}
}
