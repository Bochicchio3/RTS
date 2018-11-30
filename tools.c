#include "tools.h"




//DO NOT INCLUDE IN .H ALL THE HEADERS THAT SHOULD ONLY GO IN .C
//BUT I STILL HAVE TO FIGURE OUT WHICH HEADERS ARE NEEDED IN .C ONLY

void must_init(bool test, const char *description)
{
    if(test) return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}

bool must_initt(bool test)
{
    if(test){ return true;}
    // printf("couldn't initialize");
    return false;
}

//
void  initialize_graphic_and_keyboard(){

    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");
    al_install_mouse();
    must_init(al_install_mouse(), "mouse");

    timer = al_create_timer(1.0 / 30.0);
    must_init(timer, "timer");

    queue = al_create_event_queue();
    must_init(queue, "queue");

    disp = al_create_display(WINDOW_X, WINDOW_Y);
    must_init(disp, "display");

    font = al_create_builtin_font();
    must_init(font, "font");
    // ptask_init(SCHED_FIFO);
    al_start_timer(timer);


    must_init(al_init_primitives_addon(), "primitives");

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    must_init(al_init_image_addon(), "image addon");
    BACKGROUND = al_load_bitmap("universe.jpg");
    BACKGROUND_EARTH = al_load_bitmap("EARTH.jpg");
    PLANET=al_load_bitmap("rsz_moon.jpg");
    CHANDRA=al_load_bitmap("chandra.jpg");
    HUBBLE=al_load_bitmap("hubble.jpg");
    PROCESSED_IMAGE_trick=al_load_bitmap("iprocessed.bmp");
    al_convert_mask_to_alpha(HUBBLE, al_map_rgb(0,0,0));
    al_convert_mask_to_alpha(BACKGROUND_EARTH, al_map_rgb(0,0,0));
    al_convert_mask_to_alpha(PLANET, al_map_rgb(0,0,0));
    al_convert_mask_to_alpha(CHANDRA, al_map_rgb(0,0,0));

    must_init(PLANET,"planet");
    must_init(BACKGROUND, "background");
    initialize_planet_and_other_stuff();
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer));

    return;
}

void al_destroy_everything(){

  //AGGIUNGERE LE BITMAP DA DISTRUGGERE
  al_destroy_bitmap(BACKGROUND);
  al_destroy_bitmap(PLANET);
  al_destroy_bitmap(HUBBLE);
  al_destroy_bitmap(CHANDRA);
  al_destroy_font(font);
  al_destroy_display(disp);
  al_destroy_timer(timer);
  al_destroy_event_queue(queue);
}

void initialize_planet_and_other_stuff(){
  thispianeta = &(PIANETA);
  thispianeta->x = rand() % ((UNIVERSE_X-2*PLANET_RADIUS)+PLANET_RADIUS);
  thispianeta->y = rand() % ((UNIVERSE_Y-2*PLANET_RADIUS)+PLANET_RADIUS);
  // thispianeta->dx = ((((float)rand()) / RAND_MAX) - 0.5) * 2 * 4;
  // thispianeta->dy = ((((float)rand()) / RAND_MAX) - 0.5) * 2 * 4;
  thispianeta->dx =3;
  thispianeta->dy =3;
  thispianeta->type = 0;
  memset(key, 0, sizeof(key));
  telescope_selector=1;
for (int i = 0; i < 6; i++) {
  telescope[i].init=false;
  position_correction[i]=31;
  velocity_correction[i]=3;
}

  thispianeta = &(PIANETA);
  telescope_counter=0;
  int a=0;
  done = false;
  redraw = true;
}


