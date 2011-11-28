#include "TestRemoveBody.h"
#include "MyContactListenerForRemoveBody.h"
#include <set>

extern std::set<BallForRemoveBody*> ballsScheduledForRemoval;

MyContactListenerForRemoveBody myContactListenerInstance;

TestRemoveBody::TestRemoveBody(void)
{
	b2Color red(1, 0, 0);
	b2Color green(0, 1, 0);

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
		BallForRemoveBody* ball = new BallForRemoveBody(m_world, radius);
		if (i == 0) ball->m_seed=true;
		balls.push_back(ball);
	}
}

TestRemoveBody::~TestRemoveBody(void)
{
}
void TestRemoveBody::Step(Settings* settings)
{
	Test::Step(settings);
	m_debugDraw.DrawString(5, m_textLine, "Now we have remove-body test");
	m_textLine+=15;
	/*draw the ball*/
	for (int i=0; i < balls.size(); i++)
		balls[i]->renderAtBodyPosition();
	/**/
	std::set<BallForRemoveBody*>::iterator it = ballsScheduledForRemoval.begin();
	std::set<BallForRemoveBody*>::iterator end = ballsScheduledForRemoval.end();
	for (; it!=end; ++it)
	{
		BallForRemoveBody* dyingBall = *it;

		//delete ball physic body is destroyed here
		delete dyingBall;

		//.. and remove it from main list of balls
		std::vector<BallForRemoveBody*>::iterator it = std::find(balls.begin(), balls.end(), dyingBall);
		if (it != balls.end())
			balls.erase(it);
	}
	ballsScheduledForRemoval.clear();
}