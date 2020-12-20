/*
 *  2020.10.4
 *  joynics.cpp
 *  ver 0.9
 *  Kunihito Mitsuboshi
 *  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */

/*
 *  ~/tools/libics3/script/setup.sh
 *  sudo chmod o+rw /dev/ttyUSB0
 */

#include <iostream>

//#include <iomanip>
#include <vector>
#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/joystick.h>

#include <stdexcept>
#include <fstream>
#include <chrono> /* std::this_thread::sleep_for(std::chrono::seconds(3)); sleep(3);*/
#include <thread> /* std::this_thread::sleep_for(std::chrono::microseconds(3)); usleep(3);*/
#include <ics3/ics>

#define JOY_DEV "/dev/input/js0"
#define SERVO_DEV "/dev/ttyUSB0"

int main(int argc, char *argv[])
{
	int joy(-1), num_of_axis(0), num_of_buttons(0);
	char name_of_joystick[80];
	std::vector<int> joy_a;
	std::vector<char> joy_b;

	joy = open(JOY_DEV,O_RDONLY);

	ioctl(joy, JSIOCGAXES, &num_of_axis);
	joy_a.resize(num_of_axis,0);
	ioctl(joy, JSIOCGBUTTONS, &num_of_buttons);
	joy_b.resize(num_of_buttons,0);
	ioctl(joy, JSIOCGNAME(80), &name_of_joystick);

	std::cout << "JOYSTICK NAME : " << name_of_joystick << std::endl;


	auto servo_id(0), servo_d(0);

	ics::ICS3 servo {SERVO_DEV, ics::Baudrate::RATE115200()};

	servo_id = servo.getID();
	std::cout << "KONDO SERVO ID : " << (int)servo_id << std::endl;

	while(true)
	{
		js_event js;
		read(joy, &js, sizeof(js_event));

		switch (js.type & ~JS_EVENT_INIT)
		{
		case JS_EVENT_AXIS :
			joy_a[(int)js.number] = js.value;
			break;
		case JS_EVENT_BUTTON :
			joy_b[(int)js.number] = js.value;
			break;
		}

		std::cout << "AXIS0 : " << joy_a[0] << std::endl;
		servo_d = (int)(joy_a[0]/300);

		auto ans = servo.move(servo_id, ics::Angle::newDegree(servo_d));
		std::cout << "POSITION : " << ans.getRaw() << std::endl;

		usleep(500);
	}

	close(joy);

	return(0);
}
