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

typedef struct {
	int startFrame;
	int length;
	int speed;
	int loop;
} Animation;

typedef enum {
	ANIM_IDLE,
	ANIM_RUN,
	ANIM_JUMP,
	ANIM_ATTACK,
	ANIM_BLOCK,
	ANIM_HURT,
	ANIM_DEATH,
	ANIM_COUNT,
} AnimState;
#endif // !SPRITES_H
