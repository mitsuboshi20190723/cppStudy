BUILD = build

mkdirbuild	:
	mkdir build && echo "make hw or make ffer or make gauss or make kservo or make joynics or make fd"

hw	: hello_world/hw.c
	gcc -o $(BUILD)/HW hello_world/hw.c

gauss	: math/gauss.c
	gcc math/gauss.c -o $(BUILD)/GAUSS -lm

ffer	: math/ffer.cpp
	g++ math/ffer.cpp -o $(BUILD)/FFER

kservo	: serial/kservo.c
	gcc serial/kservo.c -o $(BUILD)/KSERVO

joynics	: serial/joynics.cpp
	g++ -std=c++11 -o $(BUILD)/JOYNICS serial/joynics.cpp -lics3

fd	: math/fd.cpp
	g++ -o $(BUILD)/FD math/fd.cpp `pkg-config --cflags opencv` `pkg-config --libs opencv` -ldlib -llapack -lblas  -lX11 -lpthread -ljpeg -lpng -lgif


clean	:
	rm -rf $(BUILD)
