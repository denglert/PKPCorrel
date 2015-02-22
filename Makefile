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
label=testpreproc
dotrkCorr=no
trkCorrlabel=TrackCorrection_full_pT_typdep_coarsebins
trkCorrFile=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/trkCorr/$(trkCorrlabel)/trkCorrections_0.root
Anaconfig=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/AnalysisFW/setup/MinBias
PIDconfig=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/PIDUtils/config/config_default
#inputfile=root://eoscms//eos/cms/store/group/phys_heavyions/denglert/pPb2013_HighMultiplicityForest_merged/HIRun2013-28Sep2013-v1_pPb_run_210498-210658/pPb2013_HM_28Sep2013_v1_HiForest_pPb_run_210498-210658_1.root
#inputfile=root://eoscms//eos/cms/store/group/phys_heavyions/denglert/pPb2013_HighMultiplicityForest_merged/HIRun2013-PromptReco-v1_Pbp_run_211313-211631/pPb2013_HM_PromptReco-v1_HiForest_Pbp_run_211313-211631_16.root
inputfile=root://eoscms//eos/cms/store/group/phys_heavyions/denglert/pPb2013_minBiasForest_merged/HiForest_pPb2013_PromptReco_run_211313-211631_12.root
#inputfile=root://eoscms.cern.ch//eos/cms/store/group/phys_heavyions/denglert/pPb_MC_vzhukova-EPOS_RECO_batch_HiForest_trketafix/pPb_MC_HiForest_allbatch1.root
nEvents=-1
jobid=0

tag=$(label)_nEv_$(nEvents)

############################
# * PREPROCESS - GENLEVEL* #
############################
# Command: preproc_gen

# Parameters
label_preproc_gen=test
#inputfile_preproc_gen=root://eoscms.cern.ch//eos/cms/store/group/phys_heavyions/denglert/pPb_MC_HIJING_MB_HiForest_dEdxcalib_on_500kMCEv_1.9m_mtrkdedx_added_minptfix/pPb_MC_HIJING_MB_mergedHiForest_1.9mEv.root
inputfile_preproc_gen=root://eoscms.cern.ch//eos/cms/store/group/phys_heavyions/denglert/pPb_MC_vzhukova-EPOS_RECO_batch_HiForest/pPb_MC_HiForest_allbatch.root
nEvents_preproc_gen=200
jobid_preproc_gen=0

tag_preproc_gen=$(label_preproc_gen)_nEv_$(nEvents_preproc_gen)

########################
# * PROCESS BATCHJOB * #
########################
# Command: procbatchjob
#Compare_vns_inputfile2=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/results/MC_vzhukova-EPOS_RECO_batch_comparison_recolevel_2nd_chariot_proton_mindEdx_3.4_trkCorr_no/dump.root

#Compare_vns_inputfile1=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/results/MC_vzhukova-EPOS_RECO_batch_comparison_genelevel_2nd_beta/dump.root

