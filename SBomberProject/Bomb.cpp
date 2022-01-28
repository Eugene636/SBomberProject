
#include <iostream>

#include "Bomb.h"
#include "MyTools.h"

using namespace std;
using namespace MyTools;

void Bomb::Draw() const
{
    ScreenSingleton::getInstance().SetColor(CC_LightMagenta);
    ScreenSingleton::getInstance().GotoXY(x, y);
    cout << "*";
}
void BombDecorator::Draw() const
{
    bomb.Draw();
    // Некоторое изменение внешнего вида бомбы
    GotoXY(bomb.GetX(), bomb.GetY() - 1);
    cout << "|";
}
void BombDecorator::SetPos(double nx, double ny) { bomb.SetPos(nx, ny); }
uint16_t BombDecorator::GetWidth() const { return bomb.GetWidth(); }
void BombDecorator::Move(uint16_t time){
    bomb.Move(time);
}
void BombDecorator::SetSpeed(double sp) { bomb.SetSpeed(sp); }
void BombDecorator::SetDirection(double nx, double ny) { bomb.SetDirection(nx, ny); }
double BombDecorator::GetY() const  { return bomb.GetY(); }
double BombDecorator::GetX() const  { return bomb.GetX(); }