void   draw_task(){

    al_draw_bitmap(BACKGROUND, 0, 0, 0);
    al_draw_bitmap(BACKGROUND_EARTH, 0, 450, 0);
    al_draw_bitmap(PLANET, thispianeta->x, thispianeta->y, 0);
    al_draw_bitmap(CHANDRA, 850, 450, 0);
    al_draw_bitmap(HUBBLE, 50, 450, 0);
    al_draw_text(font, al_map_rgb(255, 255, 255), 25, 960, 0, "Premere il tasto 'D' per aggiungere \n un telescopio, seleziona il telescopio tramite i tasti 'SU', 'GIU', 'DESTRA', 'SINISTRA' per selezionare un telescopio e usare i tasti 'P'");
    // al_draw_text(font, al_map_rgb(255, 255, 255), 25, 980, 0, "il numero di telescopi e");
    al_draw_textf(font,al_map_rgb(255, 100, 200),25,980,0, "Il numero di telescopi e': %d, A e B correzione posizione %d, C e D correzione velocita %d, il telescopio selezionato e %d", telescope_counter,position_correction[telescope_selector],velocity_correction[telescope_selector],telescope_selector);
  for (int counter = 0; counter <= telescope_counter; counter++)
    {

            switch (counter)
            {
                case 0:   {if (telescope[counter].init==true)
                {      al_draw_rectangle(telescope[counter].telescope_position_x, telescope[counter].telescope_position_y, telescope[counter].telescope_position_x+CAMERA_ACQUISITION_WIDHT, telescope[counter].telescope_position_y+CAMERA_ACQUISITION_HEIGHT, al_map_rgb_f(1, 0, 0),3);
                al_draw_bitmap(TELESCOPE_IMAGE_DEFINITIVE[counter], 1100, 50, 0);
                al_draw_textf(font,al_map_rgb(255, 0, 0),1100,25,0, "correzione posizione %d",position_correction[counter]);
                al_draw_textf(font,al_map_rgb(255, 0, 0),1100,35,0, "correzione velocita %d ",velocity_correction[counter]);
}}
                case 1:  { if (telescope[counter].init==true && counter==1)
                {     al_draw_rectangle(telescope[counter].telescope_position_x, telescope[counter].telescope_position_y, telescope[counter].telescope_position_x+CAMERA_ACQUISITION_WIDHT, telescope[counter].telescope_position_y+CAMERA_ACQUISITION_HEIGHT, al_map_rgb_f(0, 0, 1),3);
                  al_draw_bitmap(TELESCOPE_IMAGE_DEFINITIVE[counter], 1300, 50, 0);
                  al_draw_textf(font,al_map_rgb(0, 0, 255),1300,25,0, "correzione posizione %d",position_correction[counter]);
                  al_draw_textf(font,al_map_rgb(0, 0, 255),1300,35,0, "correzione velocita %d ",velocity_correction[counter]);
                }}
                case 2:   {if (telescope[counter].init==true && counter==2)
                {      al_draw_rectangle(telescope[counter].telescope_position_x, telescope[counter].telescope_position_y, telescope[counter].telescope_position_x+CAMERA_ACQUISITION_WIDHT, telescope[counter].telescope_position_y+CAMERA_ACQUISITION_HEIGHT, al_map_rgb_f(1, 1, 0),3);
                     al_draw_bitmap(TELESCOPE_IMAGE_DEFINITIVE[counter], 1100, 250, 0);
                     al_draw_textf(font,al_map_rgb(255, 255, 0),1100,225,0, "correzione posizione %d",position_correction[counter]);
                     al_draw_textf(font,al_map_rgb(255, 255, 0),1100,235,0, "correzione velocita %d ",velocity_correction[counter]);
}}
                case 3:   {if (telescope[counter].init==true && counter==3)
                {       al_draw_rectangle(telescope[counter].telescope_position_x, telescope[counter].telescope_position_y, telescope[counter].telescope_position_x+CAMERA_ACQUISITION_WIDHT, telescope[counter].telescope_position_y+CAMERA_ACQUISITION_HEIGHT, al_map_rgb_f(1, 0, 1),3);
                    al_draw_bitmap(TELESCOPE_IMAGE_DEFINITIVE[counter], 1300, 250, 0);
                    al_draw_textf(font,al_map_rgb(255, 0, 255),1300,225,0, "correzione posizione %d",position_correction[counter]);
                    al_draw_textf(font,al_map_rgb(255, 0, 255),1300,235,0, "correzione velocita %d ",velocity_correction[counter]);
}}
                case 4:  {if (telescope[counter].init==true && counter==4)
                {        al_draw_rectangle(telescope[counter].telescope_position_x, telescope[counter].telescope_position_y, telescope[counter].telescope_position_x+CAMERA_ACQUISITION_WIDHT, telescope[counter].telescope_position_y+CAMERA_ACQUISITION_HEIGHT, al_map_rgb_f(0, 1, 1),3);
                  al_draw_bitmap(TELESCOPE_IMAGE_DEFINITIVE[counter], 1100, 450, 0);
                  al_draw_textf(font,al_map_rgb(0, 255, 255),1100,425,0, "correzione posizione %d",position_correction[counter]);
                  al_draw_textf(font,al_map_rgb(0, 255, 255),1100,435,0, "correzione velocita %d ",velocity_correction[counter]);
}}
                case 5:  {if (telescope[counter].init==true && counter==5)
                {        al_draw_rectangle(telescope[counter].telescope_position_x, telescope[counter].telescope_position_y, telescope[counter].telescope_position_x+CAMERA_ACQUISITION_WIDHT, telescope[counter].telescope_position_y+CAMERA_ACQUISITION_HEIGHT, al_map_rgb_f(1, 1, 1),3);
                   al_draw_bitmap(TELESCOPE_IMAGE_DEFINITIVE[counter], 1300, 450, 0);
                   al_draw_textf(font,al_map_rgb(255, 255, 255),1300,425,0, "correzione posizione %d",position_correction[counter]);
                   al_draw_textf(font,al_map_rgb(255, 255, 255),1300,435,0, "correzione velocita %d ",velocity_correction[counter]);
}}
                // case 1:  al_save_bitmap("image_telescope1.bmp",telescope[i].TELESCOPE_IMAGE);
                // case 2:  al_save_bitmap("image_telescope2.bmp",telescope[i].TELESCOPE_IMAGE);
                // case 3:  al_save_bitmap("image_telescope3.bmp",telescope[i].TELESCOPE_IMAGE);
                // case 4:  al_save_bitmap("image_telescope4.bmp",telescope[i].TELESCOPE_IMAGE);
                // case 5:  al_save_bitmap("image_telescope5.bmp",telescope[i].TELESCOPE_IMAGE);

        }
         // al_draw_bitmap(TELESCOPE_IMAGE_DEFINITIVE[telescope_counter], 1100, 850, 0);
    }
    al_draw_rectangle(1100, 100-50, 1250, 250-50, al_map_rgb_f(0, 0, 0),10);
    al_draw_rectangle(1300, 100-50, 1450, 250-50, al_map_rgb_f(0, 0, 0),10);
    al_draw_rectangle(1100, 300-50, 1250, 450-50, al_map_rgb_f(0, 0, 0),10);
    al_draw_rectangle(1300, 300-50, 1450, 450-50, al_map_rgb_f(0, 0, 0),10);
    al_draw_rectangle(1100, 500-50, 1250, 650-50, al_map_rgb_f(0, 0, 0),10);
    al_draw_rectangle(1300, 500-50, 1450, 650-50, al_map_rgb_f(0, 0, 0),10);
    al_draw_rectangle(1300, 650, 1450, 800, al_map_rgb_f(0.5, 1, 0.5),5);

   al_draw_bitmap(PROCESSED_IMAGE_trick, 1300, 650, 0);
    return;
}



