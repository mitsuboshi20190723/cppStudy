hw	: hello_world/hw.c
	gcc -o hw hello_world/hw.c

kekka	: kekka/kekka.c
	gcc kekka/kekka.c -o kekka -lm

kservo	: serial/kservo.c
	gcc serial/kservo.c -o kservo

#kservo	: serial/kservo.cpp
#	g++ -std=c++11 -o kservo serial/kservo.cpp -lics3

# matadd	: cuda/matadd.cu
#	nvcc -o matadd cuda/matadd.cu

clean	:
	rm hw kekka kservo matadd 
