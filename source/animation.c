#include "../include/animation.h"
#include "../include/physics.h"

void change_animation(Character *p, const Animation *newAnim)
{
	if (p->currentAnim == newAnim)
	{
		return;
	}

	p->currentAnim = newAnim;
	p->animTimer = 0;
	p->animFrame = 0;
}

void update_animation(Character *p)
{
	p->animTimer++;

	if (p->animTimer > p->currentAnim->speed)
	{
		p->animTimer = 0;
		p->animFrame++;

		if (p->animFrame >= p->currentAnim->length)
		{
			if (p->currentAnim->loop)
			{
				p->animFrame = 0;
			}
			else
			{
				p->animFrame = p->currentAnim->length - 1;
			}
		}
	}
}
