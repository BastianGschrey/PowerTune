echo -e "\e[32mTest SD write speed"
echo -e "\e[39m"
sync; dd if=/dev/zero of=~/test.tmp bs=500K count=1024
echo -e "\e[32mTest SD Read Speed"
echo -e "\e[39m"
sync; echo 3 | sudo tee /proc/sys/vm/drop_caches
sync; time dd if=~/test.tmp of=/dev/null bs=500K count=1024
echo -e "\e[32mDelete temp files"
echo -e "\e[39m"
rm ~/test.tmp
echo -e "\e[32mMeasure Volts"
echo -e "\e[39m"
vcgencmd measure_volts core
echo -e "\e[32mChecking CAN BOard"
echo -e "\e[39m"
sudo ifdown can0
sudo ifup can0
echo -e "\e[32mFinished"
echo -e "\e[39m"

