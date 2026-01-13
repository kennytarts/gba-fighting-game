#ifndef PHYSICS_H
#define PHYSICS_H

#include "gba.h"
#include "sprites.h"

#define FIXED_SHIFT 8
#define FLOAT_TO_FIXED(f) ((int)((f) * (1 << FIXED_SHIFT)))
#define INT_TO_FIXED(i) ((i) << FIXED_SHIFT)
#define FIXED_TO_INT(f) ((f) >> FIXED_SHIFT)

typedef enum { IDLE, RUN, JUMP, ATTACK, HURT, BLOCK } State;

typedef struct {
	int x, y;
	int dx, dy;
	int width, height;
	u8 isGrounded;
	State state;
	int stateTimer;
	u8 facingRight;
	int health;

	const Animation *currentAnim;
	int animTimer;
	int animFrame;
} Character;

#endif // PHYSICS_H
