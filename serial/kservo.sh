#!/bin/bash

##
 #  2020.12.5
 #  kservo.sh
 #  ver 1.0
 #  Kunihito Mitsuboshi
 #  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 ##

# sudo sh -c 'echo "ftdi_sio" >> /etc/modules'
lsusb | grep 165c:0008
c=lsusb | grep 165c:0008
if [ -z "$c" ]; then
	echo "donnot connect USB"
	exit
fi
lsmod | grep ftdi

exit
sudo modprobe ftdi-sio
sudo sh -c 'echo 165C 0008 > /sys/bus/usb-serial/drivers/ftdi_sio/new_id'
sudo chmod o+rw /dev/ttyUSB0

# ls -l /dev/ttyUSB*
# cat /sys/bus/usb-serial/drivers/ftdi_sio/new_id
# dmesg