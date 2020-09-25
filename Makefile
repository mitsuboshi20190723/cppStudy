hw	: hw.c
	gcc -o hw hw.c

kservo	: kservo.cpp
	g++ -std=c++11 -o kservo kservo.cpp -lics3

clean	:
	rm hw kservo
