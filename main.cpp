#include <iostream>

#include "sdlgl/graphics/graphics.h"
#include <sdlgl/game/clock.h>
#include <sdlgl/game/scene.h>
#include <sdlgl/input/inputs.h>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>

#include <sdlgl/game/scene.h>
#include <sdlgl/game/context.h>
#include <sdlgl/ui/fps_display.h>
#include <sdlgl/ui/entity_count.h>
#include <sdlgl/utilities/noise.h>

#include "entities/grid.h"


#define KEY_TOGGLE_DEBUG_VISUALS SDL_SCANCODE_GRAVE // Tilde


void game_loop(Context context, Scene *scene) {

    context.inputs->update();
    context.clock->tick();
    context.graphics->clear_screen({255, 255, 255, 255});

    scene->update(context.clock->get_delta());
    scene->render();

    if (context.inputs->is_key_down_event(KEY_TOGGLE_DEBUG_VISUALS)) {
        context.graphics->toggle_debug_visuals();
    }

    if (context.inputs->is_key_down_event(SDL_SCANCODE_SPACE)) {
        context.graphics->capture_bmp("screenshot.bmp");
    }

    if (context.inputs->get_quit()) {
        *context.loop = false;
    }

    context.graphics->present_renderer(context.clock->get_delta());

}


int main() {

    srand(time(NULL));

    PerlinNoise::init();

    Context context(new Graphics(1920, 1080), new Audio(), new Inputs(), new Clock());

    // Load resources
    context.graphics->get_resources()->load_resources("resources.json");

    // Create and populate scene
    Scene *scene = new Scene(context.graphics, context.audio, context.inputs);

    // UI entities
    scene->add_entity(new FPS_Display(
        scene, "base_text", {0, 0, 0, 255}));
    scene->add_entity(new EntityCount(
        scene, "base_text", {0, 0, 0, 255}));

    scene->add_entity(new Grid(scene, -160, 120, 30*32, 30*16, 30));

    while (*context.loop) {

        game_loop(context, scene);

    }

    return 0;
}
