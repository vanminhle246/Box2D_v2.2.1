#include "TestJumpingEvent.h"
#include "MyContactListenerForJumping.h"

MyContactListenerForJumping myContactListenerInstance;
TestJumpingEvent::TestJumpingEvent(void)
{
	numFootContacts = 0;
	b2BodyDef myBodyDef;
	b2PolygonShape polygonShape;

	//fixture definition
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &polygonShape;
	myFixtureDef.density = 1;

	myBodyDef.type = b2_staticBody;
	myBodyDef.position.Set(0, 0);
	b2Body* staticBody = m_world->CreateBody(&myBodyDef);

	//add four walls to the static body
	polygonShape.SetAsBox(20, 1, b2Vec2(0, 0), 0); //ground
	staticBody->CreateFixture(&myFixtureDef);
	polygonShape.SetAsBox(20, 1, b2Vec2(0, 40), 0); //ceiling
	staticBody->CreateFixture(&myFixtureDef);
	polygonShape.SetAsBox(1, 20, b2Vec2(-20, 20), 0); //left wall
	staticBody->CreateFixture(&myFixtureDef);
	polygonShape.SetAsBox(1, 20, b2Vec2(20, 20), 0); //right wall
	staticBody->CreateFixture(&myFixtureDef);

	
	myBodyDef.position.Set(-5, 5);
	myBodyDef.type = b2_dynamicBody;

	//shape definition
	polygonShape.SetAsBox(1, 1);

	for (int i=0; i<5; i++)
	{
		b2Fixture* fixture = m_world->CreateBody(&myBodyDef)->CreateFixture(&myFixtureDef);
		fixture->SetUserData( (void*) 1); //tag square boxes as 1
	}

	//myBodyDef.position.Set(5, 10);
	//change size
	polygonShape.SetAsBox(0.5, 1); //a 1x2 rectangle

	for (int i=0; i<5; i++)
	{
		b2Fixture* fixture = m_world->CreateBody(&myBodyDef)->CreateFixture(&myFixtureDef);
		fixture->SetUserData( (void*)2 ); //tag smaller rectangular boxes as 2
	}

	myBodyDef.type = b2_dynamicBody;
	myBodyDef.fixedRotation = true;

	polygonShape.SetAsBox(1, 2);

	myFixtureDef.shape = &polygonShape;
	myFixtureDef.density = 1;

	myBodyDef.position.Set(0, 10);
	m_body = m_world->CreateBody(&myBodyDef);

	m_body->CreateFixture(&myFixtureDef);

	polygonShape.SetAsBox(0.3, 0.1, b2Vec2(0, -2), 0);
	myFixtureDef.isSensor = true;
	b2Fixture* footSensorFixture = m_body->CreateFixture(&myFixtureDef);
	footSensorFixture->SetUserData((void*)3 );
	
	m_world->SetContactListener(&myContactListenerInstance);
}

TestJumpingEvent::~TestJumpingEvent(void)
{
}

void TestJumpingEvent::Step(Settings* settings)
{
	//run the default physics and rendering
	Test::Step(settings);

	//show some text in the main screen
	m_debugDraw.DrawString(5, m_textLine, "Now we have a jumping event test");
	m_textLine += 15;
	
	m_debugDraw.DrawString(5, m_textLine, "Can I jump here? %s", numFootContacts>0?"yes":"no");
	m_textLine += 15;
}