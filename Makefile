###################################################################
###  ***  Proton, kaon & pion - charged hadron correlations *** ### 
###################################################################
### ---  Main area  --- ###
###########################
##################
# * PREPROCESS * #
##################
# Command: preproc

# Parameters
label=default
dotrkCorr=yes
trkCorrlabel=TrackCorrection_full_pT_typdep_coarsebins
trkCorrFile=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/trkCorr/$(trkCorrlabel)/trkCorrections_0.root
inputfile=root://eoscms.cern.ch//eos/cms/store/group/phys_heavyions/denglert/pPb2013_HighMultiplicityForest_merged/HIRun2013-28Sep2013-v1_pPb_run_210498-210658/pPb2013_HM_28Sep2013_v1_HiForest_pPb_run_210498-210658_0.root
nEvents=10000
jobid=0

tag=$(label)_nEv_$(nEvents)

############################
# * PREPROCESS - GENLEVEL* #
############################
# Command: preproc_gen

# Parameters
label_preproc_gen=genlevel
inputfile_preproc_gen=root://eoscms.cern.ch//eos/cms/store/group/phys_heavyions/denglert/pPb_MC_HIJING_MB_dEdxcalib_on_500kMCEv_1.9m/pPb_MC_HIJING_MB_mergedHiForest_1.9mEv.root
nEvents_preproc_gen=10000
jobid_preproc_gen=0

tag_preproc_gen=$(label_preproc_gen)_nEv_$(nEvents_preproc_gen)

########################
# * PROCESS BATCHJOB * #
########################
# Command: procbatchjob

# Parameters
#batchjobtag=FULLDATA_EventSel_Finezvtxbins
#batchjobtag=FULLDATA_selfcorrelincl_tracksel_fix_temp
#batchjobtag=FULLDATA_selfcorrelincl_code_fix_1nd_queue
#batchjobtag=FULLDATA_selfcorrelincl_code_fix_1nd_queue_new
#batchjobtag=full_searchingforbkgrbug_temp
#batchjobtag=full_withone_ev_1nd_temp
#batchjobtag=full_withone_ev_and_faultyassocPID_temp
#batchjobtag=MinBias_Etalon_2nd
#batchjobtag=MinBias_HighMulti_All
batchjobtag=MinBias_noTrackCorrection_1nw_eta_0.8_temp
filetoprocess=correl_ana.root
#filetoprocess=correl_selection20.root

##################################
# = PROCESS BATCHJOB & PUBLISH = #
##################################
# Command: procbatchjob_and_publish

procbatchjob_and_publish_tag=FULLDATA_EventSel_Finezvtxbins
procbatchjob_and_publish_filetoprocess=correl_FULL.root
procbatchjob_and_publish_wwwdir=~/www/PionKaonProtCorrelation
procbatchjob_and_publish_wwwwtag=FULLDATA_EventSel_Finezvtxbins_dEtamax_3.00_rev1

########################
# * Process Light * #
########################
# Command: process_light

# Parameters
#batchjobtag=FULLDATA_EventSel_Finezvtxbins
#batchjobtag=FULLDATA_selfcorrelincl_tracksel_fix_temp
#batchjobtag=FULLDATA_selfcorrelincl_code_fix_1nd_queue
#batchjobtag=FULLDATA_selfcorrelincl_code_fix_1nd_queue_new
#batchjobtag=full_searchingforbkgrbug_temp
#batchjobtag=full_withone_ev_1nd_temp
#batchjobtag=full_withone_ev_and_faultyassocPID_temp
#batchjobtag=MinBias_Etalon_2nd
#batchjobtag=MinBias_HighMulti_All
#filetoprocess=correl_MinBiasHighMulti.root
#filetoprocess=correl_selection20.root


###############
# = Publish = #
###############
# Command: publish

publish_tag=MinBias_HighMulti_All
publish_wwwdir=~/www/PionKaonProtCorrelation
publish_wwwtag=MinBias_HighMulti_All_rev4

