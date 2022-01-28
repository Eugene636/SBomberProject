#pragma once

#include <vector>

#include "LevelGUI.h"
#include "Plane.h"
#include "Bomb.h"
#include "Ground.h"
#include "Tank.h"
#include "SBomber.h"
/*
class Command // базовый класс «Команда» имеет две виртуальные функции Выполнения и Отмены
{
protected:
	Document* doc;
public:
	virtual ~Command() {}
	virtual void Execute(std::vector <>) = 0;
	virtual void unExecute() = 0;

	void setDocument(Document* _doc)
	{
		doc = _doc;
	}
};
*/
class IAbstract_command {
protected:
public:	
	virtual ~IAbstract_command() {}
	virtual void Execute() = 0;
	virtual void Execute(const Plane* pplane, uint16_t& bombs,
		const double& speed, const CraterSize& cr_size, int16_t& scores) = 0;
};

class StaticObjectDelete_command : public IAbstract_command{
protected:
	GameObject* pObj;
	std::vector <GameObject*>& vObj;
	virtual void Execute(const Plane* pplane, uint16_t& bombs,
		const double& speed, const CraterSize& cr_size, int16_t& scores);
public:
	StaticObjectDelete_command(GameObject* _pObj, std::vector <GameObject*>& _vObj);
	void Execute() override;
};


class DynamicObjectDelete_command : public IAbstract_command {
protected:
	DynamicObject* pObj;
	std::vector <DynamicObject*>& vObj;
	virtual void Execute(const Plane* pplane, uint16_t& bombs,
		const double& speed, const CraterSize& cr_size, int16_t& scores);
public:
	DynamicObjectDelete_command(DynamicObject* _pObj, std::vector <DynamicObject*>& _vObj);
	void Execute() override;
};
class D_Bomb : public IAbstract_command {
	std::vector <DynamicObject*>& vObj;
public:
	D_Bomb(std::vector <DynamicObject*>& _vObj) : vObj(_vObj) {}
	void Execute(const Plane* pplane, uint16_t& bombs,
		const double& speed, const CraterSize& cr_size, int16_t& scores) override;
	void Execute() override;
};
class D_BombDecorator : public IAbstract_command {
	std::vector <DynamicObject*>& vObj;
public:
	
	D_BombDecorator(std::vector <DynamicObject*>& _vObj);
	void Execute(const Plane* pplane, uint16_t& bombs,
		const double& speed, const CraterSize& cr_size, int16_t& scores) override;
	void Execute() override;
};


