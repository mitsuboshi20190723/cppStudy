BUILD = build

mkdirbuild	:
	mkdir build && echo "make hw or make gauss or make ffer or make perceptron or make joycon or make hb or make kservo or make ics_servo_rom or make fd"

hw	: hello_world/hw.c
	gcc -o $(BUILD)/HW hello_world/hw.c -w

gauss	: math/gauss.c
	gcc math/gauss.c -o $(BUILD)/GAUSS -lm

ffer	: math/ffer.cpp
	g++ math/ffer.cpp -o $(BUILD)/FFER

perceptron	: math/perceptron.cpp
	g++ -D HALF math/perceptron.cpp -o $(BUILD)/PERCEPTRON_HALF

joycon	: serial/joycon.c
	gcc serial/joycon.c -o $(BUILD)/JOYCON

kservo	: serial/kservo.c
	gcc serial/kservo.c -o $(BUILD)/KSERVO

hb	: serial/hb.c
	gcc serial/hb.c -o $(BUILD)/HB

ics_servo_rom	: serial/ics_servo_rom.cpp
	g++ -std=c++11 -o $(BUILD)/ICS_SERVO_ROM serial/ics_servo_rom.cpp -lics3

fd	: math/fd.cpp
	g++ -o $(BUILD)/FD math/fd.cpp `pkg-config --cflags opencv4` `pkg-config --libs opencv4` -ldlib -llapack -lblas  -lX11 -lpthread -ljpeg -lpng -lgif -lwebp


clean	:
	rm -rf $(BUILD)
