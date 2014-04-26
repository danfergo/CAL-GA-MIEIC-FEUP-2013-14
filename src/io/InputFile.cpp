/*
 * InputFile.cpp
 *
 *  Created on: Apr 19, 2014
 *      Author: Daniel Gomes
 */

#include "InputFile.h"

#include <string>
using namespace std;


bool inputTransferesDataFile(){


	  string buffer, line;
	  ifstream myfile ("C:\\Users\\Tiago Gomes\\workspace\\Transferes\\Debug\\DataFile.csv");
	  buffer = "";
	  if (myfile.is_open())
	  {
	    while ( getline (myfile,line) )
	    {
	    	buffer += line + '\n';
	    }
	    myfile.close();
	  }
	  else cout << "Unable to open file";


	  cout << buffer;


	return true;
}
