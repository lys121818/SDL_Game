#pragma once
#include "Defines.h"

/*================================
// STARTING SETTING OF THE GAME //
================================*/

/// GAME SETTINGS
#define MAXGAMEOBJECT 10	// Max range of gameobject to be create
#define IMMUNETIME 1		// Set time of when Immune happens
#define GRAVITYPOWER 300	// Gravity
#define COLLISIONINDEX	10	// Index of Collision Number

/*	BACKGROUND	*/
// * Size
#define BACKGROUNDTILESIZE	30	// Size of Tile
// * Speed
#define BACKGROUNDMOVESPEED 50


/*	PLAYER	*/ 
// Sprite Sheet
#define PLAYERSPRITE	PUMPKIN
// * Position
#define PLAYERPOSITION 600.0, 450.0

// * Transform
#define PLAYERSIZE		50.0

// * Speed
#define PLAYERSPEED		300.0

// * Health
#define PLAYERHEALTH	100	

#define PLAYERATTACKPOWER	10


/*	ENEMY	*/
// * Transform
#define ENEMYSIZE	50.0
// * Speed
#define ENEMYSPEED	200.0

#define ENEMYATTACKPOWER	10


/* BUTTON */
// * Transform
#define BUTTONSIZE	230.0


/* OBJECTS */
#define OBJECTDAMAGE	100

/*=============== 
|| Calculation  ||	PLAYER
||==============================================================================================================*/
// * size																										||
#define PLAYERWIDTH		PLAYERSIZE				// Width													    ||   
#define PLAYERHEIGHT	(PLAYERSIZE * 1.5)		// Height														||
#define PLAYERSIZEVECTOR2	PLAYERWIDTH, PLAYERHEIGHT	// Size in Vector2 form									||
// * speed																										||
#define PLAYERMAXSPEED	(PLAYERSPEED * 1.5)		// Maximum speed			 									||
#define PLAYERMINSPEED	(PLAYERSPEED * 0.5)		// Minimum speed												||
// * health																										||
#define PLAYERMAXHEALTH	PLAYERHEALTH			// Maximum health												||
//==============================================================================================================//


/*===============
|| Calculation  ||	ENEMY
||==============================================================================================================*/
// * size																										||
#define ENEMYWIDTH	ENEMYSIZE			// Width																||
#define ENEMYHEIGHT	(ENEMYSIZE * 1.5)	// Height																||
#define ENEMYSIZEVECTOR2	ENEMYWIDTH, ENEMYHEIGHT	// Size in Vector2 form										||
//==============================================================================================================//


/*===============
|| Calculation  ||	BUTTON
||==============================================================================================================*/
// * size																										||
#define BUTTONWIDTH		BUTTONSIZE			// Width																||
#define BUTTONHEIGHT	(BUTTONSIZE * 0.3)	// Height																||
#define BUTTONSIZEVECTOR2	ENEMYWIDTH, ENEMYHEIGHT	// Size in Vector2 form										||
//==============================================================================================================//

