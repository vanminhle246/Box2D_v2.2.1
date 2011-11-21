#include "TestDrawObject.h"

TestDrawObject::TestDrawObject(void)
{
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
	Ball* ball = new Ball(m_world, 1);
	balls.push_back(ball);
	/**/
	for (int i=0; i<20; i++)
	{
		float radius = 1+ 2*(rand() / (float)RAND_MAX );
		Ball* ball = new Ball(m_world, radius);
		balls.push_back(ball);
	}
}

TestDrawObject::~TestDrawObject(void)
{
}

void TestDrawObject::Step(Settings* settings)
{
	//run the default physics and rendering
	Test::Step(settings);

	//show some text in the main screen
	m_debugDraw.DrawString(5, m_textLine, "Now we have a draw-object test");
	m_textLine += 15;

	for (int i=0; i < balls.size(); i++)
		balls[i]->renderAtBodyPosition();
}