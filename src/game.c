#include <raylib.h>

#include <stdio.h>
#include <stdlib.h>

#include "entities/button.h"
#include "entities/upgrades/upgrade.h"
#include "game.h"
#include "graphics/window.h"

#define WIDTH 1280
#define HEIGHT 720
#define TITLE "Rust Takeover"

static Game *init(void);

static void update(Game *game);
static void tick(Game *game);
static void render(Game *game);

static void terminate(Game *game);

static Game *init(void)
{
	Game *game = malloc(sizeof(Game));

	game->window = window_init(WIDTH, HEIGHT, TITLE);
	InitAudioDevice();

	game->button = button_init(WIDTH, HEIGHT);
	game->upgrades = upgrade_list_create(WIDTH, HEIGHT);

	return game;
}

void game_run(void)
{
	Game *game = init();

    const double delta_time = 1.0 / 60.0;

    double currentTime = GetTime();
	double newTime;
    double accumulator = 0.0;

    while (!window_should_close())
    {
		update(game);

        newTime = GetTime();

        accumulator += newTime - currentTime;
        currentTime = newTime;

        while (accumulator >= delta_time)
        {
            tick(game);
            accumulator -= delta_time;
        }

        render(game);
    }

	terminate(game);
}

static void update(Game *game)
{
	window_update(game->window);

	button_update(game->button);
	upgrade_update(game->upgrades, game->button);
}

static void tick(Game *game)
{
}

static void render(Game *game)
{
	BeginDrawing();
	ClearBackground(game->window->background);

	button_render(game->button);
	upgrade_render(game->upgrades);
	
	// for (Node *temp = game->entities->head; temp != NULL; temp = temp->next) {
	// 	DrawRectangleRec(((Entity *)temp->data)->body, ((Entity *)temp->data)->color);
	// }

	EndDrawing();
}

static void terminate(Game *game)
{
	CloseAudioDevice();
	window_destroy(game->window);

	upgrade_list_destroy(game->upgrades);
	free(game);
}
