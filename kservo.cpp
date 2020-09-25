#include <iostream>
#include <stdexcept>
#include <fstream>
#include <chrono>
#include <thread>
#include <ics3/ics>


main()
{
	ics::ICS3 s {"/dev/ttyUSB0", ics::Baudrate::RATE115200()};
	auto d=50;

	auto id = s.getID();
	std::cout << "ID : " << (int)id << std::endl;
/*
	try {
		auto rom = s.getRom(id);

		std::cout << "SIZE OF ROM : " << sizeof(rom) << std::endl;
		std::fstream f;
		f.open("kondo.rom", std::ios::out|std::ios::binary);
		f.write((const char*)&rom, sizeof(rom));
		f.close();
	}
	catch (...) {
		std::cout << "Error" << std::endl;
		std::exit(1);
	}
*/

	std::cout << "input DEGREE : "; std::cin >> d;
	s.move(id, ics::Angle::newDegree(d));

	std::this_thread::sleep_for(std::chrono::milliseconds(2000));

	auto ans = s.move(id, ics::Angle::newDegree(d));
	std::cout << "POS = " << ans.getRaw() << std::endl;

	return(0);
}
