filename=$1
fileindex=$2
secondind=$2
fileindex="$(( $fileindex - 1 ))"
while [ ! -r $filename.$fileindex -a $fileindex -gt 0 ] ; do
  fileindex="$(( $fileindex - 1 ))"
done
while [ $fileindex -gt 0 ] ; do
  secondind="$(( $fileindex + 1 ))"
  cp $filename.$fileindex $filename.$secondind
  fileindex="$(( $fileindex - 1 ))"
done
cp $filename $filename.1