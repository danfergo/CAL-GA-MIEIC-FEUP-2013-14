/*
 * Service.cpp
 *
 *  Created on: 19/04/2014
 *      Author: Daniel
 */

#include "Service.h"

Service::Service(unsigned d, Local * l){
	setDropoff(d);
	local = l;
}


void Service::setDropoff(unsigned d){
	dropoff = d;
}

unsigned Service::getDropoff() const{
	return dropoff;
}
