#!/bin/sh
echo "Updating Daemons"
cp -r /home/pi/src/daemons/. /home/pi/daemons/
cd /home/pi/daemons
chmod +x OBD
chmod +x Haltechd
chmod +x Consult
#chmod +x BRZ86d
#chmod +x MazdaCAN
#chmod +x EM80d
#chmod +x Mictorechd
