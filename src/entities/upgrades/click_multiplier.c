#include <stdio.h>

#include "entities/upgrades/click_multiplier.h"
#include "entities/upgrades/upgrade.h"

Upgrade *click_multiplier_create(void)
{
	Upgrade *click_multiplier = upgrade_create(UPGRADE_CLICK_MULTIPLIER, 1);

	return click_multiplier;
}

void click_multiplier_update(Button *button, Upgrade *click_multiplier)
{
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		int32_t x = GetMouseX();
		int32_t y = GetMouseY();

		if (x >= click_multiplier->entity->body.x && x <= click_multiplier->entity->body.x + click_multiplier->entity->body.width &&
			y >= click_multiplier->entity->body.y && y <= click_multiplier->entity->body.y + click_multiplier->entity->body.height) {
			button->click_value *= 2;
			printf("%u\n", ++click_multiplier->amount);
		}
	}
}
