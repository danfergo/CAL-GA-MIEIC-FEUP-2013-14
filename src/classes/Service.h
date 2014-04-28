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
	unsigned soonerTime;
	unsigned laterTime;

	unsigned arrivalTime;
	Local * local;
	unsigned peopleQuantity;
public:
	Service(unsigned peopleQuantity, unsigned arrival, Local * local, Map * map);
	bool operator==(const Service & s) const;

	unsigned getSoonerTime() const;
	unsigned getLaterTime() const;
	unsigned getArrivalTime() const;

	unsigned getPeopleQuantity() const;
	Local * getLocal() const;
};

#endif /* SERVICE_H_ */
