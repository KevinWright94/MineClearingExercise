/*
 * space.h
 * Created on: Oct 14, 2016
 * Author: Kevin Wright
 */
#ifndef SPACE_H_
#define SPACE_H_
#include<string>
#include<fstream>
#include<cmath>
#include<vector>
#include<iostream>

using namespace std;

/*
 * Stores the locations for all the mines and the vessel.
 * handles the reading / writing of 2d representations of the field
 */
class Space{
public:
	struct coordinates{
		int x;
		int y;
		int z;
	};
	void initField(string);
protected:
	vector<coordinates> mineList;
	int mineCount;
	coordinates shipLocation;
	bool minesRemain();
	bool minesPassed();
	void drawField();
private:
	coordinates parseField(string);
	coordinates findCenter(int, int);
};

#endif /* SPACE_H_ */
