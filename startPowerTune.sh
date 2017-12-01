#!/bin/sh
#check if the PowerTune build directory exists
if [ ! -d "$/home/pi/PowerTunebuild" ]; then
#remove install directory
sudo rm -r /opt/PowerTune
#move build directory to install directory
sudo mv /home/pi/PowerTunebuild /opt/PowerTune
fi
/opt/PowerTune/PowerTuneQMLGui