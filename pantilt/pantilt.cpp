/*
 *  2021.2.6
 *  pantilt.cpp
 *  ver 1.8
 *  Kunihito Mitsuboshi
 *  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */

#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include "motion.hpp"


#define JOY_DEV "/dev/input/js0"
#define VIDEO_DEV "/dev/video0"
#define SERVO_DEV "/dev/ttyUSB0"


#define AXIS_NEUTRAL 0
#define AXIS_PERSTEP 0.0039 /* -32,768(-127.8)   0(0)   32,767(127.8) */

#define IMGX_NEUTRAL 320
#define IMGX_PERSTEP 0.1
#define IMGY_NEUTRAL 240
#define IMGY_PERSTEP 0.1 /*?*/

#define SERVO_NEUTRAL 7500
#define SERVO_PERSTEP 0.034 /* 3,500(-135)   7,500(0)   11,500(135) */


int main(int argc, char **argv)
{
	joystick jd;
	icsservo sd;
	webcam vd;
	motion pan, tilt;

	if(jd.connect(JOY_DEV) < 0) { std::cout << "Do not open " << JOY_DEV << std::endl; return -1; }
	if(sd.connect(SERVO_DEV) < 0) { std::cout << "Do not open " << SERVO_DEV << std::endl; return -1; }

	pan.set_motion(jd.axis(0), AXIS_NEUTRAL, AXIS_PERSTEP*0.5, 1, SERVO_NEUTRAL, SERVO_PERSTEP);
	tilt.set_motion(jd.axis(1), AXIS_NEUTRAL, AXIS_PERSTEP*-0.25, 2, SERVO_NEUTRAL, SERVO_PERSTEP);

	while(true)
	{
		sd.set_pos( jd.get_ctl( &pan ) );

		sd.set_pos( jd.get_ctl( &tilt ) );

		std::this_thread::sleep_for(std::chrono::microseconds(1000));
	}

	jd.disconnect();
	sd.disconnect();

	return 0;
}
