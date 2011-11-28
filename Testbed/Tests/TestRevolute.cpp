#include "TestRevolute.h"
#include "TestFriction.h"

TestRevolute::TestRevolute(void)
{
	b2BodyDef myBodyDef;
	b2PolygonShape polygonShape;

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

	myBodyDef.type = b2_dynamicBody;
	b2PolygonShape boxShape;
	boxShape.SetAsBox(2, 2);
	b2CircleShape circleShape;
	circleShape.m_radius = 2;

	//make a box to the left
	myBodyDef.position.Set(-3, 10);
	myFixtureDef.shape = &boxShape;
	m_bodyA = m_world->CreateBody(&myBodyDef);
	m_bodyA->CreateFixture( &myFixtureDef);

	//make a circle to the right
	myBodyDef.position.Set(3, 10);
	myFixtureDef.shape = &circleShape;
	m_bodyB = m_world->CreateBody(&myBodyDef);
	m_bodyB->CreateFixture(&myFixtureDef);

	b2RevoluteJointDef revoluteJointDef;
	revoluteJointDef.bodyA = m_bodyA;
	revoluteJointDef.bodyB = m_bodyB;
	revoluteJointDef.collideConnected = false;
	revoluteJointDef.localAnchorA.Set(2, 2);
	revoluteJointDef.localAnchorB.Set(0, 0);
	m_joint = (b2RevoluteJoint*)m_world->CreateJoint(&revoluteJointDef);

	/*create chain*/
	myBodyDef.position.Set(5, 10);
	polygonShape.SetAsBox(1, 0.25);
	myFixtureDef.shape = &polygonShape;

	b2Body* link = m_world->CreateBody(&myBodyDef);
	link->CreateFixture(&myFixtureDef);

	revoluteJointDef.localAnchorA.Set(0.75, 0);
	revoluteJointDef.localAnchorB.Set(-0.75, 0);
	for (int i = 0; i<10; i++)
	{
		b2Body* newLink = m_world->CreateBody(&myBodyDef);
		newLink->CreateFixture(&myFixtureDef);
		revoluteJointDef.bodyA = link;
		revoluteJointDef.bodyB = newLink;
		m_world->CreateJoint(&revoluteJointDef);
		link = newLink;
	}

	myFixtureDef.shape = &circleShape;
	b2Body* chainBase = m_world->CreateBody(&myBodyDef);
	chainBase->CreateFixture(&myFixtureDef);

	revoluteJointDef.bodyA = m_groundBody;
	revoluteJointDef.bodyB = chainBase;
	revoluteJointDef.localAnchorA.Set(4, 20);
	revoluteJointDef.localAnchorB.Set(0, 0);
	m_world->CreateJoint(&revoluteJointDef);

	revoluteJointDef.bodyA = link;
	revoluteJointDef.bodyB = chainBase;
	revoluteJointDef.localAnchorA.Set(0.75, 0);
	revoluteJointDef.localAnchorB.Set(1.75, 0);
	m_world->CreateJoint(&revoluteJointDef);
	/**/
}

TestRevolute::~TestRevolute(void)
{
}
void TestRevolute::Step(Settings* settings)
{
	//run the default physics and rendering
	Test::Step(settings);

	//show some text in the main screen
	m_debugDraw.DrawString(5, m_textLine, "Now we have revolute test");
	m_textLine += 15;

	m_debugDraw.DrawString(5, m_textLine, "Current joint angle: %f deg", m_joint->GetJointAngle()*RADTODEG);
	m_textLine += 15;

	m_debugDraw.DrawString(5, m_textLine, "Current joint angle: %f deg/s", m_joint->GetJointSpeed()*RADTODEG);
	m_textLine += 15;
}