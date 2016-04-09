#!/bin/bash
njobs=50
for i in `seq 0 $((njobs-1))`
do
root -l -q -b "makeTree.C($i)"
done

hadd amptTree.root jb*/amptTree.root 
jbi=jb$i

