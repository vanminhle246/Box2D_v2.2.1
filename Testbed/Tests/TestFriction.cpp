#include "TestFriction.h"

TestFriction::TestFriction(void)
{
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;
	myBodyDef.position.Set(0, 20);
	b2Body* dynamicBody = m_world->CreateBody(&myBodyDef);

	//prepare a shape definition
	b2PolygonShape polygonShape;
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &polygonShape;
	myFixtureDef.density = 1; //mật độ, tỉ trọng
	myFixtureDef.friction = 1; //sự ma sát
	/*
	density = 0 và friction = 0 : vật sẽ trượt nhưng ko lăn
	density = 0 và friction = 1 : vật sẽ ko chuyển động
	density = 1 và friction = 0 : vật sẽ lăn 1 vòng duy nhất rồi trượt
	density = 1 và friction = 1 : vật sẽ lăn đều đặn
	*/
	b2Fixture* myFixture;
	//add four square fixtures around the body center
	for (int i=0; i< 4; i++)
	{
		b2Vec2 pos(sinf(i*90*DEGTORAD), cosf(i*90*DEGTORAD));
		polygonShape.SetAsBox(1, 1, pos, 0);
		myFixture = dynamicBody->CreateFixture(&myFixtureDef);
	}

	myBodyDef.type = b2_staticBody;
	myBodyDef.position.Set(0, 0);
	b2Body* staticBody = m_world->CreateBody(&myBodyDef);
	
	b2EdgeShape edgeShape;
	edgeShape.Set(b2Vec2(-15, 0), b2Vec2(15, 7));
	myFixtureDef.shape = &edgeShape;
	staticBody->CreateFixture(&myFixtureDef);

	//dynamicBody->DestroyFixture(myFixture);
	//m_world->SetGravity(b2Vec2(1.5, -10));
}

TestFriction::~TestFriction(void)
{
}
void TestFriction::Step(Settings* settings)
{
	//run the default physics and rendering
	Test::Step(settings);

	//show some text in the main screen
	m_debugDraw.DrawString(5, m_textLine, "Now we have a friction test");
	m_textLine += 15;
}