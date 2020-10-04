hw	: hw.c
	gcc -o hw hw.c

kekka	: math/kekka.c
	gcc math/kekka.c -o kekka -lm

kservo	: serial/kservo.cpp
	g++ -std=c++11 -o kservo serial/kservo.cpp -lics3

cuda    : cuda.cu
	nvcc -o cuda cuda.cu

clean	:
	rm hw kekka kservo cuda
