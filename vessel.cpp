#include"vessel.h"
#include"space.h"

//takes a command and moves the ship accordingly
void Vessel::move(command move){
	switch (move){
	case north:
		shipLocation.y--;
		break;
	case south:
		shipLocation.y++;
		break;
	case east:
		shipLocation.x++;
		break;
	case west:
		shipLocation.x--;
		break;
	case fall:
		shipLocation.z++;
		break;
	default:
		cout << "COMMAND : " << move <<" NOT A RECOGNIZED MOVEMENT.\n";
		break;
	}
}

//takes a fire command and fires at the intended locations
void Vessel::firePattern(command fireP){
	coordinates fireLocation;
	switch(fireP){
	case alpha: //'x' shape
		fireLocation.x = shipLocation.x-1;
		fireLocation.y = shipLocation.y-1;
		fireLocation.z = shipLocation.z;
		fire(fireLocation);

		fireLocation.x = shipLocation.x-1;
		fireLocation.y = shipLocation.y+1;
		fire(fireLocation);

		fireLocation.x = shipLocation.x+1;
		fireLocation.y = shipLocation.y-1;
		fire(fireLocation);

		fireLocation.x = shipLocation.x+1;
		fireLocation.y = shipLocation.y+1;
		fire(fireLocation);
		break;

	case beta: //'+' shape
		fireLocation.x = shipLocation.x-1;
		fireLocation.y = shipLocation.y;
		fireLocation.z = shipLocation.z;
		fire(fireLocation);

		fireLocation.x = shipLocation.x;
		fireLocation.y = shipLocation.y-1;
		fire(fireLocation);

		fireLocation.x = shipLocation.x;
		fireLocation.y = shipLocation.y+1;
		fire(fireLocation);

		fireLocation.x = shipLocation.x+1;
		fireLocation.y = shipLocation.y;
		fire(fireLocation);
		break;

	case gamma://'-' shape
		fireLocation.x = shipLocation.x-1;
		fireLocation.y = shipLocation.y;
		fireLocation.z = shipLocation.z;
		fire(fireLocation);

		fireLocation.x = shipLocation.x;
		fireLocation.y = shipLocation.y;
		fire(fireLocation);

		fireLocation.x = shipLocation.x+1;
		fireLocation.y = shipLocation.y;
		fire(fireLocation);
		break;

	case delta: //'|' shape
		fireLocation.x = shipLocation.x;
		fireLocation.y = shipLocation.y-1;
		fireLocation.z = shipLocation.z;
		fire(fireLocation);

		fireLocation.x = shipLocation.x;
		fireLocation.y = shipLocation.y;
		fire(fireLocation);

		fireLocation.x = shipLocation.x;
		fireLocation.y = shipLocation.y+1;
		fire(fireLocation);
		break;
	default:
		cout << "COMMAND : " << fireP <<" NOT A RECOGNIZED FIRE PATTERN.\n";
		break;
	}
}

//fires at a specific coordinates
void Vessel::fire(coordinates fireLocation){
	for(unsigned int g = 0; g < mineList.size(); g++){
		if (fireLocation.x == mineList[g].x && fireLocation.y == mineList[g].y && fireLocation.z < mineList[g].z){
			mineList.erase(mineList.begin()+g);
		}
	}
}

