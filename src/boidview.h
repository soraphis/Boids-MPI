#ifndef BOIDVIEW_H
#define BOIDVIEW_H

#include "BoidModel.h"
#include "SDL/SDL.h"
#include <time.h>

class BoidView
{
public:
    BoidView(BoidModel* model);

    void init();
    void update();
    void close(bool &quit);
private:
    BoidModel* model;
    SDL_Surface* screen = NULL;
    clock_t timer;
};

#endif // BOIDVIEW_H
