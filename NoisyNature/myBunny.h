
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

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

private:
	/* add your private declarations */
	int health;

	Timer ht;
	int hunger;
	int hungerdelay;
	MyBush* closestbush;
};

#endif