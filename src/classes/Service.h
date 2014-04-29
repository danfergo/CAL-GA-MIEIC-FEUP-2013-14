/*
 * Service.h
 *
 *  Created on: 19/04/2014
 *      Author: Daniel
 */

#ifndef SERVICE_H_
#define SERVICE_H_

#include "Local.h"
#include "Map.h"

class Service {
private:
	unsigned arrivalTime;
	Local * local;
	unsigned peopleQuantity;
public:
	Service(unsigned peopleQuantity, unsigned arrival, Local * local);
	bool operator==(const Service & s) const;

	unsigned getArrivalTime() const;
	unsigned getPeopleQuantity() const;
	Local * getLocal() const;
};

#endif /* SERVICE_H_ */
