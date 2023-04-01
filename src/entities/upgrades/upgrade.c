#include <stdlib.h>

#include "raylib.h"
#include "util/list.h"
#include "entities/upgrades/upgrade.h"
#include "entities/upgrades/click_multiplier.h"

Upgrade *upgrade_create(UpgradeType type, uint32_t text_length)
{
	Upgrade *upgrade = malloc(sizeof(Upgrade));

	upgrade->type = type;

	upgrade->entity = entity_create(ENTITY_UPGRADE, 0, 0, 200, 100);

	upgrade->price = 0;
	upgrade->amount = 0;

	upgrade->text = calloc(text_length, sizeof(char));
	upgrade->text_length = text_length;

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
		DrawRectangleLines(data->entity->body.x, data->entity->body.y, data->entity->body.width, data->entity->body.height, BLACK);
	}
}

void upgrade_destroy(Upgrade *upgrade)
{
	free(upgrade->entity);
	free(upgrade->text);
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
		free(((Upgrade *)temp->data)->text);
	}

	list_free(upgrades);
}
