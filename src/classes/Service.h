/*
 * Service.h
 *
 *  Created on: 19/04/2014
 *      Author: Daniel
 */

#ifndef SERVICE_H_
#define SERVICE_H_

#include "Local.h"

class Service {
private:
	unsigned dropoff;
public:
	Local * local;
	unsigned qtdPessoas;

	Service(unsigned, Local *);

	unsigned getDropoff() const;
	void setDropoff(unsigned);
};

#endif /* SERVICE_H_ */
