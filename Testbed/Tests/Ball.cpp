#include "Ball.h"
#include "FooTest.h"

Ball::Ball(void)
{
}

Ball::~Ball(void)
{
}
Ball::Ball(b2World* world, float radius)
{
	m_contacting = false;
	m_body = NULL;
	m_radius = radius;

	//set up dynamic body, store in class variable
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;
	myBodyDef.position.Set(0, 20);
	m_body = world->CreateBody(&myBodyDef);

	//set this Ball object in the body's user data
	

	//add circle fixture
	b2CircleShape circleShape;
	circleShape.m_p.Set(0, 0);
	circleShape.m_radius = m_radius; //use class variable
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &circleShape;
	myFixtureDef.density = 1;
	m_body->CreateFixture(&myFixtureDef);
	
}
void Ball::render()
{
	/* change color according speed */
	b2Vec2 vel = m_body->GetLinearVelocity();
	float red = vel.Length() / 20.0;
	red = b2Min(1.0f, red);
	glColor3f(red, 0.5, 0.5);
	/**/
	/* set default color *
	glColor3f(1, 1, 1);
	/**/
	/* change color according contact*
	if (m_contacting)
		glColor3f(1, 0, 0); //red if collide
	else
		glColor3f(1, 1, 1); //white if non collide
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
void Ball::renderAtBodyPosition()
{
	//get current position from Box2D
	b2Vec2 pos = m_body->GetPosition();
	float angle = m_body->GetAngle();

	//call normal render at different position/rotation
	glPushMatrix();
	glTranslatef(pos.x, pos.y, 0);
	glRotated(angle*RADTODEG, 0, 0, 1); //OpenGL uses degree here
	glScalef(m_radius, m_radius, 1);
	render(); //normal render at (0,0)
	glPopMatrix();
}
void Ball::startContact()
{
	m_contacting = true;
}
void Ball::endContact()
{
	m_contacting = false;
}