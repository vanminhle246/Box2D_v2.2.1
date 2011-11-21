#include "BallUserData.h"
#include "FooTest.h"

BallUserData::BallUserData(void)
{
}

BallUserData::~BallUserData(void)
{
}

BallUserData::BallUserData(b2World* world, float radius)
{
	m_radius = radius;
	m_contacting = false;
	m_numContacts = 0;

	//set up dynamic body
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;
	float x = (rand()%38) - 19;
	float y = (rand()%38) + 1;
	myBodyDef.position.Set(x, y);
	b2Body* body = world->CreateBody(&myBodyDef);

	//set this Ball object in the body's user data
	body->SetUserData(this);

	//add circle fixture
	b2CircleShape circleShape;
	circleShape.m_p.Set(0, 0);
	circleShape.m_radius = m_radius;
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape =&circleShape;
	myFixtureDef.density = 1;
	myFixtureDef.restitution = 1;
	body->CreateFixture(&myFixtureDef);
}
void BallUserData::render()
{
	/* change color according to speed *
	b2Vec2 vel = m_linearVelocity;
	float red = vel.Length() / 20.0;
	red = b2Min(1.0f, red);
	glColor3f(red, 0.5, 0.5);
	/**/
	/* set default color*
	glColor3f(1, 1, 1);
	/**/
	/* change color according to collision*
	if (m_contacting)
		glColor3f(1, 0, 0); //red if collide
	else
		glColor3f(1, 1, 1); //white if not collide
	/**/
	/* change color according accumulating collision*/
	if (m_numContacts > 0)
		glColor3f(1, 0, 0); //red if collide
	else
		glColor3f(1, 1, 1); //white if not collide
	/**/
	/* set initial color */
	//glColor3f(m_color.r, m_color.g, m_color.b);
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
void BallUserData::renderAtBodyPosition()
{
	//call normal render at different position/rotation
	glPushMatrix();
	glTranslatef(m_position.x, m_position.y, 0);
	glRotated(m_angle*RADTODEG, 0, 0, 1); //OpenGL uses degree here
	glScalef(m_radius, m_radius, 1);
	render(); //normal render at (0,0)
	glPopMatrix();
}
void BallUserData::startContact()
{
	m_contacting = true;
	m_numContacts++;
}
void BallUserData::endContact()
{
	m_contacting = false;
	//m_numContacts--;
}
BallUserData::BallUserData(b2World* world, float radius, b2Color color, uint16 categoryBits, uint16 maskBits)
{
	m_color = color;
	m_radius = radius;
	m_contacting = false;
	m_numContacts = 0;

	//set up dynamic body
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;
	float x = (rand()%38) - 19;
	float y = (rand()%38) + 1;
	myBodyDef.position.Set(x, y);
	b2Body* body = world->CreateBody(&myBodyDef);

	//set this Ball object in the body's user data
	body->SetUserData(this);

	//add circle fixture
	b2CircleShape circleShape;
	circleShape.m_p.Set(0, 0);
	circleShape.m_radius = m_radius;
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape =&circleShape;
	myFixtureDef.density = 1;
	myFixtureDef.restitution = 1;
	body->CreateFixture(&myFixtureDef);
	
	myFixtureDef.filter.categoryBits = categoryBits;
	myFixtureDef.filter.maskBits = maskBits;
}