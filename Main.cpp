#include "Game.h"
#include "GameObject.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string writeFile(string user)
{
	//This is BROKEN
	int num = PLAYER1_SCORE;
	char name[] = "Brian Ryan";

	//This way WILL WORK
	int num1 = 2500;
	char name1[] = "Joe Bloggs";

	ofstream myfile;
	myfile.open("example.txt");

	myfile << "Player One Name: " << name << "\n";
	myfile << "Player One Score: " << num << "\n";

	myfile << "Player Two Name: " << name1 << "\n";
	myfile << "Player Two Score: " << num1 << "\n";

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

//int main() {
int main(int argv, char** argc) {

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


