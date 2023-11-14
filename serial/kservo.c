/*
 *  2023.11.14
 *  kservo.c
 *  ver.3.0
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


unsigned char GETID[] = {0xFF, 0x00, 0x00, 0x00};
unsigned char SETID[] = {0xE0, 0x01, 0x01, 0x01};
unsigned char P7500[] = {0x80, 0x3A, 0x4C};


unsigned char buff[128];


int set_pos(int dev, unsigned char id, double deg)
{
	int pos, tx_len=3;
	int i, rx_len;
	unsigned char *cmd, *pos_h, *pos_l;

	if(deg > 135 || deg < -135) return 0;
	pos = (int)(deg / 0.034) + 7500;

	for(i=0; i<128; i++) buff[i] ^= buff[i];
	cmd = buff;
	*cmd = 0x80 | id;

	pos_h = buff + 1;
	*pos_h = (unsigned char)(pos/128 & 127);
	pos_l = buff + 2;
	*pos_l = (unsigned char)(pos & 127);

	printf("TX : "); for(i=0; i < tx_len; i++) printf("%02X ", buff[i]); printf("\n");
	write(dev, buff, tx_len);

//	usleep(0.1*1000*1000);
	for(i=0; i<128; i++) buff[i] ^= buff[i];
	rx_len = read(dev, buff, sizeof(buff));
	if(0 < rx_len)
	{
		pos = (int)buff[4] * 128 + (int)buff[5];
		printf("RX : "); for(i=0; i < rx_len; i++) printf("%02X ", buff[i]); printf("\n");
	}
	else pos = -1;

	return pos;
}

int main(int argc, char *argv[])
{
	int fd;
	struct termios tio;


	fd = open("/dev/ttyUSB0", O_RDWR);
	if (fd < 0)
	{
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
	sleep(0.5);
	usleep(0.5*1000*1000);

	set_pos(fd, 1, 0);
	sleep(1);
	set_pos(fd, 1, 90);
	usleep(1*1000*1000);
	set_pos(fd, 1, 0);

	close(fd);
	return 0;
}
