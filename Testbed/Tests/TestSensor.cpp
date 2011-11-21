#include "TestSensor.h"
#include "TestFriction.h"
MyContactListenerForSensor myContactListenerInstanceForSensor;
TestSensor::TestSensor(void)
{
	b2Color red(1, 0, 0);
	b2Color green(0, 1, 0);

	//m_world->SetContactListener(&myContactListenerInstance1);
	m_world->SetGravity(b2Vec2(0, 0));
	m_world->SetContactListener(&myContactListenerInstanceForSensor);
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

	//create one friendly ship
	BallForSensor* ship = new BallForSensor(m_world, 3, green, FRIENDLY_SHIP, BOUNDARY|FRIENDLY_TOWER);
	balls.push_back(ship);
	
	//three enemy aircraft
	for (int i = 0; i < 3; i++)
		balls.push_back(new BallForSensor(m_world, 1, red, ENEMY_AIRCRAFT, BOUNDARY|RADAR_SENSOR) );

	//a tower entity
	BallForSensor* tower = new BallForSensor(m_world, 1, green, FRIENDLY_TOWER, FRIENDLY_SHIP);
	tower->m_body->SetType(b2_kinematicBody);
	balls.push_back(tower);

	//add radar sensor to ship
	b2CircleShape circleShape;
	circleShape.m_radius = 8;
	myFixtureDef.shape = &circleShape;
	myFixtureDef.isSensor = true;
	myFixtureDef.filter.categoryBits = RADAR_SENSOR;
	ship->m_body->CreateFixture(&myFixtureDef);

	float radius = 8;
	b2Vec2 vertices[8];
	vertices[0].Set(0, 0);
	for (int i =0; i<7; i++)
	{
		float angle = i/6.0*90*DEGTORAD;
		vertices[i+1].Set( radius*cosf(angle), radius*sinf(angle) );
	}
	polygonShape.Set(vertices, 8);
	myFixtureDef.shape = &polygonShape;
	tower->m_body->CreateFixture(&myFixtureDef);

	//make the tower rotate at 45 degrees per second
	tower->m_body->SetAngularVelocity(45 * DEGTORAD);
}

TestSensor::~TestSensor(void)
{
}
void TestSensor::Step(Settings* settings)
{
	//run the default physics and rendering
	Test::Step(settings);

	//show some text in the main screen
	m_debugDraw.DrawString(5, m_textLine, "Now we have a sensor test");
	m_textLine += 15;
	for (int i=0; i < balls.size(); i++)
		balls[i]->renderAtBodyPosition();
	
}