//reads the script from filename provided as string and turns it into a list of commands
//the vessel's 'falling' in the z axis is declared as commands in this function
list<Vessel::command> Vessel::readScript (string scriptFileName){
	list<command> cmdList; //for storing the commands
	string readLine;
	bool hasFired = false; //flags to ensure only one of each type of command per line of script
	bool hasMoved = false;
	command curCommand;

	ifstream scriptFile;
	scriptFile.open(scriptFileName.c_str());

	if (!scriptFile.is_open()){ //loop to insure file is opened
		cout << "ERROR: unable to locate file\nEnter Filename for script: ";
		cin >> scriptFileName;
		scriptFile.open(scriptFileName.c_str());
	}

	while (std::getline(scriptFile, readLine)){
		unsigned int v = 0; //count to read from file 1 char at a time
		string commandStr = "";

		while(v != readLine.length()){
			if(readLine[v] != ' '){
				commandStr += readLine[v];
			}
			else{ //at the end of the first command in a 2 command line
				curCommand = parseString(commandStr);
				if(curCommand < 4){ //if current command is a move command
					cmdList.push_back(curCommand);
					commandStr = "";
					hasMoved = true;
				}
				else if (curCommand >=4){ //if the current command is a fire command
					cmdList.push_back(curCommand);
					commandStr = "";
					hasFired = true;
				}
			}
			v++;
		}
		curCommand = parseString(commandStr);
		if(curCommand < 4 && hasMoved == true) //if current command is a move command and the ship has already moved this line
			cmdList.push_back(fall);
		else if(curCommand >= 4 && hasFired == true)
			cmdList.push_back(fall);

		cmdList.push_back(curCommand);
		cmdList.push_back(fall);
		hasMoved = false;
		hasFired = false;

	}
	return cmdList;
}

//returns the matching command to the string input
Vessel::command Vessel::parseString(string curCommand){
		if(curCommand.compare("north") == 0){
			return north;
		}
		else if(curCommand.compare("south") == 0){
			return south;
		}
		else if(curCommand.compare("east") == 0){
			return east;
		}
		else if(curCommand.compare("west") == 0){
			return west;
		}
		else if(curCommand.compare("alpha") == 0){
			return alpha;
		}
		else if(curCommand.compare("beta") == 0){
			return beta;
		}
		else if(curCommand.compare("gamma") == 0){
			return gamma;
		}
		else if(curCommand.compare("delta") == 0){
			return delta;
		}
		else if(curCommand.compare("fall") == 0){
			return fall;
		}
		else{
			cout <<"UNKNOWN COMMAND "<< curCommand << endl;
			return none;
		}
}

// covert an enumerated command into a string for output
string Vessel::cmdToStr(command cmd){
	string str;
	switch(cmd){
	case north:
		str = "north";
		break;
	case south:
		str = "south";
		break;
	case east:
		str = "east";
		break;
	case west:
		str = "west";
		break;
	case fall:
		str = "fall";
		break;
	case alpha:
		str = "alpha";
		break;
	case beta:
		str = "beta";
		break;
	case gamma:
		str = "gamma";
		break;
	case delta:
		str = "delta";
		break;
	default:
		str = "unknown Command";
		break;
	}
	return str;
}

//runs the script from a list of commands and returns the score
int Vessel::runScript(list<command> commands){
	command curCommand;

	int stepCount = 0;
	int score = mineCount * 10;
	int lossMove = 0;
	int lossFire = 0;

	while(!commands.empty() && minesRemain()){
			if(minesPassed()){ //fail state for passing a mine
				score = 0;
				return score;
			}
			stepCount++;
			curCommand = commands.front();
			commands.pop_front();

			cout << "Step " << stepCount << endl;
			drawField();
			cout << endl;
			while(curCommand != fall){
				if (curCommand < 4){//a value of < 4 represents 'north' 'south' 'west' or 'east'
					cout << cmdToStr(curCommand)<< " ";
					move(curCommand);
					lossMove+=2;
					if(lossMove <= (mineCount * 3) && score > 0) //ensures the max points for movement have not been lost
						score -=2;
				}
				else{ //if not a direction or fall, its a fire command
					cout << cmdToStr(curCommand)<< " ";
					firePattern(curCommand);
					lossFire+=5;
					if(lossFire <= (mineCount*5) && score > 0)
						score-=5;
				}
				curCommand = commands.front();
				commands.pop_front();
			}
			cout << endl << endl;
			move(curCommand);
			drawField();
			cout << endl;
			if (commands.empty() && minesRemain()){//fail state for script ending early
				score = 0;
				return score;
			}
		}

	if(!commands.empty()){ //check for remaining script
		score = 1;
	}
	return score;
}
