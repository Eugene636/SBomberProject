
#include <conio.h>
#include <windows.h>

#include "MyTools.h"
#include "SBomber.h"
#include "Bomb.h"
#include "Ground.h"
#include "Tank.h"
#include "House.h"
#include "SBomber_command.h"

using namespace std;
using namespace MyTools;

SBomber::SBomber()
    : exitFlag(false),
    startTime(0),
    finishTime(0),
    deltaTime(0),
    passedTime(0),
    fps(0),
    bombsNumber(10),
    score(0)
{
    FileLoggerSingletone::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");

    Plane* p = new Plane;
    p->SetDirection(1, 0.1);
    p->SetSpeed(4);
    p->SetPos(5, 10);
    vecDynamicObj.push_back(p);

    LevelGUI* pGUI = new LevelGUI;
    pGUI->SetParam(passedTime, fps, bombsNumber, score);
    const uint16_t maxX = ScreenSingleton::getInstance().GetMaxX();
    const uint16_t maxY = ScreenSingleton::getInstance().GetMaxY();
    const uint16_t offset = 3;
    const uint16_t width = maxX - 7;
    pGUI->SetPos(offset, offset);
    pGUI->SetWidth(width);
    pGUI->SetHeight(maxY - 4);
    pGUI->SetFinishX(offset + width - 4);
    vecStaticObj.push_back(pGUI);

    Ground* pGr = new Ground;
    const uint16_t groundY = maxY - 5;
    pGr->SetPos(offset + 1, groundY);
    pGr->SetWidth(width - 2);
    vecStaticObj.push_back(pGr);

    Tank* pTank = new Tank;
    pTank->SetWidth(13);
    pTank->SetPos(30, groundY - 1);
    vecStaticObj.push_back(pTank);

    pTank = new Tank;
    pTank->SetWidth(13);
    pTank->SetPos(50, groundY - 1);
    vecStaticObj.push_back(pTank);

    House * pHouse = new House;
    pHouse->SetWidth(13);
    pHouse->SetPos(80, groundY - 1);
    vecStaticObj.push_back(pHouse);

    /*
    Bomb* pBomb = new Bomb;
    pBomb->SetDirection(0.3, 1);
    pBomb->SetSpeed(2);
    pBomb->SetPos(51, 5);
    pBomb->SetSize(SMALL_CRATER_SIZE);
    vecDynamicObj.push_back(pBomb);
    */
}

SBomber::~SBomber()
{
    for (size_t i = 0; i < vecDynamicObj.size(); i++)
    {
        if (vecDynamicObj[i] != nullptr)
        {
            delete vecDynamicObj[i];
        }
    }

    for (size_t i = 0; i < vecStaticObj.size(); i++)
    {
        if (vecStaticObj[i] != nullptr)
        {
            delete vecStaticObj[i];
        }
    }
}

void SBomber::MoveObjects()
{
    FileLoggerSingletone::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");

    for (size_t i = 0; i < vecDynamicObj.size(); i++)
    {
        if (vecDynamicObj[i] != nullptr)
        {
            vecDynamicObj[i]->Move(deltaTime);
        }
    }
};

void SBomber::CheckObjects()
{
    FileLoggerSingletone::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");

    CheckPlaneAndLevelGUI();
    CheckBombsAndGround();
};

void SBomber::CheckPlaneAndLevelGUI()
{
    if (FindPlane()->GetX() > FindLevelGUI()->GetFinishX())
    {
        exitFlag = true;
    }
}

void SBomber::CheckBombsAndGround() 
{
    vector<Bomb*> vecBombs = FindAllBombs();
    Ground* pGround = FindGround();
    const double y = pGround->GetY();
    for (size_t i = 0; i < vecBombs.size(); i++)
    {
        if (vecBombs[i]->GetY() >= y) // Пересечение бомбы с землей
        {
            pGround->AddCrater(vecBombs[i]->GetX());
            CheckDestoyableObjects(vecBombs[i]);
            DeleteDynamicObj(vecBombs[i]);
        }
    }

}

