/*
 * IFCSV.h
 *
 *  Created on: Apr 20, 2014
 *      Author: Daniel Gomes
 */

#ifndef IFCSV_H_
#define IFCSV_H_

#include <string>
#include <vector>

class IFCSV {
private:
	std::vector< std::vector<std::string> >  * data;
public:
	IFCSV(std::string loc);
	std::vector< std::vector<std::string> > * read(std::string loc);
	virtual ~IFCSV();
};

#endif /* IFCSV_H_ */
