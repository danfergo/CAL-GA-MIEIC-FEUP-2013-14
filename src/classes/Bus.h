/*
 * Bus.h
 *
 *  Created on: 19/04/2014
 *      Author: Daniel
 */

#ifndef BUS_H_
#define BUS_H_

#include <string>

class Bus {
private:
	unsigned stocking;
	std::string registration;
public:
	Bus(unsigned);
	Bus(std::string,unsigned);

	void setRegistration(std::string);
	void setStocking(unsigned);

	std::string getRegistration() const;
	unsigned getStocking() const;
};

#endif /* BUS_H_ */
