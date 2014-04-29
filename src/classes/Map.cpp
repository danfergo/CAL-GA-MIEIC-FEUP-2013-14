/*
 * Map.cpp
 *
 *  Created on: 26/04/2014
 *      Author: Daniel
 */

#include "Map.h"

Map::Map(Local * airport) {
	this->addVertex(airport);
	this->airport = getVertex(airport);
}

unsigned Map::getBestTravelTime(Local *v) {
	unsigned i;
	for (i = 0; i < vertexSet.size(); i++) {
		if ((vertexSet[i]->getInfo()) == v) {
			break;
		};
	}

	if (i == vertexSet.size()) {
		return INT_MAX;
	}
	return this->edgeCost(i, 0);
}

unsigned Map::getTravelTimeBetween(Local * v1, Local * v2) {
	std::vector<Edge<Local*> > edges = getVertex(v1)->getAdj();

	for (std::vector<Edge<Local* > >::iterator itt = edges.begin();
			itt != edges.end(); itt++) {
		if ((*itt).getDest()->getInfo() == v2) {
			return (*itt).getWeight();
		}
	}
	return INT_MAX;
}

Local * Map::getAirportLocal(){
	return airport->getInfo();
}
