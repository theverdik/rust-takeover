#ifndef GAME_H
#define GAME_H

#include <raylib.h>

#include <stdint.h>

#include "util/list.h"
#include "entities/entity.h"
#include "graphics/window.h"
#include "entities/button.h"

typedef struct {
	Window *window;
	float delta_time;

	Button *button;

	List *upgrades;
} Game;

void game_run(void);

#endif // GAME_H
