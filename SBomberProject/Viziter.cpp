#include "FileLoggerSingletone.h"
#include "Plane.h"
#include "Bomb.h"
void LogViziter::log(const Bomb& bomb) const {
	FileLoggerSingletone::getInstance().WriteToLog("XBombCoord", bomb.GetX());
	FileLoggerSingletone::getInstance().WriteToLog("YBombCoord", bomb.GetY());
}

void LogViziter::log(const Plane& plane) const {
	FileLoggerSingletone::getInstance().WriteToLog("XPlaneCoord", plane.GetX());
	FileLoggerSingletone::getInstance().WriteToLog("YPlaneCoord", plane.GetY());

}