#!/bin/bash

# tasks.sh usage
# tasks.sh <workdirtag> <inputfile> <jobid> <nEvents>

####
tdir=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/preprocessed/

### Read in input arguments
workdir=$tdir$1
# preprocessor parameters:
file=$2
jobid=$3
nEvents=$4

# workdir is tdir/arg2
cd $workdir
eval `scramv1 runtime -sh`
#cmsenv       ## doesn't work

### preprocessor usage:
### preprocessor <inputfile> <jobid> <nEvents> 
### Run preprocessor
../../bin/preprocess_genlevel $file $jobid $nEvents
