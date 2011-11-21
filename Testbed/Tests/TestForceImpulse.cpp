#include "TestForceImpulse.h"

TestForceImpulse::TestForceImpulse(void)
{
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;

	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(1, 1);

	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &polygonShape;
	myFixtureDef.density = 1;

	for (int i=0; i<3; i++)
	{
		myBodyDef.position.Set(-10 + i*10, 20);
		this->bodies[i] = m_world->CreateBody(&myBodyDef);
		this->bodies[i]->CreateFixture(&myFixtureDef);
	}

	b2EdgeShape myEdgeShape;
	myEdgeShape.Set(b2Vec2(-15, 0), b2Vec2(15, 0));
	myFixtureDef.shape = &myEdgeShape;
	myBodyDef.type = b2_staticBody;
	myBodyDef.position.Set(0, 0);
	m_world->CreateBody(&myBodyDef)->CreateFixture(&myFixtureDef);
	this->forceOn = false;
}

TestForceImpulse::~TestForceImpulse(void)
{
}
void TestForceImpulse::Step(Settings* settings)
{
	//run the default physics and rendering
	Test::Step(settings);

	//show some text in the main screen
	m_debugDraw.DrawString(5, m_textLine, "Now we have a force-impulse test");
	m_textLine += 15;
	bodies[1]->ApplyForce(bodies[1]->GetMass() * - m_world->GetGravity(), bodies[1]->GetWorldCenter());
	if (this->forceOn) 
		bodies[0]->ApplyForce(b2Vec2(0, 50), bodies[0]->GetWorldCenter());
		
}
void TestForceImpulse::Keyboard(unsigned char key)
{
	switch (key)
	{
	case 'q':
		//apply gradual force upwards
		this->forceOn = !this->forceOn;
		break;
	case 'w':
		//apply immediate force upwards
		bodies[1]->ApplyLinearImpulse(b2Vec2(0, 50), bodies[1]->GetWorldCenter());
		
		break;
	case 'e':
		//teleport or 'warp' to new location
		bodies[2]->SetTransform(b2Vec2(10, 20), 0);
		break;
	case 'a':
		bodies[0]->ApplyTorque(20);
		break;
	case 's':
		bodies[1]->ApplyAngularImpulse(20);
		break;
	default:
		//run default behaviour
		Test::Keyboard(key);
	}
}