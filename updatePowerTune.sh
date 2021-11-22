#!/bin/sh
if nc -zw5 www.github.com 443; then
# Get the latest source
		if [ -d /home/pi/src ]; then
		echo "Updating to latest source "
		cd /home/pi/src
		git reset --hard
		git clean -fd
		git pull
		./updatedaemons.sh
		./updateUserDashboards.sh
		else
		echo "Create source directory and clone PowerTune Repo"
		mkdir /home/pi/src
		git clone https://github.com/BastianGschrey/PowerTune.git /home/pi/src  
		cd src
		./updatedaemons.sh
		./updateUserDashboards.sh
		fi
# Check if the Logo Folder Exists
		if [ -d /home/pi/Logo ]; then
		echo "Logo folder exists"
		else
		echo "Create Logo Folder"
		mkdir /home/pi/Logo
		fi
# Check if the maptiles folder exists
		if [ -d /home/pi/maptiles];then
		sudo rm -r  /home/pi/maptiles/
                fi
# Check if there is a build folder
		if [ -d /home/pi/building ]; then
		echo "Delete previous build folder"
		sudo rm -r /home/pi/building
		mkdir /home/pi/building
		else
		mkdir /home/pi/building
		fi
# Compile PowerTune
		cd /home/pi/building
		echo "Compiling PowerTune ... go grab a Coffee"
		/opt/QT5/bin/qmake /home/pi/src
		make -j4
# Check if the PowerTune executable exists in the build folder
		if [ -f /home/pi/building/PowertuneQMLGui ];then
		echo "Successfully compiled"
		mv /home/pi/building /home/pi/build
		sudo reboot
		else
		echo "Something went wrong"
		sudo rm -r /home/pi/building
		fi
else
echo "Update not possible , Github not reachable check your connection "
fi

