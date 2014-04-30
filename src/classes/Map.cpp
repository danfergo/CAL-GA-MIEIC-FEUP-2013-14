/*
 * Map.cpp
 *
 *  Created on: 26/04/2014
 *      Author: Daniel
 */

#include "Map.h"

Map::Map() {
}

unsigned Map::getBestTravelTime(Local *v) const{
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

unsigned Map::getTravelTimeBetween(Local * v1, Local * v2) const {
	std::vector<Edge<Local*> > edges = getVertex(v1)->getAdj();

	for (std::vector<Edge<Local* > >::iterator itt = edges.begin();
			itt != edges.end(); itt++) {
		if ((*itt).getDest()->getInfo() == v2) {
			return (*itt).getWeight();
		}

	}
	return INT_MAX;
}

Local * Map::getAirportLocal() const{
	if(vertexSet.size() == 0)
		return NULL;
	return this->vertexSet[0]->getInfo();
}

void Map::resetMap(){
	vertexSet.clear();
}


bool Map::isEmpty(){
	return vertexSet.size() == 0;
}

