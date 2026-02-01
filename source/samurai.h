
//{{BLOCK(samurai)

//======================================================================
//
//	samurai, 256x128@4, 
//	Transparent color : FF,00,FF
//	+ palette 256 entries, not compressed
//	+ 512 tiles Metatiled by 4x4 not compressed
//	Total size: 512 + 16384 = 16896
//
//	Time-stamp: 2026-01-29, 13:48:34
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================
#include "../include/sprites.h"

#ifndef GRIT_SAMURAI_H
#define GRIT_SAMURAI_H

#define samuraiTilesLen 16384
extern const unsigned int samuraiTiles[4096];

#define samuraiPalLen 512
extern const unsigned short samuraiPal[256];

extern const Animation SAMURAI_ANIMS[ANIM_COUNT];

#endif // GRIT_SAMURAI_H

//}}BLOCK(samurai)