# Parameters
#batchjobtag=full_searchingforbkgrbug_temp
#batchjobtag=full_withone_ev_1nd_temp
#batchjobtag=full_withone_ev_and_faultyassocPID_temp
#batchjobtag=MinBias_Etalon_2nd
#batchjobtag=MinBias_Etalon_2nd_try2
#batchjobtag=MinBias_2nw_trkcorrON_eta_0.8_temp
#batchjobtag=MinBias_Etalon_2nw_notrkCorr
#batchjobtag=MinBias_HighMulti_All
#batchjobtag=DipStudy_try1
#batchjobtag=MC_vzhukova-EPOS_RECO_batch_comparison_genelevel_2nd_fullkEv
#batchjobtag=MC_vzhukova-EPOS_RECO_batch_comparison_genelevel_2nd_fullkEv_etafixed
#batchjobtag=MC_vzhukova-EPOS_RECO_batch_comparison_recolevel_2nd_fullkEv_withtrkCorr
#batchjobtag=MinBias_noTrackCorrection_1nw_eta_0.8_temp
#batchjobtag=MinBias_withTrackCorrection_2nw_eta_0.8_fixedcode_temp
#batchjobtag=MinBias_withTrackCorrection_eta_0.8_fixedcode_temp
#batchjobtag=MC_vzhukova-EPOS_RECO_batch_comparison_genelevel_2nd_full_updated
#batchjobtag=MC_vzhukova-EPOS_RECO_batch_comparison_recolevel_2nd_chariot_trkCorr_no
#batchjobtag=test_nEv_200000
#batchjobtag=MC_vzhukova-EPOS_RECO_batch_comparison_genelevel_2nd_beta
#batchjobtag=MC_vzhukova-EPOS_RECO_batch_comparison_recolevel_2nd_chariot_proton_mindEdx_3.4_trkCorr_no
#batchjobtag=PIDscan_MinBias_config_default_trkCorr_no_temp/
#batchjobtag=PIDscan_HighMultiplicity_config_strict_2_trkCorr_no_temp
#batchjobtag=MC_vzhukova-EPOS_RECO_batch_comparison_genelevel_2nd_beta

#batchjobtag=MC_vzhukova-EPOS_RECO_batch_comparison_recolevel_2nd_chariot_proton_mindEdx_3.4_trkCorr_no
#batchjobtag=MC_vzhukova-EPOS_RECO_batch_comparison_genelevel_2nd_beta
batchjobtag=MC_vzhukova-EPOS_RECO_batch_comparison_recolevel_2nd_chariot_proton_mindEdx_3.4_trkCorr_no

# PIDscan HighMulti
#batchjobtag=PIDscan_MinBias_config_looser_2_trkCorr_no/
#batchjobtag=PIDscan_MinBias_config_looser_1_trkCorr_no/
#batchjobtag=PIDscan_MinBias_config_default_trkCorr_no/
#batchjobtag=PIDscan_MinBias_config_strict_1_trkCorr_no/
#batchjobtag=PIDscan_MinBias_config_strict_2_trkCorr_no/

# PIDscan MinBias 
#batchjobtag=PIDscan_MinBias_config_looser_2_trkCorr_no/
#batchjobtag=PIDscan_MinBias_config_looser_1_trkCorr_no/
#batchjobtag=PIDscan_MinBias_config_default_trkCorr_no/
#batchjobtag=PIDscan_MinBias_config_strict_1_trkCorr_no/
#batchjobtag=PIDscan_MinBias_config_strict_2_trkCorr_no/

#filetoprocess=correl_FULL.root
filetoprocess=correl_analysis_1.root
#filetoprocess=correl_tempmerge.root
#filetoprocess=correl_full.root
#filetoprocess=correl_MinBiasHighMulti.root
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
publish_wwwtag=MinBias_HighMulti_All_rev6

###########################
### ---  Test area  --- ###
###########################
# Commands:  preproctest, proctest, test
#testfile=root://eoscms.cern.ch//eos/cms/store/group/phys_heavyions/denglert/pPb2013_minBiasForest_merged/pPb2013_minBias_ReReco_run_210498-210658_merged.root
#testfile=root://eoscms//eos/cms/store/group/phys_heavyions/denglert/pPb2013_minBiasForest_merged/HiForest_pPb2013_ReReco_run_210498-210658_9.root
#testfile=root://eoscms//eos/cms/store/group/phys_heavyions/denglert/pPb2013_minBiasForest_merged/HiForest_pPb2013_ReReco_run_210498-210658_0.root
#testfile=root://eoscms//eos/cms/store/group/phys_heavyions/denglert/pPb2013_minBiasForest_merged/HiForest_pPb2013_PromptReco_run_210676-211256_6.root
#testfile=root://eoscms//eos/cms/store/group/phys_heavyions/denglert/pPb2013_minBiasForest_merged/HiForest_pPb2013_PromptReco_run_210676-211256_0.root
#testfile=root://eoscms//eos/cms/store/group/phys_heavyions/denglert/pPb2013_minBiasForest_merged/HiForest_pPb2013_PromptReco_run_211313-211631_11.root
#testfile=root://eoscms//eos/cms/store/group/phys_heavyions/denglert/pPb2013_HighMultiplicityForest_merged/HIRun2013-PromptReco-v1_Pbp_run_211313-211631/pPb2013_HM_PromptReco-v1_HiForest_Pbp_run_211313-211631_2.root
#testfile=root://eoscms//eos/cms/store/group/phys_heavyions/denglert/pPb2013_minBiasForest_merged/HiForest_pPb2013_PromptReco_run_211313-211631_11.root

