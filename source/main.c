#include "../include/animation.h"
#include "../include/gba.h"
#include "../include/interrupts.h"
#include "../include/physics.h"
#include "../include/sprites.h"
#include "fighter.h"
#include "stage.h"
#include <stdlib.h>

OBJ_ATTR shadowOAM[128];

void init_sprite_memory() {
	REG_DMA[3].src = fighterPal;
	REG_DMA[3].dst = MEM_PALETTE_OBJ;
	REG_DMA[3].cnt = (fighterPalLen / 2) | DMA3_COPY16;

	REG_DMA[3].src = fighterTiles;
	REG_DMA[3].dst = MEM_TILE_OBJ;
	REG_DMA[3].cnt = (fighterTilesLen / 4) | DMA3_COPY32;

	shadowOAM[0].attr0 = 50 | (0 << 13) | (0 << 14);
	shadowOAM[0].attr1 = 100 | (2 << 14);
	shadowOAM[0].attr2 = 0;

	MEM_OAM[0] = shadowOAM[0];
}

void init_background() {
	REG_DMA[3].src = stagePal;
	REG_DMA[3].dst = MEM_PALETTE_BG;
	REG_DMA[3].cnt = (stagePalLen / 2) | DMA3_COPY16;

	REG_DMA[3].src = stageTiles;
	REG_DMA[3].dst = MEM_TILE_BG;
	REG_DMA[3].cnt = (stageTilesLen / 4) | DMA3_COPY32;

	REG_DMA[3].src = stageMap;
	REG_DMA[3].dst = MEM_MAP;
	REG_DMA[3].cnt = (stageMapLen / 2) | DMA3_COPY16;
}

void update_visuals(Character *p, int oam_index) {
	int tileIndex = 0 + (p->currentAnim->startFrame + p->animFrame) * 16;

	shadowOAM[oam_index].attr2 = tileIndex;

	u16 attr1 = (FIXED_TO_INT(p->x) & 0x1FF) | (2 << 14);
	if (!p->facingRight) {
		attr1 |= 0x1000;
	}
	shadowOAM[oam_index].attr0 =
		(FIXED_TO_INT(p->y) & 0xFF) | (0 << 13) | (0 << 14);
	shadowOAM[oam_index].attr1 = attr1;

	MEM_OAM[0] = shadowOAM[oam_index];
}

const int GRAVITY = FLOAT_TO_FIXED(0.2);
const int JUMP_FORCE = FLOAT_TO_FIXED(-4.0);
const int MOVE_SPEED = FLOAT_TO_FIXED(2.0);
const int FLOOR_Y = INT_TO_FIXED(100);
const int FRICTION = FLOAT_TO_FIXED(0.1);

int check_collision(Character *player, Character *enemy) {
	int player_x = FIXED_TO_INT(player->x);
	int player_y = FIXED_TO_INT(player->y);

	int enemy_x = FIXED_TO_INT(enemy->x);
	int enemy_y = FIXED_TO_INT(enemy->y);

	if (player_x + player->width < enemy_x)
		return 0;
	if (player_x > enemy_x + enemy->width)
		return 0;
	if (player_y + player->height < enemy_y)
		return 0;
	if (player_y > enemy_y + enemy->height)
		return 0;

	return 1;
}

