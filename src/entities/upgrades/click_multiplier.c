#include <string.h>

#include "entities/upgrades/click_multiplier.h"
#include "entities/upgrades/upgrade.h"

Upgrade *click_multiplier_create(void)
{
	Upgrade *click_multiplier = upgrade_create(UPGRADE_CLICK_MULTIPLIER, strlen("Click Multiplier") + 1);
	strcpy(click_multiplier->name_text, "Click Multiplier");

	click_multiplier->price = 100;

	return click_multiplier;
}

void click_multiplier_update(Button *button, Upgrade *click_multiplier)
{
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		int32_t x = GetMouseX();
		int32_t y = GetMouseY();

		if (x >= click_multiplier->entity->body.x && x <= click_multiplier->entity->body.x + click_multiplier->entity->body.width &&
			y >= click_multiplier->entity->body.y && y <= click_multiplier->entity->body.y + click_multiplier->entity->body.height) {
			if (button->money >= click_multiplier->price) {
				button->money -= click_multiplier->price;
				button->click_value *= 1.5f;

				++click_multiplier->amount;
				click_multiplier->price += click_multiplier->price / 0.75f;
			}
		}
	}
}
