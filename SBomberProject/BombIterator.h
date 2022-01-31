#pragma once
#include <vector>
#include <iterator>
#include "DynamicObject.h"
#include "Bomb.h"
/*class IGameObjectIterator {
public:
    virtual std::vector<GameObject*>::iterator begin() = 0;
    virtual GameObject*& operator [] (size_t) = 0;
    virtual std::vector<GameObject*>::iterator end() = 0;
    virtual std::vector <GameObject*>& all_objects();
    virtual std::vector<GameObject*>::iterator& operator++(int);
    virtual std::vector<GameObject*>::iterator& operator++();
};*/
class BombIterator {

    std::vector<Bomb*>::iterator Iterator;
    std::vector <Bomb*> bomb_vector;
public:
    BombIterator(const std::vector <DynamicObject*>& vec);
    std::vector<Bomb*>::iterator begin();
    Bomb*& operator [] (size_t);
    std::vector<Bomb*>::iterator end();
    std::vector <Bomb*>& all_objects();
    std::vector<Bomb*>::iterator& operator++();
    std::vector<Bomb*>::iterator& operator++(int);
    void erase(size_t n);
};
void BombIterator::erase(size_t n) {
    auto it = bomb_vector.begin();
    bomb_vector.erase(it + n);
}
std::vector<Bomb*>::iterator& BombIterator::operator++ () {
    return (++Iterator);
}
std::vector<Bomb*>::iterator& BombIterator::operator++ (int) {
    std::vector<Bomb*>::iterator it = this->Iterator;
    Iterator++;
    return it;
}
std::vector <Bomb*>& BombIterator::all_objects() {
    return bomb_vector;
}

BombIterator::BombIterator(const std::vector <DynamicObject*>& vec) {
    Bomb* pBomb;
    for (int i = 0; i < vec.size(); i++) {
        pBomb = dynamic_cast<Bomb*> (vec[i]);
        if (pBomb != nullptr) bomb_vector.push_back(pBomb);
    }
    Iterator = bomb_vector.begin();
}
std::vector<Bomb*>::iterator BombIterator::begin() {

    return bomb_vector.begin();
}
std::vector<Bomb*>::iterator BombIterator::end() {
    return bomb_vector.end();
}
Bomb*& BombIterator::operator [] (size_t n) {
    return bomb_vector[n];
}


