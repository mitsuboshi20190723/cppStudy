/*
 *  2023.11.22
 *  timer.h
 *  ver.2.2
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

struct timespec ___start={0,0}, ___end;

#define ___TIME_TAKEN \
	___end.tv_sec - ___start.tv_sec, \
	___end.tv_nsec - ___start.tv_nsec

#define TIMER_START \
	printf("Timer start!\n"); \
	clock_gettime(CLOCK_MONOTONIC, &___start);

#define TIMER_STOP \
	if( !clock_gettime(CLOCK_MONOTONIC, &___end) ) \
	printf("Timer stop.\n%010ld.%09ld sec\n", ___TIME_TAKEN); \
	else printf("Timer error.\n");


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* TIMER_H */