# MINBIAS
#testfile=root://eoscms//eos/cms/store/group/phys_heavyions/denglert/pPb2013_minBiasForest_merged/HiForest_pPb2013_PromptReco_run_211313-211631_8.root

# HIGH MULT
#testfile=root://eoscms.cern.ch//eos/cms/store/group/phys_heavyions/denglert/pPb2013_HighMultiplicityForest_merged/HIRun2013-28Sep2013-v1_pPb_run_210498-210658/pPb2013_HM_28Sep2013_v1_HiForest_pPb_run_210498-210658_0.root

# MC
testfile=root://eoscms.cern.ch//eos/cms/store/group/phys_heavyions/denglert/pPb_MC_vzhukova-EPOS_RECO_batch_HiForest/pPb_MC_HiForest_allbatch.root

testnEvents=-1
testjobid=0
testdotrkCorr=no
testtrkCorrlabel=TrackCorrection_full_pT_typdep_coarsebins
testtrkCorrFile=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/trkCorr/$(trkCorrlabel)/trkCorrections_0.root

#########################
#### - EtaPhiDistr - ####
#########################
# commands: EtaPhiDistr

#EtaPhiDistr_label=EtaPhiDistr_pPb_MinBias_HIJING_MC_${EtaPhiDistr_dotrkCorr}trkCorr
EtaPhiDistr_label=EtaPhiDistr_pPb_MinBias_DATA_PIDconfig_strict_2_${EtaPhiDistr_dotrkCorr}_trkCorr

# DATA
#EtaPhiDistr_inputfile=root://eoscms.cern.ch//store/group/phys_heavyions/denglert/pPb2013_HighMultiplicityForest_merged/HIRun2013-28Sep2013-v1_pPb_run_210498-210658/pPb2013_HM_28Sep2013_v1_HiForest_pPb_run_210498-210658_0.root
#EtaPhiDistr_inputfile=root://eoscms//eos/cms/store/group/phys_heavyions/denglert/pPb2013_minBiasForest_merged/HiForest_pPb2013_PromptReco_run_211313-211631_8.root
EtaPhiDistr_inputfile=root://eoscms//eos/cms/store/group/phys_heavyions/denglert/pPb2013_minBiasForest_merged/HiForest_pPb2013_PromptReco_run_210676-211256_17.root

# MC
#EtaPhiDistr_inputfile=root://eoscms.cern.ch//store/group/phys_heavyions/denglert/pPb_MC_HIJING_MB_dEdxcalib_on_500kMCEv_1.9m/pPb_MC_HIJING_MB_mergedHiForest_1.9mEv.root

EtaPhiDistr_dotrkCorr=no
EtaPhiDistr_trkCorrlabel=batchjob_TrackCorrection_full_mtrkdedx_added_minptfixed
EtaPhiDistr_trkCorr=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/trkCorr/$(EtaPhiDistr_trkCorrlabel)/trkCorrections_0.root
EtaPhiDistr_PIDconfig=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/PIDUtils/config/config_strict_2
EtaPhiDistr_nEvents=100000
EtaPhiDistr_jobid=0
EtaPhiDistr_tag=$(EtaPhiDistr_label)_nEv_$(EtaPhiDistr_nEvents)

