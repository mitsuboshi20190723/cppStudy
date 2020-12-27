/*
 *  2020.12.28
 *  motion.cpp
 *  ver 1.0
 *  Kunihito Mitsuboshi
 *  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */

#include <iostream>
#include <vector>

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <string.h>
#include <linux/joystick.h>

#include "motion.hpp"


void motion::set_motion(int ii, double in, double ips, int oi, double on, double ops)
{
	this->a = this->da = this->aps = 0;
	this->input_id = ii; this->input_neutral = in; this->input_perstep = ips;
	this->output_id = oi; this->output_neutral = on; this->output_perstep = ops;
}

double motion::set_angle(double a)
{
	this->a = a;
	return a;
}


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

	auto logger = [](int i) { std::cout << "ID" << i << " servo found." << std::endl; };
	for(i=0; i<32; i++) if(this->get_eeprom((int)i) >= 0) logger(i);
	
	return this->c;
}

int icsservo::disconnect()
{
	return close(this->c);
}

int icsservo::get_eeprom(uchar id)
{
	int i, tx_len(2), rx_len;
	struct eeprom r;
	uchar tx[2];

	if(id < 32)
	{
		for(i = 0; i < this->s.size(); i++) if(id == this->s[i].id) break;

		tx[0] = ICS_CMD_READ | id; tx[1] = ICS_SC_EEPROM;
		write(this->c, tx, tx_len);

		rx_len = read(this->c, r.buf, sizeof(r.buf));

		if(rx_len == 68 && id == ((int)r.buf[4+57-1] & 15) * 16 + (int)r.buf[4+58-1] & 15)
		{
			memcpy(r.param, r.buf+4, ISC_EEPROM_SIZE);
			r.id = id;
			this->s.push_back(r);
		}
		else return -1;

		return id;
	}
	else return -1;
}

int icsservo::set_pos(motion *m)
{
	int pos, tx_len(3);
	uchar tx[3];

	if(m->a > 135 || m->a < -135) { std::cout << "angle out of range" << std::endl; return 0; }

	tx[0] = ICS_CMD_POS | (uchar)m->output_id;

	pos = (int)(m->a / m->output_perstep) + m->output_neutral;
	tx[1] = (uchar)(pos/128 & 127); tx[2] = (uchar)(pos & 127);

	write(this->c, tx, tx_len);
//	if(0 < read(this->c, buf, sizeof(buf))) pos = (int)buf[4] * 128 + buf[5]; else pos = -1;
	return pos;
}

/* joystick */
int joystick::connect(const char *df)
{
	int num_of_axis, num_of_buttons;

	this->c = open(df, O_RDONLY);
	if (this->c < 0) return this->c;

	ioctl(this->c, JSIOCGAXES, &num_of_axis);
	this->a.resize(num_of_axis, 0);
	ioctl(this->c, JSIOCGBUTTONS, &num_of_buttons);
	this->b.resize(num_of_buttons, 0);
	ioctl(this->c, JSIOCGNAME(80), &this->name_of_joystick);
	// if raspi & F310 : num_of_axis = 8; num_of_buttons = 11;
	// this->a.resize(num_of_axis, 0);
	// this->b.resize(num_of_buttons, 0);

	std::cout << "name : " << this->name_of_joystick << " joystick found. " ;// << std::endl;
	std::cout << "axis : " << num_of_axis << ", buttons : " << num_of_buttons << std::endl;

	return this->c;
}

int joystick::disconnect()
{
	return close(this->c);
}

int joystick::axis(int i)
{
	if(this->a.size() < i) return -1;
	else return i;
}

int joystick::buttons(int i)
{
	if(this->b.size() < i) return -1;
	else return i + JOY_BUTTON_OFFSET;
}

motion *joystick::get_ctl(motion *m)
{
	js_event js;
	read(this->c, &js, sizeof(js_event));
//	std::cout << "n : " << (int)js.number << std::endl;
	switch(js.type & ~JS_EVENT_INIT)
	{
	case JS_EVENT_AXIS:
		this->a[(int)js.number] = js.value;
		break;
	case JS_EVENT_BUTTON:
		this->b[(int)js.number] = js.value;
		break;
	}

	if(m->input_id < JOY_BUTTON_OFFSET) m->a = (double)this->a[m->input_id] * m->input_perstep;
	else m->a += (double)this->b[m->input_id % JOY_BUTTON_OFFSET] * m->input_perstep * m->da;

	return m;
}
