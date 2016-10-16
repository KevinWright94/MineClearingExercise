/*
 * vessel.h
 *
 *  Created on: Oct 14, 2016
 *      Author: Kevin Wright
 */

#ifndef VESSEL_H_
#define VESSEL_H_
#include"space.h"
#include<list>

class Vessel : public Space{
public:
	enum command{
		north, south, east, west, fall, alpha, beta, gamma, delta, none
	};
	list<command> readScript(string);
	int runScript(list<command>);
private:
	void firePattern(command);
	void fire(coordinates);
	void move(command);
	string cmdToStr(command);
	command parseString(string);
};
#endif /* VESSEL_H_ */
