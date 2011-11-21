#include "BallForCollisionCategory.h"
#include <Testbed\Tests\TestFriction.h>

BallForCollisionCategory::BallForCollisionCategory(void)
{
}

BallForCollisionCategory::~BallForCollisionCategory(void)
{
}
BallForCollisionCategory::BallForCollisionCategory(b2World* world, float radius, b2Color color, uint16 categoryBits, uint16 maskBits)
{
	m_color = color;
	m_radius = radius;
	m_contacting = false;
	m_color = color;

	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;
	float x = (rand()%38) - 19;
	float y = (rand()%38) + 1;
	myBodyDef.position.Set(x, y);
	m_body = world->CreateBody(&myBodyDef);

	b2CircleShape circleShape;
	circleShape.m_p.Set(0, 0);
	circleShape.m_radius = m_radius;
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &circleShape;
	myFixtureDef.density = 1;
	myFixtureDef.restitution = 1;
	myFixtureDef.filter.categoryBits = categoryBits;
	myFixtureDef.filter.maskBits = maskBits;

	m_body->CreateFixture(&myFixtureDef);


}
void BallForCollisionCategory::render()
{
	/* set initial color */
	glColor3f(m_color.r, m_color.g, m_color.b);
	//glColor3f(0, 1, 0); 
	/**/

	//nose and eyes
	glPointSize(4);
	glBegin(GL_POINTS);
	glVertex2f(0, 0);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glEnd();

	//mouth
	glBegin(GL_LINES);
	glVertex2f(-0.5, -0.5);
	glVertex2f(-0.16, -0.6);
	glVertex2f(0.16, -0.6);
	glVertex2f(0.5, -0.5);

	glVertex2f(-0.5, -0.5);
	glVertex2f(0.5, -0.5);

	glVertex2f(-0.16, -0.6);
	glVertex2f(0.16, -0.6);
	glEnd();

	//circle outline
	glBegin(GL_LINE_LOOP);
	for (float a = 0; a < 360*DEGTORAD; a += 30*DEGTORAD)
		glVertex2f(sinf(a), cosf(a));
	glEnd();
}
void BallForCollisionCategory::renderAtBodyPosition()
{
	//call normal render at different position/rotation
	glPushMatrix();
	glTranslatef(m_body->GetPosition().x, m_body->GetPosition().y, 0);
	glRotated(m_body->GetAngle()*RADTODEG, 0, 0, 1); //OpenGL uses degree here
	glScalef(m_radius, m_radius, 1);
	render(); //normal render at (0,0)
	glPopMatrix();
}