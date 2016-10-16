#include"space.h"
#include"vessel.h"

//Initializes the location of the mines and the ship
void Space::initField(string fieldFileName){ 
	coordinates fieldSize = parseField(fieldFileName);
	shipLocation = findCenter(fieldSize.x, fieldSize.y);
}

//takes the filename of the field, locates the mines, and returns the size of the field
Space::coordinates Space::parseField(string fieldFileName){

	ifstream fieldFile;
	coordinates size; //size of the 2d field
	size.y = 0;
	mineCount = 0;
	string curLine;

	fieldFile.open(fieldFileName.c_str());
	while(!fieldFile.is_open()){
		cout << "ERROR: unable to locate file\nEnter Filename for field data: ";
		cin >> fieldFileName;
		fieldFile.open(fieldFileName.c_str());
	}

	while(std::getline(fieldFile, curLine)){
		for (unsigned int i  = 0; i < curLine.length(); i++){
			size.x = i;
			char c = curLine[size.x];
			if (c != '.'){
				int z = 0;
				if(isupper(c)){ //subtracts from the char to reach the represented z value
					z = c - 38;
				}
				else{
					z = c - 96;
				}
				coordinates mine;
				mine.x = size.x;
				mine.y = size.y;
				mine.z = z;
				mineList.push_back(mine);
				mineCount++;
			}

		}
		size.y++;
	}
	size.z = 0;
	return size;
}

//uses the max x and y size of the field to find the center
Space::coordinates Space::findCenter(int x, int y){
	coordinates center;
	center.x = x / 2;
	center.y = y / 2;
	center.z = 0;
	return center;
}

//draws the field's current state to the console
void Space::drawField(){
	int maxDifX = 0;
	int maxDifY = 0;

	for(unsigned int x = 0; x < mineList.size(); x++){ //finds how far the farthest mine is from the ship in the x and y direction
		if (abs(shipLocation.x - mineList[x].x) > maxDifX){
			maxDifX = abs(shipLocation.x - mineList[x].x);
		}
		if (abs(shipLocation.y - mineList[x].y) > maxDifY){
			maxDifY = abs(shipLocation.y - mineList[x].y);
		}
	}

	int xStart = shipLocation.x - maxDifX;
	int yStart = shipLocation.y - maxDifY;
	int xEnd = shipLocation.x + maxDifX;
	int yEnd = shipLocation.y + maxDifY;
	char bomb;
	bool isBomb; //flag for if the current x and y coordinates have a bomb

	for (int y = yStart; y <= yEnd; y++){
		for (int x = xStart; x <=xEnd; x++){
			isBomb = false;
			for (unsigned int b = 0; b < mineList.size(); b++){ //loop through all the mines
				if (x == mineList[b].x && y == mineList[b].y && mineList[b].z > shipLocation.z){

					if(mineList[b].z > 26){ //add to the int to reach the ASCII value of the representative letter.
						bomb = mineList[b].z + 38 - shipLocation.z;
					}
					else{
						bomb = mineList[b].z + 96 - shipLocation.z;
					}

					cout << bomb;
					isBomb = true;
				}
				else if(x == mineList[b].x && y == mineList[b].y && mineList[b].z <= shipLocation.z){
					cout << '*';
					isBomb = true;
				}
			}
			if (!isBomb && shipLocation.x == x && shipLocation.y == y){ //puts an '@' at the position of the ship as long as it doesn't overlap a bomb
				cout << '@';
			}
			else if(!isBomb){
				cout << '.';
			}
		}
		cout << endl;
	}
}

//returns true if the mineList is not Empty
bool Space::minesRemain(){
	return !mineList.empty();
}

//returns true if a mine has been passed by the ship in the z direction
bool Space::minesPassed(){
	bool passedMine = false;
	for(unsigned int x = 0; x < mineList.size(); x++){
		if (mineList[x].z <= shipLocation.z){
			passedMine = true;
		}
	}
	return passedMine;
}
