#!/bin/sh
echo "Fetching latest Daemons"
cd /home/pi/src
git pull
cd
echo "Killing all  Daemons"
sudo pkill OBD
sudo pkill Haltechd
sudo pkill Consult
sudo pkill Apexid 
sudo pkill Microtechd 
sudo pkill Linkd
sudo pkill Hondatad
sudo pkill AdaptronicCANd
sudo pkill AEMV2d
sudo pkill BRZFRS86d
sudo pkill EMUCANd
sudo pkill M800ADLSet1d
sudo pkill MotecM1d
sudo pkill AudiB7d
sudo pkill AudiB8d
sudo pkill Emtrond
sudo pkill Holleyd
echo "Updating Daemons"
sudo cp -r /home/pi/src/daemons/. /home/pi/daemons/

