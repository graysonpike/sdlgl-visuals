#include <sdlgl/graphics/resources.h>

#include "point.h"


Point::Point(Scene *scene, float x, float y, int w, int h, SDL_Color color) : 
    PhysicalEntity(scene, x, y, w, h), color(color) {

    Resources *resources = scene->get_graphics()->get_resources();
    texture = resources->get_texture("tile");

}


void Point::update() {}

void Point::render() {

    SDL_Renderer *renderer = scene->get_graphics()->get_renderer();

    // Draw box
    // SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    // SDL_Rect box_rect = {(int)x, (int)(y + offset), w, h};
    // SDL_RenderFillRect(renderer, &box_rect);

    texture.draw(renderer, x, y + offset);

}

void Point::set_offset(float x) {
    offset = x;
}