#############################
#### - TrackCorrection - ####
#############################
# commands: TrackCorrection

#TrackCorrection_label=TrackCorrection_singlebin_forfig
TrackCorrection_label=trkCorr_HIJING_2mEv_final_full
#TrackCorrection_inputfileDATA=root://eoscms.cern.ch//store/group/phys_heavyions/denglert/pPb2013_HighMultiplicityForest_merged/HIRun2013-28Sep2013-v1_pPb_run_210498-210658/pPb2013_HM_28Sep2013_v1_HiForest_pPb_run_210498-210658_0.root
TrackCorrection_inputfileDATA=root://eoscms.cern.ch//store/group/phys_heavyions/denglert/pPb2013_HighMultiplicityForest_merged/HIRun2013-28Sep2013-v1_pPb_run_210498-210658/pPb2013_HM_28Sep2013_v1_HiForest_pPb_run_210498-210658_0.root
#TrackCorrection_inputfileMC=root://eoscms.cern.ch//store/group/phys_heavyions/denglert/pPb_MC_HIJING_MB_HiForest_dEdxcalib_on_500kMCEv_1.9m_mtrkdedx_added_minptfix/pPb_MC_HIJING_MB_mergedHiForest_1.9mEv.root
TrackCorrection_inputfileMC=root://eoscms.cern.ch//store/group/phys_heavyions/denglert/pPb_MC_HIJING_MB_HiForest_dEdxcalib_on_500kMCEv_1.9m_mtrkdedx_added_minptfix_trketafix/pPb_MC_mergedHiForest.root
TrackCorrection_sampleType=kPAMC
TrackCorrection_nEventsDATA=-1
TrackCorrection_nEventsMC=-1
TrackCorrection_PIDConfig=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/PIDUtils/config/default
TrackCorrection_jobid=0

TrackCorrection_tag=$(TrackCorrection_label)

###################################
### - TrackCorrection_viewer - ####
###################################
# commands: TrackCorrection_viewer
#trkdir_TrackCorrection_viewer=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/trkCorr/trkCorr_HIJING_fillsimtracksfix_test/
trkdir_TrackCorrection_viewer=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/trkCorr/trkCorr_HIJING_final_beta/
#trkdir_TrackCorrection_viewer=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/trkCorr/TrackCorrection_singlebin_forfig/
inputfilebase_TrackCorrection_viewer=trkCorrections_0.root
inputfile_TrackCorrection_viewer=$(trkdir_TrackCorrection_viewer)$(inputfilebase_TrackCorrection_viewer)

##############################
#### - MC_CrosscheckFig - ####
##############################
# commands: MC_CrosscheckFig

MC_CrosscheckFig_label=MC_gene_reco_level_CrossCheck_EPOS_trkCorr_no
MC_CrosscheckFig_inputfileRECO=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/results/MC_vzhukova-EPOS_RECO_batch_comparison_recolevel_2nd_chariot_trkCorr_no/dump.root
#MC_CrosscheckFig_inputfileGENE=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/results/MC_vzhukova-EPOS_RECO_batch_comparison_genelevel_2nd_full_updated/dump.root
MC_CrosscheckFig_inputfileGENE=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/results/MC_vzhukova-EPOS_RECO_batch_comparison_genelevel_2nd_beta/dump.root
#MC_CrosscheckFig_inputfileGENE=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/results/MC_vzhukova-EPOS_RECO_batch_comparison_genelevel_2nd_fullkEv_etafixed/dump.root

#########################
#### - Compare_vns - ####
#########################
# commands: Compare_vns

Compare_vns_label=MC_gene_reco_level_CrossCheck_EPOS_trkCorr_no_offset_protmindEdx3.4
Compare_vns_label1=gen
Compare_vns_label2=reco
Compare_vns_inputfile1=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/results/MC_vzhukova-EPOS_RECO_batch_comparison_genelevel_2nd_beta/dump.root
Compare_vns_inputfile2=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/results/MC_vzhukova-EPOS_RECO_batch_comparison_recolevel_2nd_chariot_proton_mindEdx_3.4_trkCorr_no/dump.root
#Compare_vns_inputfile2=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/results/MC_vzhukova-EPOS_RECO_batch_comparison_recolevel_2nd_chariot_trkCorr_no/dump.root

