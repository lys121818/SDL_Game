#pragma once

#define CREATOR	"Jason Lee"

#define SEED -1

#define SAVE_FILE_DEFAULT	"savedata_default.save"
#define SAVE_FILE_1	"savedata_1.save"
#define SAVE_FILE_2	"savedata_2.save"
#define SAVE_FILE_3	"savedata_3.save"

/// COLOR
#define BLACK   0,0,0,SDL_ALPHA_OPAQUE
#define WHITE	255,255,255,SDL_ALPHA_OPAQUE
#define RED     255,0,0,SDL_ALPHA_OPAQUE
#define GREEN   0,255,0,SDL_ALPHA_OPAQUE
#define BLUE    0,0,255,SDL_ALPHA_OPAQUE
#define YELLOW  255,255,0,SDL_ALPHA_OPAQUE
#define GRAY	128,128,128,SDL_ALPHA_OPAQUE


/// WINDOW SETTINGS
// Window Size
#define WINDOWWIDTH 800
#define WINDOWHEIGHT 600

// SCENE CHANGE
#define LOADINGTIME 2.0

// SOUNDS
#define MAXVOLUME	128

/// VECTOR2 SETTINGS
// Direction
#define RIGHT	1.0,0.0
#define LEFT	-1.0,0.0
#define DOWN	0.0,1.0
#define UP		0.0,-1.0
#define ZERO	0.0,0.0

// Counter Direction
#define STOPRIGHT	LEFT
#define STOPLEFT	RIGHT
#define STOPDOWN	UP
#define STOPUP		DOWN

// Txt file for Tiled Map
#define TILEMAP		"assets/TxtFile/TiledMap.txt"
#define BOSSMAP		"assets/TxtFile/BossMap.txt"

#define PLAYER_INFO	"assets/TxtFile/PlayerInfo.txt"

