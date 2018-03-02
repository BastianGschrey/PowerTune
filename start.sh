#!/bin/sh
#export QT_QPA_EGLFS_PHYSICAL_WIDTH=155
#export QT_QPA_EGLFS_PHYSICAL_HEIGHT=86
if [ -d /home/pi/build ];then
sudo rm -r /opt/PowerTune
sudo mkdir /opt/PowerTune
sudo chown pi:pi /opt/PowerTune
rsync -r /home/pi/build/. /opt/PowerTune
sudo rm -r /home/pi/build
cd /opt/PowerTune
./PowertuneQMLGui
else
cd /opt/PowerTune
./PowertuneQMLGui
fi

