#include "TestRotation.h"
#include "FooTest.h"

TestRotation::TestRotation(void)
{
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;

	//hexagonal shape definition
	b2PolygonShape polygonShape;
	b2Vec2 vertices[6];
	for (int i=0; i<6; i++)
	{
		float angle = -i/6.0 * 360 * DEGTORAD;
		vertices[i].Set(sinf(angle), cosf(angle));
	}
	vertices[0].Set(0, 4); //change one vertex to be pointy
	polygonShape.Set(vertices, 6);

	//fixture definition
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &polygonShape;
	myFixtureDef.density = 1;

	//create dynamic body
	myBodyDef.position.Set(0, 10);
	body = m_world->CreateBody(&myBodyDef);
	body->CreateFixture(&myFixtureDef);

	//zero gravity 
	m_world->SetGravity(b2Vec2(0, 0));
	clickedPoint = b2Vec2(0, 20);
}

TestRotation::~TestRotation(void)
{
}
void TestRotation::Step(Settings* settings)
{
	//run the default physics and rendering
	Test::Step(settings);

	//show some text in the main screen
	m_debugDraw.DrawString(5, m_textLine, "Now we have a rotation");
	m_textLine += 15;

	//include gl library
	glPointSize(4);
	glBegin(GL_POINTS);
	glVertex2f(clickedPoint.x, clickedPoint.y);
	glEnd();

	float bodyAngle = body->GetAngle();
	b2Vec2 toTarget = clickedPoint - body->GetPosition();
	float desireAngle = atan2f(-toTarget.x, toTarget.y);

	//view these in real time
	m_debugDraw.DrawString(5, m_textLine, "Body angle %.3f", bodyAngle*RADTODEG);
	m_textLine +=15;
	m_debugDraw.DrawString(5, m_textLine, "Target angle %.3f", desireAngle*RADTODEG);
	m_textLine +=15;

	body->SetTransform(body->GetPosition(), desireAngle);

	body->SetAngularVelocity(0);

	float totalRotation = desireAngle - bodyAngle;
	float change = 1*DEGTORAD; //rotate 1 degree per time step
	float newAngle = bodyAngle + b2Min(change, b2Max(-change, totalRotation));
	body->SetTransform(body->GetPosition(), newAngle);
	while (totalRotation < -180*DEGTORAD) totalRotation += 360*DEGTORAD;
	while (totalRotation > 180*DEGTORAD) totalRotation -= 360*DEGTORAD;
	
}
void TestRotation::MouseDown(const b2Vec2& p)
{
	//store last mouse-down position
	clickedPoint = p;

	//do normal behaviour
	Test::MouseDown(p);
}