void SBomber::CheckDestoyableObjects(Bomb * pBomb)
{
    vector<DestroyableGroundObject*> vecDestoyableObjects = FindDestoyableGroundObjects();
    const double size = pBomb->GetWidth();
    const double size_2 = size / 2;
    for (size_t i = 0; i < vecDestoyableObjects.size(); i++)
    {
        const double x1 = pBomb->GetX() - size_2;
        const double x2 = x1 + size;
        if (vecDestoyableObjects[i]->isInside(x1, x2))
        {
            score += vecDestoyableObjects[i]->GetScore();
            DeleteStaticObj(vecDestoyableObjects[i]);
        }
    }
}

void SBomber::DeleteDynamicObj(DynamicObject* pObj)
{
    DynamicObjectDelete_command command (pObj, vecDynamicObj);
    CommandExecuter(&command);
}

void SBomber::DeleteStaticObj(GameObject* pObj)
{
    StaticObjectDelete_command command (pObj, vecStaticObj);
    CommandExecuter(&command);
}

vector<DestroyableGroundObject*> SBomber::FindDestoyableGroundObjects() const
{
    vector<DestroyableGroundObject*> vec;
    Tank* pTank;
    House* pHouse;
    for (size_t i = 0; i < vecStaticObj.size(); i++)
    {
        pTank = dynamic_cast<Tank*>(vecStaticObj[i]);
        if (pTank != nullptr)
        {
            vec.push_back(pTank);
            continue;
        }

        pHouse = dynamic_cast<House*>(vecStaticObj[i]);
        if (pHouse != nullptr)
        {
            vec.push_back(pHouse);
            continue;
        }
    }

    return vec;
}

Ground* SBomber::FindGround() const
{
    Ground* pGround;

    for (size_t i = 0; i < vecStaticObj.size(); i++)
    {
        pGround = dynamic_cast<Ground *>(vecStaticObj[i]);
        if (pGround != nullptr)
        {
            return pGround;
        }
    }

    return nullptr;
}

vector<Bomb*> SBomber::FindAllBombs() const
{
    vector<Bomb*> vecBombs;

    for (size_t i = 0; i < vecDynamicObj.size(); i++)
    {
        Bomb* pBomb = dynamic_cast<Bomb*>(vecDynamicObj[i]);
        if (pBomb != nullptr)
        {
            vecBombs.push_back(pBomb);
        }
    }

    return vecBombs;
}

Plane* SBomber::FindPlane() const
{
    for (size_t i = 0; i < vecDynamicObj.size(); i++)
    {
        Plane* p = dynamic_cast<Plane*>(vecDynamicObj[i]);
        if (p != nullptr)
        {
            return p;
        }
    }

    return nullptr;
}

LevelGUI* SBomber::FindLevelGUI() const
{
    for (size_t i = 0; i < vecStaticObj.size(); i++)
    {
        LevelGUI* p = dynamic_cast<LevelGUI*>(vecStaticObj[i]);
        if (p != nullptr)
        {
            return p;
        }
    }

    return nullptr;
}

void SBomber::ProcessKBHit()
{
    int c = _getch();

    if (c == 224)
    {
        c = _getch();
    }

    FileLoggerSingletone::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked. key = ", c);

    switch (c) {

    case 27: // esc
        exitFlag = true;
        break;

    case 72: // up
        FindPlane()->ChangePlaneY(-0.25);
        break;

    case 80: // down
        FindPlane()->ChangePlaneY(0.25);
        break;

    case 'b':
        DropBomb();
        break;

    case 'B':
        DropBomb();
        break;

    default:
        break;
    }
}

void SBomber::DrawFrame()
{
    FileLoggerSingletone::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");

    for (size_t i = 0; i < vecDynamicObj.size(); i++)
    {
        if (vecDynamicObj[i] != nullptr)
        {
            vecDynamicObj[i]->Draw();
        }
    }

    for (size_t i = 0; i < vecStaticObj.size(); i++)
    {
        if (vecStaticObj[i] != nullptr)
        {
            vecStaticObj[i]->Draw();
        }
    }

    ScreenSingleton::getInstance().GotoXY(0, 0);
    fps++;

    FindLevelGUI()->SetParam(passedTime, fps, bombsNumber, score);
}

void SBomber::TimeStart()
{
    FileLoggerSingletone::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");
    startTime = GetTickCount64();
}

