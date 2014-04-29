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
#include <limits.h>
TransfersSystem::TransfersSystem(unsigned stocking, unsigned overhead) :
		overhead(60), locals(), busStocking(stocking) {
}

unsigned TransfersSystem::absSoonerTime(Service * s) {
	return s->getArrivalTime() - locals.getBestTravelTime(s->getLocal())
			- overhead;
}

unsigned TransfersSystem::absLatterTime(Service * s) {
	return s->getArrivalTime() - locals.getBestTravelTime(s->getLocal());
}

void TransfersSystem::clearData() {
	locals.resetMap();
	services.clear();
	dropPeople = NULL;
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
		int min, int max, unsigned previousDist, Service * lastSrv,
		std::queue<Service *> & ret) {

	if (srvsLeft.size() == 0) // 1. if N is a goal state/node, return “success”
		return true;

	// 2. (optional) if N is a leaf state/node, return “failure”

	std::vector<Service *> clnServices(srvsLeft);
	Service * tmpSrv;
	int nMin, nMax, tmpDist;

	std::vector<Service *>::iterator it = clnServices.begin(); //3. for each successor/child C of N,
	for (; it != clnServices.end(); it++) {
		//3.1. (if appropriate) set new state
		tmpSrv = popService(srvsLeft, it);

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
			tmpDist = locals.getTravelTimeBetween(tmpSrv->getLocal(),
					lastSrv->getLocal());

			nMax = tmpSrv->getArrivalTime() - tmpDist - previousDist;
			nMin = absSoonerTime(tmpSrv);
			if (nMin <= nMax) {
				nMax = nMax < (max - tmpDist) ? nMax : (max - tmpDist);
				nMin = nMin > (min - tmpDist) ? nMin : (min - tmpDist);
				if (nMin <= nMax) { // Possible to explore
					if (calcSimplePathRecursive(srvsLeft, nMin, nMax,
							tmpDist + previousDist, tmpSrv, ret)) {
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
bool TransfersSystem::calcComplexPathRecursive(
		std::vector<Service *> & srvsLeft, int min, int max,
		unsigned previousDist, unsigned previousStck, Service * lastSrv,
		std::queue<Service *> & ret) {
	if (srvsLeft.size() == 0)  // 1. if N is a goal state/node, return “success”
		return true;

	// 2. (optional) if N is a leaf state/node, return “failure”

	std::vector<Service *> clnServices(srvsLeft);
	Service * tmpSrv;
	std::vector<Edge<Local> > edges;
	int nMin, nMax, tmpDist;

	for (std::vector<Service *>::iterator it = clnServices.begin(); //3. for each successor/child C of N,
	it != clnServices.end(); it++) {
		//3.1. (if appropriate) set new state
		tmpSrv = popService(srvsLeft, it);

		//3.2. explore state/node C
		//3.3. if exploration was successful, return “success”

		if (lastSrv == NULL) {
			tmpDist = locals.getBestTravelTime(tmpSrv->getLocal());
			if (calcComplexPathRecursive(srvsLeft, absSoonerTime(tmpSrv),
					absLatterTime(tmpSrv), tmpDist, tmpSrv->getPeopleQuantity(),
					tmpSrv, ret)) {
				ret.push(tmpSrv);
				return true;
			}
		} else {
			if (tmpSrv->getPeopleQuantity() + previousStck <= busStocking) {
				tmpDist = locals.getTravelTimeBetween(tmpSrv->getLocal(),
						lastSrv->getLocal());

				nMax = tmpSrv->getArrivalTime() - tmpDist - previousDist;
				nMin = absSoonerTime(tmpSrv);
				if (nMin <= nMax) {

					nMax = nMax < (max - tmpDist) ? nMax : (max - tmpDist);
					nMin = nMin > (min - tmpDist) ? nMin : (min - tmpDist);
					if (nMin <= nMax) { // Possible to explore
						if (calcComplexPathRecursive(srvsLeft, nMin, nMax,
								tmpDist + previousDist,
								tmpSrv->getPeopleQuantity() + previousStck,
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

	}
	// tries to drop people.
	if (lastSrv != NULL && !(*lastSrv == *dropPeople)) {
		tmpDist = locals.getBestTravelTime(lastSrv->getLocal());
		if (calcComplexPathRecursive(srvsLeft, -999999, max - tmpDist, 0,
				0, dropPeople, ret)) {
			ret.push(dropPeople);
			return true;
		}
	}

	//4. return “failure”
	return false;

}

bool TransfersSystem::calcComplexPath(std::vector<Service *> services,
		std::queue<Service *> & ret) {
	for (std::vector<Service *>::iterator it = services.begin();
			it != services.end(); it++) {
		if (busStocking < (*it)->getPeopleQuantity()) {
			return false;
		}
	}

	return calcComplexPathRecursive(services, 0, 0, 0, 0, NULL, ret);
}

bool TransfersSystem::addDataFromFile(std::string filename) {
	clearData();

	string line;
	std::vector<std::string> data;
	unsigned state = 0;
	ifstream myfile(filename.c_str());

	std::vector<Local *> locs;

	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			if (line.substr(0, 5) == "Local") {
				state = 1;
			} else if (line.substr(0, 8) == "Distance") {
				state = 2;

			} else if (line.substr(0, 7) == "Service") {
				state = 3;
			} else {
				data = TextUserInterface::strsplit(line, ";");

				switch (state) {
				case 1: // reading Locals
					if (data.size() == 1 && line != "") {
						locs.push_back(new Local(data[0]));
						locals.addVertex(locs[locs.size() - 1]);
						//cout << locs.size() << " | " << line << endl;
						locals.getVertex(locs[locs.size() - 1])->addEdge(
								locals.getVertex(locs[locs.size() - 1]), 0);
					} else {
						if (line != "") {
							locals.resetMap();
							return false;
						}
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
					} else {
						if (line != "") {
							locals.resetMap();
							return false;
						}
					}
					break;
				case 3: // reading Services
					if (data.size() == 3) {
						services.push_back(
								new Service(atoi(data[1].c_str()),
										atoi(data[2].c_str()),
										locs[atoi(data[0].c_str())]));
					} else {
						if (line != "") {
							locals.resetMap();
							return false;
						}
					}
					break;
				}

			}

		}
		myfile.close();
		dropPeople = new Service(0, 0, locals.getAirportLocal());

	} else {
		return false;
	}
}
