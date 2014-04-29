/*
 * Service.h
 *
 *  Created on: 19/04/2014
 *      Author: Daniel
 */

#ifndef SERVICE_H_
#define SERVICE_H_

#include "Local.h"
#include "Map.h"

/**
 * Classe Service. Representa um servi�o prestado pela empresa. Um servi�o � caraterizado por um local de recolha, uma tempo determinado para estar no aeroporto e uma quantidade de pessoas a transportar.
 */
class Service {
private:
	/**
	 * tempo determinado para estar no aeroporto (numero de minutos desde as 0 horas)
	 */
	unsigned arrivalTime;
	/**
	 * Local de recolha dos passageiros
	 */
	Local * local;
	/**
	 * Quantidade de passageiros a transportar
	 */
	unsigned peopleQuantity;
public:
	/**
	 * Construtor da classe Servi�o
	 * @param peopleQuantity quantidade de passageiros a transportar
	 * @param arrival tempo determinado para estar no aeroporto (numero de minutos desde as 0 horas)
	 * @param local Local de recolha dos passageiros
	 */
	Service(unsigned peopleQuantity, unsigned arrival, Local * local);
	/**
	 * Operador igual entre servi�os.
	 * Verifica se dados dois servi�os estes s�o iguais. Admite-se a n�o existenicia de servi�os diferentes com o mesmo numero de passageiros, partindo do mesmo local, com o mesmo exato tempo determinado pra estar no aeroporto.
	 * @param service servi�o a comparar com
	 * @return retorna verdadeiro caso os servi�os representem o mesmo servi�o, retorna falso caso contr�rio.
	 */
	bool operator==(const Service & service) const;
	/**
	 *  Esta fun��o retorna o tempo determinado para estar no aeroporto (numero de minutos desde as 0 horas)
	 *  @return tempo determinado para estar no aeroporto (numero de minutos desde as 0 horas)
	 */
	unsigned getArrivalTime() const;
	/**
	 * Esta fun��o retorna a quantidade de passageiros a transportar
	 * @return Quantidade de passageiros a transportar
	 */
	unsigned getPeopleQuantity() const;
	/**
	 * Esta fun��o retorna um apontador para o local de recolha dos passageiros
	 * @return esta fun��o retorna um apontador para o local de recolha dos passageiros
	 */
	Local * getLocal() const;
};

#endif /* SERVICE_H_ */
