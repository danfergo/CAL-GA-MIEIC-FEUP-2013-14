/*
 * IFCSV.cpp
 *
 *  Created on: Apr 20, 2014
 *      Author: Daniel Gomes
 */

#include "IFCSV.h"

#include <iostream>
#include <fstream>

IFCSV::IFCSV(std::string loc) {
	read(loc);
}

std::vector< std::vector<std::string> > * IFCSV::read(std::string loc){
	delete(data);


}

IFCSV::~IFCSV() {
	delete(data);
}

