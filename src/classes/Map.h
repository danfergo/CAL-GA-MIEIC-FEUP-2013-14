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


/**
 * Classe Mapa.
 * Representa o mapa de locais segundo um Grafo.
 */
class Map : public Graph<Local*> {
	/**
	 * Vertice do grafo correspondente ao aeroporto.
	 * As arestas deste mapa devem onter a distancia temporal mais curta (em minutos) entre os diversos locais.
	 */
	Vertex<Local*> * airport;
public:
	/**
	 * Construtor da classe Mapa.
	 * @param airport local do aeroporto (num caso mais abragente, local de entrega de passageiros).
	 */
	Map(Local * airport);
	/**
	 * Esta função retorna o tempo, pelo caminho mais curto, entre um determinado local e o aeroporto.
	 * @param local local a calcular distancia temporal (em minutos)
	 * @return distancia temporal (em minutos)
	 */
	unsigned getBestTravelTime(Local  *local);
	/**
	 * Esta função calcula o tempo, pelo caminho mais curto, entre dois determinados determinados locais do mapa.
	 * @param local1 um dos locais
	 * @param local2 outro dos dois locais
	 * @return distancia temporal entre os dois locais (em minutos)
	 */
	unsigned getTravelTimeBetween(Local *local1, Local *local2);

	/**
	 * Esta função retorna um apontador para o local do Aeroporto
	 * return apontador para aeroporto
	 */
	Local * getAirportLocal();
};

#endif /* MAP_H_ */
