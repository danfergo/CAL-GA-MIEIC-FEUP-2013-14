/*
 * TransfersSystem.h
 *
 *  Created on: 21/04/2014
 *      Author: Daniel
 */

#ifndef PLAN_H_
#define PLAN_H_

#include <vector>
#include "Map.h"
#include "Service.h"
#include "Local.h"
#include <queue>

static const unsigned busStocking = 30;
static const unsigned overhead = 60;

class TransfersSystem {
private:
	unsigned overhead;
	Map locals;
	unsigned busStocking;
	std::vector<Service> services;
	Service * dropPeople;
	bool calcSimplePathRecursive(std::vector<Service *> & services2plane, unsigned min, unsigned max, unsigned dist ,Service * current,
			std::queue<Service *> & ret);
	bool calcComplexPathRecursive(std::vector<Service *> & services2plane, unsigned min, unsigned max, unsigned dist , unsigned stocking, Service * current,
				std::queue<Service *> & ret);

public:
	TransfersSystem(Map map,unsigned busStocking);
	bool addDataFromFile(std::string filename);
	void clearData();
	bool calcSimplePath(std::vector<Service *> services2plan,
			std::queue<Service *> & ret);


	std::vector<std::vector<Service *> > calcComplexPath(
			std::vector<Service *> services);
	std::vector<std::vector<std::vector<Service *> > > planTransfers();
};

#endif /* PLAN_H_ */
