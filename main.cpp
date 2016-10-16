#include<string>
#include<iostream>
#include<fstream>
#include<list>

#include"space.h"
#include"vessel.h"

using namespace std;

int main(){
	int score;
	list<Vessel::command> script;
	string fieldFile;
	string scriptFile;

	Space *testSpace;
	Vessel* ship;

	testSpace = ship = new Vessel;

	cout << "Enter Filename for field data: ";
	cin >> fieldFile;
	testSpace->initField(fieldFile); //Initialize field

	cout << "Enter filename for script: ";
	cin >> scriptFile;
	script = ship->readScript(scriptFile);
	score = ship->runScript(script);

	cout << "results: ";
	if (score > 0){
		cout << "Pass ("<<score<<")\n";
	}
	else{
		cout << "Fail ("<<score<<")\n";
	}
	return 0;
}
