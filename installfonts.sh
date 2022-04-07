#!/bin/bash
# -Installs associated fonts for  PowerTuneDigital
if [ -d /usr/share/fonts/PowertuneDigital ]; then
sudo rsync --recursive /home/pi/src/fonts/ /usr/share/fonts/PowertuneDigital/
else
sudo mkdir /usr/share/fonts/PowertuneDigital/
sudo rsync --recursive /home/pi/src/fonts/ /usr/share/fonts/PowertuneDigital/
fi
