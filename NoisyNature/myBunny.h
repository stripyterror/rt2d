
#ifndef MYBUNNY_H
#define MYBUNNY_H

#include <rt2d/entity.h>
#include "myBush.h"

class MyBunny : public Entity
{
public:
	/// @brief Constructor
	MyBunny();
	/// @brief Destructor
	virtual ~MyBunny();

	MyBush* FindPlant(std::vector<MyBush*> & bl);

	void WalktoPlant(float deltaTime);
	bool MyBunny::Eat();

	Point2 test;

	bool eating = false;
	bool doneEating = false;
	bool inEatingDistance;

	float distanceToClosestBush = 10000000;
	float dtb;
	MyBush* closestbush;

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

private:
	/* add your private declarations */
	int health;
	float speed;

	Timer eb;
	Timer ht;

	int hunger;
	int hungerdelay;
	int eatingtime;

	Vector2 velocity;
};

#endif