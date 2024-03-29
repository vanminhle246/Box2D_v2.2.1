#include "TestJump.h"

TestJump::TestJump(void)
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

TestJump::~TestJump(void)
{
}
void TestJump::Step(Settings* settings)
{
	//run the default physics and rendering
	Test::Step(settings);
	b2Vec2 vel = body->GetLinearVelocity();

	//show some text in the main screen
	m_debugDraw.DrawString(5, m_textLine, "Now we have a jumping test");
	m_textLine += 15;

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
	if (remainingJumpSteps > 0)
	{
		/* apply force directly *
		body->ApplyForce(b2Vec2(0, 500), body->GetWorldCenter());
		/**/

		/* change velocity by 10 in one time step
		then, spread the force over 6 time steps
		*/
		float force = body->GetMass() * 10 / (1/60.0);
		force /= 6.0;
		body->ApplyForce(b2Vec2(0, force), body->GetWorldCenter());
		/**/
		remainingJumpSteps--;
	}
}
void TestJump::Keyboard(unsigned char key)
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
	case 'j': //jump
		{
			b2Vec2 vel = body->GetLinearVelocity();
			vel.y = 10; //upwards - don't change x velocity
			body->SetLinearVelocity(vel);
			break;
			/* Ấn j nhiều lần thì object vẫn bay lên cao hơn
			/?\ Vì sao vật vẫn rơi khi đã thiết kế tốc độ di chuyển của vật ko đổi
			*/
		}
	case 'k':
		{
			remainingJumpSteps = 6;
			break;
		}
	case 'l':
		{
			//to change velocity by 10
			float impulse = body->GetMass()*10;
			body->ApplyLinearImpulse(b2Vec2(0, impulse), body->GetWorldCenter());
		}
	default:
		Test::Keyboard(key);
	}
}