/*
 * FileCSV.cpp
 *
 *  Created on: 21/04/2014
 *      Author: Daniel
 */

#include "FileCSV.h"

#include <fstream>


IFileCSV::IFileCSV(std::string filename) {
	std::ifstream ifile;

	if (ifile.is_open()) {
		std::string datastring = "", line;

		while (getline(ifile, line)) {
			datastring += line + '\n';
		}

		ifile.close();

		bool textstring = false;
		int startPtr = 0, endPtr = startPtr+1;

	//	std::vector<std::string> * tempLineVec = &data.push_back(*(new std::vector<std::string>()));

	/*	if(textstring[startPtr] == '"' ){
			textstring = true;
			startPtr++;endPtr++;
		}

		while(true){
			if(textstring[startPtr] == '"' ){

			}
			endPtr++;
		}
*/
	}
	// throw FileNotAvailableExeption();
}

std::vector<std::vector<std::string> > IFileCSV::getData() {
	return data;
}
