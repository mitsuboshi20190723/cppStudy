BUILD = build

hw	: hello_world/hw.c
	gcc -o $(BUILD)/HW hello_world/hw.c

kekka	: kekka/kekka.c
	gcc kekka/kekka.c -o $(BUILD)/KEKKA -lm

kservo	: serial/kservo.c
	gcc serial/kservo.c -o $(BUILD)/KSERVO

joynics	: serial/joynics.cpp
	g++ -std=c++11 -o $(BUILD)/JOYNICS serial/joynics.cpp -lics3

# matadd	: cuda/matadd.cu
#	nvcc -o MATADD cuda/matadd.cu

clean	:
	rm -rf $(BUILD)