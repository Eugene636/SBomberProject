#pragma once

#include "DynamicObject.h"
#ifndef Bomb_H
#define Bomb_H
class Bomb : public DynamicObject
{
public:

	static const uint16_t BombCost = 10; // стоимость бомбы в очках

	void Draw() const override;
	void accept(const Viziter& e) override;
private:
};
#endif;
#ifndef Viziter_H
#define Viziter_H
class Plane;
#include "Viziter.h"
//#include "Plane.h"
#endif
