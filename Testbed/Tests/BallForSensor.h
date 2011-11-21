#pragma once
#include "..\framework\test.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include "freeglut/freeglut.h"
#endif
#include <vector>

class BallForSensor
{
public:
	b2Body* m_body;
	b2Color m_color;
	float m_radius;
	bool m_contacting;
	std::vector<BallForSensor *> visibleEnemies;

	BallForSensor(void);
	~BallForSensor(void);
	BallForSensor(b2World* world, float radius, b2Color color, uint16 categoryBits, uint16 maskBits);
	void render();
	void renderAtBodyPosition();
	void radarAcquiredEnemy(BallForSensor* enemy);
	void radarLostEnemy(BallForSensor* enemy);
};
