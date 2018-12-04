#include "tools.h"



int main() {


  initialize_graphic_and_keyboard();


  while(1)
  {//MI ASPETTO CHE LA GESTIONE REAL TIME VADA QUI??
      al_wait_for_event(queue, &event);
      Bouncer_Handler();
      Get_User_Input();
      PID_controller_telescopes();
      if(done)
          break;

      if(redraw && al_is_event_queue_empty(queue))
      {
        ALLEGRO_VERTEX v[4];
        al_clear_to_color(al_map_rgb(0, 0, 0)); //BACKGROUND

         draw_task();

         pthread_create (&planet,NULL, task, NULL);
        // IMAGE_ACQUISITION();

        // if (a==0)
        // {
        //   a++;
        //   IMAGE_ACQUISITION();
        //   // TELESCOPE_IMAGE_DEFINITIVE[telescope_counter]=al_create_bitmap(CAMERA_ACQUISITION_WIDHT,CAMERA_ACQUISITION_HEIGHT);
        //   // TELESCOPE_IMAGE_DEFINITIVE[telescope_counter]=al_load_bitmap("image_telescope.jpg");
        //   // must_init(TELESCOPE_IMAGE_DEFINITIVE[telescope_counter],"telescope");
        // }
        // // Image_Processing();


        al_flip_display();

        redraw = false;
      }
  }

  al_destroy_everything();
  return 0;
}
