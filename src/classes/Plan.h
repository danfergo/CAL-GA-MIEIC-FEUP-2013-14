/*
 * Plan.h
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



class Plan {
private:
	Graph<Local> locals;
	std::vector<Service> services;
	std::vector<Bus> buses;

public:
	Plan();
	bool addData();
	void clearData();

	bool calcSimplePath(Bus * bus, std::vector<Service *> services);
	bool calcComplexPath(Bus * bus, std::vector<Service *> services);
	bool planTransfers();
};

#endif /* PLAN_H_ */
