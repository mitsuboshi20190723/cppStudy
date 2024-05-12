/*
 *  2024.5.12
 *  hb.c
 *  ver.1.0
 *  Kunihito Mitsuboshi
 *  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */


#include <stdio.h>
#include <unistd.h>


int main()
{
	int heartbeat;

	for(heartbeat=1;;heartbeat=++heartbeat%2)
	{
		printf("%d\n", heartbeat);
		usleep(500000); /* sleep(0.5); <- error */
	}

	return(0);
}
