#!/bin/sh
echo "Checking if Bull Dash1 is installed"
rsync -a -v --ignore-existing /home/pi/src/exampleDash/Logo/Bull_Style1.png /home/pi/Logo/
rsync -a -v --ignore-existing /home/pi/src/exampleDash/UserDashboards/Bull_Style1.txt /home/pi/Userdashboards/
echo "Checking if Bull Dash2 is installed"
rsync -a -v --ignore-existing /home/pi/src/exampleDash/Logo/Bull_Style2.png /home/pi/Logo/
rsync -a -v --ignore-existing /home/pi/src/exampleDash/UserDashboards/Bull_Style2.txt /home/pi/Userdashboards/
echo "Checking if MFD Dash is installed "
rsync -a -v --ignore-existing /home/pi/src/exampleDash/Logo/MFD.png /home/pi/Logo/
rsync -a -v --ignore-existing /home/pi/src/exampleDash/UserDashboards/MFD.txt /home/pi/Userdashboards/
