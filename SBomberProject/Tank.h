#pragma once

#include "Mediator.h"
#include <stdint.h>

#include "DestroyableGroundObject.h"

class Tank : public DestroyableGroundObject
{
public:

	bool __fastcall isInside(double x1, double x2) const override;

	inline uint16_t GetScore() const override { return score; }

	void send_message();

	void Draw() const override;
	Tank();
	~Tank();
private:
	Mediator& mediator;
	const uint16_t score = 30;
	std::string messages[5] = { "The damned bomb plane!", "My cannon more bigger than you!", 
	"I have kill a lot of plane!", "My gun in your ass!", "I have shoot to your mom!"};
};