void Bouncer_Handler()
{
  switch(event.type)
  {
      case ALLEGRO_EVENT_TIMER:

        thispianeta->x += thispianeta->dx;
        thispianeta->y += thispianeta->dy;

        //DA AGGIUSTARE I RAGGI OPPORTUNAMENTE

        if(thispianeta->x < 0) // BOUNCE SULLA PARETE DI SINISTRA
        {
            thispianeta->x  *= -1;
            thispianeta->dx *= -1;
        }
        if(thispianeta->x > 640) // BOUNCE SULLA PARETE DI DESTRA
        {
            thispianeta->x -= (thispianeta->x - 640);
            thispianeta->dx *= -1;
        }
        if(thispianeta->y < 0) // BOUNCE SULLA PARETE IN ALTO
        {
            thispianeta->y  *= -1;
            thispianeta->dy *= -1;
        }
        if(thispianeta->y > 250) // BOUNCE SULLA PARETE IN BASSO
        {
            thispianeta->y -= (thispianeta->y - 250);
            thispianeta->dy *= -1;
        }

        redraw = true;
        break;

//      case ALLEGRO_EVENT_KEY_DOWN:
      case ALLEGRO_EVENT_DISPLAY_CLOSE:
          done = true;
          break;
    }
}



void IMAGE_ACQUISITION()
{
   for (int i = 0; i <telescope_counter; i++)
   {

     if (telescope[i].init==false){
      telescope[i].telescope_position_y= rand() % 760;
      telescope[i].telescope_position_x= rand() % 900;}
      telescope[i].TELESCOPE_IMAGE=al_create_bitmap(CAMERA_ACQUISITION_WIDHT,CAMERA_ACQUISITION_HEIGHT);
      TELESCOPE_IMAGE_DEFINITIVE[i]=al_create_bitmap(CAMERA_ACQUISITION_WIDHT,CAMERA_ACQUISITION_HEIGHT);

      telescope[i].init=true;

      //NAscondere i telescopi dall-acqiusizione!!!!!!!!!!!
      telescope[i].TELESCOPE_IMAGE= al_create_sub_bitmap(al_get_backbuffer(disp),telescope[i].telescope_position_x, telescope[i].telescope_position_y, CAMERA_ACQUISITION_WIDHT,CAMERA_ACQUISITION_HEIGHT);
      // al_save_bitmap("image.bmp",al_create_sub_bitmap(al_get_backbuffer(disp),telescope[i].telescope_position_x, telescope[i].telescope_position_y, CAMERA_ACQUISITION_WIDHT,CAMERA_ACQUISITION_HEIGHT));

      switch (i)
        {
            case 0: { al_save_bitmap("image_telescope0.bmp",telescope[i].TELESCOPE_IMAGE);
                    TELESCOPE_IMAGE_DEFINITIVE[i]=al_load_bitmap("image_telescope0.bmp");
                    break;}
            case 1:  {al_save_bitmap("image_telescope1.bmp",telescope[i].TELESCOPE_IMAGE);
                    TELESCOPE_IMAGE_DEFINITIVE[i]=al_load_bitmap("image_telescope1.bmp");
                    break;}
            case 2:  {al_save_bitmap("image_telescope2.bmp",telescope[i].TELESCOPE_IMAGE);
                    TELESCOPE_IMAGE_DEFINITIVE[i]=al_load_bitmap("image_telescope2.bmp");
                    break;}
            case 3: { al_save_bitmap("image_telescope3.bmp",telescope[i].TELESCOPE_IMAGE);
                    TELESCOPE_IMAGE_DEFINITIVE[i]=al_load_bitmap("image_telescope3.bmp");
                    break;}
            case 4:  {al_save_bitmap("image_telescope4.bmp",telescope[i].TELESCOPE_IMAGE);
                    TELESCOPE_IMAGE_DEFINITIVE[i]=al_load_bitmap("image_telescope4.bmp");
                    break;}
            case 5:  {al_save_bitmap("image_telescope5.bmp",telescope[i].TELESCOPE_IMAGE);
                    TELESCOPE_IMAGE_DEFINITIVE[i]=al_load_bitmap("image_telescope5.bmp");
                    break;}

        }

    }
}