#########################
#### - Compare_vns - ####
#########################
# commands: Compare_vns

Compare_vns_multi_workdir=MultiComparsion

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
	@echo dotrkCorr: $(dotrkCorr)
	@echo trkCorrFile: $(trkCorrFile)
	@echo PIDconfig: $(PIDconfig)
	@echo Number of events: $(nEvents)
	@echo
	cd ./preprocessed/$(tag); ../../bin/preprocess $(inputfile) $(dotrkCorr) $(trkCorrFile) $(Anaconfig) $(PIDconfig) $(jobid) $(nEvents);


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
	@echo PIDconfig: $(EtaPhiDistr_PIDconfig)
	@echo
	cd ./results/$(EtaPhiDistr_tag); ../../bin/EtaPhiDistr $(EtaPhiDistr_inputfile) $(EtaPhiDistr_dotrkCorr) $(EtaPhiDistr_trkCorr) $(EtaPhiDistr_PIDconfig) $(EtaPhiDistr_jobid) $(EtaPhiDistr_nEvents);

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
	cd ./trkCorr/$(TrackCorrection_tag); ../../bin/TrackCorrection $(TrackCorrection_inputfileDATA) $(TrackCorrection_inputfileMC) $(TrackCorrection_sampleType) $(TrackCorrection_jobid) $(TrackCorrection_nEventsDATA) $(TrackCorrection_nEventsMC) $(TrackCorrection_PIDConfig);

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

### MC_CrosscheckFig
MC_CrosscheckFig : build_MC_CrosscheckFig
	@rm -rf ./results/$(MC_CrosscheckFig_label); mkdir ./results/$(MC_CrosscheckFig_label); 
	@echo -e "\nMC_CrosscheckFig"
	@echo
	@echo WORKDIR: $(MC_CrosscheckFig_label)
	cd ./results/$(MC_CrosscheckFig_label); ../../bin/MC_CrosscheckFig $(MC_CrosscheckFig_inputfileRECO) $(MC_CrosscheckFig_inputfileGENE)

build_MC_CrosscheckFig : 
	@cd src; make ../bin/MC_CrosscheckFig


### Compare_vns
Compare_vns : build_Compare_vns
	@rm -rf ./results/$(Compare_vns_label); mkdir ./results/$(Compare_vns_label); 
	@echo -e "\nCompare_vns"
	@echo
	@echo WORKDIR: $(Compare_vns_label)
	cd ./results/$(Compare_vns_label); ../../bin/Compare_vns $(Compare_vns_label1) $(Compare_vns_label2) $(Compare_vns_inputfile1) $(Compare_vns_inputfile2)

build_Compare_vns : 
	@cd src; make ../bin/Compare_vns

### Compare_vns_multi
Compare_vns_multi : build_Compare_vns_multi
	@rm -rf ./results/$(Compare_vns_multi_workdir); mkdir ./results/$(Compare_vns_multi_workdir); 
	@echo -e "\nCompare_vns_multi"
	@echo
	@echo WORKDIR: $(Compare_vns_multi_workdir)
	cd ./results/$(Compare_vns_multi_workdir); ../../bin/Compare_vns_multi

build_Compare_vns_multi : 
	@cd src; make ../bin/Compare_vns_multi

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

####
# Touch
touch :
	@ touch ./src/SetupCustomTrackTree.cpp
	@ touch ./src/PIDUtils.cpp
	@ touch ./src/preprocess.cpp
	@ touch ./src/AnalysisFW.cpp
	@ touch ./src/AnalysisBinning.cpp
	@ touch ./src/CorrelationUtils.cpp
