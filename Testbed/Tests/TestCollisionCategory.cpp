#include "TestCollisionCategory.h"
#include "MyContactListener.h"
MyContactListener myContactListenerInstance1;

TestCollisionCategory::TestCollisionCategory(void)
{
	b2Color red(1, 0, 0);
	b2Color green(0, 1, 0);

	m_world->SetContactListener(&myContactListenerInstance1);
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
	
	/**
	for (int i=0; i < 3; i++)
		balls.push_back(new BallForCollisionCategory(m_world, 3, green, 0, 0) );
	for (int i=0; i<3; i++)
		balls.push_back(new BallForCollisionCategory(m_world, 3, red, 0, 0) );
	for (int i=0; i<3; i++)
		balls.push_back(new BallForCollisionCategory(m_world, 1, green, 0, 0) );
	for (int i=0; i<3; i++)
		balls.push_back(new BallForCollisionCategory(m_world, 1, red, 0, 0) );
	/**/
	/**/
	for (int i=0; i < 3; i++)
		balls.push_back(new BallForCollisionCategory(m_world, 3, green, FRIENDLY_SHIP, BOUNDARY|FRIENDLY_SHIP|ENEMY_SHIP) );
	for (int i=0; i<3; i++)
		balls.push_back(new BallForCollisionCategory(m_world, 3, red, ENEMY_SHIP, BOUNDARY|FRIENDLY_SHIP|FRIENDLY_SHIP) );
	for (int i=0; i<3; i++)
		balls.push_back(new BallForCollisionCategory(m_world, 1, green, FRIENDLY_AIRCRAFT, BOUNDARY|ENEMY_AIRCRAFT) );
	for (int i=0; i<3; i++)
		balls.push_back(new BallForCollisionCategory(m_world, 1, red, ENEMY_AIRCRAFT, BOUNDARY|FRIENDLY_AIRCRAFT) );
	/**/
}

TestCollisionCategory::~TestCollisionCategory(void)
{
}
void TestCollisionCategory::Step(Settings* settings)
{
	Test::Step(settings);

	m_debugDraw.DrawString(5, m_textLine, "Now we have category collision test");
	m_textLine+=15;
	for (int i=0; i < balls.size(); i++)
		balls[i]->renderAtBodyPosition();
}
