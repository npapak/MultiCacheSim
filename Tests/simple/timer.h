#ifndef _APPS_TIMER_H_
#define _APPS_TIMER_H_

#include <sys/time.h>

static unsigned long _timer_h_G_starttime;
static unsigned long _timer_h_G_endtime;

static void START_TIME(void)
{
  struct timeval time;
  gettimeofday(&time, NULL);
  _timer_h_G_starttime = time.tv_usec + time.tv_sec * 1000000;
}

static void STOP_TIME(void)
{
  struct timeval time;
  gettimeofday(&time, NULL);
  _timer_h_G_endtime = time.tv_usec + time.tv_sec * 1000000;
}


static unsigned long GET_TIME(void)
{
  return _timer_h_G_endtime - _timer_h_G_starttime;
}



static void PRINT_CPUS_AND_TIME(void)
{
  printf("%lu us\n", GET_TIME());
}

static void PRINT_TIME(void)
{
  printf("Application time: %.3lf ms\n", (double)GET_TIME()/1000.0);
}

#endif
