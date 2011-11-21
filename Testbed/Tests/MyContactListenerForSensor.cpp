#include "MyContactListenerForSensor.h"

MyContactListenerForSensor::MyContactListenerForSensor(void)
{
}

MyContactListenerForSensor::~MyContactListenerForSensor(void)
{
}
void MyContactListenerForSensor::BeginContact(b2Contact* contact)
{
	BallForSensor* radarEntity;
	BallForSensor* aircraftEntity; 
	if (getRadarAndAircraft(contact, radarEntity, aircraftEntity ))
		radarEntity->radarAcquiredEnemy(aircraftEntity);
}
void MyContactListenerForSensor::EndContact(b2Contact* contact)
{
	BallForSensor* radarEntity;
	BallForSensor* aircraftEntity; 
	if (getRadarAndAircraft(contact, radarEntity, aircraftEntity ))
		radarEntity->radarLostEnemy(aircraftEntity);
}
bool MyContactListenerForSensor::getRadarAndAircraft(b2Contact* contact, BallForSensor*& radarEntity, BallForSensor*& aircraftEntity)
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();
	
	//make sure only one of the fixtures was a sensor
	bool sensorA = fixtureA->IsSensor();
	bool sensorB = fixtureB->IsSensor();

	if (! (sensorA ^ sensorB))
		return false;
	BallForSensor* entityA = static_cast<BallForSensor *> (fixtureA->GetBody()->GetUserData());
	BallForSensor* entityB = static_cast<BallForSensor *> (fixtureB->GetBody()->GetUserData());
	if (sensorA) //fixtureB must be an enemy aircraft
	{
		radarEntity = entityA;
		aircraftEntity = entityB;
	}
	else //fixtureA must be an enemy aircraft
	{
		radarEntity = entityB;
		aircraftEntity = entityA;
	}
	return true;
}