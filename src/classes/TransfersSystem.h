/*
 * TransfersSystem.h
 *
 *  Created on: 21/04/2014
 *      Author: Daniel
 */

#ifndef PLAN_H_
#define PLAN_H_

#include <vector>
#include "../libs/Graph.h"
#include "Service.h"
#include "Local.h"
#include "Bus.h"
#include <stack>

static const unsigned busStocking = 30;
static const unsigned overhead = 60;

class TransfersSystem {
private:
	Graph<Local> locals;
	std::vector<Service> services;

public:
	TransfersSystem();
	bool addDataFromFile(std::string filename);
	void clearData();
	bool calcSimplePath(std::vector<Service *> & services2plane, std::stack<Service *> & ret);
	std::vector<std::vector<Service *> > calcComplexPath(std::vector<Service *> services);
	std::vector< std::vector< std::vector<Service *> > > planTransfers();
};

#endif /* PLAN_H_ */
