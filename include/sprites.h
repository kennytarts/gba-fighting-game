#ifndef SPRITES_H
#define SPRITES_H

#include "gba.h"

typedef struct {
	u16 attr0;
	u16 attr1;
	u16 attr2;
	u16 fill;
} OBJ_ATTR;

#define OAM_MEM ((volatile OBJ_ARR *)0x07000000)

typedef struct{
	int startFrame;
	int length;
	int speed;
	int loop;
} Animation;

static const Animation ANIM_IDLE = {0, 8, 8, 1};
static const Animation ANIM_RUN = {8, 8, 8, 1};
static const Animation ANIM_JUMP = {16, 2, 8, 0};
static const Animation ANIM_ATTACK = {22, 2, 8, 0};
static const Animation ANIM_FALL = {24, 2, 8, 0};
static const Animation ANIM_DEATH = {40, 6, 8, 0};
static const Animation ANIM_BLOCK = {48, 4, 8, 0};
#endif // !SPRITES_H
