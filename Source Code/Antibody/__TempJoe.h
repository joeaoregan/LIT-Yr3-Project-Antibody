// One collision check for both players

/*

void Game::collisionCheck() {
// 2017/03/22 Reduce code for collision checks with players on Game Object list
int numPlayers;					// Number of players to loop for
if (twoPlayer) numPlayers = 2;
else numPlayers = 1;


for (int PLAYER = 0; PLAYER < numPlayers; numPlayers++) {
	// Check if Player 1 or 2 has collided with another game object
	for (int index = 0; index != listOfGameObjects.size(); ++index) {
		if (checkCollision(&listOfGameObjects[PLAYER]->getCollider(), &listOfGameObjects[index]->getCollider()) == true) {

			listOfGameObjects[PLAYER]->setScore(listOfGameObjects[PLAYER]->getScore() + listOfGameObjects[index]->getScore());

			// If the players saw is active
			if (listOfGameObjects[PLAYER]->getSawActive()) {
				if (listOfGameObjects[index]->getSubType() == LARGE_BLOOD_CELL) listOfGameObjects[index]->setAlive(false);	// If the players saw is active and it collides with a large blood cell, the blood cell is destroyed
				if (listOfGameObjects[index]->getSubType() == BLOCKAGE) listOfGameObjects[index]->setAlive(false);
			}

			//if (listOfGameObjects[index]->getSubType() == BLOCKAGE) player1->setVelX(player1->getVelX() - player1->getVelX() -BACKGROUND_SCROLL_SPEED);
			if (listOfGameObjects[index]->getSubType() == BLOCKAGE) {
				listOfGameObjects[PLAYER]->setX((listOfGameObjects[PLAYER]->getX() + listOfGameObjects[index]->getVelX()) - listOfGameObjects[PLAYER]->getVelX());

				if (listOfGameObjects[PLAYER]->getSubType() == PLAYER1) player1->moveLeft(true);
				else if (listOfGameObjects[PLAYER]->getSubType() == PLAYER2) player2->moveLeft(true);
			}

			// Power Ups
			if (listOfGameObjects[index]->getType() == POWER_UP) {
				if (listOfGameObjects[index]->getSubType() == POWER_UP_HEALTH) {
					managePlayerHealth(PLAYER_1, -listOfGameObjects[index]->getDamage());
					infoMessage("Player 1 has increased their health!!!", PLAYER_1);
				}
				else if (listOfGameObjects[index]->getSubType() == POWER_UP_LASER) {
					listOfGameObjects[PLAYER]->setLaserGrade(listOfGameObjects[PLAYER]->getLaserGrade() + 1);
					//Laser1 = true;
					infoMessage("Player 1 has upgraded their laser!!!", PLAYER_1);
				}
				else if (listOfGameObjects[index]->getSubType() == POWER_UP_ROCKET) {
					listOfGameObjects[PLAYER]->setNumRockets(listOfGameObjects[PLAYER]->getNumRockets() + 1);
					infoMessage("Player 1 has collected a Rocket!!! Rockets: " + std::to_string(listOfGameObjects[PLAYER]->getNumRockets()), PLAYER_1);
				}
				else if (listOfGameObjects[index]->getSubType() == POWER_UP_CHECKPOINT) {
					infoMessage("Checkpoint Reached!!!");
					std::cout << "Checkpoint reached!\n";
					countdownTimer += 20;
				}
				else if (listOfGameObjects[index]->getSubType() == POWER_UP_LIVES) {
					if (listOfGameObjects[PLAYER]->getNumLives() < MAX_NUM_LIVES) {
						listOfGameObjects[PLAYER]->setNumLives(listOfGameObjects[PLAYER]->getNumLives() + 1);
						infoMessage("Player 1 has increased their number of lives!!!", PLAYER_1);
					}
					else
						infoMessage("Player 1 has already has the max number of lives!!!", PLAYER_1);
				}

				listOfGameObjects[index]->setAlive(false);

				Audio::Instance()->playFX("bonusP1FX");
			}
			// Enemies
			else if (listOfGameObjects[index]->getSubType() == ENEMY_SHIP_LASER || listOfGameObjects[index]->getSubType() == BLUE_VIRUS_BULLET || listOfGameObjects[index]->getSubType() == VIRUS_FIREBALL) {
				managePlayerHealth(PLAYER_1, listOfGameObjects[index]->getDamage());															// Score used to inicate amount to remove from health --> need to add damage variable
			}
			else if (listOfGameObjects[index]->getSubType() == ENEMY_SHIP) {
				if (listOfGameObjects[PLAYER]->getSawActive()) {
					listOfGameObjects[index]->setAlive(false);																				// If saw is active kill that enemy
				}
				else
					if (!gPlayer1Texture.getFlash()) managePlayerHealth(PLAYER_1, listOfGameObjects[index]->getDamage() / 5, "Enemy Ship");	// Take off 5 health
			}
			else if (listOfGameObjects[index]->getSubType() == VIRUS_GREEN || listOfGameObjects[index]->getSubType() == VIRUS_ORANGE || listOfGameObjects[index]->getSubType() == VIRUS_BLUE) {
				if (listOfGameObjects[index]->getSubType() == VIRUS_GREEN) {
					spawnEnemyVirus(VIRUS_SMALL_GREEN, listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY());
					spawnEnemyVirus(VIRUS_SMALL_GREEN, listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY());
					listOfGameObjects[index]->setAlive(false);						// If saw is active kill that enemy
				}
				else if (listOfGameObjects[index]->getSubType() == VIRUS_ORANGE) {
					spawnEnemyVirus(VIRUS_SMALL_ORANGE, listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY());
					spawnEnemyVirus(VIRUS_SMALL_ORANGE, listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY());
					listOfGameObjects[index]->setTimer(0);
				}
				else if (listOfGameObjects[index]->getSubType() == VIRUS_BLUE) {
					spawnEnemyVirus(VIRUS_SMALL_BLUE, listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY());
					spawnEnemyVirus(VIRUS_SMALL_BLUE, listOfGameObjects[index]->getX(), listOfGameObjects[index]->getY());
					listOfGameObjects[index]->setAlive(false);						// If saw is active kill that enemy
				}
				else if (!gPlayer1Texture.getFlash()) managePlayerHealth(PLAYER_1, listOfGameObjects[index]->getDamage() / 3, "Enemy Virus");	// If player 1 isn't flashing, Take off 5 health
			}

			// Make sure the player isn't colliding with it's own weapon or a blood cell
			if (listOfGameObjects[index]->getType() != PLAYER_WEAPON && listOfGameObjects[index]->getType() != BLOOD_CELL && listOfGameObjects[index]->getSubType() != BLOCKAGE)
				listOfGameObjects[index]->setAlive(false);	// If it's not a collision between a player and a player weapon or a blood cell
		}
	}
}


*/