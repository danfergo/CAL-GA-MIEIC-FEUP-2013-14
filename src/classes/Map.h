/*
 * Map.h
 *
 *  Created on: 26/04/2014
 *      Author: Daniel
 */

#ifndef MAP_H_
#define MAP_H_

#include "Local.h"
#include "../libs/Graph.h"

class Map : public Graph<Local*> {
	Vertex<Local*> * airport;
public:
	Map(Local * airport);
	unsigned getBestTravelTime(Local  *v);
	unsigned getTravelTimeBetween(Local *v, Local *v2);
	Local * getAirportLocal();


};

#endif /* MAP_H_ */
