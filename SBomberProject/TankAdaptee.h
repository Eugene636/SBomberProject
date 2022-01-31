#pragma once

#include "DestroyableGroundObject.h"
#include "ScreenSingleton.h"

class TankAdaptee {
public:

	TankAdaptee() : x(0.0), y(0.0), width(0) { }

	void Paint() const;
	bool __fastcall isInRange(double x1, double x2) const;

	inline uint16_t GetScore() const;

	inline void SetPos(double nx, double ny);
	inline double GetY() const;
	inline double GetX() const;

	inline void SetWidth(uint16_t widthN);
	inline uint16_t GetWidth() const;

protected:

	double x, y;
	uint16_t width;
	const uint16_t score = 30;
};

class TankAdapter : public DestroyableGroundObject {
	TankAdaptee tank;
public:
	void SetPos(double, double)  override;
	uint16_t GetWidth() const override;
	void Draw() const override;
	bool __fastcall isInside(double, double) const;
	uint16_t GetScore () const;
};



