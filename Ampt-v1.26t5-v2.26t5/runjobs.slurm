#!/bin/bash
#SBATCH --nodes=1
#SBATCH --time=0-03:00:00
#SBATCH --mem-per-cpu=4G
#SBATCH --output=jb0d00.out
#SBATCH --job-name="jb0d00pAuv1"

cd /jb0

cp input.ampt ana/
echo "#  AMPT started at " `date` > start.time
./ampt < nseed_runtime > nohup.out
uname -n >> nohup.out
cat start.time >> nohup.out
rm -f start.time
echo "#  AMPT Program finished at " `date` >> nohup.out

# Remove jobs from /scratch and move to /store if output exceeds quota
#cp -rf /scratch/palmerjh/ampt/pAu/bMax_3/prod01/jb0 /store/user/palmerjh/ampt/pAu/bMax_3/prod01
#rm -rf /scratch/palmerjh/ampt/pAu/bMax_3/prod01/jb0

exit 0

