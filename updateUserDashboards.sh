#!/bin/sh
echo "copy new Dashboards"
rsync -a -v --ignore-existing /home/pi/src/exampleDash/Logo/*.png /home/pi/Logo/
rsync -a -v --ignore-existing /home/pi/src/exampleDash/UserDashboards/*.txt /home/pi/UserDashboards/

echo "fix MFD"
cp /home/pi/src/exampleDash/UserDashboards/MFD.txt /home/pi/UserDashboards/


