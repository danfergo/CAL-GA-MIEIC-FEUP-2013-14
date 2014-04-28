/*
 * TransfersSystem.cpp
 *
 *  Created on: 21/04/2014
 *      Author: Daniel
 */

#include "TransfersSystem.h"

#include <iostream>
#include <fstream>

#include "../libs/tui/TextUserInterface.h"
#include <stdlib.h>     /* atoi */

TransfersSystem::TransfersSystem(Map locals, unsigned stocking) :
		overhead(60), locals(locals), busStocking(stocking), dropPeople(new Service(0,0,&locals.getAirport(),&locals)) {
}

bool addDataFromFile(std::string filename) {
	return true;
}

void TransfersSystem::clearData() {
}

bool TransfersSystem::calcSimplePathRecursive(std::vector<Service *> & sL2p,
		unsigned min, unsigned max, unsigned dist, Service * current,
		std::queue<Service *> & ret) {

	if (sL2p.size() == 0)  // 1. if N is a goal state/node, return “success”
		return true;

	// 2. (optional) if N is a leaf state/node, return “failure”

	std::vector<Service *> tempSerivces(sL2p);
	Service * tempService;
	unsigned nMin, nMax, tempDist;

	for (std::vector<Service *>::iterator it = tempSerivces.begin(); //3. for each successor/child C of N,
	it != tempSerivces.end(); it++) {
		//3.1. (if appropriate) set new state
		std::vector<Service *>::iterator itt = sL2p.begin();
		for (; itt != sL2p.end(); itt++) {
			if (**it == **itt) {
				tempService = &(**itt);
				sL2p.erase(itt);
				break;
			}
		}

		//3.2. explore state/node C
		//3.3. if exploration was successful, return “success”

		if (current == NULL) {
			tempDist = locals.getBestTravelTime(*(tempService->getLocal()));
			if (calcSimplePathRecursive(sL2p, tempService->getSoonerTime(),
					tempService->getLaterTime(), tempDist, tempService, ret)) {
				ret.push(tempService);
				return true;
			}
		} else {
			tempDist = locals.getTravelTimeBetween(*(current->getLocal()),
					*(*it)->getLocal());

			nMax = (*it)->getArrivalTime() - tempDist - dist;
			nMin = (*it)->getSoonerTime();
			if (nMin < nMax) {
				nMax = nMax < max - dist ? nMax : max - dist;
				nMin = nMin > min - dist ? nMin : min - dist;
				if (nMin < nMax) { // Possible to explore
					if (calcSimplePathRecursive(sL2p, min, max, tempDist + dist,
							tempService, ret)) {
						ret.push(tempService);
						return true;
					}
				}

			}

		}

		//3.4 (if step 3.1 was performed) restore previous state
		sL2p.push_back(tempService);

	}

	//4. return “failure”
	return false;
}

bool TransfersSystem::calcSimplePath(std::vector<Service *> services2plane,
		std::queue<Service *> & ret) {
	unsigned stocking = 0;
	for (std::vector<Service *>::iterator it = services2plane.begin();
			it != services2plane.end(); it++) {
		stocking += (*it)->getPeopleQuantity();
	}

	if (busStocking < stocking)
		return false;

	ret.empty(); // ensuring that the queue is empty
	return calcSimplePathRecursive(services2plane, 0, 0, 0, NULL, ret);
}

std::vector<std::vector<Service *> > TransfersSystem::calcComplexPath(
		std::vector<Service *> services) {
	std::vector<std::vector<Service *> > ret;

}

bool TransfersSystem::calcComplexPathRecursive(std::vector<Service *> & sL2p,
		unsigned min, unsigned max, unsigned dist, unsigned stocking,
		Service * current, std::queue<Service *> & ret) {

	if (sL2p.size() == 0)  // 1. if N is a goal state/node, return “success”
		return true;

	// 2. (optional) if N is a leaf state/node, return “failure”

	std::vector<Service *> tempSerivces(sL2p);
	Service * tempService;
	std::vector<Edge<Local> > edges;
	unsigned nMin, nMax, tempDist;

	for (std::vector<Service *>::iterator it = tempSerivces.begin(); //3. for each successor/child C of N,
	it != tempSerivces.end(); it++) {
		//3.1. (if appropriate) set new state
		std::vector<Service *>::iterator itt = sL2p.begin();
		for (; itt != sL2p.end(); itt++) {
			if (**it == **itt) {
				tempService = &(**itt);
				sL2p.erase(itt);
				break;
			}
		}

		//3.2. explore state/node C
		//3.3. if exploration was successful, return “success”

		if (current == NULL) {
			tempDist = locals.getBestTravelTime(*(tempService->getLocal()));
			if (calcSimplePathRecursive(sL2p, tempService->getSoonerTime(),
					tempService->getLaterTime(), tempDist, tempService, ret)) {
				ret.push(tempService);
				return true;
			}
		} else {
			if ((*it)->getPeopleQuantity() + stocking <= busStocking) {
				tempDist = locals.getTravelTimeBetween(*(current->getLocal()),
						*(*it)->getLocal());

				nMax = (*it)->getArrivalTime() - tempDist - dist;
				nMin = (*it)->getSoonerTime();
				if (nMin < nMax) {
					nMax = nMax < max - dist ? nMax : max - dist;
					nMin = nMin > min - dist ? nMin : min - dist;
					if (nMin < nMax) { // Possible to explore
						if (calcComplexPathRecursive(sL2p, min, max,
								tempDist + dist,
								(*it)->getPeopleQuantity() + stocking,
								tempService, ret)) {
							ret.push(tempService);
							return true;
						}
					}
				}
			}
		}

		//3.4 (if step 3.1 was performed) restore previous state
		sL2p.push_back(tempService);

		// tries to drop people.
		dist = locals.getBestTravelTime(*current->getLocal());
		if(calcComplexPathRecursive(sL2p, min - dist, max - dist, 0, 0, dropPeople,ret)){
			ret.push(dropPeople);
			return true;
		}
	}

	//4. return “failure”
	return false;

}

std::vector<std::vector<std::vector<Service *> > > TransfersSystem::planTransfers() {
	std::vector<std::vector<std::vector<Service *> > > ret;

	return ret;
}

bool TransfersSystem::addDataFromFile(std::string filename) {
	string line;
	std::vector<std::string> data;
	unsigned state = 0;
	ifstream myfile(filename.c_str());

	std::vector<Local *> locs;

	if (myfile.is_open()) {
		while (getline(myfile, line)) {

			if (line.substr(0, 5) == "Local") {
				state = 1;
				break;
			} else if (line.substr(0, 8) == "Distance") {
				state = 2;
				break;
			} else if (line.substr(0, 7) == "Service") {
				state = 3;
				break;
			}

			data = TextUserInterface::strsplit(line, ";");

			switch (state) {
			case 1:
				if (data.size() == 1) {
					locs.push_back(new Local(data[0]));
					locals.addVertex(*locs.front());
					locals.getVertex(*locs.front())->addEdge(
							locals.getVertex(*locs.front()), 0);
				}
				break;
			case 2:
				if (data.size() == 3) {
					locals.getVertex(*locs[atoi(data[0].c_str())])->addEdge(
							locals.getVertex(*locs[atoi(data[1].c_str())]),
							(double) atoi(data[2].c_str()));
				}
				break;
			case 3:
				if (data.size() == 3) {
					services.push_back(
							*new Service(atoi(data[1].c_str()),
									atoi(data[2].c_str()),
									locs[atoi(data[0].c_str())], &locals));
				}
				break;
			}

		}
		myfile.close();
	}
}
