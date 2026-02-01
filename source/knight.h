
//{{BLOCK(knight)

//======================================================================
//
//	knight, 256x128@4, 
//	Transparent color : FF,00,FF
//	+ palette 256 entries, not compressed
//	+ 512 tiles Metatiled by 4x4 not compressed
//	Total size: 512 + 16384 = 16896
//
//	Time-stamp: 2026-01-29, 13:48:38
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================
#include "../include/sprites.h"

#ifndef GRIT_KNIGHT_H
#define GRIT_KNIGHT_H

#define knightTilesLen 16384
extern const unsigned int knightTiles[4096];

#define knightPalLen 512
extern const unsigned short knightPal[256];

extern const Animation KNIGHT_ANIMS[ANIM_COUNT];

#endif // GRIT_KNIGHT_H

//}}BLOCK(knight)
