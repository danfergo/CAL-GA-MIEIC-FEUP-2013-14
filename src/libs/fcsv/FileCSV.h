/*
 * FileCSV.h
 *
 *  Created on: 21/04/2014
 *      Author: Daniel
 */

#ifndef FILECSV_H_
#define FILECSV_H_

#include <vector>
#include <string>

class IFileCSV {
private:
	std::vector<std::vector<std::string> > data;
public:
	IFileCSV(std::string filename);
	std::vector<std::vector<std::string> > getData();
};

#endif /* FILECSV_H_ */
