#include "Tank.h"


Mediator::Mediator() {}
Mediator& Mediator::getInstance() {
	static Mediator med;
	return med;
}
void Mediator::AddTank(Tank* ptank) {
	Tank_messages messages;
	messages.pTank = ptank;
	tank_messages.push_back(messages);
}
void Mediator::DeleteTank(Tank* ptank) {
	int i;
	for (i = 0; i < tank_messages.size(); i++) {
		if (tank_messages[i].pTank == ptank) break;
	}
	tank_messages.erase(tank_messages.begin() + i);
}
void Mediator::Take_message(const std::string& mess, Tank* ptank) {
	for (int i = 0; i < tank_messages.size(); i++) {
		if (tank_messages[i].pTank == ptank) {
			if (tank_messages[i].messages.size() < 10) tank_messages[i].messages.push_front(mess);
		}
	}
	return;
}
std::vector <std::string>* Mediator::Get_message()  {
	std::vector <std::string>* mess = new std::vector <std::string>;
	for (int i = 0; i < tank_messages.size(); i++) {
		if (!tank_messages[i].messages.empty()) {
			mess->push_back(*(tank_messages[i].messages.end() - 1));
			tank_messages[i].messages.pop_back();
		}
	}
	return mess;
}

std::vector <double>* Mediator::Get_tank_position() {
	std::vector <double>* pos = new std::vector<double>;
	for (int i = 0; i < tank_messages.size(); i++) {
		if (!tank_messages[i].messages.empty()) {
			pos->push_back((tank_messages[i].pTank)->GetX());
			tank_messages[i].messages.pop_back();
		}
	}
	return pos;
}