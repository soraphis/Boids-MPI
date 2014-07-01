#include "boidview.h"
#include "SDL/SDL.h"
#include "Float2.h"
#include <stdio.h>
#include <time.h>
#include "test.h"
//#include <mpi/mpi.h>
#include <mpi.h>
#include <vector>
#include <cmath>

extern field myField;
extern int tID;

BoidView::BoidView(BoidModel* model) : model(model)
{
	timer = clock();
}


void BoidView::init(){
    SDL_Init(SDL_INIT_EVERYTHING);
    screen = SDL_SetVideoMode(myField.width*3, myField.height*3, 32, SDL_SWSURFACE);
}

void BoidView::update(){


    double d = ((double)clock()-timer) / ((double)CLOCKS_PER_SEC);
    if(d < 30){
        SDL_Delay((30 - d));
    }
    timer = clock();


    Uint32 pixel = 0x0000ff00;
    Uint32 *pixels = (Uint32 *)screen->pixels;
    SDL_FillRect(screen, &screen->clip_rect, 0x00000000);
//    printf("hi... %d", model->getSwarmSize());

    for ( auto itr = model->swarm.begin(), end = model->swarm.end(); itr != end; itr++ ){
    	int x = (int)floorf(itr->getPosX());
    	int y = (int)floorf(itr->getPosY());
    	x *= 3; y *= 3;
        for(int _x = 0; _x < 3; _x++){
            for(int _y = 0; _y < 3; _y++){
                int r = (x+_x)+(y+_y)*screen->w;
                if(r >= 0 && r <= screen->w*screen->h)
                    pixels[r] = pixel;
            }
        }//*/
    }

    SDL_Flip(screen);

}

void BoidView::close(bool &quit){
    if(tID != 0)
        return;

    SDL_Event event;
    while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT){
            quit = true;
       }
    }
    if(quit){
        SDL_Quit();
    }
}
