#pragma once

/// COLOR
#define BLACK   0,0,0,SDL_ALPHA_OPAQUE
#define WHITE	255,255,255,SDL_ALPHA_OPAQUE
#define RED     255,0,0,SDL_ALPHA_OPAQUE
#define GREEN   0,255,0,SDL_ALPHA_OPAQUE
#define BLUE    0,0,255,SDL_ALPHA_OPAQUE
#define YELLOW  255,255,0,SDL_ALPHA_OPAQUE

/// IMAGE LOCATIONS
// Single Image
#define BACKGROUND	"assets/Space.png"
#define PLAYER		"assets/Pig.bmp"
#define BULLET		"assets/Globe.gif"
#define STATIONARY1	"assets/Cat.jpg"
#define STATIONARY2	"assets/Dice.png"

// Image Sprite
#define TILES		"assets/Tiles.png"			// 128 * 128
#define OBJECTS		"assets/Objects.png"		// 64 * 64

// Animation Sprite Sheet
#define PUMPKIN			"assets/Pumpkin.png"		// 200 * 300
#define ZOMBIEMALE		"assets/ZombieMale.png"		// 200 * 300
#define ZOMBIEFEMALE	"assets/ZombieFemale.png"	// 200 * 300


/// WINDOW SETTINGS
// Window Size
#define WINDOWWIDTH 800
#define WINDOWHEIGHT 600

/// VECTOR2 SETTINGS
// Direction
#define RIGHT	1,0
#define LEFT	-1,0
#define DOWN	0,1
#define UP		0,-1

// Counter Direction
#define STOPRIGHT	LEFT
#define STOPLEFT	RIGHT
#define STOPDOWN	UP
#define STOPUP		DOWN