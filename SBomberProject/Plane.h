#pragma once

#include "DynamicObject.h"
#ifndef Plane_H
#define Plane_H
class Viziter;
class Plane : public DynamicObject {
public:

    void Draw() const override;

    inline void ChangePlaneY(double dy) { yDirection += dy; }
    void accept(const Viziter& e) override;
private:

};
#endif
#ifndef Viziter_H
#define Viziter_H
class Bomb;
#include "Viziter.h"
#include "Bomb.h"
#endif

