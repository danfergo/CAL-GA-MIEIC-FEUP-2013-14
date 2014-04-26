/*
 * TransfersSystem.cpp
 *
 *  Created on: 21/04/2014
 *      Author: Daniel
 */

#include "TransfersSystem.h"

TransfersSystem::TransfersSystem() {

}

bool addDataFromFile(std::string filename) {
	return true;
}

void TransfersSystem::clearData() {
}

bool TransfersSystem::calcSimplePathRecursive(
		std::vector<Service *> & services2plane, std::stack<Service *> & ret) {
	// 1. if N is a goal state/node, return “success”
	if (services2plane.size() == 0) {
		return true;
	}

	// 2. (optional) if N is a leaf state/node, return “failure”

	std::vector<Service *> tempSerivces(services2plane);
	Service * tempService;

	//3. for each successor/child C of N,
	for (std::vector<Service *>::iterator it = tempSerivces.begin();
			it != tempSerivces.end(); it++) {

		if(ret.size() != 0 || ret.top()->local){

		//3.1. (if appropriate) set new state

		for (std::vector<Service *>::iterator itt = services2plane.begin();
				itt != services2plane.end(); itt++) {
			if (**it == **itt) {
				tempService = &(**itt);
				services2plane.erase(itt);
				break;
			}
		}

		//3.2. explore state/node C
		//3.3. if exploration was successful, return “success”
		if (this->calcSimplePath(services2plane, ret))
			return true;


		//3.4 (if step 3.1 was performed) restore previous state
		services2plane.push_back(tempService);

		}
	}

	//4. return “failure”
	return false;
}

bool TransfersSystem::calcSimplePath(std::vector<Service *> & services2plane,
		std::stack<Service *> & ret) {
	unsigned stocking = 0;
	for (std::vector<Service *>::iterator it = services2plane.begin();
			it != services2plane.end(); it++) {
		stocking += (*it)->qtdPessoas;
	}

	if (busStocking > stocking)
		return false;

	return calcSimplePathRecursive(services2plane, ret);
}

std::vector<std::vector<Service *> > TransfersSystem::calcComplexPath(
		std::vector<Service *> services) {
	std::vector<std::vector<Service *> > ret;

	return ret;
}

std::vector<std::vector<std::vector<Service *> > > TransfersSystem::planTransfers() {
	std::vector<std::vector<std::vector<Service *> > > ret;

	return ret;
}
