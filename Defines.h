#pragma once

/// COLOR
#define BLACK   0,0,0,SDL_ALPHA_OPAQUE
#define WHITE	255,255,255,SDL_ALPHA_OPAQUE
#define RED     255,0,0,SDL_ALPHA_OPAQUE
#define GREEN   0,255,0,SDL_ALPHA_OPAQUE
#define BLUE    0,0,255,SDL_ALPHA_OPAQUE
#define YELLOW  255,255,0,SDL_ALPHA_OPAQUE


/// WINDOW SETTINGS
// Window Size
#define WINDOWWIDTH 800
#define WINDOWHEIGHT 600

// SCENE CHANGE
#define LOADINGTIME 2.0

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

// Txt file for Tiled Map
#define TILEMAP		"assets/TiledMap.txt"