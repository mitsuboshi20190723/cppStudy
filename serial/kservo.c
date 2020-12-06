/*
 *  2020.12.6
 *  kservo.c
 *  ver 1.0
 *  Kunihito Mitsuboshi
 *  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */


#include <stdio.h>
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>


unsigned char P7500[] = {0x81, 0x3A, 0x4C};
unsigned char P3968[] = {0x81, 0x1F, 0x00};


int main(int argc, char *argv[])
{
	unsigned char buf[256];
	int fd, len, i;
	struct termios tio;


	fd = open("/dev/ttyUSB0", O_RDWR);
	if (fd < 0) {
		printf("Do not open /dev/ttyUSB0\n");
		return -1;
	}

	tio.c_iflag = tio.c_oflag = tio.c_lflag = 0;
	tio.c_cflag = B115200 | CLOCAL | PARENB | CREAD | CS8;
	tio.c_cc[VMIN] = tio.c_cc[VTIME] = 1;

	// cfsetispeed(&tio, B115200);
	// cfsetospeed(&tio, B115200);
	// cfmakeraw(&tio);
	tcsetattr(fd, TCSANOW, &tio);
	// ioctl(fd, TCSETS, &tio);


	write(fd, P7500, 3);
	sleep(1);
	write(fd, P3968, 3);
	usleep(1*1000*1000);
	write(fd, P7500, 3);

	len = read(fd, buf, sizeof(buf));
	if (0 < len)
	{
		for(i = 0; i < len; i++) printf("%02X ", buf[i]);
		printf("\n");
	}


	close(fd);
	return 0;
}
