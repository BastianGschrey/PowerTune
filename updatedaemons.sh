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
echo "Updating Daemons"
cp -r /home/pi/src/daemons/. /home/pi/daemons/
cd /home/pi/daemons
chmod +x OBD
chmod +x Haltechd
chmod +x Consult
chmod +x Apexid 
chmod +x Microtechd 
chmod +x Linkd
#chmod +x BRZ86d
#chmod +x MazdaCAN
#chmod +x EM80d
