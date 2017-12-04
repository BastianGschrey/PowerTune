# PowerTune
PowerTune is a Modern Gauge Display for Apexi Power FC and Adaptronic Select ECU based on QT5.8




Testet Platforms :

Ubuntu 17.04 
Windows 10 
Raspbian Jessie 2017-04-10


#### Implemented PowerFC variants:

#### Mazda :
* 13B-REW 

#### Nissan :
* RB20DET
* RB26DETT
* SR20DET1
* CA18DET
* RB25DET

#### Toyota :  
* 4E-FTE2
* 1JZ-GTE
* 1JZ-GTE3
* 1ZZ-FRE
* 2jZ-GTE1
* 2ZZ-GE
* 3S-GE
* 3S-GTE3
* 3S-GTE
* 3E-FTE2



| Tested Vehicles Apexi PFC :      | ECU Variant:          | FC Hako:      | FC Datalogit:  |
| -------------------------------- |:---------------------:|:-------------:|:--------------:|
| Mazda RX7 FD3S         | (13B-REW)   | <big>__✓__     | |
| Toyota MR2     | (3S-GTE3)        | <big>__✓__     | |
| Nissan Skyline R32 GT-TR    | (RB26DETT)       |    |<big>__✓__    |


#### Adaptronic Variants :

* Adaptronic Select series:
* All variants
* Adaptronic Modular series :
* All variants

#### Tested Vehicles Adaptronic :              ECU Variant:         
* FD3S                                         PNP S8*           <big>__✓__       

Implemented Features :

* Remote control GoPro Recording on off
* Logging to user selectable CSV file for Adaptronic 
* Logging to user selectable txt file for Power FC 
* Differential Aux input Settings for Power FC (2 for FC Hako / 4 For Datalogit) 
* GPS for NMEA 0183 compliant devices via Serial (Tested with BU-353S4 GPS Mouse) 
* Switching between metric and Imperial values


<big>_Build a Raspberry Pi image with Buildroot:_</big>


This was tested on Ubuntu 17.04

  ```
  $ git clone https://github.com/MarkusIppy/buildroot.git
  ```
  ```
  $ cd buildroot
  ```
  ```
  $ make powertune_rpi3_defconfig
  ```

If you use another screen than the official pi Screen , edit the following file 

  ```
  $ nano /buildroot/board/powertune/rpi3/rootfs/profile.d/qt5-env.sh
  ```

  Press "Ctrl+x" when you finished modifing the file and plress "y" to save

  ```
  $ make
  ```



This will download all required sourcecode into a seperate folder called "dl"
Once the compilation has finished it will create a pi image called "powertune.img" in the folder
/buildroot/output/images

Flash the image to your SD card ( you can user Etcher or do it via command Line ) 
Etcher can be downloaded her https://etcher.io/

The image currently has a boot time of approx 17 seconds until PowerTune is starting ( i am still working on optimization ) 

About the image :
The username and password are :

user: root
pw: root

Not all linux commands are supported and there is no need to use sudo 

Should you wish to use Wlan :

quit powertune 

login with username and password

Type the following :

$nano /etc/network/wpa_supplicant.conf

Enter your WLAN SSID and Password 

Press "Ctrl+x" then press "y" to save

$reboot

Now your pi will always log into WLAN at boot 


<big>_Build your own Debian Stretch image:_</big>


On a fresh Debian Stretch image build QT5.8 
i made some scripts here :
```
https://github.com/MarkusIppy/QT5.x-raspbian-stretch
```

Now download the sourcecode for PowerTune
```
$ git clone https://github.com/BastianGschrey/PowerTune.git
```
Your source code is now available in /home/pi/PowerTune

Now creade a directory where we compile and start PowerTune from :
```
$ sudo mkdir /opt/PowerTune
```
```
$ sudo chown pi:pi /opt/PowerTune
```

Compile PowerTune:
```
$ cd /opt/PowerTune
```

```
$ qmake /home/pi/PowerTune/PowerTuneQMLGui.pro
```
```
$ make -j4
```
now PowerTune is installed in /opt/PowerTune



Create a start script for PowerTune :

```
$ sudo nano /home/pi/startPowerTune.sh

```
Insert the following text into startPowerTune.sh

```
export QT_QPA_EGLFS_PHYSICAL_WIDTH=155
export QT_QPA_EGLFS_PHYSICAL_HEIGHT=86
/opt/PowerTune/PowerTuneQMLGui
```
save the file by pressing "ctrl"+"x" and then press "y"

Make the script executable :
```
$ sudo chmod +x /home/pi/startPowerTune.sh 
```

Test the script 
```
$ ./startPowerTune.sh
```

Now we can build ourselfs a update script for PowerTune
```
$ sudo nano /home/pi/update.sh
```
Insert the following into the file 
```
cd /home/pi/PowerTune
git pull
cd /opt/PowerTune
qmake /home/pi/PowerTune/PowerTuneQMLGui.pro
make -j4
```
save the file by pressing "ctrl"+"x" and then press "y"

Make the script executable :
```
$ sudo chmod +x /home/pi/update.sh 
```

Making PowerTune Autostart at Boot

Create a sercive to launch the startPowerTune.sh script at boot 

```
$ sudo nano /etc/systemd/system/PowerTune.service

```

Insert the following text into PowerTune.service

```
[Unit]

Description=PowerTune

[Service]

Type=simple

ExecStart=/home/pi/startPowerTune.sh

[Install]

WantedBy=multi-user.target

```

Test if the script works:
```
$ sudo systemctl start PowerTune.service
```
If PowerTune is launching , quit PowerTune

Now enable the script 

```
$ sudo systemctl enable PowerTune.service
```

Reboot your pi and you should see PowerTune starting at boot 
 
```
$ sudo reboot
```


12.Launch a custom video at boot with OMXPlayer
 

```
$ sudo nano /etc/systemd/system/bootsplash.service
```

Copy the following content into the file and save it ( this example assumes you have a video called "bootvideo.mp4" in the folder: "/home/pi/"  :

```
[Unit]
Description=BootSplash
DefaultDependencies=no
After=local-fs.target
Before=basic.target

[Service]
Type=simple
ExecStart=/usr/bin/omxplayer -b /home/pi/bootvideo.mp4

[Install]
WantedBy=getty.target

```


Test if the script works:
```
$ sudo systemctl start bootsplash.service
```
If the video is playing , then enable the script:
```
$ sudo systemctl enable bootsplash.service
```
Reboot your pi and you should see your video at boot 
```
$ sudo reboot
```
