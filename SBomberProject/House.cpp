
#include <iostream>

#include "House.h"
#include "MyTools.h"

using namespace std;
using namespace MyTools;

bool House::isInside(double x1, double x2) const
{
	const double XBeg = x + 2;
	const double XEnd = x + width - 1;

	if (x1 < XBeg && x2 > XEnd)
	{
		return true;
	}

	if (x1 > XBeg && x1 < XEnd)
	{
		return true;
	}

	if (x2 > XBeg && x2 < XEnd)
	{
		return true;
	}

	return false;
}

void House::Draw() const
{
	ScreenSingleton::getInstance().SetColor(CC_Yellow);
	for (int i = 6; i >= 0; i--) {
		ScreenSingleton::getInstance().GotoXY(x, y - i);
		for (int k = 0; k < 14; k++) {
			cout<<look[i][k];
		}
	}
}

void HouseBuilderA::walls() {
	pHouse->look[0][0] = ' ';
	for (int i = 1; i <= 12; i++) {
		pHouse->look[0][i] = '#';
	}
	pHouse->look[0][13] = ' ';
	for (int k = 1; k <= 2; k++) {
		pHouse->look[k][0] = ' ';
		pHouse->look[k][1] = '#';
		pHouse->look[k][12] = '#';
		for (int i = 2; i < 12; i++) {
			pHouse->look[k][i] = ' ';
		}
		pHouse->look[k][13] = ' ';
	}
}
void HouseBuilderA :: window() {
	pHouse->look[3][0] = ' ';
	for (int i = 1; i <= 12; i++) {
		pHouse->look[3][i] = '#';
	}
	pHouse->look[3][13] = ' ';
	pHouse->look[4][0] = ' ';
	pHouse->look[4][1] = '#';
	pHouse->look[4][12] = '#';
	for (int i = 2; i < 12; i++) {
		pHouse->look[4][i] = ' ';
	}
	pHouse->look[4][13] = ' ';
}
void HouseBuilderA::roof() {
	for (int i = 0; i < 3; i++) pHouse->look[5][i] = ' ';
	for (int i = 3; i < 11; i++) pHouse->look[5][i] = '#';
	for (int i = 11; i < 14; i++) pHouse->look[5][i] = ' ';
}
void HouseBuilderA::chimney() {
	for (int i = 0; i < 6; i++) pHouse->look[6][i] = ' ';
	pHouse->look[6][6] = '#';
	for (int i = 7; i < 14; i++) pHouse->look[6][i] = ' ';
}
House* HouseDirector::Construct(HouseBuilder& builder) {

	builder.walls();
	builder.window();
	builder.roof();
	builder.chimney();
	return builder.getHouse();
}
House* HouseBuilder::getHouse() { return pHouse; }

/*cout << "  ########  ";
ScreenSingleton::getInstance().GotoXY(x, y - 4);
cout << "##        ##";
ScreenSingleton::getInstance().GotoXY(x, y - 3);
cout << "############";
ScreenSingleton::getInstance().GotoXY(x, y - 2);
cout << "#          #";
ScreenSingleton::getInstance().GotoXY(x, y - 1);
cout << "#          #";
ScreenSingleton::getInstance().GotoXY(x, y);
cout << "############";*/