/*
 *  2020.12.20
 *  pantilt.cpp
 *  ver 0.1
 *  Kunihito Mitsuboshi
 *  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */


#include <iostream>
#include <vector>

//#include <iomanip>
#include <chrono> /* std::this_thread::sleep_for(std::chrono::seconds(3)); sleep(3);*/
#include <thread> /* std::this_thread::sleep_for(std::chrono::microseconds(3)); usleep(3);*/

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h> /* servo */
#include <linux/joystick.h>

/* kondo servo ics */
#define ICS_CMD_POS 0x80
#define ICS_CMD_READ 0xA0
#define ICS_SC_EEPROM 0x00
#define ICS_SC_TCH 0x05
#define ISC_EEPROM_SIZE 64
#define ICS_BUFF_SIZE 70

#define SERVO_NEUTRAL 7500
#define SERVO_PERSTEP 0.034 /* 3,500(-135)   7,500(0)   11,500(135) */

typedef unsigned char uchar;

struct eeprom
{
	uchar param[ISC_EEPROM_SIZE];
	uchar id;
};

int get_eeprom(int dev, char id)
{
	int tx_len(2);
	char buf[ICS_BUFF_SIZE];

	buf[0] = ICS_CMD_READ & id; buf[1] = ICS_SC_EEPROM;
	write(dev, buf, tx_len);

	if(0 < read(dev, buf, sizeof(buf))) return id; else return -1;
}

int set_pos(int dev, char id, double deg)
{
	int pos, tx_len(3);
	char buf[ICS_BUFF_SIZE], *cmd, *pos_h, *pos_l;

	if(deg > 135 || deg < -135) return 0;

	cmd = buf; 
	*cmd = ICS_CMD_POS & id;

	pos = (int)(deg / SERVO_PERSTEP) + SERVO_NEUTRAL;

	pos_h = buf + 1;
	*pos_h = (char)(pos%128 & 127);
	pos_l = buf + 2;
	*pos_l = (char)(pos & 127);

	write(dev, buf, tx_len);

//	if(0 < read(dev, buf, sizeof(buf))) pos = (int)buf[4] * 128 + buf[5]; else pos = -1;

	return pos;
}
/* kondo servo ics */

#define AXIS_NEUTRAL 0
#define AXIS_PERSTEP 0.0039 /* -32,768(-127.8)   0(0)   32,767(127.8) */

double get_ctl(int dev, std::vector<int> a, std::vector<char> b, int num)
{
	js_event js;
	read(dev, &js, sizeof(js_event));

	switch(js.type & ~JS_EVENT_INIT)
	{
	case JS_EVENT_AXIS :
		a[(int)js.number] = js.value;
		break;
	case JS_EVENT_BUTTON :
		b[(int)js.number] = js.value;
		break;
	}

	return (double)a[num] * AXIS_PERSTEP;
}

#define JOY_DEV "/dev/input/js0"
#define SERVO_DEV "/dev/ttyUSB0"


int main(int argc, char **argv)
{
	int jd(-1), num_of_axis(0), num_of_buttons(0);
	char name_of_joystick[80];
	std::vector<int> joy_a;
	std::vector<char> joy_b;

	jd = open(JOY_DEV, O_RDONLY);
	if (jd < 0)
	{
		printf("Do not open /dev/input/js0\n");
		return -1;
	}

	ioctl(jd, JSIOCGAXES, &num_of_axis);
	joy_a.resize(num_of_axis,0);
	ioctl(jd, JSIOCGBUTTONS, &num_of_buttons);
	joy_b.resize(num_of_buttons,0);
	ioctl(jd, JSIOCGNAME(80), &name_of_joystick);

	std::cout << "JOYSTICK NAME : " << name_of_joystick << std::endl;


	int sd(-1);
	double servo_d;
	struct termios tio;

	sd = open("/dev/ttyUSB0", O_RDWR);
	if (sd < 0)
	{
		printf("Do not open /dev/ttyUSB0\n");
		return -1;
	}

	tio.c_iflag = tio.c_oflag = tio.c_lflag = 0;
	tio.c_cflag = B115200 | CLOCAL | PARENB | CREAD | CS8;
	tio.c_cc[VMIN] = tio.c_cc[VTIME] = 1;
	tcsetattr(sd, TCSANOW, &tio);
	// ioctl(sd, TCSETS, &tio);

	while(true)
	{
		servo_d = get_ctl(jd, joy_a, joy_b, 0);

		set_pos(sd, 0, servo_d);

		std::this_thread::sleep_for(std::chrono::microseconds(500));
	}

	close(sd);
	close(jd);

	return(0);
}
