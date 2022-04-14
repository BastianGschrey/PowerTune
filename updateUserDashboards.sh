#!/bin/sh
echo "copy new Dashboards"
rsync -a -v --ignore-existing /home/pi/srcofficial/exampleDash/Logo/*.png /home/pi/Logo/
rsync -a -v --ignore-existing /home/pi/srcofficial/exampleDash/UserDashboards/*.txt /home/pi/UserDashboards/

echo "fix MFD"
cp /home/pi/srcofficial/exampleDash/UserDashboards/MFD.txt /home/pi/UserDashboards/


