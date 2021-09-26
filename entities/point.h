#ifndef POINT_H
#define POINT_H

#include "sdlgl/game/physical_entity.h"

class Point : public PhysicalEntity {

	float offset;
	SDL_Color color;
	Texture texture;

public:

    Point(Scene *scene, float x, float y, int w, int h, SDL_Color color);

    void update();
    void render();
    void set_offset(float x);

};

#endif