void Image_Processing()
{

  //CAPIRE COME LOCKARE LE IMMAGINI
  al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_ONE);
  PROCESSED_IMAGE=al_create_bitmap(CAMERA_ACQUISITION_WIDHT,CAMERA_ACQUISITION_HEIGHT);
// fare la media pixel per pixel

  al_set_target_bitmap(PROCESSED_IMAGE);
  al_lock_bitmap(PROCESSED_IMAGE, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READWRITE) ;
for (int i = 0; i < CAMERA_ACQUISITION_WIDHT; i++)
{
    for (int j = 0; j < CAMERA_ACQUISITION_HEIGHT; j++)
    {
      for (int k = 0; k < telescope_counter; k++)
      {
        //questa va sostituita!!!
        al_put_blended_pixel(i,j, al_get_pixel(TELESCOPE_IMAGE_DEFINITIVE[k],i,j));
      }

    }
}
al_unlock_bitmap(PROCESSED_IMAGE) ;
al_save_bitmap("iprocessed.bmp",PROCESSED_IMAGE);
return;
}


void PID_controller_telescopes() {
    for (int i = 0; i <= telescope_counter; i++)
    {
        switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:
            if (telescope[i].init==true) {
            if (telescope[i].telescope_position_x<=thispianeta->x+position_correction[i]){telescope[i].telescope_position_x+= velocity_correction[i];}
               else{telescope[i].telescope_position_x-= velocity_correction[i];}
           if (telescope[i].telescope_position_y<=position_correction[i]+thispianeta->y){telescope[i].telescope_position_y+=velocity_correction[i];}
              else{telescope[i].telescope_position_y-= velocity_correction[i];}
        }


              redraw = true;
              break;

            // case ALLEGRO_EVENT_KEY_DOWN:
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
          }
    }

}
void Get_User_Input(){
  switch(event.type)
  {
  case ALLEGRO_EVENT_TIMER:
       if(key[ALLEGRO_KEY_UP])
       {IMAGE_ACQUISITION();}
       if(key[ALLEGRO_KEY_DOWN])
       {  Image_Processing();}
       if(key[ALLEGRO_KEY_LEFT])
       {  if(telescope_counter<5) telescope_counter++;}
       if(key[ALLEGRO_KEY_RIGHT])
       {  if(telescope_counter>-1) {telescope[telescope_counter].init=false; if(telescope_counter!=0){telescope_counter--;}}}
       if(key[ALLEGRO_KEY_A])
       { position_correction[telescope_selector]++;}
       if(key[ALLEGRO_KEY_S])
       { position_correction[telescope_selector]--;}
       if(key[ALLEGRO_KEY_D])
       { velocity_correction[telescope_selector]++;}
       if(key[ALLEGRO_KEY_F])
       { velocity_correction[telescope_selector]--;}
       if(key[ALLEGRO_KEY_1])
       { telescope_selector=0;}
       if(key[ALLEGRO_KEY_2])
       { telescope_selector=1;}
       if(key[ALLEGRO_KEY_3])
        { telescope_selector=2;}
       if(key[ALLEGRO_KEY_4])
        { telescope_selector=3;}
       if(key[ALLEGRO_KEY_5])
        { telescope_selector=4;}
       if(key[ALLEGRO_KEY_6])
        { telescope_selector=5;}

      if(key[ALLEGRO_KEY_ESCAPE])
           done = true;

       for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
           key[i] &= KEY_SEEN;

       redraw = true;
       break;

   case ALLEGRO_EVENT_KEY_DOWN:
       key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
       break;
   case ALLEGRO_EVENT_KEY_UP:
       key[event.keyboard.keycode] &= KEY_RELEASED;
       break;
     }
}


