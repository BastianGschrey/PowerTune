#!/bin/bash
#Remove Logs 
echo "Cleanup system logs"
sudo rm -r  /var/log
#Modify Journal Conf
echo "Modify Journal.conf"
sudo sed -i -e 's/#Storage=auto/Storage=none/g' /etc/systemd/journald.conf
#Disable rsyslog
echo "Disable rsyslog"
sudo systemctl disable rsyslog
