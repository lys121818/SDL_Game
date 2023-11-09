#pragma once
#include "Defines.h"

/*================================
// STARTING SETTING OF THE GAME //
================================*/

/// GAME SETTINGS
#define MAX_GAMEOBJECT 10	// Max range of gameobject to be create
#define IMMUNE_TIME 1		// Set time of when Immune happens
#define GRAVITY_POWER 300	// Gravity
#define COLLISION_INDEX	10	// Index of Collision Number

/*	BACKGROUND	*/
// * Size
#define BACKGROUND_TILE_SIZE	30	// Size of Tile
// * Speed
#define BACKGROUND_MOVE_SPEED 50


/*	PLAYER	*/ 
// Sprite Sheet
#define PLAYER_SPRITE	PUMPKIN
// * Position
#define PLAYER_POSITION 600.0, 450.0

// * Transform
#define PLAYER_SIZE		50.0

// * Speed
#define PLAYER_SPEED		300.0

// * Health
#define PLAYER_HEALTH	100	

#define PLAYER_ATTACK_POWER	10

#define PLAYER_JUMP_POWER	1000


/*	ENEMY	*/
// * Transform
#define ENEMY_SIZE	50.0
// * Speed
#define ENEMY_SPEED	200.0

#define ENEMY_ATTACK_POWER	10


/* BUTTON */
// * Transform
#define BUTTON_SIZE	230.0


/* OBJECTS */
#define OBJECT_DAMAGE	10

/* UI */
#define HEALTHBAR_POSITION	50, 50	// X, Y
#define HEALTHBAR_SIZE		200		// X, (X / 4)

/*=============== 
|| Calculation  ||	PLAYER
||==============================================================================================================*/
// * size																										||
#define PLAYER_WIDTH		PLAYER_SIZE				// Width												    ||   
#define PLAYER_HEIGHT	(PLAYER_SIZE * 1.5)		// Height														||
#define PLAYER_SIZE_VECTOR2	PLAYER_WIDTH, PLAYER_HEIGHT	// Size in Vector2 form									||
// * speed																										||
#define PLAYER_MAX_SPEED	(PLAYER_SPEED * 1.5)		// Maximum speed			 							||
#define PLAYER_MIN_SPEED	(PLAYER_SPEED * 0.5)		// Minimum speed										||
// * health																										||
#define PLAYER_MAX_HEALTH	PLAYER_HEALTH			// Maximum health											||
//==============================================================================================================//


/*===============
|| Calculation  ||	ENEMY
||==============================================================================================================*/
// * size																										||
#define ENEMY_WIDTH	ENEMY_SIZE			// Width																||
#define ENEMY_HEIGHT	(ENEMY_SIZE * 1.5)	// Height															||
#define ENEMY_SIZE_VECTOR2	ENEMY_WIDTH, ENEMY_HEIGHT	// Size in Vector2 form									||
//==============================================================================================================//


/*===============
|| Calculation  ||	BUTTON
||==============================================================================================================*/
// * size																										||
#define BUTTON_WIDTH		BUTTON_SIZE			// Width														||
#define BUTTON_HEIGHT	(BUTTON_SIZE * 0.3)	// Height															||
#define BUTTON_SIZE_VECTOR2	BUTTON_WIDTH, BUTTON_HEIGHT	// Size in Vector2 form									||
//==============================================================================================================//


/*===============
|| Calculation  ||	UI
||==============================================================================================================*/
// * size																										||
#define HEALTHBAR_WIDTH		HEALTHBAR_SIZE			// Width													||
#define HEALTHBAR_HEIGHT		(HEALTHBAR_SIZE * 0.25)	// Height												||
#define HEALTBARH_SIZE_VECTOR2	HEALTHBAR_WIDTH, HEALTHBAR_HEIGHT	// Size in Vector2 form						||
//==============================================================================================================//



/* Key for Function Calls */

#define HEALTHBAR_UI_FUNCTION	"HealthbarUpdate"