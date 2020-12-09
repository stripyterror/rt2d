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

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

private:
	/* add your private declarations */
};

#endif