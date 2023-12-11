/*
 *  2023.12.12
 *  joycon.c
 *  ver 0.9
 *  Kunihito Mitsuboshi
 *  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */


#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/joystick.h>


#define JOY_DEV "/dev/input/js0"


int main(int argc, char *argv[])
{
	int i;
	int joy, num_of_axis, num_of_buttons;
	char name_of_joycon[80];
	int joy_a[16];
	int joy_b[16];
	struct js_event js;

	joy = open(JOY_DEV, O_RDONLY);

	ioctl(joy, JSIOCGAXES, &num_of_axis);
	ioctl(joy, JSIOCGBUTTONS, &num_of_buttons);
	ioctl(joy, JSIOCGNAME(80), &name_of_joycon);

	for(i=0; i < num_of_axis; i++) joy_a[i] = 0;
	for(i=0; i < num_of_buttons; i++) joy_b[i] = 0;


	while(1)
	{
		read(joy, &js, sizeof(js));

		switch (js.type & ~JS_EVENT_INIT)
		{
		case JS_EVENT_AXIS :
			joy_a[(int)js.number] = js.value;
			break;
		case JS_EVENT_BUTTON :
			joy_b[(int)js.number] = js.value;
			break;
		}

		printf("\n\n\n\n\nJOY NAME : %s  ( %d axis,  %d bottons )\n\n", name_of_joycon, num_of_axis, num_of_buttons);
		printf("         %6d                      %6d            \n", joy_a[2], joy_a[5]);
		printf("         %3d                      %3d            \n", joy_b[4], joy_b[5]);
		printf("                     %3d    %3d                     \n", joy_b[6], joy_b[7]);
		printf("         %6d                      %3d            \n",         joy_a[7],         joy_b[3]);
		printf("    %6d    %6d            %3d       %3d       \n", joy_a[6], joy_a[6], joy_b[2], joy_b[1]);
		printf("         %6d                      %3d            \n",         joy_a[7],         joy_b[0]);
		printf("                                                 \n");
		printf("         %6d                      %6d            \n",         joy_a[1],         joy_a[4]);
		printf("    %6d    %6d            %6d    %6d       \n", joy_a[0], joy_a[0], joy_a[3], joy_a[3]);
		printf("         %6d                      %6d            \n",         joy_a[1],         joy_a[4]);
                printf("\n\n\n\n\n\nCtrl+C to exit.\n");

		usleep(500);
	}

	close(joy);

	return(0);
}
