hw	: hw.c
	gcc -o hw hw.c

kekka	: math/kekka.c
	gcc math/kekka.c -o math/kekka -lm

kservo	: kservo.cpp
	g++ -std=c++11 -o kservo kservo.cpp -lics3

cuda    : cuda.cu
	nvcc -o cuda cuda.cu

clean	:
	rm hw math/kekka kservo cuda
