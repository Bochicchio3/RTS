#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <sched.h>
#include <semaphore.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <string.h>
#include <pthread.h>



int main(int argc, char **argv){

   ALLEGRO_DISPLAY *display = NULL;
   ALLEGRO_BITMAP* PLANET=NULL;
   // PLANET=al_load_bitmap("rsz_moon.jpg");

   if(!al_init()) {
      fprintf(stderr, "failed to initialize allegro!\n");
      return -1;
   }

   display = al_create_display(640, 480);
   if(!display) {
      fprintf(stderr, "failed to create display!\n");
      return -1;
   }

   al_clear_to_color(al_map_rgb(0,0,0));
   // al_draw_bitmap(PLANET,0,0,0);

   // al_set_target_bitmap(PLANET);
   // // al_lock_bitmap(PLANET, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READWRITE) ;
   // for (int i = 0; i < 120; i++)
   // {
   //   for (int j = 0; j < 120; j++)
   //   {
   //       //questa va sostituita!!!
   //  al_put_pixel(i,j, al_map_rgb_f(0, 0, 0));
   //    }
   // }
   while (1) {
     /* code */al_draw_rectangle(100, 100-50, 150, 250-50, al_map_rgb_f(0, 0, 0),10);
al_flip_display();
   }
   // al_unlock_bitmap(PLANET) ;


   al_rest(10.0);

   al_destroy_display(display);
   al_destroy_bitmap(PLANET);

   return 0;
}
