/*
 * Bus.cpp
 *
 *  Created on: 19/04/2014
 *      Author: Daniel
 */

#include "Bus.h"

Bus::Bus(unsigned s){
	 setStocking(s);
}

Bus::Bus(std::string r,unsigned s){
	setRegistration(r);
	setStocking(s);
}

void Bus::setRegistration(std::string r){
	registration = r;
}
void Bus::setStocking(unsigned s){
	 stocking = s;
}

std::string Bus::getRegistration() const{
	return registration;
}
unsigned Bus::getStocking() const{
	return stocking;
}


