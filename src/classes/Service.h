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
 * Classe Service. Representa um serviço prestado pela empresa. Um serviço é caraterizado por um local de recolha, uma tempo determinado para estar no aeroporto e uma quantidade de pessoas a transportar.
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
	 * Construtor da classe Serviço
	 * @param peopleQuantity quantidade de passageiros a transportar
	 * @param arrival tempo determinado para estar no aeroporto (numero de minutos desde as 0 horas)
	 * @param local Local de recolha dos passageiros
	 */
	Service(unsigned peopleQuantity, unsigned arrival, Local * local);
	/**
	 * Operador igual entre serviços.
	 * Verifica se dados dois serviços estes são iguais. Admite-se a não existenicia de serviços diferentes com o mesmo numero de passageiros, partindo do mesmo local, com o mesmo exato tempo determinado pra estar no aeroporto.
	 * @param service serviço a comparar com
	 * @return retorna verdadeiro caso os serviços representem o mesmo serviço, retorna falso caso contrário.
	 */
	bool operator==(const Service & service) const;
	/**
	 *  Esta função retorna o tempo determinado para estar no aeroporto (numero de minutos desde as 0 horas)
	 *  @return tempo determinado para estar no aeroporto (numero de minutos desde as 0 horas)
	 */
	unsigned getArrivalTime() const;
	/**
	 * Esta função retorna a quantidade de passageiros a transportar
	 * @return Quantidade de passageiros a transportar
	 */
	unsigned getPeopleQuantity() const;
	/**
	 * Esta função retorna um apontador para o local de recolha dos passageiros
	 * @return esta função retorna um apontador para o local de recolha dos passageiros
	 */
	Local * getLocal() const;
};

#endif /* SERVICE_H_ */
