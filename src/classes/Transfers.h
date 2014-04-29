/*
 * Transfers.h
 *
 *  Created on: 28/04/2014
 *      Author: Daniel
 */

#ifndef TRANSFERS_H_
#define TRANSFERS_H_

#include <string>
#include <vector>
#include "Map.h"
#include "Service.h"

namespace Transfers {

unsigned busStocking = 30;
unsigned overhead = 60;

Map locals();
std::vector<Service> services;
Service * dropPeople;

bool calcSimplePathRecursive(std::vector<Service *> & services2plane,
		unsigned min, unsigned max, unsigned dist, Service * current,
		std::queue<Service *> & ret);
bool calcComplexPathRecursive(std::vector<Service *> & services2plane,
		unsigned min, unsigned max, unsigned dist, unsigned stocking,
		Service * current, std::queue<Service *> & ret);

bool insertDataFromFile(std::string filename);

bool calcSimplePath(std::vector<Service *> services2plan,
		std::queue<Service *> & ret);

std::vector<std::vector<Service *> > calcComplexPath(
		std::vector<Service *> services);

std::vector<std::vector<std::vector<Service *> > > planTransfers();

} /* namespace Transfers */

#endif /* TRANSFERS_H_ */
