#ifndef UPGRADE_H
#define UPGRADE_H

#include <raylib.h>

#include "util/list.h"
#include "entities/entity.h"
#include "entities/button.h"

#define UPGRADE_WIDTH 100
#define UPGRADE_HEIGHT 25

typedef enum {
	UPGRADE_CLICK_MULTIPLIER
} UpgradeType;

typedef struct {
	UpgradeType type;

	Entity *entity;

	uint32_t price;
	uint32_t amount;

	char *text;
	uint32_t text_length;
} Upgrade;

Upgrade *upgrade_create(UpgradeType type, uint32_t text_length);

void upgrade_update(List *upgrades, Button *button);
void upgrade_render(List *upgrades);

void upgrade_destroy(Upgrade *upgrade);

List *upgrade_list_create(int32_t window_width, int32_t window_height);
void upgrade_list_destroy(List *upgrades);


#endif // UPGRADE_H
