#include <iostream>

#include "sdlgl/graphics/graphics.h"
#include <sdlgl/game/clock.h>
#include <sdlgl/game/scene.h>
#include <sdlgl/game/simple_context.h>
#include <sdlgl/input/inputs.h>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>

#include <sdlgl/ui/fps_display.h>
#include <sdlgl/ui/entity_count.h>
#include <sdlgl/utilities/noise.h>

#include "entities/grid.h"


#define KEY_TOGGLE_DEBUG_VISUALS SDL_SCANCODE_GRAVE // Tilde


void game_loop(SimpleContext context) {

    context.inputs->update();
    context.clock->tick();
    context.graphics->clear_screen({255, 255, 255, 255});

    context.scene->update(context.clock->get_delta());
    context.scene->render();

    if (context.inputs->is_key_down_event(KEY_TOGGLE_DEBUG_VISUALS)) {
        context.graphics->toggle_debug_visuals();
    }

    if (context.inputs->get_quit()) {
        *context.loop = false;
    }

    context.graphics->present_renderer(context.clock->get_delta());

}


int main() {

    srand(time(NULL));

    PerlinNoise::init();

    SimpleContext context(new Graphics(1920, 1080), new Inputs(), new Clock());

    // Load resources
    context.graphics->get_resources()->load_resources("resources.json");

    // Create and populate scene
    context.scene = new Scene(context.inputs, context.graphics);

    // UI entities
    context.scene->add_entity(new FPS_Display(
        context.scene, "base_text", {0, 0, 0, 255}));
    context.scene->add_entity(new EntityCount(
        context.scene, "base_text", {0, 0, 0, 255}));

    context.scene->add_entity(new Grid(context.scene, -160, 120, 1600, 900, 50));

    while (*context.loop) {

        game_loop(context);

    }

    return 0;
}
