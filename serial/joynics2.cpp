/*
 *  2020.12.22
 *  joynics2.cpp
 *  ver 1.0
 *  Kunihito Mitsuboshi
 *  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */

#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h> /* servo */
#include <string.h>
#include <linux/joystick.h>



#define ICS_CMD_POS         0x80
#define ICS_CMD_READ        0xA0
#define ICS_SC_EEPROM       0x00
#define ICS_SC_TCH          0x05
#define ISC_EEPROM_SIZE     0x40 // 64
#define ICS_BUFF_SIZE       0x50 // 80




#define SERVO_NEUTRAL 7500
#define SERVO_PERSTEP 0.034 /* 3,500(-135)   7,500(0)   11,500(135) */

typedef unsigned char uchar;

struct eeprom
{
	uchar param[ISC_EEPROM_SIZE];
	uchar id;
};

class icsservo
{
public:
	int c;
	std::vector<eeprom> id;

	int connect(const char *);
	int disconnect();
	int get_eeprom(uchar);
	int set_pos(uchar, double);
};




#define AXIS_NEUTRAL 0
#define AXIS_PERSTEP 0.0039 /* -32,768(-127.8)   0(0)   32,767(127.8) */

class joystick
{
	char name_of_joystick[80];
public:
	int c;
	std::vector<int> joy_a;
	std::vector<char> joy_b;

	int connect(const char *);
	int disconnect();
	double get_ctl(int);
};





/* kondo ics servo */
int icsservo::connect(const char *df)
{
	uchar i;
	struct termios tio;

	this->c = open(df, O_RDWR);
	if (this->c < 0) return -1;

	tio.c_iflag = tio.c_oflag = tio.c_lflag = 0;
	tio.c_cflag = B115200 | CLOCAL | PARENB | CREAD | CS8;
	tio.c_cc[VMIN] = tio.c_cc[VTIME] = 1;
	tcsetattr(this->c, TCSANOW, &tio);
	// ioctl(this->c, TCSETS, &tio);

	for(i=0; i<32; i++) if(this->get_eeprom(i) < 0) printf("EEPROM ERROR\n");

	return this->c;
}

int icsservo::disconnect()
{
	close(this->c);
}

int icsservo::get_eeprom(uchar id)
{
	int i, tx_len(2), rx_len;
	struct eeprom r;
	uchar buf[ICS_BUFF_SIZE], *cmd, *sc;

	if(id < 32)
	{
		for(i = 0; i < this->id.size(); i++) if(id == this->id[i].id) break;

		cmd = buf;
		*cmd = ICS_CMD_READ | id;
		sc = buf + 1;
		*sc = ICS_SC_EEPROM;
//		std::cout << "TX : " << std::showbase << std::hex << (int)buf[0] << " " << (int)buf[1];
		write(this->c, buf, tx_len);

		rx_len = read(this->c, buf, sizeof(buf));
//		std::cout << ",   RX_LEN : " << std::dec << rx_len << std::endl;
		if(id == ((int)buf[4+57-1] & 15) * 16 + (int)buf[4+58-1] & 15)
		{
			memcpy(r.param, buf+4, 64);
			r.id = id;
			this->id.push_back(r);
		}
		else return -1;

		return id;
	}
	else return -1;
}

int icsservo::set_pos(uchar id, double deg)
{
	int pos, tx_len(3);
	uchar buf[ICS_BUFF_SIZE], *cmd, *pos_h, *pos_l;

	if(deg > 135 || deg < -135) return 0;

	cmd = buf; 
	*cmd = ICS_CMD_POS | id;

	pos = (int)(deg / SERVO_PERSTEP) + SERVO_NEUTRAL;

	pos_h = buf + 1;
	*pos_h = (uchar)(pos/128 & 127);
	pos_l = buf + 2;
	*pos_l = (uchar)(pos & 127);

	write(this->c, buf, tx_len);
//	if(0 < read(this->c, buf, sizeof(buf))) pos = (int)buf[4] * 128 + buf[5]; else pos = -1;
	return pos;
}

/* joystick */
int joystick::connect(const char *df)
{
	int num_of_axis, num_of_buttons;

	this->c = open(df, O_RDONLY);
	if (this->c < 0) return -1;

	ioctl(this->c, JSIOCGAXES, &num_of_axis);
	this->joy_a.resize(num_of_axis,0);
	ioctl(this->c, JSIOCGBUTTONS, &num_of_buttons);
	this->joy_b.resize(num_of_buttons,0);
	ioctl(this->c, JSIOCGNAME(80), &this->name_of_joystick);

	return this->c;
}

int joystick::disconnect()
{
	close(this->c);
}

double joystick::get_ctl(int num)
{
	js_event js;
	read(this->c, &js, sizeof(js_event));
//	std::cout << "n : " << (int)js.number << std::endl;
	switch(js.type & ~JS_EVENT_INIT)
	{
	case JS_EVENT_AXIS:
		this->joy_a[(int)js.number] = js.value;
		break;
	case JS_EVENT_BUTTON:
		this->joy_b[(int)js.number] = js.value;
		break;
	}

	return (double)this->joy_a[num] * AXIS_PERSTEP ;
}



#define JOY_DEV "/dev/input/js0"
#define SERVO_DEV "/dev/ttyUSB0"

int main(int argc, char **argv)
{
	joystick jd;
	icsservo sd;
	double deg(0);


	if(jd.connect("/dev/input/js0") < 0) { printf("Do not open /dev/input/js0\n"); return -1; }
	if(sd.connect("/dev/ttyUSB0") < 0) { printf("Do not open /dev/ttyUSB0\n"); return -1; }


	while(true)
	{
		sd.set_pos(1, jd.get_ctl(0)/2); /* pan */

		sd.set_pos(2, -jd.get_ctl(1)/4); /* tilt */

		deg = jd.get_ctl(3);
		std::cout << deg << std::endl;
		sd.set_pos(3, deg/4);

		std::this_thread::sleep_for(std::chrono::microseconds(1000));
	}


	jd.disconnect();
	sd.disconnect();

	return 0;
}
