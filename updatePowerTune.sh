#!/bin/sh
if nc -zw5 www.github.com 443; then
# Get the latest source
		if [ -d /home/pi/src ]; then
		echo "Updating to latest source "
		cd /home/pi/src
		git pull
		else
		echo "Create source directory and clone PowerTune Repo"
		mkdir /home/pi/src
		git clone https://github.com/BastianGschrey/PowerTune.git /home/pi/src  
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
		echo "Update maptiles"
		cp -a /home/pi/src/GPSTracks/.  /home/pi/maptiles/
		else
		mkdir /home/pi/maptiles
		cp -a /home/pi/src/GPSTracks/. /home/pi/maptiles
                fi
# Check if there is a build folder
		if [ -d /home/pi/build ]; then
		echo "Delete previous build folder"
		sudo rm -r /home/pi/build
		mkdir /home/pi/build
		else
		mkdir /home/pi/build
		fi
# Compile PowerTune
		cd /home/pi/build
		echo "Compiling PowerTune ... go grab a Coffee"
                /opt/QT5/bin/qmake /home/pi/src
		make -j4
# Check if the PowerTune executable exists in the build folder
		if [ -f /home/pi/build/PowertuneQMLGui ];then
		echo "Successfully compiled"
		sudo reboot
		else
		echo "Something went wrong"
		sudo rm -r /home/pi/build
		fi
else
echo "Update not possible , Github not reachable check your connection "
fi