###########################
### ---  Test area  --- ###
###########################
# Commands:  preproctest, proctest, test
#testfile=root://eoscms.cern.ch//eos/cms/store/group/phys_heavyions/denglert/pPb2013_minBiasForest_merged/pPb2013_minBias_ReReco_run_210498-210658_merged.root
#testfile=root://eoscms//eos/cms/store/group/phys_heavyions/denglert/pPb2013_minBiasForest_merged/HiForest_pPb2013_ReReco_run_210498-210658_9.root
testfile=root://eoscms//eos/cms/store/group/phys_heavyions/denglert/pPb2013_minBiasForest_merged/HiForest_pPb2013_ReReco_run_210498-210658_0.root
#testfile=root://eoscms.cern.ch//eos/cms/store/group/phys_heavyions/denglert/pPb2013_HighMultiplicityForest_merged/HIRun2013-28Sep2013-v1_pPb_run_210498-210658/pPb2013_HM_28Sep2013_v1_HiForest_pPb_run_210498-210658_0.root
testnEvents=10000
testjobid=0
testdotrkCorr=yes
testtrkCorrlabel=TrackCorrection_full_pT_typdep_coarsebins
testtrkCorrFile=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/trkCorr/$(trkCorrlabel)/trkCorrections_0.root

#########################
#### - EtaPhiDistr - ####
#########################
# commands: EtaPhiDistr

EtaPhiDistr_label=EtaPhiDistr_pPb_DATA_trkCorrected_with_PIDcorrections
# DATA
EtaPhiDistr_inputfile=root://eoscms.cern.ch//store/group/phys_heavyions/denglert/pPb2013_HighMultiplicityForest_merged/HIRun2013-28Sep2013-v1_pPb_run_210498-210658/pPb2013_HM_28Sep2013_v1_HiForest_pPb_run_210498-210658_0.root
# MC
#EtaPhiDistr_inputfile=root://eoscms.cern.ch//store/group/phys_heavyions/denglert/pPb_MC_HIJING_MB_dEdxcalib_on_500kMCEv_1.9m/pPb_MC_HIJING_MB_mergedHiForest_1.9mEv.root
EtaPhiDistr_dotrkCorr=yes
#EtaPhiDistr_trkCorrlabel=TrackCorrection_full_pT_typdep_coarsebins
EtaPhiDistr_trkCorrlabel=batchjob_TrackCorrection_full_mtrkdedx_added_minptfixed
EtaPhiDistr_trkCorr=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/trkCorr/$(EtaPhiDistr_trkCorrlabel)/trkCorrections_0.root
EtaPhiDistr_nEvents=100000
EtaPhiDistr_jobid=0
EtaPhiDistr_tag=$(EtaPhiDistr_label)_nEv_$(EtaPhiDistr_nEvents)

#############################
#### - TrackCorrection - ####
#############################
# commands: TrackCorrection

TrackCorrection_label=TrackCorrection_charge_negative
TrackCorrection_inputfileDATA=root://eoscms.cern.ch//store/group/phys_heavyions/denglert/pPb2013_HighMultiplicityForest_merged/HIRun2013-28Sep2013-v1_pPb_run_210498-210658/pPb2013_HM_28Sep2013_v1_HiForest_pPb_run_210498-210658_0.root
TrackCorrection_inputfileMC=root://eoscms.cern.ch//store/group/phys_heavyions/denglert/pPb_MC_HIJING_MB_HiForest_dEdxcalib_on_500kMCEv_1.9m_mtrkdedx_added_minptfix/pPb_MC_HIJING_MB_mergedHiForest_1.9mEv.root
TrackCorrection_sampleType=kPAMC
TrackCorrection_nEventsDATA=-1
TrackCorrection_nEventsMC=-1
TrackCorrection_jobid=0

TrackCorrection_tag=$(TrackCorrection_label)

###################################
### - TrackCorrection_viewer - ####
###################################
# commands: TrackCorrection_viewer
#trkdir_TrackCorrection_viewer=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/trkCorr/batchjob_TrackCorrection_full_mtrkdedx_added_minptfixed/
trkdir_TrackCorrection_viewer=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/trkCorr/TrackCorrection_charge_negative/
inputfilebase_TrackCorrection_viewer=trkCorrections_0.root
inputfile_TrackCorrection_viewer=$(trkdir_TrackCorrection_viewer)$(inputfilebase_TrackCorrection_viewer)

#####################
### - PIDSetup - ####
#####################
# commands: PIDSetup
inputfile_PIDSetup=dedxmap_run_210498-210658_merged_full.root

