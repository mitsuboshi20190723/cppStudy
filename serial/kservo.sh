#!/bin/bash

##
 #  2023.11.14
 #  kservo.sh
 #  ver.1.2
 #  Kunihito Mitsuboshi
 #  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 ##


# Insert DUAL USB adapter on ICS mode.


# sudo sh -c 'echo "ftdi_sio" >> /etc/modules'
lsusb | grep 165c:0008
lsmod | grep ftdi

sudo modprobe ftdi-sio
sudo sh -c 'echo 165C 0008 > /sys/bus/usb-serial/drivers/ftdi_sio/new_id'
sleep 1

sudo chmod o+rw /dev/ttyUSB0

ls -l /dev/ttyUSB*
# cat /sys/bus/usb-serial/drivers/ftdi_sio/new_id
# sudo dmesg
