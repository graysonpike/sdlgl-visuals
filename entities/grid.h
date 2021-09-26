#ifndef GRID_H
#define GRID_H

#include <vector>

#include "sdlgl/game/physical_entity.h"
#include "sdlgl/game/clock.h"
#include "sdlgl/utilities/noise.h"

#include "./point.h"

class Grid : public PhysicalEntity {

    int n;
    std::vector<Point*> points;
    Clock clock;
    void init_points();

public:

    Grid(Scene *scene, float x, float y, int w, int h, int n);
    void render();
    void update();

};

#endif
