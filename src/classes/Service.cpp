/*
 * Service.cpp
 *
 *  Created on: 19/04/2014
 *      Author: Daniel
 */

#include "Service.h"

Service::Service(unsigned peopleQuantity, unsigned arrival, Local * local, Map * map){
	this->peopleQuantity = peopleQuantity;
	this->arrivalTime = arrival;
	this->local = local;

	this->laterTime = this->arrivalTime - map->getBestTravelTime(*local);
	this->soonerTime = laterTime - 60;
}

bool Service::operator==(const Service & s) const{
	return (local == s.local && peopleQuantity == s.peopleQuantity && s.arrivalTime == arrivalTime);
}

unsigned Service::getSoonerTime() const{
	return soonerTime;
}
unsigned Service::getLaterTime() const{
	return laterTime;
}

unsigned Service::getPeopleQuantity() const{
	return peopleQuantity;
}

unsigned Service::getArrivalTime() const{
	return arrivalTime;
}
Local * Service::getLocal() const{
	return local;
}


