#include "../include/gba.h"


void __attribute__((target("arm"))) vblank_handler()
{
	REG_IF = IRQ_VBLANK;

	(*(volatile u16 *)0x03007FF8) |= IRQ_VBLANK;

}

void init_interrupts()
{

	// Address is BIOS interrupt vector
	(*(volatile u32 *)0x03007FFC) = (u32)vblank_handler;
	REG_DISPSTAT |= (1 << 3);
	REG_IE |= IRQ_VBLANK;
	REG_IME = 1;
}
