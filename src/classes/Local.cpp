/*
 * Local.cpp
 *
 *  Created on: 19/04/2014
 *      Author: Daniel
 */

#include "Local.h"

Local::Local(std::string s){
	setName(s);
}

std::string Local::getName() const{
	return name;
}
void Local::setName(std::string n){
	name = n;
}


bool Local::operator==(const Local & loc) const{
	return getName() == loc.getName();
}
