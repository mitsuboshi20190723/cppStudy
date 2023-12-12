/*
 *  2023.12.12
 *  joycon.c
 *  ver.1.0
 *  Kunihito Mitsuboshi
 *  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */


#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/joystick.h>


#define JOY_DEV "/dev/input/js0"


int A(int a){ return a; }
int B(int b){ return b; }
int P(int a){ return a>0 ? a : 0; }
int N(int a){ return a<0 ? a : 0; }

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

		printf("\n\n\n\nJOY NAME : %s ( %d axis,  %d bottons )\n", name_of_joycon, num_of_axis, num_of_buttons);
		printf("                                              \n");
		printf("         %6d                      %6d         \n",       A(joy_a[2]),              A(joy_a[5]));
		printf("          %d                               %d \n",       B(joy_b[4]),              B(joy_b[5]));
		printf("                  %d               %d         \n",       B(joy_b[6]),              B(joy_b[7]));
		printf("       %6d                           %d       \n",       N(joy_a[1]),              B(joy_b[3]));
		printf("  %6d    %6d                 %d         %d    \n", N(joy_a[0]), P(joy_a[0]), B(joy_b[2]), B(joy_b[1]));
		printf("       %6d                           %d       \n",       P(joy_a[1]),              B(joy_b[0]));
		printf("                                              \n");
		printf("       %6d                      %6d           \n",       N(joy_a[7]),              N(joy_a[4]));
		printf("  %6d    %6d            %6d    %6d            \n", N(joy_a[6]), P(joy_a[6]), N(joy_a[3]), P(joy_a[3]));
		printf("       %6d                      %6d           \n",       P(joy_a[7]),              P(joy_a[4]));
		printf("                                              \n");
		printf("                                    %d        \n",                                 B(joy_b[8]));
		printf("\n\n\n\nCtrl+C to exit.                       \n");

		usleep(500);
	}

	close(joy);

	return(0);
}
