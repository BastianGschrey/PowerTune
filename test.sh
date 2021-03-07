echo Test SD write speed
sync; dd if=/dev/zero of=~/test.tmp bs=500K count=1024
echo Test SD Read speed
sync; echo 3 | sudo tee /proc/sys/vm/drop_caches
sync; time dd if=~/test.tmp of=/dev/null bs=500K count=1024
echo Delete the temporary file
rm ~/test.tmp
