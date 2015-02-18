#!/bin/bash

# tasks.sh usage
# tasks.sh <workdirtag> <inputfile> <jobid> <nEvents>

####
tdir=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/preprocessed/

### Read in input arguments
binary=$1
workdir=$tdir$2
# preprocessor parameters:
file=$3
dotrkCorr=$4
trkCorrFile=$5
PIDconfig=$6
jobid=$7
nEvents=$8

# workdir is tdir/arg2
cd $workdir

#eval `scramv1 runtime -sh`

### preprocessor usage:
### preprocessor <inputfile> <jobid> <nEvents> 
### Run preprocessor
$binary $file $dotrkCorr $trkCorrFile $PIDconfig $jobid $nEvents
#../../bin/preprocess $file $dotrkCorr $trkCorrFile $PIDconfig $jobid $nEvents
