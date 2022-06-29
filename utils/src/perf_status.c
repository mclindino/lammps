#include "perf_status.h"

void set_out_file(char* fileName)
{
  extern_file = true;
  
  char path[80];
  strcpy(path, "../results/"); strcat(path, fileName); strcat(path, ".csv");
  out_file = fopen(path, "w");
  fprintf(out_file, "Rank,ParamountInteration,InterationTime,AccumulatedTime\n");
}

void set_early_stop_(int number)
{
  early_stop = true;
  stop_in = number;
}

double get_current_time()
{
    struct timeval tp;
    struct timezone tzp;
    gettimeofday(&tp,&tzp);
    return ((double) tp.tv_sec + (double) tp.tv_usec * 1.e-6 );
}

void init_application_()
{
  init_time_application = get_current_time();
  current_iteration = 0;
  total_time_application = 0;
  accumulated_time = 0;
}

void end_application_()
{
  end_time_application = get_current_time();
  total_time_application = end_time_application - init_time_application;
  print_timestep(PRINT_APPLICATION);
  if (extern_file) fclose(out_file);
}

void begin_iteration_()
{
  if (enable_pi)
  {
    init_time_pi = get_current_time();
    current_iteration++;
  }
}

void end_iteration_()
{
  if (enable_pi)
  {
    int rank;
    double current_time = get_current_time();

    end_time_pi = current_time - init_time_pi;
    accumulated_time += end_time_pi;

    print_timestep(PRINT_ITERATION);
    if(early_stop && current_iteration == stop_in) {
      MPI_Finalize();
      if (extern_file) fclose(out_file);
      exit(0);
    }
  }
}

void print_timestep(int type)
{
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (extern_file == false)
  {
    switch(type)
    {
      case PRINT_ITERATION:
        if (enable_pi) printf("[PI-INFO] Paramount Iteration: Rank=%i\tCurrent Iteration=%i\tTime of iteration=%f\tAccumulated time=%f\n", rank, current_iteration, end_time_pi, accumulated_time);
        break;
      
      case PRINT_APPLICATION:
        printf("[APP-INFO] Application Info: Paramount Interations (PI)=%i\tAverage of PI=%f\tTotal time=%f\n", current_iteration, (double) accumulated_time/current_iteration, total_time_application);
        break;
    }
  } else
  {
    fprintf(out_file, "%i", rank); fprintf(out_file, ",");
    fprintf(out_file, "%i", current_iteration); fprintf(out_file, ",");
    fprintf(out_file, "%f", end_time_pi); fprintf(out_file, ",");
    fprintf(out_file, "%f", accumulated_time); fprintf(out_file, "\n");
  }

}

void set_enable(int x)
{
  enable_pi = x;
}