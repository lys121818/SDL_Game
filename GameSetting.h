#pragma once
//////////////////////////////////
// STARTING SETTING OF THE GAME //
//////////////////////////////////

#define MAXGAMEOBJECT 10	// Max range of gameobject to be create

// PLAYER SETTINGS
#define PLAYERPOSITION 400.0, 300.0	// Starting position of the player

#define PLAYERSIZE		50.0		// Starting size of the player
#define PLAYERWIDTH		PLAYERSIZE	// Starting size of the player width
#define PLAYERHEIGHT	(PLAYERSIZE * 1.5)	// Starting size of the player height
#define PLAYERSIZEVECTOR2	PLAYERWIDTH, PLAYERHEIGHT	// Starting size of the player in vector2 form

#define PLAYERSPEED		300.0	// Normal speed of player movement
#define PLAYERMAXSPEED	(PLAYERSPEED * 1.5)// Maximum speed of player movement
#define PLAYERMINSPEED	(PLAYERSPEED * 0.5)	// Minimum speed of player movement

#define PLAYERHEALTH	100	// Starting value of player health
#define PLAYERMAXHEALTH	PLAYERHEALTH	// Maximum value of player health

// Set time of when Immune happens
#define IMMUNETIME 1

// ENEMY SETTINGS
#define ENEMYSIZE	50.0		// Starting size of the enemy
#define ENEMYWIDTH	ENEMYSIZE	// Starting size of the enemy width
#define ENEMYHEIGHT	(ENEMYSIZE * 1.5)	// Starting size of the enemy height
#define ENEMYSIZEVECTOR2	ENEMYWIDTH, ENEMYHEIGHT	// Starting size of the enemy in vector2 form

#define ENEMYSPEED	300.0

// BACKGROUND SETTINGS
#define BACKGROUNDTILESIZE	30	// Size of background tile

