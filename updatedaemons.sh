#!/bin/sh
echo "Disable System Logs"
cd /home/pi/srcofficial
./fixlog.sh
echo "Install fonts"
cd /home/pi/srcofficial/fonts
sudo cp *.* /usr/local/share/fonts
echo "Fetching latest Daemons"
cd /home/pi/srcofficial
git pull
cd
echo "Killing all  Daemons"
sudo pkill AdaptronicCANd
sudo pkill AEMV2d
sudo pkill Apexid
sudo pkill AudiB7d
sudo pkill AudiB8d
sudo pkill BlackboxM3
sudo pkill BRZFRS86d
sudo pkill Consult
sudo pkill Emtrond
sudo pkill EMUCANd
sudo pkill EVOXCAN
sudo pkill FordBarraBXCAN
sudo pkill FordBarraBXCANOBD
sudo pkill FordBarraFG2xCAN
sudo pkill FordBarraFG2XCANOBD
sudo pkill FordBarraFGMK1CAN
sudo pkill FordBarraFGMK1CANOBD
sudo pkill GMCANd
sudo pkill Haltechd
sudo pkill Holleyd
sudo pkill Hondatad
sudo pkill Linkd
sudo pkill M800ADLSet1d
sudo pkill M800ADLSet3d
sudo pkill MaxxECUd
sudo pkill Microtechd
sudo pkill MotecM1d
sudo pkill NISSAN370Z
sudo pkill NISSAN350Z
sudo pkill OBD
sudo pkill MegasquirtCan
sudo pkill EMSCAN
sudo pkill WRX2012
sudo pkill Testdaemon
sudo pkill ecoboost
sudo pkill WolfEMS
sudo pkill GMCANOBD
sudo pkill genericcan
sudo pkill FTCAN20
sudo pkill Delta
sudo pkill BigNET
sudo pkill R35
sudo pkill Prado
sudo pkill ProEFI
sudo pkill TeslaSDU
sudo pkill DTAFast
echo "Removing previous Versions"

sudo rm /home/pi/daemons/ProEFI
sudo rm /home/pi/daemons/DTAFast
sudo rm /home/pi/daemons/TeslaSDU
sudo rm /home/pi/daemons/AdaptronicCANd
sudo rm /home/pi/daemons/AEMV2d
sudo rm /home/pi/daemons/Apexid
sudo rm /home/pi/daemons/AudiB7d
sudo rm /home/pi/daemons/AudiB8d
sudo rm /home/pi/daemons/BlackboxM3
sudo rm /home/pi/daemons/BRZFRS86d
sudo rm /home/pi/daemons/Consult
sudo rm /home/pi/daemons/Emtrond
sudo rm /home/pi/daemons/EMUCANd
sudo rm /home/pi/daemons/EMSCAN
sudo rm /home/pi/daemons/EVOXCAN
sudo rm /home/pi/daemons/FordBarraBXCAN
sudo rm /home/pi/daemons/FordBarraBXCANOBD
sudo rm /home/pi/daemons/FordBarraFG2xCAN
sudo rm /home/pi/daemons/FordBarraFG2XCANOBD
sudo rm /home/pi/daemons/FordBarraFGMK1CAN
sudo rm /home/pi/daemons/FordBarraFGMK1CANOBD
sudo rm /home/pi/daemons/Haltechd
sudo rm /home/pi/daemons/Holleyd
sudo rm /home/pi/daemons/Hondatad
sudo rm /home/pi/daemons/Linkd
sudo rm /home/pi/daemons/M800ADLSet1d
sudo rm /home/pi/daemons/M800ADLSet3d
sudo rm /home/pi/daemons/MaxxECUd
sudo rm /home/pi/daemons/Microtechd
sudo rm /home/pi/daemons/MotecM1d
sudo rm /home/pi/daemons/NISSAN370Z
sudo rm /home/pi/daemons/NISSAN350Z
sudo rm /home/pi/daemons/OBD
sudo rm /home/pi/daemons/GMCANd
sudo rm /home/pi/daemons/MegasquirtCan
sudo rm /home/pi/daemons/WRX2012
sudo rm /home/pi/daemons/Testdaemon
sudo rm /home/pi/daemons/ecoboost
sudo rm /home/pi/daemons/WolfEMS
sudo rm /home/pi/daemons/GMCANOBD
sudo rm /home/pi/genericcan
sudo rm /home/pi/FTCAN20
sudo rm /home/pi/Delta
sudo rm /home/pi/BigNET
sudo rm /home/pi/R35
sudo rm /home/pi/Prado

echo "Updating Daemons"
cp -r /home/pi/src/daemons/. /home/pi/daemons/
cp /home/pi/src/*.sh /home/pi/
