/*
 *  2023.12.12
 *  ics_servo_rom.cpp
 *  ver.0.2
 *  Kunihito Mitsuboshi
 *  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */


// g++ -std=c++11 -o ICS_SERVO_ROM ics_servo_rom.cpp -lics3

#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <ics3/ics>


#define SERVO_DEV "/dev/ttyUSB0"


int main(int argc, char *argv[])
{
	char in[50];
	auto servo_id(0), servo_d(0);

	for(int i=0; i<argc; i++) std::cout << " " << argv[i]; std::cout << std::endl;


//	if servo open error
	ics::ICS3 servo {SERVO_DEV, ics::Baudrate::RATE115200()};

	servo_id = servo.getID();
	std::cout << "KONDO SERVO ID : " << (int)servo_id << std::endl;


	try
	{
		std::cout << "input ID > "; std::cin >> in;
		auto id = std::atoi(in);
		auto rom = servo.getRom(id);

		std::cout << "SIZE OF ROM : " << sizeof(rom) << std::endl;
		std::fstream f;
		f.open("kondo.rom", std::ios::out|std::ios::binary);
		f.write((const char*)&rom, sizeof(rom));
		f.close();
	}
	catch (...)
	{
		std::cout << "Error" << std::endl;
		std::exit(1);
	}

	while(true)
	{
		std::cout << "input DEGREE (-130 to 130) > "; std::cin >> in;
		if((in[0] >= 'a' && in[0] <= 'z') || (in[0] >= 'A' && in[0] <= 'Z')) return 0;

		servo_d = std::atof(in);
		if(servo_d >= -130 && servo_d <= 130)
		{
			servo.move(servo_id, ics::Angle::newDegree(servo_d));

			std::this_thread::sleep_for(std::chrono::milliseconds(2000));

			auto ans = servo.move(servo_id, ics::Angle::newDegree(servo_d));
			std::cout << "POS = " << ans.getRaw() << std::endl;
		}
	}


//	servo close

	return(0); // return 0;
}
