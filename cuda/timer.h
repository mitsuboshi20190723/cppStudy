/*
 *  2022.2.20
 *  timer.h
 *  ver 1.0
 *  Kunihito Mitsuboshi
 *  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */

#ifndef TIMER_H
#define TIMER_H


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#include <stdio.h>
#include <time.h>
#include <sys/time.h>


struct timeval ___start, ___end;

#define ___TIME_TAKEN \
	(float)(___end.tv_sec - ___start.tv_sec) + \
	(float)(___end.tv_usec - ___start.tv_usec) / 1000000

#define TIMER_START \
	printf("Timer start!\n"); \
	gettimeofday(&___start, NULL);

#define TIMER_STOP \
	if( !gettimeofday(&___end, NULL) ) \
	printf("Timer stop.\n%f sec\n", ___TIME_TAKEN); \
	else printf("Timer error.\n");


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* TIMER_H */
