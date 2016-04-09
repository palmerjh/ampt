#!/bin/sh
rm ampt
rm *.o
rm ana/*

make
njobs=50
for i in `seq 0 $(($njobs-1))`
do

jbi=jb$i
mkdir $jbi
mkdir $jbi/ana
cp input.ampt $jbi
cp nseed_runtime $jbi
echo "$(( $i*1000 ))" > $jbi/nseed_runtime
cp ampt $jbi
cp runjobs.slurm $jbi
sed "s/jb0/$jbi/g" $jbi/runjobs.slurm > $jbi/runjob$i.slurm
rm $jbi/runjobs.slurm

cd $jbi
sbatch runjob$i.slurm
cd ..

done



