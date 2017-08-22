#include "Game.h"
//#include "GameObject.h"// This breaks code
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string writeFile(string user) 
{

	char name[] = "Joe KKK Bloggs";
	int num = 2500;
	

	ofstream myfile;
	myfile.open("example.txt");

	myfile << "Player Two Name: " << name << "\n";
	myfile << "Player Two Score: " << num << "\n";

	myfile << flush;
	myfile.close();

	return string();
}

string readFile(string line)
{
	ifstream a_file("example.txt");

	if (a_file.is_open())
	{
		while (getline(a_file, line))
		{
			cout << line << '\n';
		}
		a_file.close();
	}
	else cout << "Unable to open file";

	return string();
}

int main() {

	string user;
	writeFile(user);

	string line;
	readFile(line);

	srand(static_cast<unsigned int>(time(0)));	//Seed the random number

	Game game;				//Create a game object

	game.update();

	game.close();			//Free resources and close SDL*/

	system("pause");

	return 0;
}


