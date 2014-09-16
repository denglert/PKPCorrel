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

#workdir=MinBias_Etalon_2nd
workdir=HighMultiplicty_1nw
nEvents=-1
queue=2nw

####################
### --- TEST --- ###
####################
# ./submitall.sh test
# parameteres
testworkdir=testsubmission
testnEvents=100
testqueue=test


##########################################################
# script environment
inputlist="list_highmult"

sourcedir=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/src
batchdir=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/batch
tdir=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/preprocessed/

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
	rm -rf test
	mkdir test
	cp $inputlist ./test
	cp tasks.sh ./test
   cd $tdir
	rm -rf $testworkdir
	mkdir $testworkdir
	cd $batchdir/test
	echo "TEST SUBMISSION"
	echo "Number of jobs: 2"
	echo -e "\nSending jobs..."
	# Send jobs
	for (( i = 1; i < 3; i++ )); do
		source=$(awk "NR == $i" $inputlist)
		echo $source 
		bsub -J PreProcess_PKP_test_$i -q $testqueue tasks.sh $testworkdir $source $i $testnEvents 
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
	source=$(awk "NR == $i" $inputlist)
	echo $source 
	bsub -J PrepProcess_PKP_$i -q $queue tasks.sh $workdir $source $i $nEvents
	done
fi 

echo -e "\nAll jobs submitted."
echo -e "WORKDIR: $workdir\n"
echo "Checking job status with 'bjobs -u denglert'."
bjobs -u denglert
