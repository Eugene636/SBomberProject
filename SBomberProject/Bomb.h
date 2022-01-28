#pragma once
#include "DynamicObject.h"

class Bomb : public DynamicObject
{
public:

	static const uint16_t BombCost = 10; // стоимость бомбы в очках

	void Draw() const override;

private:

};

class BombDecorator : public DynamicObject {
public:
	void Draw() const override;
	void SetPos(double nx, double ny) override;
	uint16_t GetWidth() const override;
	void Move(uint16_t time) override;
	void SetSpeed(double) override;
	void SetDirection(double, double) override;
	double GetY() const override; 
	double GetX() const override; 
private :
	Bomb bomb;
};

