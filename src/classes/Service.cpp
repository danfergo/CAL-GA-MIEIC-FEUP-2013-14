/*
 * Service.cpp
 *
 *  Created on: 19/04/2014
 *      Author: Daniel
 */

#include "Service.h"

Service::Service(unsigned peopleQuantity, unsigned arrival, Local * local) {
	this->peopleQuantity = peopleQuantity;
	this->arrivalTime = arrival;
	this->local = local;
}

bool Service::operator==(const Service & s) const {
	return (local == s.local && peopleQuantity == s.peopleQuantity
			&& s.arrivalTime == arrivalTime);
}

unsigned Service::getPeopleQuantity() const {
	return peopleQuantity;
}

unsigned Service::getArrivalTime() const {
	return arrivalTime;
}
Local * Service::getLocal() const {
	return local;
}

