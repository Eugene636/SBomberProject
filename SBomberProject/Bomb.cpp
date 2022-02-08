
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

void Bomb::accept(const Viziter& e) {

    e.log(*this);
}
Bomb::Bomb(const std::vector<DestroyableGroundObject*>& observable_vector) {
    for (DestroyableGroundObject* n : observable_vector) {
        AddObserver(n);
    }
}
void Bomb::AddObserver(DestroyableGroundObject* pObject) {
    observers.push_back(pObject);
}

DestroyableGroundObject* Bomb::CheckDestroyableObjects() {

 //   vector<DestroyableGroundObject*> vecDestoyableObjects = FindDestoyableGroundObjects();
    const double size = this->GetWidth();
    const double size_2 = size / 2;
    for (size_t i = 0; i < observers.size(); i++)
    {
        const double x1 = this->GetX() - size_2;
        const double x2 = x1 + size;
        if (observers[i]->isInside(x1, x2))
        {
            return observers[i];
 //           score += observers[i]->GetScore();
 //           DeleteStaticObj(vecDestoyableObjects[i]);
        }
    }
    return nullptr;
}

