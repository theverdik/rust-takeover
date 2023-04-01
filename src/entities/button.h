#ifndef BUTTON_H
#define BUTTON_H

#include <raylib.h>

#include <stdint.h>

#include "util/list.h"
#include "entities/entity.h"

typedef struct {
	int32_t window_width, window_height;

	Entity *entity;
	Texture2D texture;
	
	float money;
	char money_text[50];

	uint64_t click_value;
} Button;

Button *button_init(int32_t window_width, int32_t window_height);

void button_update(Button *button);
void button_render(Button *button);

void button_destroy(Button *button);

#endif // BUTTON_H
