#ifndef GBA_H
#define GBA_H

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct {
	const void *src;
	volatile void *dst;
	volatile u32 cnt;
} DMA_REC;

#define REG_DISPCNT (*(volatile u32 *)0x04000000)
#define VRAM ((volatile u16 *)0x06000000)

#define MODE3 0x0003
#define BG2_ENABLE 0x0400

#define MODE0 0x0000
#define BG0_ENABLE 0x0100

// Read more: https://gbadev.net/gbadoc/registers.html#REG_BGCNT
#define REG_BG0CNT (*(volatile u16 *)0x04000008)
#define BG_PRIORITY(p) ((p) << 0)
#define BG_CBB(a) ((a) << 2)
#define BG_SBB(m) ((m) << 8)
#define BG_CP(t) ((t) << 7)
#define BG_TILE_SIZE(s) ((s) << 14)

#define OBJ_ENABLE 0x1000
#define OBJ_1D_MAP 0x0040

// Background Tile
#define MEM_PALETTE_BG (volatile u16 *)0x05000000;
#define MEM_TILE_BG (volatile u32 *)0x06000000;
#define MEM_MAP (volatile u16 *)0x0600F800;

#define MEM_PALETTE_OBJ ((volatile u16 *)0x05000200)
#define MEM_TILE_OBJ ((volatile u32 *)0x06010000)
#define MEM_OAM ((volatile OBJ_ATTR *)0x07000000)

// Interrupt - IE = Enable, IF = Flags, IME = Master Enable
#define REG_IE (*(volatile u16 *)0x04000200)
#define REG_IF (*(volatile u16 *)0x04000202)
#define REG_IME (*(volatile u16 *)0x04000208)

// Interrupt Bit Masks
#define IRQ_VBLANK (1 << 0)

#define REG_DISPSTAT (*(volatile u16 *)0x04000004)

#define REG_VCOUNT (*(volatile u16 *)0x04000006)
#define RGB15(r, g, b) ((r) | ((g) << 5) | ((b) << 10))
#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 160

#define REG_KEYINPUT (*(volatile u16 *)0x04000130)
#define MGBA_DEBUG_PORT (*(volatile u16 *)0x04F00000)
#define KEY_A 0x0001
#define KEY_B 0x0002
#define KEY_SELECT 0x0004
#define KEY_START 0x0008
#define KEY_RIGHT 0x0010
#define KEY_LEFT 0x0020
#define KEY_UP 0x0040
#define KEY_DOWN 0x0080
#define KEY_R 0x0100
#define KEY_L 0x0200

#define REG_DMA ((volatile DMA_REC *)0x040000B0)
#define DMA3_COPY32 0x84000000
#define DMA3_COPY16 0x80000000

#endif // !GBA_H
