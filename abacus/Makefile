
CC     = g++
CFLAGS = -g
TARGET = hexsoroban
OBJS   = soroban.o
SLIB   = libsorobanarchive.a
SLOBJS = sorobanlib.o sorobanclass.o
DLIB   = libsoroban.so
DLOBJS = sorobanconsole.o


all : $(TARGET)

$(TARGET) : $(OBJS) $(SLIB) $(DLIB)
	$(CC) $(CFLAGS) $(OBJS) -L. -lsorobanarchive $(DLIB) -o $(TARGET)
	@echo "\n\nexport LD_LIBRARY_PATH=.\n\n"

soroban.o : soroban.hpp soroban.cpp
	$(CC) $(CFLAGS) -c soroban.cpp



libsorobanarchive.a : $(SLOBJS)
	ar rcs libsorobanarchive.a $(SLOBJS)

sorobanlib.o : soroban.hpp sorobanlib.cpp
	$(CC) $(CFLAGS) -c sorobanlib.cpp

sorobanclass.o : soroban.hpp sorobanclass.cpp
	$(CC) $(CFLAGS) -c sorobanclass.cpp



libsoroban.so : $(DLOBJS)
	$(CC) $(CFLAGS) -shared $(DLOBJS) -o libsoroban.so

sorobanconsole.o : sorobanframe.hpp sorobanconsole.cpp
	$(CC) $(CFLAGS) -fPIC -c sorobanconsole.cpp





ns : nextsoroban.cpp
	$(CC) $(CFLAGS) nextsoroban.cpp -o ns



clean :
	rm -f $(TARGET) $(OBJS) $(SLIB) $(SLOBJS) $(DLIB) $(DLOBJS) ns
