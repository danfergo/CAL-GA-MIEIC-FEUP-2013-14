/*
 * Local.h
 *
 *  Created on: 19/04/2014
 *      Author: Daniel
 */

#ifndef LOCAL_H_
#define LOCAL_H_

#include <string>

class Local {
private:
	std::string name;
public:
	Local(const Local& l);
	Local(std::string);

	std::string getName() const;
	void setName(std::string);
	bool operator==(const Local & loc) const;
};

#endif /* LOCAL_H_ */
