/*
 *  2020.12.28
 *  motion.hpp
 *  ver 1.0
 *  Kunihito Mitsuboshi
 *  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */


#define ICS_CMD_POS         0x80
#define ICS_CMD_READ        0xA0
#define ICS_SC_EEPROM       0x00
#define ICS_SC_TCH          0x05
#define ISC_EEPROM_SIZE     0x40 // 64
#define ICS_BUFF_SIZE       0x50 // 80

#define JOY_NAME_SIZE       80
#define JOY_BUTTON_OFFSET   100

typedef unsigned char uchar;

class motion
{
public:
	double a;
	double da;
	double aps;

	int input_id;
	double input_neutral;
	double input_perstep;

	int output_id;
	double output_neutral;
	double output_perstep;


	void set_motion(int, double, double, int, double, double);
	double set_angle(double);
};


struct eeprom
{
	uchar param[ISC_EEPROM_SIZE];
	uchar buf[ICS_BUFF_SIZE];
	uchar id;
};

class icsservo
{
	int c;
	std::vector<eeprom> s;

public:
	int connect(const char *);
	int disconnect();
	int get_eeprom(uchar);
	int set_pos(motion *);
};


class joystick
{
	char name_of_joystick[JOY_NAME_SIZE];
	int c;
	std::vector<int> a;
	std::vector<char> b;

public:
	int connect(const char *);
	int disconnect();
	int axis(int);
	int buttons(int);
	motion *get_ctl(motion *);
};