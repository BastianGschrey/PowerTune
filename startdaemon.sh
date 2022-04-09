#!/bin/sh
sudo ifdown can0
sudo ifup can0
#PLMS Consult Cable drivers
sudo modprobe ftdi_sio
sudo sh -c 'echo "0403 c7d9" > /sys/bus/usb-serial/drivers/ftdi_sio/new_id'
cd /home/pi/daemons
./Link

