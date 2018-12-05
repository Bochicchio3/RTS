#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <sched.h>
#include <stdlib.h>

// task parameter
#define task_ID 1
#define task_PERIOD 20
#define task_PRIORITY 20
#define task_DEADLINE 1



struct      task_par {
    int     arg;          // argument of the task
    int     period;       // period of the task
    int     deadline;     // relative deadline of the task
    int     priority;     // priority of the task
    int     dmiss;        // number of deadline misses
    struct  timespec at;  // absolute activation time
    struct  timespec dl;  // absolute deadline
};

void time_copy(struct timespec *td, struct timespec ts){

    td->tv_sec = ts.tv_sec;
    td->tv_nsec = ts.tv_nsec;
}


void time_add_ms(struct timespec *t, int ms){

    t->tv_sec += ms/1000;
    t->tv_nsec += (ms%1000)*1000000;

    if (t->tv_nsec > 1000000000){
        t->tv_nsec -= 1000000000;
        t->tv_sec += 1;
    }
}
int time_cmp(struct timespec t1, struct timespec t2){

    if (t1.tv_sec > t2.tv_sec) return 1;
    if (t1.tv_sec < t2.tv_sec) return -1;
    if (t1.tv_nsec > t2.tv_nsec) return 1;
    if (t1.tv_nsec < t2.tv_nsec) return -1;
    return 0;
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




void init_task_param(struct task_par *task_parameter){
task_parameter->period=task_PERIOD;
task_parameter->deadline=task_DEADLINE;
task_parameter->priority=task_PRIORITY;
}


void init_attributes(pthread_attr_t * attr, struct sched_param* par, int priority, int scheduler){
    pthread_attr_init(attr);
    pthread_attr_setinheritsched(attr, PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setschedpolicy    (attr, scheduler);
    par->sched_priority = priority;
    pthread_attr_setschedparam(attr, par);
}


void* graphic_task(void* str_arg){
struct task_par* str;


    str = (struct task_par*) str_arg;
    set_period(str);

    while (1)
        {
        // do task
        printf("x increment finished\n");
        sleep(1);

        if(deadline_miss(str)) printf("ho mancato la deadline");
        wait_for_period(str);
        }
}

// void *inc_x(void *x_void_ptr)
// {
//
// /* increment x to 100 */
// int *x_ptr = (int *)x_void_ptr;
// while(++(*x_ptr) < 100);
//
// printf("x increment finished\n");
//
// /* the function must return something - NULL will do */
// return NULL;
// }



void init_thread(pthread_t* thread_id){
pthread_attr_t      task_attr;
struct sched_param  task_par;
struct task_par*    thread_task_param;

    thread_task_param = (struct task_par*)malloc(sizeof(struct task_par));
    init_task_param (thread_task_param);
    init_attributes(&task_attr, &task_par, task_PRIORITY, SCHED_FIFO);
    pthread_create(thread_id, &task_attr, graphic_task,(void*) thread_task_param);
}




/* this function is run by the second thread */


int main()
{

pthread_t thread;


init_thread(&thread);


pthread_join(thread, NULL);

return 0;

// Distruggere l'attributo?????
}
