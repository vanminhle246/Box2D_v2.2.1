#include "TestRayCast.h"
#include "TestFriction.h"
#include "MyQueryCallback.h"

float currentRayAngle = 0;

TestRayCast::TestRayCast(void)
{
	//a static body
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_staticBody;
	myBodyDef.position.Set(0, 0);
	b2Body* staticBody = m_world->CreateBody(&myBodyDef);

	//shape definition
	b2PolygonShape polygonShape;
	b2EdgeShape edgeShape;

	//fixture definition
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &edgeShape;

	//add four walls to the static body
	b2Vec2 bl(-20, 0);
	b2Vec2 br(20, 0);
	b2Vec2 tl(-20, 40);
	b2Vec2 tr(20, 40);
	
	edgeShape.Set(bl, br);
	staticBody->CreateFixture(&myFixtureDef);
	edgeShape.Set(tl, tr);
	staticBody->CreateFixture(&myFixtureDef);
	edgeShape.Set(bl, tl);
	staticBody->CreateFixture(&myFixtureDef);
	edgeShape.Set(br, tr);
	staticBody->CreateFixture(&myFixtureDef);
	
	myBodyDef.type = b2_dynamicBody;
	myBodyDef.position.Set(0, 20);
	myFixtureDef.shape = &polygonShape;
	polygonShape.SetAsBox(2, 2);
	myFixtureDef.density = 1;
	for (int i=0; i< 5; i++)
		m_world->CreateBody(&myBodyDef)->CreateFixture(&myFixtureDef);

	//circles
	b2CircleShape circleShape;
	circleShape.m_radius = 2;
	myFixtureDef.shape = &circleShape;
	for (int i = 0; i< 5; i++)
		m_world->CreateBody(&myBodyDef)->CreateFixture(&myFixtureDef);
	m_world->SetGravity(b2Vec2(0, 0));
}

TestRayCast::~TestRayCast(void)
{
}
void TestRayCast::Step(Settings* settings)
{
	Test::Step(settings);

	m_debugDraw.DrawString(5, m_textLine, "Now we have ray cast test");
	m_textLine+=15;

	currentRayAngle += 360 / 20.0 / 60.0 * DEGTORAD; 

	//calculate points of ray
	float rayLength = 25;
	b2Vec2 p1(0, 20);
	b2Vec2 p2 = p1 + rayLength * b2Vec2(sinf(currentRayAngle), cosf(currentRayAngle) );



	//set up input
	b2RayCastInput input;
	input.p1 = p1;
	input.p2 = p2;
	input.maxFraction = 1;

	//check every fixture of every body to find closest
	float closestFraction = 1; //start with end of line as p2
	b2Vec2 intersectionNormal(0, 0);
	for (b2Body* b = m_world->GetBodyList(); b; b = b->GetNext())
	{
		for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			b2RayCastOutput output;
			if (! f->RayCast(&output, input, 0)) continue;
			if (output.fraction < closestFraction)
			{
				closestFraction = output.fraction;
				intersectionNormal = output.normal;
			}
		}
	}
	b2Vec2 intersectionPoint = p1 + closestFraction*(p2 - p1);

	//draw a line
	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
	glVertex2f(p1.x, p1.y);
	glVertex2f(intersectionPoint.x, intersectionPoint.y);
	glEnd();

	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex2f(intersectionPoint.x, intersectionPoint.y);
	glEnd();
	
	b2Vec2 lowerPosition(b2Min(mouseDownPos.x, mouseUpPos.x), b2Min(mouseDownPos.y, mouseUpPos.y));
	b2Vec2 upperPosition(b2Max(mouseDownPos.x, mouseUpPos.x), b2Max(mouseDownPos.y, mouseUpPos.y));
	m_debugDraw.DrawString(5, m_textLine, "Position %.3f %.3f <> %.3f %.3f ", mouseDownPos.x, mouseDownPos.y, mouseUpPos.x, mouseUpPos.y);
	m_textLine+=15;
	m_debugDraw.DrawString(5, m_textLine, "Position %.3f %.3f <> %.3f %.3f ", lowerPosition.x, lowerPosition.y, upperPosition.x, upperPosition.y);
	m_textLine+=15;
	/**/
	glColor3f(1, 1, 1);
	glBegin(GL_LINE_LOOP);
	glVertex2f(lowerPosition.x, lowerPosition.y);
	glVertex2f(upperPosition.x, lowerPosition.y);
	glVertex2f(upperPosition.x, upperPosition.y);
	glVertex2f(lowerPosition.x, upperPosition.y);
	glEnd();
	/**/
	MyQueryCallback queryCallback;
	b2AABB aabb;
	aabb.lowerBound = lowerPosition;
	aabb.upperBound = upperPosition;
	m_world->QueryAABB(&queryCallback, aabb);
	glPointSize(6);
	glBegin(GL_POINTS);
	for (int i=0; i<queryCallback.foundBodies.size(); i++)
	{
		b2Vec2 pos = queryCallback.foundBodies[i]->GetPosition();
		glVertex2f(pos.x, pos.y);
	}
	glEnd();
}
/**/
void TestRayCast::MouseDown(const b2Vec2& p)
{
	mouseDownPos = mouseUpPos = p;
	Test::MouseDown(p);
}
void TestRayCast::MouseUp(const b2Vec2& p)
{
	mouseUpPos = p;
	Test::MouseUp(p);
}
/**/