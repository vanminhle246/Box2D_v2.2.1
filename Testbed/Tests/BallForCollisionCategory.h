#pragma once
#include "..\framework\test.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include "freeglut/freeglut.h"
#endif
enum _entityCategory
{
	BOUNDARY = 0x0001,
	FRIENDLY_SHIP = 0x0002,
	ENEMY_SHIP = 0x0004,
	FRIENDLY_AIRCRAFT = 0x0008,
	ENEMY_AIRCRAFT = 0x0010,
	FRIENDLY_TOWER = 0x0020,
	RADAR_SENSOR = 0x0040
};
class BallForCollisionCategory :
	public Test
{
public:
	b2Body* m_body;
	b2Color m_color;
	float m_radius;
	bool m_contacting;
	BallForCollisionCategory(void);
	~BallForCollisionCategory(void);
	BallForCollisionCategory(b2World* world, float radius, b2Color color, uint16 categoryBits, uint16 maskBits);
	void render();
	void renderAtBodyPosition();
};