int main() {
	init_background();
	init_sprite_memory();
	REG_DISPCNT = MODE0 | BG0_ENABLE | OBJ_ENABLE | OBJ_1D_MAP;
	REG_BG0CNT =
		BG_PRIORITY(0) | BG_CBB(0) | BG_SBB(31) | BG_CP(0) | BG_TILE_SIZE(0);

	init_interrupts();

	Character p;
	p.x = INT_TO_FIXED(120);
	p.y = INT_TO_FIXED(20);
	p.dx = 0;
	p.dy = 0;
	p.width = 10;
	p.height = 10;
	p.isGrounded = 0;
	p.state = IDLE;
	p.facingRight = 1;
	p.currentAnim = &ANIM_IDLE;
	p.animTimer = 0;
	p.animFrame = 0;

	Character e;
	e.x = INT_TO_FIXED(100);
	e.y = INT_TO_FIXED(100);
	e.dx = 0;
	e.dy = 0;
	e.width = 10;
	e.height = 10;
	e.isGrounded = 0;
	e.state = BLOCK;

	while (1) {
		// BIOs Call 5: VBLlankIntrWait (Puts CPU into low-power sleep until
		// VBlank interrupt fires.
		__asm("swi 0x05");

		update_animation(&p);
		update_visuals(&p, 0);

		// Player state
		p.dx = 0;
		e.dx = 0;
		switch (p.state) {
		case IDLE:
			change_animation(&p, &ANIM_IDLE);
			if (!(REG_KEYINPUT & KEY_RIGHT) | !(REG_KEYINPUT & KEY_LEFT)) {
				p.state = RUN;
			}

			if (!(REG_KEYINPUT & KEY_A) && p.isGrounded) {
				p.state = JUMP;
				p.dy = JUMP_FORCE;
				p.isGrounded = 0;
			}
			if (!(REG_KEYINPUT & KEY_B)) {
				p.state = ATTACK;
				p.stateTimer = 12;
			}
			if (!(REG_KEYINPUT & KEY_R) | !(REG_KEYINPUT & KEY_L)) {
				p.state = BLOCK;
			}
			break;
		case RUN:
			change_animation(&p, &ANIM_RUN);
			if (!(REG_KEYINPUT & KEY_RIGHT)) {
				p.facingRight = 1;
				p.dx = MOVE_SPEED;
			}

			if (!(REG_KEYINPUT & KEY_LEFT)) {
				p.facingRight = 0;
				p.dx = -MOVE_SPEED;
			}

			if ((REG_KEYINPUT & KEY_RIGHT) && (REG_KEYINPUT & KEY_LEFT)) {
				p.state = IDLE;
			}

			if (!(REG_KEYINPUT & KEY_A) && p.isGrounded) {
				p.state = JUMP;
				p.dy = JUMP_FORCE;
				p.isGrounded = 0;
			}
			break;
		case JUMP:
			change_animation(&p, &ANIM_JUMP);
			if (!(REG_KEYINPUT & KEY_RIGHT)) {
				p.facingRight = 1;
				p.dx = MOVE_SPEED;
			}

			if (!(REG_KEYINPUT & KEY_LEFT)) {
				p.facingRight = 0;
				p.dx = -MOVE_SPEED;
			}
			break;
		case ATTACK:
			change_animation(&p, &ANIM_ATTACK);
			p.stateTimer--;
			if (p.stateTimer <= 0) {
				p.state = IDLE;
			}
			// Start up
			else if (p.stateTimer > 12) {
				// player_color = RGB15(31, 31, 31);
			}
			// Active
			else if (p.stateTimer <= 10 && p.stateTimer > 5) {
				// player_color = RGB15(31, 31, 0);
				if (check_collision(&p, &e)) {
					// enemy_color = RGB15(31, 0, 0);
					if (e.state == BLOCK) {

						if ((FIXED_TO_INT(p.x) + p.width) / 2 <
							(FIXED_TO_INT(e.x) + e.width) / 2) {
							e.dx = FLOAT_TO_FIXED(0.5);
						} else {
							e.dx = -FLOAT_TO_FIXED(0.5);
						}
					} else {
						if ((FIXED_TO_INT(p.x) + p.width) / 2 <
							(FIXED_TO_INT(e.x) + e.width) / 2) {
							e.dx = MOVE_SPEED;
						} else {
							e.dx = -MOVE_SPEED;
						}
						e.state = HURT;
						e.stateTimer = 10;
					}
				}
			}
			// Cooldown
			else if (p.stateTimer <= 5) {
				// player_color = RGB15(10, 10, 10);
			}
			break;
		case HURT:
			break;
		case BLOCK:
			change_animation(&p, &ANIM_BLOCK);
			if ((REG_KEYINPUT & KEY_R) && (REG_KEYINPUT & KEY_L)) {
				p.state = IDLE;
			}
			break;
		}

		// Enemy state
		switch (e.state) {
		case IDLE:
			break;
		case RUN:
			break;
		case JUMP:
			break;
		case ATTACK:
			break;
		case BLOCK:
			// enemy_color = RGB15(31, 0, 31);
			break;
		case HURT:
			e.stateTimer--;
			if (e.stateTimer <= 0 && e.isGrounded) {
				e.state = IDLE;
				// enemy_color = RGB15(0, 0, 31);
			}
			break;
		}
		// Player Physics
		p.dy += GRAVITY;
		p.x += p.dx;
		p.y += p.dy;

		if (p.y > FLOOR_Y) {
			p.y = FLOOR_Y;
			p.dy = 0;
			p.isGrounded = 1;
			if (p.state == JUMP) {
				p.state = IDLE;
			}
		}

		// Player not out of bound
		if (p.x < 0) {
			p.x = 0;
		}
		if (p.x > INT_TO_FIXED(SCREEN_WIDTH) - INT_TO_FIXED(p.width)) {
			p.x = INT_TO_FIXED(SCREEN_WIDTH) - INT_TO_FIXED(p.width);
		}

		// Enemy Physics
		e.dy += GRAVITY;

		if (e.dx > 0)
			e.dx -= FRICTION;
		if (e.dx < 0)
			e.dx += FRICTION;

		if (abs(e.dx) < FRICTION)
			e.dx = 0;

		e.x += e.dx;
		e.y += e.dy;

		if (e.y > FLOOR_Y) {
			e.y = FLOOR_Y;
			e.dy = 0;
			e.isGrounded = 1;
		}

		// Enemy not out of bound
		if (e.x < 0) {
			e.x = 0;
		}
		if (e.x > INT_TO_FIXED(SCREEN_WIDTH) - INT_TO_FIXED(e.width)) {
			e.x = INT_TO_FIXED(SCREEN_WIDTH) - INT_TO_FIXED(e.width);
		}
	}

	return 0;
}