//------------------------------------------------------------------------------
// TIME_ADD_MS: adds a value ms expressed in milliseconds to the time variable
// pointed by t
//------------------------------------------------------------------------------

void time_add_ms(struct timespec *t, int ms){

    t->tv_sec += ms/1000;
    t->tv_nsec += (ms%1000)*1000000;

    if (t->tv_nsec > 1000000000){
        t->tv_nsec -= 1000000000;
        t->tv_sec += 1;
    }
}

//------------------------------------------------------------------------------
// WAIT_FOR_PERIOD:suspends the calling thread until the next activation and,
// when awaken,updates activation time
//------------------------------------------------------------------------------

void wait_for_period (struct task_par *tp){

    clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME,&(tp->at), NULL);
    time_add_ms(&(tp->at), tp->period);
    time_add_ms(&(tp->dl), tp->period);
}


//------------------------------------------------------------------------------
// SET_PERIOD: reads the current time and computes the next activation time and
// the absolute deadline of the task
//------------------------------------------------------------------------------

void set_period(struct task_par *tp){

struct timespec t;

    clock_gettime(CLOCK_MONOTONIC, &t);
    time_copy(&(tp->at), t);
    time_copy(&(tp->dl), t);
    time_add_ms(&(tp->at), tp->period);
    time_add_ms(&(tp->dl), tp->deadline);
}

//------------------------------------------------------------------------------
// TIME_COPY: copies a source time variable ts in a destination variable
// pointed by td
//------------------------------------------------------------------------------

void time_copy(struct timespec *td, struct timespec ts){

    td->tv_sec = ts.tv_sec;
    td->tv_nsec = ts.tv_nsec;
}

//------------------------------------------------------------------------------
// DEADLINE_MISS: increments the value of dmiss when e deadline is missed
//------------------------------------------------------------------------------

int deadline_miss(struct task_par *tp){

struct timespec now;

    clock_gettime(CLOCK_MONOTONIC, &now);

    if (time_cmp(now, tp->dl)>0) {
        tp->dmiss++;
        return 1;
    }
    return 0;
}

//------------------------------------------------------------------------------
// TIME_CMP: compares two time variables t1 and t2 and returns 0 if
// they are equal, 1 if t1>t2, -1 if t1<t2
//------------------------------------------------------------------------------

int time_cmp(struct timespec t1, struct timespec t2){

    if (t1.tv_sec > t2.tv_sec) return 1;
    if (t1.tv_sec < t2.tv_sec) return -1;
    if (t1.tv_nsec > t2.tv_nsec) return 1;
    if (t1.tv_nsec < t2.tv_nsec) return -1;
    return 0;
}

// COSE DA FARE>
// 1) INIZIARE A DEFINIRE LE TASK REAL TIME
// 2)CONTROLLO DECENTE DELLE IMMAGINI DI ALLEGRO E DELLE OPERAZIONI PIXEL WISE
// 3) AGGIUNGERE RUMORE AD I TELESCOPI
// 4) IMPLEMENTARE UN CONTROLLORE PID DIGNITOSO
// 5) CAPIRE LA GESTIONE DI TASK E DEL TEMPO
// 6) CAPIRE FUNZIONE DI MUTEX LOCK ECC...
// 7) REVISIONE PESANTE DEL CODICE PER COMPLIANCE AGLI standard
// 8) INIZIARE A SCRIVERE IL PROGETTO
// 9) INCONTRO CON BUTTAZZO PER VERIFICA
