
//{{BLOCK(stage)

//======================================================================
//
//	stage, 256x256@4, 
//	+ palette 256 entries, not compressed
//	+ 463 tiles (t|f reduced) not compressed
//	+ regular map (flat), not compressed, 32x32 
//	Total size: 512 + 14816 + 2048 = 17376
//
//	Time-stamp: 2026-01-08, 11:12:35
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_STAGE_H
#define GRIT_STAGE_H

#define stageTilesLen 14816
extern const unsigned int stageTiles[3704];

#define stageMapLen 2048
extern const unsigned short stageMap[1024];

#define stagePalLen 512
extern const unsigned short stagePal[256];

#endif // GRIT_STAGE_H

//}}BLOCK(stage)
