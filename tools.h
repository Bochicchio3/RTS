
#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED


// #include <allegro.h>
#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

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






//SHOULD CHANGE THE ORDER, STD FIRSTS

/*################DEFINE USER INTERFACE WINDOWS##############*/

#define WINDOW_X 1500
#define WINDOW_Y 1000
#define UNIVERSE_X 1200
#define UNIVERSE_Y 600
#define TELESCOPES_REGION_X 300
#define TELESCOPES_REGION_Y 600
#define TELESCOPE_IMAGES_REGION_x 1200
#define TELESCOPE_IMAGES_REGION_Y 200
#define INSTRUCTION_X 1500
#define INSTRUCTION_Y 100
#define PROCESSED_IMAGE_X 300
#define PROCESSED_IMAGE_Y 200
#define KEY_SEEN     1
#define KEY_RELEASED 2
#define MAX_TELESCOPES 6
#define CAMERA_ACQUISITION_WIDHT 150
#define CAMERA_ACQUISITION_HEIGHT 150
#define PLANET_RADIUS 40


//DEFINISCO I PARAMEMTRI DELLE TASK
// TASK DRAWING, TASK INPUT, TASK TELESCOPI CONTROLLO ED ACQUISIZIONE,TASK PIANETA, TASK IMAGE PROCESSING
//TASK PIANETA
#define PLANET_ID 1
#define PLANET_PERIOD 20
#define PLANET_PRIORITY 20
#define PLANET_DEADLINE 10

//TASK TELESCOPE
#define TELESCOPE_ID 2
#define TELESCOPE_PERIOD 20
#define TELESCOPE_PRIORITY 20
#define TELESCOPE_DEADLINE 10

//TASK IMAGE_ACQUISITION
#define IMAGE_ACQUISITION_ID 2
#define IMAGE_ACQUISITION_PERIOD 20
#define IMAGE_ACQUISITION_PRIORITY 20
#define IMAGE_ACQUISITION_DEADLINE 10

//TASK IMAGE_PROCESSING
#define IMAGE_PROCESSING_ID 3
#define IMAGE_PROCESSING_PERIOD 20
#define IMAGE_PROCESSING_PRIORITY 20
#define IMAGE_PROCESSING_DEADLINE 10
//TASK DRAWING
#define GRAPHIC_TASK_ID 4
#define GRAPHIC_TASK_PERIOD 20
#define GRAPHIC_TASK_PRIORITY 20
#define GRAPHIC_TASK_DEADLINE 10

// TASK INPUT
#define INPUT_ID 5
#define INPUT_PERIOD 20
#define INPUT_PRIORITY 20
#define INPUT_DEADLINE 10

//DEFINISCO LE STRUTTURE NECESSARIE

struct planet_status {
int PLANET_POSITION_X;
int PLANET_POSITION_Y;
int PLANET_VELOCITY_X;
int PLANET_VELOCITY_y;
}  PIANETA_1;

// 
// struct sched_param {
// int sched_priority;
// } my_par;


struct      task_par {
    int     arg;          // argument of the task
    int     period;       // period of the task
    int     deadline;     // relative deadline of the task
    int     priority;     // priority of the task
    int     dmiss;        // number of deadline misses
    struct  timespec at;  // absolute activation time
    struct  timespec dl;  // absolute deadline
};

// enum struct task_param{
// DRAW
// PLANET
// TELESCOPE_AND_CONTROL
// IMAGE_PROCESSING
//
//
// }

// void init_graphics_task_param(struct task_par *task_parameter);
// void init_image_processing_task_param(struct task_par *task_parameter);
// void init_telescope_and_control_task_param(struct task_par *task_parameter,int telescope_number);
// void init_planet_task_param(struct task_par *task_parameter);
// void init_input_task_param(struct task_par *task_parameter);
//
// void init_graphic_thread()
// void init_image_processing_thread()
// void init_telescope_and_control_thread()
// void init_planet_thread()
// void init_input_thread()
//
// void graphic_task()
// void image_processing_task()
// void telescope_and_control_task()
// void planet_task()
// void input_task()



struct telescopes_status{
int telescope_id;
bool init;
int telescope_position_x;
// int vel_x;
// int vel_y;
int telescope_position_y;
ALLEGRO_BITMAP* TELESCOPE_IMAGE;
ALLEGRO_BITMAP* TELESCOPE;
} telescope[MAX_TELESCOPES];

struct planet_image{
int CAMERA_ACQUISITION [CAMERA_ACQUISITION_WIDHT][CAMERA_ACQUISITION_HEIGHT];
};


enum BOUNCER_TYPE {
    BT_PLANET
};

typedef struct BOUNCER
{
    float x, y;
    float dx, dy;
    int type;
} BOUNCER;


bool done;
bool redraw;
int a;

/*################FUNCTIONS#############*/
void get_random_number();
void initialize_graphic_and_keyboard();
void draw_user_interface();
void moveBall();
void planet_task();
void must_init(bool test, const char *description);
bool must_initt(bool test);
void al_destroy_everything();
void initialize_planet();
void Bouncer_Handler();
void Create_Telescope();
void IMAGE_ACQUISITION();
void Image_Processing();
void PID_controller_telescopes();
void Get_User_Input();
void task_param_assignement();

void initialize_planet_and_other_stuff();



void time_add_ms(struct timespec*, int);
void wait_for_period (struct task_par*);
void set_period(struct task_par*);
void time_copy(struct timespec*, struct timespec);
int deadline_miss(struct task_par*);
int time_cmp(struct timespec, struct timespec);

/*################GLOBAL VARIABLES###########*/

// BITMAP *background;
// BITMAP *bmp;
//
// int width = 220;//width of box
// int height = 440;//height of box
// int radius = 5;//radius of ball
//
// int x = 110;//initial position of ball
// int y = 220;//initial position of ball
//
// int tempX;
// int tempY;
//
// //Keep track of direction of motion here.
// //0= northwest 1 = southwest, 2 = northeast,
// //3 = southeast
// int dir;
//
//
ALLEGRO_TIMER* timer;
ALLEGRO_EVENT_QUEUE* queue;
ALLEGRO_DISPLAY* disp;
ALLEGRO_FONT* font;

ALLEGRO_BITMAP* PLANET;
ALLEGRO_BITMAP* BACKGROUND_EARTH;
ALLEGRO_BITMAP* BACKGROUND;


ALLEGRO_BITMAP* CHANDRA;
ALLEGRO_BITMAP* HUBBLE;
ALLEGRO_BITMAP* GRAN_TELESCOPIO_CANARIAS;
ALLEGRO_BITMAP* LARGE_BINOCULAR_TELESCOPE;
ALLEGRO_BITMAP* GIANT_MAGELLAN_TELESCOPE;
ALLEGRO_BITMAP* KECK_I;
ALLEGRO_BITMAP* SCREEN;

ALLEGRO_BITMAP* TELESCOPE_IMAGE_DEFINITIVE[6];
ALLEGRO_BITMAP* PROCESSED_IMAGE;
ALLEGRO_BITMAP* PROCESSED_IMAGE_trick;

unsigned char key[ALLEGRO_KEY_MAX];



ALLEGRO_EVENT event;
ALLEGRO_KEYBOARD_STATE ks;

BOUNCER PIANETA;
BOUNCER* thispianeta;

int telescope_counter;
int position_correction[6];
int velocity_correction[6];
int telescope_selector;



#endif // TOOLS_H_INCLUDED