####################
### - dEdxMap - ####
####################
# commands: dEdxMap

label_dEdxMap=HIJING_MC_MB_original
#inputfile_dEdxMap=root://eoscms.cern.ch//eos/cms/store/group/phys_heavyions/denglert/pPb2013_minBiasForest_merged/pPb2013_minBias_ReReco_run_210498-210658_merged.root
#inputfile_dEdxMap=root://eoscms.cern.ch//store/group/phys_heavyions/denglert/pPb_MC_HIJING_MB_dEdxcalib_on_500kMCEv_1.9m_mtrkdedx_added/pPb_MC_HIJING_MB_HiForest_mergedHiForest_1.9mEv.root
inputfile_dEdxMap=root://eoscms.cern.ch//store/group/phys_heavyions/denglert/pPb_MC_HIJING_MB_HiForest_dEdxcalib_on_500kMCEv_1.9m_mtrkdedx_added_minptfix/pPb_MC_HIJING_MB_mergedHiForest_1.9mEv.root
nEvents_dEdxMap=10000
jobid_dEdxMap=0 

##########################################################
all :


##########################################################
preproc : build_preproc
	@rm -rf ./preprocessed/$(tag); mkdir ./preprocessed/$(tag); 
	@echo -e "\nPREPROCESSING."
	@echo
	@echo WORKDIR: $(tag)
	@echo 
	@echo Testfile: $(inputfile)
	@echo Number of events: $(nEvents)
	@echo
	cd ./preprocessed/$(tag); ../../bin/preprocess $(inputfile) $(jobid) $(nEvents);

preproc_gen : build_preproc_gen
	@rm -rf ./preprocessed/$(tag_preproc_gen); mkdir ./preprocessed/$(tag_preproc_gen); 
	@echo -e "\nPREPROCESSING."
	@echo
	@echo WORKDIR: $(tag_preproc_gen)
	@echo 
	@echo Testfile: $(inputfile_preproc_gen)
	@echo Number of events: $(nEvents_preproc_gen)
	@echo
	cd ./preprocessed/$(tag_preproc_gen); ../../bin/preprocess_genlevel $(inputfile_preproc_gen) $(jobid_preproc_gen) $(nEvents_preproc_gen);

SimplePreProc: build_SimplePreProc
	@rm -rf ./preprocessed/$(tag); mkdir ./preprocessed/$(tag); 
	@echo -e "\nSIMPLE PREPROCESSING."
	@echo
	@echo WORKDIR: $(tag)
	@echo 
	@echo Testfile: $(inputfile)
	@echo Number of events: $(nEvents)
	@echo
	cd ./preprocessed/$(tag); ../../bin/SimplePreProc $(inputfile) $(jobid) $(nEvents);

proc : build_proc
	@rm -rf ./results/$(tag)
	./bin/process ./preprocessed/$(tag)/correl_analysis_$(jobid).root $(tag)  


procbatchjob : build_proc
	@rm -rf ./results/$(batchjobtag);
	./bin/process ./preprocessed/$(batchjobtag)/$(filetoprocess) $(batchjobtag)  


procbatchjob_and_publish : build_proc
	@rm -rf ./results/$(procbatchjob_and_publish_tag)
	./bin/process ./preprocessed/$(procbatchjob_and_publish_tag)/$(procbatchjob_and_publish_filetoprocess) $(procbatchjob_and_publish_tag)  
	./makePublic.sh $(procbatchjob_and_publish_tag) $(procbatchjob_and_publish_wwwdir) $(procbatchjob_and_publish_wwwwtag)


publish :
	./makePublic.sh $(publish_tag) $(publish_wwwdir) $(publish_wwwtag)

###### - Test - ########
preproctest : build_preproc
	@rm -rf ./preprocessed/test; mkdir ./preprocessed/test; 
	@echo -e "\nPREPROCESSING TEST."
	@echo
	@echo WORKDIR: test
	@echo Testfile: $(testfile)
	@echo Number of events: $(testnEvents)
	@echo
	cd ./preprocessed/test; ../../bin/preprocess $(testfile) $(testdotrkCorr) $(testtrkCorrFile) $(testjobid) $(testnEvents);

