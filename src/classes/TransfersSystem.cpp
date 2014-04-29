/*
 * TransfersSystem.cpp
 *
 *  Created on: 21/04/2014
 *      Author: Daniel
 */

#include "TransfersSystem.h"

#include "../libs/tui/TextUserInterface.h"
#include <iostream>
#include <fstream>

#include <stdlib.h>     /* atoi */

TransfersSystem::TransfersSystem(Local * airport, unsigned stocking,unsigned overhead) :
		overhead(60), locals(airport), busStocking(stocking) {
	dropPeople = new Service(0, 0, locals.getAirportLocal());
}

unsigned TransfersSystem::absSoonerTime(Service * s) {
	return s->getArrivalTime() - locals.getBestTravelTime(s->getLocal());
}

unsigned TransfersSystem::absLatterTime(Service * s) {
	return s->getArrivalTime() - locals.getBestTravelTime(s->getLocal())
			- overhead;
}

bool addDataFromFile(std::string filename) {
	return true;
}

void TransfersSystem::clearData() {
}

Service * popService(std::vector<Service *> & vec2search,
		const std::vector<Service *>::iterator & srv) {
	Service * ret;
	for (std::vector<Service *>::iterator it = vec2search.begin();
			it != vec2search.end(); it++) {
		if (**it == **srv) {
			ret = &(**it);
			vec2search.erase(it);
			return ret;
		}
	}
	return NULL;
}


bool TransfersSystem::calcSimplePathRecursive(std::vector<Service *> & srvsLeft,
		unsigned min, unsigned max, unsigned previousDist, Service * lastSrv,
		std::queue<Service *> & ret) {

	if (srvsLeft.size() == 0)  // 1. if N is a goal state/node, return “success”
		return true;

	// 2. (optional) if N is a leaf state/node, return “failure”

	std::vector<Service *> clnServices(srvsLeft);
	Service * tmpSrv;
	unsigned nMin, nMax, tempDist;

	std::vector<Service *>::iterator it = clnServices.begin(); //3. for each successor/child C of N,
	for (;  it != clnServices.end(); it++) {
		//3.1. (if appropriate) set new state
		tmpSrv = popService(srvsLeft,it);

		//3.2. explore state/node C
		//3.3. if exploration was successful, return “success”

		if (lastSrv == NULL) {
			tempDist = locals.getBestTravelTime(tmpSrv->getLocal());
			if (calcSimplePathRecursive(srvsLeft, absSoonerTime(tmpSrv),
					absLatterTime(tmpSrv), tempDist, tmpSrv, ret)) {
				ret.push(tmpSrv);
				return true;
			}
		} else {
			tempDist = locals.getTravelTimeBetween(lastSrv->getLocal(),
					(*it)->getLocal());

			nMax = (*it)->getArrivalTime() - tempDist - previousDist;
			nMin = absSoonerTime((*it));
			if (nMin < nMax) {
				nMax = nMax < max - previousDist ? nMax : max - previousDist;
				nMin = nMin > min - previousDist ? nMin : min - previousDist;
				if (nMin < nMax) { // Possible to explore
					if (calcSimplePathRecursive(srvsLeft, min, max, tempDist + previousDist,
							tmpSrv, ret)) {
						ret.push(tmpSrv);
						return true;
					}
				}

			}

		}

		//3.4 (if step 3.1 was performed) restore previous state
		srvsLeft.push_back(tmpSrv);

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



bool TransfersSystem::calcComplexPathRecursive(std::vector<Service *> & srvsLeft,
		unsigned min, unsigned max, unsigned previousDist, unsigned previousStck,
		Service * lastSrv, std::queue<Service *> & ret) {

	if (srvsLeft.size() == 0)  // 1. if N is a goal state/node, return “success”
		return true;

	// 2. (optional) if N is a leaf state/node, return “failure”

	std::vector<Service *> clnServices(srvsLeft);
	Service * tmpSrv;
	std::vector<Edge<Local> > edges;
	unsigned nMin, nMax, tmpDist;

	for (std::vector<Service *>::iterator it = clnServices.begin(); //3. for each successor/child C of N,
	it != clnServices.end(); it++) {
		//3.1. (if appropriate) set new state
		tmpSrv = popService(srvsLeft,it);

		//3.2. explore state/node C
		//3.3. if exploration was successful, return “success”

		if (lastSrv == NULL) {
			tmpDist = locals.getBestTravelTime(tmpSrv->getLocal());
			if (calcSimplePathRecursive(srvsLeft, absSoonerTime(tmpSrv),
					absLatterTime(tmpSrv), tmpDist, tmpSrv, ret)) {
				ret.push(tmpSrv);
				return true;
			}
		} else {
			if ((*it)->getPeopleQuantity() + previousStck <= busStocking) {
				tmpDist = locals.getTravelTimeBetween(lastSrv->getLocal(),
						(*it)->getLocal());

				nMax = (*it)->getArrivalTime() - tmpDist - previousDist;
				nMin = absSoonerTime(*it);
				if (nMin < nMax) {
					nMax = nMax < max - previousDist ? nMax : max - previousDist;
					nMin = nMin > min - previousDist ? nMin : min - previousDist;
					if (nMin < nMax) { // Possible to explore
						if (calcComplexPathRecursive(srvsLeft, min, max,
								tmpDist + previousDist,
								(*it)->getPeopleQuantity() + previousStck,
								tmpSrv, ret)) {
							ret.push(tmpSrv);
							return true;
						}
					}
				}
			}
		}

		//3.4 (if step 3.1 was performed) restore previous state
		srvsLeft.push_back(tmpSrv);

		// tries to drop people.
		previousDist = locals.getBestTravelTime(lastSrv->getLocal());
		if (calcComplexPathRecursive(srvsLeft, min - previousDist, max - previousDist, 0, 0,
				dropPeople, ret)) {
			ret.push(dropPeople);
			return true;
		}
	}

	//4. return “failure”
	return false;

}


std::vector<std::vector<Service *> > TransfersSystem::calcComplexPath(
		std::vector<Service *> services) {

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
			case 1: // reading Locals
				if (data.size() == 1) {
					locs.push_back(new Local(data[0]));
					locals.addVertex(locs.front());
					locals.getVertex(locs.front())->addEdge(
							locals.getVertex(locs.front()), 0);
				}
				break;
			case 2: // reading Distances
				if (data.size() == 3) {
					locals.getVertex(locs[atoi(data[0].c_str())])->addEdge(
							locals.getVertex(locs[atoi(data[1].c_str())]),
							(double) atoi(data[2].c_str()));
					locals.getVertex(locs[atoi(data[1].c_str())])->addEdge(
							locals.getVertex(locs[atoi(data[0].c_str())]),
							(double) atoi(data[2].c_str()));
				}
				break;
			case 3: // reading Services
				if (data.size() == 3) {
					services.push_back(
							*new Service(atoi(data[1].c_str()),
									atoi(data[2].c_str()),
									locs[atoi(data[0].c_str())]));
				}
				break;
			}

		}
		myfile.close();
	}
}
