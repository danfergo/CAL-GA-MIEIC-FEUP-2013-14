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
 * As arestas deste mapa devem onter a distancia temporal mais curta (em minutos) entre os diversos locais.
 */
class Map : public Graph<Local*> {
public:
	/**
	 * Construtor da classe Mapa.
	 */
	Map();
	/**
	 * Esta fun��o retorna o tempo, pelo caminho mais curto, entre um determinado local e o aeroporto.
	 * @param local local a calcular distancia temporal (em minutos)
	 * @return distancia temporal (em minutos)
	 */
	unsigned getBestTravelTime(Local  *local);
	/**
	 * Esta fun��o calcula o tempo, pelo caminho mais curto, entre dois determinados determinados locais do mapa.
	 * @param local1 um dos locais
	 * @param local2 outro dos dois locais
	 * @return distancia temporal entre os dois locais (em minutos)
	 */
	unsigned getTravelTimeBetween(Local *local1, Local *local2);

	/**
	 * Esta fun��o retorna um apontador para o local do Aeroporto
	 * return apontador para aeroporto
	 */
	Local * getAirportLocal();

	/**
	 * Esta funcao elimina todos os vertex do mapa
	 */
	void resetMap();
	/**
	 * Esta funcao retorna verdadeiro se o mapa contiver locais, retorna falso caso contr�rio.
	 */
	bool isEmpty();
};

#endif /* MAP_H_ */
