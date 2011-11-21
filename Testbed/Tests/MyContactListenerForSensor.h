#pragma once
#include <Box2d\dynamics\b2worldcallbacks.h>
#include "BallForSensor.h"

class MyContactListenerForSensor :
	public b2ContactListener
{
public:
	MyContactListenerForSensor(void);
	~MyContactListenerForSensor(void);
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	bool getRadarAndAircraft(b2Contact* contact, BallForSensor*& radarEntity, BallForSensor*& aircraftEntity);
};
