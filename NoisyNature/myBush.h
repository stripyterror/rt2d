#ifndef MYBUSH_H
#define MYBUSH_H

#include <rt2d/entity.h>

class MyBush : public Entity
{
public:
	/// @brief Constructor
	MyBush();
	/// @brief Destructor
	virtual ~MyBush();

	void MyBush::Duplicate();

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);
	bool isEaten;

	bool childCooldown = false;
	bool childBirth = false;

	float childtimer;
	Timer vt;

private:
	/* add your private declarations */
};

#endif