#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "button.h"
#include "graphics/renderer.h"
#include "raylib.h"

#define WIDTH 325
#define HEIGHT 325

#define MONEY_TEXT_SIZE 50

// static uint8_t get_digits(uint32_t n);

Button *button_init(int32_t window_width, int32_t window_height)
{
	Button *button = malloc(sizeof(Button));

	button->window_width = window_width;
	button->window_height = window_height;

	button->entity = entity_create(ENTITY_BUTTON, (window_width >> 1) - (WIDTH >> 1), (window_height >> 1) - (HEIGHT >> 1), WIDTH, HEIGHT);
	button->texture = LoadTexture("assets/textures/rust.png");

	button->money = 0;
	memset(button->money_text, 0, MONEY_TEXT_SIZE);
	strcpy(button->money_text, "Codebases rewritten in Rust: 0");

	button->click_value = 1;

	return button;
}

void button_update(Button *button)
{
	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
		int32_t x = GetMouseX();
		int32_t y = GetMouseY();
		if (x >= button->entity->body.x && x <= button->entity->body.x + button->entity->body.width &&
		    y >= button->entity->body.y && y <= button->entity->body.y + button->entity->body.height) {
			button->entity->body.width = WIDTH - 25;
			button->entity->body.height = HEIGHT - 25;

			button->entity->body.x = (button->window_width >> 1) - ((WIDTH - 25) >> 1);
			button->entity->body.y = (button->window_height >> 1) - ((HEIGHT - 25) >> 1);
		}
	}
	else if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
		int32_t x = GetMouseX();
		int32_t y = GetMouseY();

		if (x >= button->entity->body.x && x <= button->entity->body.x + button->entity->body.width &&
		    y >= button->entity->body.y && y <= button->entity->body.y + button->entity->body.height) {
			button->money += button->click_value;

			memset(button->money_text, 0, MONEY_TEXT_SIZE);
			sprintf(button->money_text, "Codebases rewritten in Rust: %.0f", button->money);

			// Resize button to compensate for the shrinking that happens when mouse button is pressed

			button->entity->body.width = WIDTH;
			button->entity->body.height = HEIGHT;

			button->entity->body.x = (button->window_width >> 1) - (WIDTH >> 1);
			button->entity->body.y = (button->window_height >> 1) - (HEIGHT >> 1);
		}
	}
}

void button_render(Button *button)
{
	renderer_render_textured_entity(button->entity, &button->texture);

	DrawText(button->money_text, (button->window_width >> 1) - (MeasureText(button->money_text, 35) >> 1), 0, 35, BLACK);
}

void button_destroy(Button *button)
{
	free(button->entity);
	UnloadTexture(button->texture);
	free(button);
}

// static uint8_t get_digits(uint32_t n)
// {
// 	if (n < 10) return 1;
//     if (n < 100) return 2;
//     if (n < 1000) return 3;
//     if (n < 10000) return 4;
//     if (n < 100000) return 5;
//     if (n < 1000000) return 6;
//     if (n < 10000000) return 7;
//     if (n < 100000000) return 8;
//     if (n < 1000000000) return 9;

// 	return 10;
// }
