#include <iostream>
#include <math.h>

#include <sdlgl/utilities/math.h>

#include "grid.h"


Grid::Grid(Scene *scene, float x, float y, int w, int h, int n) : 
    PhysicalEntity(scene, x, y, w, h), n(n) {

    init_points();

}


void Grid::init_points() {

    float max_dim = std::max((float)w, (float)h);
    std::pair<float, float> center = std::pair<float, float>(x + (max_dim / 2), y + (max_dim / 2));
    float spacing = max_dim / n;

    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int j = 0; j < n; j++) {
            
            std::pair<float, float> pos = std::pair<float, float>(i * spacing, j * spacing);

            // Rotate point
            pos = Math::rotate_about_point(center, pos, M_PI / 4);

            // Vertical Adjust Point
            pos.second -= (max_dim / 2) - ((float)h / 2);

            // Squash grid vertically to fit y dimension
            float dist_from_center = pos.second - (y + (float)h/2);
            pos.second = (float)h/2 + dist_from_center * h / sqrt(2*max_dim*max_dim);

            // Squash grid vertically to fit x dimension
            dist_from_center = pos.first - (x + (float)w/2);
            pos.first = (float)w/2 + dist_from_center * w / sqrt(2*max_dim*max_dim);


            points.push_back(new Point(scene, pos.first, pos.second, 3, 3, (SDL_Color){0, 0, 0, 255}));
        }
    }

}

float x_function(float time) {
    return sin(time * 0.5);
}

float y_function(float time) {
    return sin(time * 0.5);
}

void Grid::update() {

    float time = clock.get_total_delta();

    // for (unsigned int i = 0; i < n; i++) {
    //     for (unsigned int j = 0; j < n; j++) {
    //         float offset = noise.generate(i, j);
    //         // float offset = (30 * (x_function(time + (float)j/4)) + (30 * y_function(time + (float)i/4)));
    //         points[i*n + j%n]->set_offset(offset);
    //     }
    // }

    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int j = 0; j < n; j++) {
            float offset = 100 * PerlinNoise::generate(i * 0.05 + time / 1.7, j * 0.05 + time / 1.7);
            // float offset = (30 * (x_function(time + (float)j/4)) + (30 * y_function(time + (float)i/4)));
            points[i*n + j%n]->set_offset(offset);
        }
    }

}


void Grid::render() {

    for (unsigned int i = 0; i < points.size(); i++) {
        points[i]->render();
    }

}
