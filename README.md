# ampt
A Multi-Phase Transport model for high-energy nuclear collisions. 

How To run in latest forked version and generate ROOT TTree:

#1) cd to Ampt-v1.26t5-v2.26t5. Adjust values in input.ampt as desired. Adjust njobs in submit.sh if need be. Default is 150000 events (3000 events/job times 50 jobs).

#2) Run 'sh submit.sh'.

#3) After all jobs finish, cd to the directory containing all of them (default is Ampt-v1.26t5-v2.26t5/). Make sure the CMS environment has been set up such that ROOT is recognizable. Run 'sh makeTree.sh'.

#4) Done! Output file with TTree will be called amptTree.root.

Note: Depending on how many events you generate, you may surpass your /home, /scratch, or /data quotas. For example, I required 14 G to generate 150000 jobs. In some cases, I had to modify runJobs.slurm to send completed jobs to a directory I made in /store. In such cases, I had to copy over makeTree.sh and makeTree.C to create amptTree.root.

The main source codes are from [Zi-Wei Lin](http://myweb.ecu.edu/linz/ampt/).
