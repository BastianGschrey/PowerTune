#!/bin/sh
cd /home/pi/PowerTune
git pull
mkdir /home/pi/PowerTunebuild
cd /home/pi/PowerTunebuild
qmake /home/pi/PowerTune
make -j4
sudo reboot now