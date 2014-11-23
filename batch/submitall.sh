#!/bin/sh

# Flag = test or full
flag=$1

####################################################
### Batch submission parameters for PreProcessor ###
####################################################

#########################
### --- MAIN AREA --- ###
#########################
# ./submitall.sh full
# parameters

#workdir=MC_comparison_recolevel_2nw_fullEv_trkCorrOFF
#workdir=MinBias_withTrackCorrection_2nw_eta_0.8
#workdir=HighMult_withTrackCorrection_2nw_eta_0.8_gogo
workdir=MC_vzhukova-EPOS_RECO_batch_comparison_recolevel_1nw_fullkEv_notrkCorr
dotrkCorr=no
trkCorrlabel=batchjob_TrackCorrection_full_mtrkdedx_added_minptfixed
trkCorrFile=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/trkCorr/${trkCorrlabel}/trkCorrections_0.root
nEvents=-1
queue=1nw
#inputlist="list_minbias"
#inputlist="list_highmult"
inputlist="list_MC_vzhukova-EPOS_RECO_batch_HiForest"

####################
### --- TEST --- ###
####################
# ./submitall.sh test
# parameteres
testworkdir=testsubmission
testdotrkCorr=no
testtrkCorrlabel=batchjob_TrackCorrection_full_mtrkdedx_added_minptfixed
testtrkCorrFile=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/trkCorr/${trkCorrlabel}/trkCorrections_0.root
testnEvents=10
testqueue=test


##########################################################
# script environment

sourcedir=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/src
batchdir=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/batch
tdir=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/preprocessed/
trkFilebase=trkCorr

#########################################################

njobs=`cat $inputlist | wc -l`

### Read in the list of sources
echo -e ""
echo "Inputfile: $inputlist" 
echo "Number of files in the filelist: $njobs" 

lim=`expr $njobs + 1`

### Submit jobs
## Test submission
if [ "$flag" == "test" ]; then
	rm -rf $testworkdir
	mkdir $testworkdir
	cp $inputlist ./$testworkdir
	cp tasks.sh ./$testworkdir
   cd $tdir
	rm -rf $testworkdir
	mkdir $testworkdir
	cd $batchdir/$testworkdir
	echo "TEST SUBMISSION"
	echo "Number of jobs: 2"
	echo -e "\nSending jobs..."
	# Send jobs
	for (( i = 1; i < 3; i++ )); do
		testtrkCorrFileit=$batchdir/$testworkdir/${trkFilebase}_${i}.root
		cp $testtrkCorrFile ${testtrkCorrFileit}
		source=$(awk "NR == $i" $inputlist)
		echo $source 
		bsub -J PreProcess_PKP_test_$i -q $testqueue tasks.sh $testworkdir $source $testdotrkCorr $testtrkCorrFileit $i $testnEvents 
	done
elif [ "$flag" == "full" ]; then
	# Remove previous workdir and create new one
	rm -rf $workdir
	mkdir $workdir
	cp $inputlist ./$workdir
	cp tasks.sh ./$workdir
	cd $tdir
	rm -rf $workdir
	mkdir $workdir
	cd $batchdir/$workdir
	echo "FULL DATASET SUBMISSION"
	echo "WORKDIR: $workdir"
	echo "Number of jobs: $njobs"
	echo -e "\nSending jobs..."
	# Send jobs
	for (( i = 1; i < ($lim); i++ )); do
		trkCorrFileit=$batchdir/$workdir/${trkFilebase}_${i}.root
		cp $trkCorrFile ${trkCorrFileit}
		source=$(awk "NR == $i" $inputlist)
		echo $source
		bsub -J ${workdir}_$i -q $queue tasks.sh $workdir $source $dotrkCorr $trkCorrFileit $i $nEvents
	done
fi 

echo -e "\nAll jobs submitted."
echo -e "WORKDIR: $workdir\n"
echo "Checking job status with 'bjobs -u denglert'."
bjobs -u denglert
