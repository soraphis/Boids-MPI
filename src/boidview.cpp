//#include "boidview.h"
//#include "SDL/SDL.h"
//#include "Float2.h"
//#include <stdio.h>
//#include <time.h>
//#include "test.h"
////#include <mpi/mpi.h>
//#include <mpi.h>
//
//extern field myField;
//extern int tID;
//
//BoidView::BoidView(BoidModel* model) : model(model)
//{
//
//}
//
//
//void BoidView::init(){
//	timer = clock();
//    SDL_Init(SDL_INIT_EVERYTHING);
//    screen = SDL_SetVideoMode(myField.width*2, myField.height*2, 32, SDL_SWSURFACE);
//}
//
//void BoidView::update(){
//
//
//    double d = ((double)clock()-timer) / ((double)CLOCKS_PER_SEC);
//    if(d < 6.25)
//        SDL_Delay((6.25 - d));
//
//
//    timer = clock();
//
//
//    Uint32 pixel = 0x00ff0000;
//    Uint32 *pixels = (Uint32 *)screen->pixels;
//    SDL_FillRect(screen, &screen->clip_rect, 0x00000000);
////    printf("hi... %d", model->getSwarmSize());
//    for(int i = 0; i < model->getSwarmSize(); i++){
//        Float2 pos = model->swarm[i].getPos();
//        /*
//        int p = (int)(pos.getX()+pos.getY()*screen->w);
//        if(p >= 0 && p <= screen->w*screen->h)
//            pixels[p] = pixel;
//        /*/
//        int x = pos.getX()*2;
//        int y = pos.getY()*2;
//        for(int _x = 0; _x < 2; _x++){
//            for(int _y = 0; _y < 2; _y++){
//                int r = (x+_x)+(y+_y)*screen->w;
//                if(r >= 0 && r <= screen->w*screen->h)
//                    pixels[r] = pixel;
//            }
//        }//*/
//    }
//
//    SDL_Flip(screen);
//
//}
//
//void BoidView::close(bool &quit){
//    if(tID != 0)
//        return;
//
//    SDL_Event event;
//    while(SDL_PollEvent(&event)){
//        if(event.type == SDL_QUIT){
//            quit = true;
//       }
//    }
//    if(quit){
//        SDL_Quit();
//    }
//}
