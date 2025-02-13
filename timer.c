#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/time.h>

#include "timer.h"


double sinceEpoch(){
	struct timeval tv;
	gettimeofday(&tv, NULL);
	time_t seconds = tv.tv_sec;
	useconds_t micros = tv.tv_usec;
	
	double time = seconds + micros / 1e6;
	return time;
}

double interval(double time){
	return sinceEpoch() - time;	
}