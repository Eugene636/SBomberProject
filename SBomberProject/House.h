#pragma once
class House;
class HouseBuilder;
class HouseBuilderA;
#include <stdint.h>

#include "DestroyableGroundObject.h"
enum detail { Simple_house };

class House : public DestroyableGroundObject
{
public:

	bool __fastcall isInside(double x1, double x2) const override;

	inline uint16_t GetScore() const override { return score; }

	void Draw() const override;


private:
	char look[7][14];
	const uint16_t score = 40;
	friend class HouseBuilderA;
};
class HouseBuilder {
protected:
	House* pHouse;
public:
	HouseBuilder() : pHouse(new House) {}
	virtual void walls() {};
	virtual void roof() {};
	virtual void chimney() {};
	virtual void window() {};
	House* getHouse();
};
class HouseBuilderA : public HouseBuilder {
public:
	void walls() override;
	void roof() override;
	void chimney() override;
	void window() override;
};

class HouseDirector {
public:
	House* Construct(HouseBuilder& builder);
};

