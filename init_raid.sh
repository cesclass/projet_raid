echo "rm RAID/*"
rm RAID/*

echo "Disques virtuels RAID 0 C"
echo "create vDisk[0:1]r0"
touch RAID/vDisk0r0
touch RAID/vDisk1r0

echo "Disques virtuels RAID 1 C"
echo "create vDisk[0:1]r1"
touch RAID/vDisk0r1
touch RAID/vDisk1r1

echo "Disques virtuels RAID 5 C"
echo "create vDisk[0:3]r5"
touch RAID/vDisk0r5
touch RAID/vDisk1r5
touch RAID/vDisk2r5
touch RAID/vDisk3r5

echo "Disques virtuels RAID 5 JAVA"
echo "create jvDisk[0:3]"
touch RAID/jvDisk0
touch RAID/jvDisk1
touch RAID/jvDisk2
touch RAID/jvDisk3
