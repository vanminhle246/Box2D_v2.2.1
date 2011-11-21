#include "TestMovingConstantSpeed.h"

TestMovingConstantSpeed::TestMovingConstantSpeed(void)
{
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;

	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(1, 1);

	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &polygonShape;
	myFixtureDef.density = 1;

	myBodyDef.position.Set(0, 10);
	body = m_world->CreateBody(&myBodyDef);
	body->CreateFixture(&myFixtureDef);

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

	moveState = MS_STOP;
}

TestMovingConstantSpeed::~TestMovingConstantSpeed(void)
{
}
void TestMovingConstantSpeed::Step(Settings* settings)
{
	//run the default physics and rendering
	Test::Step(settings);

	//show some text in the main screen
	m_debugDraw.DrawString(5, m_textLine, "Now we have a moving at constant speed");
	m_textLine += 15;

	b2Vec2 vel = body->GetLinearVelocity();
	/* constant velocity*
	switch (moveState)
	{
	case MS_LEFT: vel.x = -5; break;
	case MS_STOP: vel.x = 0; break;
	case MS_RIGHT: vel.x = 5; break;
	}
	body->SetLinearVelocity(vel);
	/**/

	/* gradual velocity*
	switch (moveState)
	{
	case MS_LEFT: vel.x = b2Max(vel.x - 0.1f, -5.0f); break;
	case MS_STOP: vel.x *= 0.98; break;
	case MS_RIGHT: vel.x = b2Max(vel.x + 0.1f, 5.0f); break;
	}
	body->SetLinearVelocity(vel);
	/**/

	/*barely force*
	float force = 0;
	switch (moveState)
	{
		case MS_LEFT: 
			if (vel.x > -5) force = -50.0f; 
			break;
		case MS_STOP: 
			force = vel.x * (-10); 
			break;
		case MS_RIGHT:
			if (vel.x < 5) force = 50; 
			break;
	}
	body->ApplyForce(b2Vec2(force, 0), body->GetWorldCenter());	
	/**/

	/*desire force*
	float desireVel = 0;
	switch (moveState)
	{
	case MS_LEFT: desireVel = -5; break;
	case MS_STOP: desireVel = 0; break;
	case MS_RIGHT: desireVel = 5; break;
	}
	float velChange = desireVel - vel.x;
	float force = body->GetMass()*velChange/(1/60.0);
	body->ApplyForce(b2Vec2(force, 0), body->GetWorldCenter());
	/**/

	/*impulse*/
	float desireVel = 0;
	switch (moveState)
	{
	case MS_LEFT: desireVel = -5; break;
	case MS_STOP: desireVel = 0; break;
	case MS_RIGHT: desireVel = 5; break;
	}
	float velChange =desireVel - vel.x;
	float impulse = body->GetMass()*velChange;
	body->ApplyLinearImpulse(b2Vec2(impulse, 0), body->GetWorldCenter());
	/**/
}
void TestMovingConstantSpeed::Keyboard(unsigned char key)
{
	switch (key)
	{
	case 'q': //move left
		moveState = MS_LEFT;
		break;
	case 'w': //stop
		moveState = MS_STOP;
		break;
	case 'e': //move right
		moveState = MS_RIGHT;
		break;
	default:
		Test::Keyboard(key);
	}
}
