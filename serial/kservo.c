/*
 *  2020.12.20
 *  kservo.c
 *  ver 2.0
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

int set_pos(int dev, char id, double deg)
{
	int pos, tx_len=3;
	int i, rx_len;
	unsigned char buf[10], *cmd, *pos_h, *pos_l;

	if(deg > 135 || deg < -135) return 0;

	cmd = buf; 
	*cmd = 0x80 | id;

	pos = (int)(deg / 0.034) + 7500;

	pos_h = buf + 1;
	*pos_h = (unsigned char)(pos/128 & 127);
	pos_l = buf + 2;
	*pos_l = (unsigned char)(pos & 127);

	printf("TX : "); for(i = 0; i < tx_len; i++) printf("%02X ", buf[i]); printf("\n");
	write(dev, buf, tx_len);

//	usleep(0.1*1000*1000);

	rx_len = read(dev, buf, sizeof(buf));
	if(0 < rx_len)
	{
		pos = (int)buf[4] * 128 + buf[5];
		printf("RX : ");
		for(i = 0; i < rx_len; i++) printf("%02X ", buf[i]);
		printf("\n");
	}
	else pos = -1;

	return pos;
}

int main(int argc, char *argv[])
{
	int fd;
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

	set_pos(fd, 1, 0);
	sleep(1);
	set_pos(fd, 1, 90);
	usleep(1*1000*1000);
	set_pos(fd, 1, 0);

	close(fd);
	return 0;
}
