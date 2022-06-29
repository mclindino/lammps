#include <mpi.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <string.h>

#define PRINT_APPLICATION 0
#define PRINT_ITERATION 1

typedef enum {false, true} bool;

int     enable_pi = 0;

FILE    *out_file;
bool    extern_file = false;

double  init_time_application;
double  end_time_application;
double  total_time_application;

double  init_time_pi;
double  end_time_pi;
int     current_iteration;
double  accumulated_time;

int     stop_in = 20;
bool    early_stop = false;

void    init_application_();
void    end_application_();
void    begin_iteration_();
void    end_iteration_();
void    set_early_stop_(int);
void    print_timestep(int);
void    set_out_file(char*);
void    set_enable(int);
double  get_current_time();