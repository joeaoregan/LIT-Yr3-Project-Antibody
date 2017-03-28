/*	-----------------------------------------------------------------------------------------------------------------------------------------------------
		- Name:					randomMessageGenerator.h
		- Description:			Generates random messages from lists of messages for certain situations
		- Information:			Generate messages for a new level, blockages, a boss spawning, or the player spawning

		- Log:

			2017/03/04			Added function to display a random message at the start of each level
								Added function to display a random spawning message for blockages
								Added function to display a random spawning message for Boss Enemies
								Added function to display a random spawning message for Player Ships
------------------------------------------------------------------------------------------------------------------------------------------------------- */
#ifndef RANDOM_MESSAGE_H
#define RANDOM_MESSAGE_H

#include <string>

// 2017/03/04 Display a random message at the start of each level
std::string randomLevelMessageGenerator(int currentLevel) {
	std::string randomText;

	if (currentLevel == 1 ) {
		int randomMessage = rand() % 6;
		if (randomMessage == 0) randomText = "Looks like we are starting at the start ...Level 1.";
		else if (randomMessage == 1) randomText = "I'm going to call this 'Level 1' ...try and get through 3 of these";
		else if (randomMessage == 2) randomText = "This is the start, keep going until the finish ...obviously";
		else if (randomMessage == 3) randomText = "You have picked a great place to begin ...the beginning";
		else if (randomMessage == 4) randomText = "We are off to a good start ...I've no idea where this is!!";
		else if (randomMessage == 5) randomText = "Welcome to Level 1. The bad guys are this way >>>";
	}
	else if (currentLevel == 2) {
		int randomMessage = rand() % 7;
		if (randomMessage == 0) randomText = "You made it to level 2, get ready for another level of disappoinment";
		else if (randomMessage == 1) randomText = "I'm going to call this 'Level 2', because it's clearly the 2nd level";
		else if (randomMessage == 2) randomText = "Nearly there, you still have one more level after this one ...Yay!";
		else if (randomMessage == 3) randomText = "Level 2: Introducing more of the same stuff, scrolling right to left";
		else if (randomMessage == 4) randomText = "I still don't know where I am. Is there such thing as vein sign posts?";
		else if (randomMessage == 5) randomText = "Now Playing 'Level 2'. More bad guys are this way >>>";
		else if (randomMessage == 6) randomText = "Level 2: Are we there yet??? ...no, 1 more to go";
	}
	else if (currentLevel == 3) {
		int randomMessage = rand() % 7;
		if (randomMessage == 0) randomText = "You made it to level 3, yes, we are there yet";
		else if (randomMessage == 1) randomText = "I'm going to call this 'Level 3', the third in a disappointing trilogy";
		else if (randomMessage == 2) randomText = "Level 3: Nearly there! When you're done you get a big prize of nothing";
		else if (randomMessage == 3) randomText = "Level 3: Even more of the same stuff, moving in the same direction";
		else if (randomMessage == 4) randomText = "Third Level: I mightn't know where I am, but I know I'm close";
		else if (randomMessage == 5) randomText = "Predictabley, even More bad guys are this way >>>";
		else if (randomMessage == 6) randomText = "Third Level (ha ha, you said turd!)";
	}

	return randomText;
}

// 2017-03-04 Display a random spawning message for blockages
std::string randomBlockageMessage() {
	std::string randomText;

	int randomMessage = rand() % 5;

	if (randomMessage == 0) randomText = "Something appears to be blocking the way ahead!!";
	else if (randomMessage == 1) randomText = "It looks like we are going to have to cut our way through here";
	else if (randomMessage == 2) randomText = "Looks like we will have to find a way past this!!";
	else if (randomMessage == 3) randomText = "Something big and yellow is coming. Giant Custard?";
	else if (randomMessage == 4) randomText = "I should have brought my Sword. Gonna have to hack my way through!";

	return randomText;
}

// 2017/03/04 Display a random spawning message for boss enemies
std::string randomBossMessage() {
	std::string randomText;

	int randomMessage = rand() % 6;

	if (randomMessage == 0) randomText = "It looks like theres something big coming";
	else if (randomMessage == 1) randomText = "Is it a bird? Is it a plane? ...Eh no, a giant beard?";
	else if (randomMessage == 2) randomText = "A Head? Seems to be all kinds of crap coming our way";
	else if (randomMessage == 3) randomText = "Look at the big flappy mouth on this lad!!!";
	else if (randomMessage == 4) randomText = "I can see right up this guys nose!!!";
	else if (randomMessage == 5) randomText = "Looks its a Boss Enemy approaching ...Points for originality!!";

	return randomText;
}

// 2017/03/04 Display a random spawning message for Player Ships
std::string randomPlayerMessage(int player) {
	std::string randomText;

	int randomMessage = rand() % 6;

	if (randomMessage == 0) randomText = "Spawning ...that's gotta hurt!";
	else if (randomMessage == 1) randomText = "If you just avoid the bad guys, you won't have to spawn again!";
	else if (randomMessage == 2) randomText = "Normally spawning is only for straight after you did dumb things";
	else if (randomMessage == 3) randomText = "Looks like we have a spawner";
	else if (randomMessage == 4) randomText = "Player " + std::to_string(1) + " has just spawned";
	else if (randomMessage == 5) randomText = "Looks like player spawning ...originality at its best!!";

	return randomText;
}
#endif