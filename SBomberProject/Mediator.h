#include <vector>
#include <string>
#include <deque>
#pragma once
#include "GameObject.h"
class Tank;
struct Tank_messages {
	Tank* pTank;
	std::deque <std::string> messages;
};
class Mediator {
	Mediator();
	Mediator(const Mediator&) = delete;
	Mediator& operator = (const Mediator&) = delete;
	std::vector<Tank_messages> tank_messages;
public:
	void AddTank(Tank*);
	void DeleteTank(Tank*);
	void Take_message(const std::string&, Tank*);
	std::vector <std::string>* Get_message();
	std::vector <double>* Get_tank_position();
	static Mediator& getInstance();
};