proctest : build_proc
	@rm -rf ./correl1D/test ./correl2D/test ./sigtobkgrvspt/test/ ./spectrum/test/ ./v2vspt/test ./fit/test;
	./bin/process ./preprocessed/test/correl_analysis_$(testjobid).root test 


######################################################
### AnalysisFwTest
AnaFwTest : build_AnaFwTest
	./bin/AnaFwTest $(inputfile_AnaFwTest);

build_AnaFwTest : 
	@cd src; make ../bin/AnaFwTest

######################################################
### EtaPhiDistr
EtaPhiDistr : build_EtaPhiDistr
	@rm -rf ./results/$(EtaPhiDistr_tag); mkdir ./results/$(EtaPhiDistr_tag); 
	@echo -e "\nPREPROCESSING."
	@echo
	@echo WORKDIR: $(EtaPhiDistr_tag)
	@echo 
	@echo Testfile: $(EtaPhiDistr_inputfile)
	@echo Number of events: $(EtaPhiDistr_nEvents)
	@echo
	cd ./results/$(EtaPhiDistr_tag); ../../bin/EtaPhiDistr $(EtaPhiDistr_inputfile) $(EtaPhiDistr_dotrkCorr) $(EtaPhiDistr_trkCorr) $(EtaPhiDistr_jobid) $(EtaPhiDistr_nEvents);

######################################################
### TrackCorrection
TrackCorrection : build_TrackCorrection
	@rm -rf ./trkCorr/$(TrackCorrection_tag); mkdir ./trkCorr/$(TrackCorrection_tag); 
	@echo -e "\nTrackCorrection."
	@echo
	@echo WORKDIR: $(TrackCorrection_tag)
	@echo 
	@echo DATA - file: $(TrackCorrection_inputfileDATA)
	@echo DATA - Number of events: $(TrackCorrection_nEventsDATA)
	@echo MC - file: $(TrackCorrection_inputfileMC)
	@echo MC - Number of events: $(TrackCorrection_nEventsMC)
	@echo
	cd ./trkCorr/$(TrackCorrection_tag); ../../bin/TrackCorrection $(TrackCorrection_inputfileDATA) $(TrackCorrection_inputfileMC) $(TrackCorrection_sampleType) $(TrackCorrection_jobid) $(TrackCorrection_nEventsDATA) $(TrackCorrection_nEventsMC);

######################################################
### PIDSetup
PIDSetup : build_PIDSetup
	cd PIDtest; ../bin/PIDSetup $(inputfile_PIDSetup);

build_PIDSetup : 
	@cd src; make ../bin/PIDSetup

######################################################
### TrackCorrection_viewer
TrackCorrection_viewer : build_TrackCorrection_viewer
	cd $(trkdir_TrackCorrection_viewer); rm *.png; rm *.pdf; ../../bin/TrackCorrection_viewer $(inputfile_TrackCorrection_viewer);

build_TrackCorrection_viewer : 
	@cd src; make ../bin/TrackCorrection_viewer

######################################################
### dEdxMap
dEdxMap : build_dEdxMap
	@rm -rf ./dEdxMaps/$(label_dEdxMap); mkdir ./dEdxMaps/$(label_dEdxMap); 
	@echo -e "\ndEdxmap."
	@echo
	@echo WORKDIR: $(label_dEdxMap)
	cd ./dEdxMaps/$(label_dEdxMap); ../../bin/makedEdxMap $(inputfile_dEdxMap) $(jobid_dEdxMap) $(nEvents_dEdxMap);

build_dEdxMap : 
	@cd src; make ../bin/makedEdxMap

######################################################
### UtilityTest
utiltest : build_utiltest
	./bin/utilitytest

build_utiltest :
	@cd src; make ../bin/utilitytest

######################################################
# Build
build :
	@cd src; make

build_preproc:
	@cd src; make ../bin/preprocess

build_preproc_gen:
	@cd src; make ../bin/preprocess_genlevel

build_SimplePreProc:
	@cd src; make ../bin/SimplePreProc

build_EtaPhiDistr:
	@cd src; make ../bin/EtaPhiDistr

build_TrackCorrection:
	@cd src; make ../bin/TrackCorrection

build_proc:
	@cd src; make ../bin/process