void SBomber::TimeFinish()
{
    finishTime = GetTickCount64();
    deltaTime = uint16_t(finishTime - startTime);
    passedTime += deltaTime;

    FileLoggerSingletone::getInstance().WriteToLog(string(__FUNCTION__) + " deltaTime = ", (int)deltaTime);
}

void SBomber::DropBomb()
{
    D_BombDecorator command(vecDynamicObj);
    CommandExecuter(&command, 2);
}
StaticObjectDelete_command::StaticObjectDelete_command(GameObject* _pObj, std::vector <GameObject*>& _vObj) :
    pObj(_pObj), vObj(_vObj) {}
DynamicObjectDelete_command::DynamicObjectDelete_command(DynamicObject* _pObj, std::vector <DynamicObject*>& _vObj) :
    pObj(_pObj), vObj(_vObj) {}
void DynamicObjectDelete_command::Execute(const Plane* pplane, uint16_t& bombs,
    const double& speed, const CraterSize& cr_size, int16_t& scores) {}
void StaticObjectDelete_command::Execute() {
        auto it = vObj.begin();
        for (; it != vObj.end(); it++)
        {
            if (*it == pObj)
            {
                vObj.erase(it);
                break;
            }
        }
}
void DynamicObjectDelete_command::Execute() {
    auto it = vObj.begin();
    for (; it != vObj.end(); it++)
    {
        if (*it == pObj)
        {
            vObj.erase(it);
            break;
        }
    }
}
void D_Bomb::Execute(const Plane* pplane, uint16_t& bombs,
    const double& speed, const CraterSize& cr_size, int16_t& scores) {
    if (bombs > 0)
    {
        FileLoggerSingletone::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");

        //Plane* pPlane = FindPlane();
        double x = pplane->GetX() + 4;
        double y = pplane->GetY() + 2;

        Bomb* pBomb = new Bomb;
        pBomb->SetDirection(0.3, 1);
        pBomb->SetSpeed(speed);
        pBomb->SetPos(x, y);
        pBomb->SetWidth(cr_size);

        vObj.push_back(pBomb);
        bombs--;
        scores -= Bomb::BombCost;
    }
}
void D_BombDecorator::Execute(const Plane* pplane, uint16_t& bombs,
    const double& speed, const CraterSize& cr_size, int16_t& scores) {
    if (bombs > 0)
    {
        FileLoggerSingletone::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");

        //Plane* pPlane = FindPlane();
        double x = pplane->GetX() + 4;
        double y = pplane->GetY() + 2;

        BombDecorator* pBombDecorator = new BombDecorator;
        pBombDecorator->SetDirection(0.3, 1);
        pBombDecorator->SetSpeed(speed);
        pBombDecorator->SetPos(x, y);
        pBombDecorator->SetWidth(cr_size);

        vObj.push_back(pBombDecorator);
        bombs--;
        scores -= Bomb::BombCost;
    }
}
void D_BombDecorator::Execute() {}
void D_Bomb::Execute() {}
D_BombDecorator::D_BombDecorator(std::vector <DynamicObject*>& _vObj) : vObj(_vObj) {}
void StaticObjectDelete_command::Execute(const Plane* pplane, uint16_t& bombs,
    const double& speed, const CraterSize& cr_size, int16_t& scores) {}
void SBomber::CommandExecuter(IAbstract_command* command) {
    command->Execute();
}
void SBomber::CommandExecuter(IAbstract_command* command, double sp) {
    Plane* pplane = FindPlane();
    sp = 2;
    command->Execute(pplane, bombsNumber, sp, SMALL_CRATER_SIZE, score);
}
/*if (bombsNumber > 0)
 {
     FileLoggerSingletone::getInstance().WriteToLog(string(__FUNCTION__) + " was invoked");

     Plane* pPlane = FindPlane();
     double x = pPlane->GetX() + 4;
     double y = pPlane->GetY() + 2;

     Bomb* pBomb = new Bomb;
     pBomb->SetDirection(0.3, 1);
     pBomb->SetSpeed(2);
     pBomb->SetPos(x, y);
     pBomb->SetWidth(SMALL_CRATER_SIZE);

     vecDynamicObj.push_back(pBomb);
     bombsNumber--;
     score -= Bomb::BombCost;
 }*/