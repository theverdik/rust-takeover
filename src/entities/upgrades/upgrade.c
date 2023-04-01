#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util/list.h"
#include "entities/upgrades/upgrade.h"
#include "entities/upgrades/click_multiplier.h"

#define PRICE_TEXT_SIZE 28
#define AMOUNT_TEXT_SIZE 21

#define NAME_FONT_SIZE 26
#define PRICE_FONT_SIZE 23
#define AMOUNT_FONT_SIZE 30

Upgrade *upgrade_create(UpgradeType type, uint32_t name_length)
{
	Upgrade *upgrade = calloc(1, sizeof(Upgrade));

	upgrade->type = type;

	upgrade->entity = entity_create(ENTITY_UPGRADE, 0, 0, 300, 100);

	upgrade->price = 0;
	upgrade->amount = 0;

	upgrade->name_text = calloc(name_length, sizeof(char));
	upgrade->name_length = name_length;

	return upgrade;
}

void upgrade_update(List *upgrades, Button *button)
{
	for (Node *temp = upgrades->head; temp != NULL; temp = temp->next) {
		Upgrade *data = temp->data;
		if (data->type == UPGRADE_CLICK_MULTIPLIER)
			click_multiplier_update(button, data);
	}
}

void upgrade_render(List *upgrades)
{
	for (Node *temp = upgrades->head; temp != NULL; temp = temp->next) {
		Upgrade *data = temp->data;
		DrawRectangleLinesEx(data->entity->body, 2.0f, BLACK);

		DrawText(data->name_text, data->entity->body.x + 4, data->entity->body.y + 2, NAME_FONT_SIZE, BLACK);
		
		memset(data->price_text, 0, PRICE_TEXT_SIZE);
		sprintf(data->price_text, "Price: %u", data->price);
		DrawText(data->price_text, data->entity->body.x + 4, data->entity->body.y + data->entity->body.height - PRICE_FONT_SIZE - 2, PRICE_FONT_SIZE, BLACK);

		memset(data->amount_text, 0, AMOUNT_TEXT_SIZE);
		sprintf(data->amount_text, "%u", data->amount);
		DrawText(data->amount_text, data->entity->body.x + data->entity->body.width - MeasureText(data->amount_text, AMOUNT_FONT_SIZE) - 4,
		         data->entity->body.y + (data->entity->body.height / 2) - (AMOUNT_FONT_SIZE >> 1) - 2, AMOUNT_FONT_SIZE, BLACK);
	}
}

void upgrade_destroy(Upgrade *upgrade)
{
	free(upgrade->entity);
	free(upgrade->name_text);
	free(upgrade);
}

List *upgrade_list_create(int32_t window_width, int32_t window_height)
{
	List *list = list_create();

	Upgrade *prev = NULL;

	prev = list_add(list, click_multiplier_create(), sizeof(Upgrade))->data;
	prev->entity->body.x = window_width - prev->entity->body.width;
	prev->entity->body.y = 0;

	return list;
}

void upgrade_list_destroy(List *upgrades)
{
	for (Node *temp = upgrades->head; temp != NULL; temp = temp->next) {
		free(((Upgrade *)temp->data)->entity);
		free(((Upgrade *)temp->data)->name_text);
	}

	list_free(upgrades);
}
