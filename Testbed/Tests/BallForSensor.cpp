#include "BallForSensor.h"
#include "TestFriction.h"

BallForSensor::BallForSensor(void)
{
}

BallForSensor::~BallForSensor(void)
{
}
BallForSensor::BallForSensor(b2World* world, float radius, b2Color color, uint16 categoryBits, uint16 maskBits)
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
	m_body->SetUserData(this);
}
void BallForSensor::render()
{
	/* set initial color *
	glColor3f(m_color.r, m_color.g, m_color.b);
	
	/**/
	/* change color according radar perception*/
	if (visibleEnemies.size() > 0)
	{
		glColor3f(1, 1, 0); //yellow
	}
	else
		glColor3f(m_color.r, m_color.g, m_color.b);
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
void BallForSensor::renderAtBodyPosition()
{
	//call normal render at different position/rotation
	b2Vec2 pos = m_body->GetPosition();
	glPushMatrix();
	glTranslatef(pos.x, pos.y, 0);
	glRotated(m_body->GetAngle()*RADTODEG, 0, 0, 1); //OpenGL uses degree here
	glScalef(m_radius, m_radius, 1);
	render(); //normal render at (0,0)
	glPopMatrix();
	
	/**
	glPushMatrix();
	glColor3f(1, 1, 1);
	glLineStipple(1, 0xF0F0);
	glEnable(GL_LINE_STIPPLE);
	glBegin(GL_LINES);
	for (int i=0; i < visibleEnemies.size(); i++ )
	{
		b2Vec2 enemyPosition = visibleEnemies[i]->m_body->GetPosition();
		glVertex2f(pos.x, pos.y);
		glVertex2f(enemyPosition.x, enemyPosition.y);
	}
	glEnd();
	glDisable(GL_LINE_STIPPLE);
	glPopMatrix();
	/**/
}
void BallForSensor::radarAcquiredEnemy(BallForSensor* enemy)
{
	visibleEnemies.push_back(enemy);
}
void BallForSensor::radarLostEnemy(BallForSensor* enemy)
{
	visibleEnemies.erase( std::find(visibleEnemies.begin(), visibleEnemies.end(), enemy));
}