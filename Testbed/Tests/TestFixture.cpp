#include "TestFixture.h"

TestFixture::TestFixture(void)
{
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;
	myBodyDef.position.Set(-10, 20);

	b2Body* dynamicBody1 = m_world->CreateBody(&myBodyDef);

	b2CircleShape circleShape;
	circleShape.m_p.Set(0, 0);
	circleShape.m_radius = 1;

	b2FixtureDef myFixtureDef;
	myFixtureDef.density = 1;
	myFixtureDef.shape = &circleShape;
	dynamicBody1->CreateFixture(&myFixtureDef);


	/**
	b2Vec2 vertices[12];
	vertices[0].Set(0, -1);
	vertices[1].Set(1, 0);
	vertices[2].Set(1, -2);
	vertices[3].Set(2, -2);
	vertices[4].Set(2, 2);
	vertices[5].Set(1, 2);
	vertices[6].Set(0, 1);
	vertices[7].Set(-1, 2);
	vertices[8].Set(-2, 2);
	vertices[9].Set(-2, -2);
	vertices[10].Set(-1, -2);
	vertices[11].Set(-1, 0);
	/**/
	/**/
	b2Vec2 vertices[5];
	vertices[0].Set(-1 +10,  2);
	vertices[1].Set(-1 +10,  0);
	vertices[2].Set( 0 +10, -3);
	vertices[3].Set( 1 +10,  0);
	vertices[4].Set( 1 +10,  1);
	/**/
	b2PolygonShape polygonShape;
	polygonShape.Set(vertices, 5);

	myFixtureDef.shape = &polygonShape;
	myBodyDef.position.Set(0, 20);
	b2Body* dynamicBody2 = m_world->CreateBody(&myBodyDef);
	dynamicBody2->CreateFixture(&myFixtureDef);

	polygonShape.SetAsBox(2, 1);
	myBodyDef.position.Set(10, 20);

	b2Body* dynamicBody3 = m_world->CreateBody(&myBodyDef);
	dynamicBody3->CreateFixture(&myFixtureDef);

	myBodyDef.type = b2_staticBody;
	myBodyDef.position.Set(0, 0);
	b2EdgeShape edgeShape; 
	edgeShape.Set(b2Vec2(-15,0), b2Vec2(15,0));
	myFixtureDef.shape = &edgeShape;
	//polygonShape.SetAsBox(15, 0.01);
	b2Body* staticBody = m_world->CreateBody(&myBodyDef);
	staticBody->CreateFixture(&myFixtureDef);
}

TestFixture::~TestFixture(void)
{
}
void TestFixture::Step(Settings* settings)
{
	//run the default physics and rendering
	Test::Step(settings);

	//show some text in the main screen
	m_debugDraw.DrawString(5, m_textLine, "Now we have a fixture test");
	m_textLine += 15;
}