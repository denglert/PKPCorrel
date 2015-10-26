###################################################################
###  ***  Proton, kaon & pion - charged hadron correlations *** ### 
###################################################################

#AnalysisBinning = AnalysisBinning_HIN14002_HighMult
#AnalysisBinning = AnalysisBinning_HIN15007_MinBias_ThreeBins
#AnalysisBinning = AnalysisBinning_HIN15007_MinBias
#AnalysisBinning = AnalysisBinning_HIN15007_MinBias_SingleBin
#AnalysisBinning = AnalysisBinning_HIN15007_HighMult
#AnalysisBinning = AnalysisBinning_HIN15007_MinBias_HighMult
AnalysisBinning = AnalysisBinning_test

###########################
### ---  Main area  --- ###
###########################
##################
# * PREPROCESS * #
##################
# Command: preproc

# Parameters
#label=Dip_study_pPb_MC_vzhukova-EPOS_RECO_trkCorr_no
label=Dip_study
dotrkCorr=yes
trkCorrlabel=trkCorr_HIJING_PIDConfig_default_Enigma_PID_match
trkCorrFile=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/trkCorr/$(trkCorrlabel)/trkCorrections_0.root
PIDconfig=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/PIDUtils/config/config_default
#inputfile=root://eoscms//eos/cms/store/group/phys_heavyions/denglert/pPb2013_HighMultiplicityForest_merged/HIRun2013-28Sep2013-v1_pPb_run_210498-210658/pPb2013_HM_28Sep2013_v1_HiForest_pPb_run_210498-210658_1.root
#inputfile=root://eoscms//eos/cms/store/group/phys_heavyions/denglert/pPb2013_HighMultiplicityForest_merged/HIRun2013-PromptReco-v1_Pbp_run_211313-211631/pPb2013_HM_PromptReco-v1_HiForest_Pbp_run_211313-211631_16.root
#inputfile=root://eoscms//eos/cms/store/group/phys_heavyions/denglert/pPb2013_minBiasForest_merged/HiForest_pPb2013_PromptReco_run_211313-211631_12.root
#inputfile=root://eoscms.cern.ch//eos/cms/store/group/phys_heavyions/denglert/pPb_MC_vzhukova-EPOS_RECO_batch_HiForest_trketafix/pPb_MC_HiForest_allbatch2.root
#inputfile=root://eoscms//eos/cms/store/group/phys_heavyions/denglert/pPb2013_minBiasForest_merged/HiForest_pPb2013_PromptReco_run_210676-211256_0.root
#inputfile=root://eoscms.cern.ch//eos/cms/store/group/phys_heavyions/denglert/pPb2013_HighMultiplicityForest_merged/HIRun2013-PromptReco-v1_pPb_run_210676-211256/pPb2013_HM_PromptReco-v1_HiForest_pPb_run_210676-211256_0.root
inputfile=root://eoscms//eos/cms/store/group/phys_heavyions/denglert/pPb2013_HighMultiplicityForest_merged/HIRun2013-PromptReco-v1_Pbp_run_211313-211631/pPb2013_HM_PromptReco-v1_HiForest_Pbp_run_211313-211631_25.root
#inputfile=root://eoscms//eos/cms/store/group/phys_heavyions/denglert/pPb2013_HighMultiplicityForest_merged/HIRun2013-PromptReco-v1_pPb_run_210676-211256/pPb2013_HM_PromptReco-v1_HiForest_pPb_run_210676-211256_51.root
#inputfile=root://eoscms//eos/cms/store/group/phys_heavyions/denglert/pPb2013_minBiasForest_merged/HiForest_pPb2013_PromptReco_run_210676-211256_19.root
#inputfile=root://eoscms//eos/cms/store/group/phys_heavyions/denglert/pPb2013_HighMultiplicityForest_merged/HIRun2013-28Sep2013-v1_pPb_run_210498-210658/pPb2013_HM_28Sep2013_v1_HiForest_pPb_run_210498-210658_43.root
#inputfile=root://eoscms//eos/cms/store/group/phys_heavyions/denglert/pPb2013_minBiasForest_merged/HiForest_pPb2013_PromptReco_run_211313-211631_12.root
isMC=no
nEvents=50000
jobid=0

tag=$(label)_nEv_$(nEvents)

############################
# * PREPROCESS - GENLEVEL* #
############################
# Command: preproc_gen

# Parameters
label_preproc_gen=PtResStudy_pPb_MC_vzhukova-EPOS_RECO_batch_GENE_NoSmear_FULL
#inputfile_preproc_gen=root://eoscms.cern.ch//eos/cms/store/group/phys_heavyions/denglert/pPb_MC_HIJING_MB_HiForest_dEdxcalib_on_500kMCEv_1.9m_mtrkdedx_added_minptfix/pPb_MC_HIJING_MB_mergedHiForest_1.9mEv.root
#inputfile_preproc_gen=root://eoscms.cern.ch//eos/cms/store/group/phys_heavyions/denglert/pPb_MC_vzhukova-EPOS_RECO_batch_HiForest_trketafix/pPb_MC_HiForest_allbatch1.root
inputfile_preproc_gen=root://eoscms.cern.ch//eos/cms/store/group/phys_heavyions/denglert/pPb_MC_vzhukova-EPOS_RECO_batch_HiForest_trketafix/pPb_MC_HiForest_allbatch1.root
nEvents_preproc_gen=-1
jobid_preproc_gen=0
PIDconfig_preproc_gen=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/PIDUtils/config/config_default

tag_preproc_gen=$(label_preproc_gen)_nEv_$(nEvents_preproc_gen)

######################################
# * PREPROCESS - GENLEVEL SMEARING * #
######################################
# Command: preproc_genlevel_smearing

# Parameters
label_preproc_genlevel_smearing=PtResStudy_pPb_MC_vzhukova-EPOS_RECO_batch_GENE_Smeared_FULL
#inputfile_preproc_genlevel_smearing=root://eoscms.cern.ch//eos/cms/store/group/phys_heavyions/denglert/pPb_MC_HIJING_MB_HiForest_dEdxcalib_on_500kMCEv_1.9m_mtrkdedx_added_minptfix/pPb_MC_HIJING_MB_mergedHiForest_1.9mEv.root
#inputfile_preproc_genlevel_smearing=root://eoscms.cern.ch//eos/cms/store/group/phys_heavyions/denglert/pPb_MC_vzhukova-EPOS_RECO_batch_HiForest_trketafix/pPb_MC_HiForest_allbatch1.root
inputfile_preproc_genlevel_smearing=root://eoscms.cern.ch//eos/cms/store/group/phys_heavyions/denglert/pPb_MC_vzhukova-EPOS_RECO_batch_HiForest_trketafix/pPb_MC_HiForest_allbatch2.root
jobid_preproc_genlevel_smearing=0
PIDconfig_preproc_genlevel_smearing=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/PIDUtils/config/config_default
#ptresfile_preproc_genlevel_smearing=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/studies/PtResolution/HIJING_FULL_pt_0.2-3.0/PtResolutions_Params_HIJING_FULL_pt_0.2-3.0.root
ptresfile_preproc_genlevel_smearing=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/studies/PtResolution/HIJING_FULL_pt_0.2-3.0/PtResolutions_Params_HIJING_FULL_pt_0.2-3.0.root
nEvents_preproc_genlevel_smearing=-1
tag_preproc_genlevel_smearing=$(label_preproc_genlevel_smearing)_nEv_$(nEvents_preproc_genlevel_smearing)

#################################
# * PREPROCESS - GENPARTICLES * #
#################################
# Command: preproc_genparticles

# Parameters
label_preproc_genparticles=test
#inputfile_preproc_genparticles=root://eoscms.cern.ch//eos/cms/store/group/phys_heavyions/denglert/pPb_MC_HIJING_MB_HiForest_dEdxcalib_on_500kMCEv_1.9m_mtrkdedx_added_minptfix/pPb_MC_HIJING_MB_mergedHiForest_1.9mEv.root
inputfile_preproc_genparticles=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/pPb_MC_HiForest.root
nEvents_preproc_genparticles=4000
jobid_preproc_genparticles=0
PIDconfig_preproc_genparticles=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/PIDUtils/config/config_default
tag_preproc_genparticles=$(label_preproc_genparticles)_nEv_$(nEvents_preproc_genparticles)

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
#batchjobtag=MC_vzhukova-EPOS_RECO_batch_comparison_recolevel_2nd_chariot_proton_mindEdx_3.4_trkCorr_no

# PIDscan HighMulti
#batchjobtag=PIDscan_trueHighMultiplicity_config_looser_2_trkCorr_no/
#batchjobtag=PIDscan_trueHighMultiplicity_config_looser_1_trkCorr_no/
#batchjobtag=PIDscan_trueHighMultiplicity_config_default_trkCorr_no/
#batchjobtag=PIDscan_trueHighMultiplicity_config_strict_1_trkCorr_no/
#batchjobtag=PIDscan_trueHighMultiplicity_config_strict_2_trkCorr_no/

#batchjobtag=MC_vzhukova-EPOS_RECO_batch_recolevel_PIDconfig_default_trkCorr_yes
#batchjobtag=EPOS_RECO_level_trkCorr_yes_nEv_2000
#batchjobtag=EPOS_RECO_level_trkCorr_no_nEv_-1
#batchjobtag=MC_vzhukova-EPOS_RECO_batch_comparison_genelevel_2nd_newbin
#batchjobtag=HighMult_full_PIDConfig_default_celes_i_trkCorr_no
#batchjobtag=Daedalus_I_MinBias_Full_PIDConfig_default_trkCorr_no_temp
#batchjobtag=EPOS_RECO_level_trkCorr_yes_nEv_10000
#batchjobtag=Daedalus_I_HighMult_Full_PIDConfig_default_trkCorr_no_temp
#batchjobtag=Daedalus_MC_vzhukova-EPOS_RECO_batch_PIDconfig_default_trkCorr_no
#batchjobtag=test_nEv_2000


#batchjobtag=Enigma_MC_vzhukova-EPOS_RECO_batch_GENE
#batchjobtag=Enigma_MC_vzhukova-EPOS_RECO_batch_RECO_PIDconfig_default_nomaxtrkCorrcut_trkCorr_yes

##########################################
## Enigma MinBias HighMult Full Dataset ##
##########################################

#batchjobtag=Enigma_MinBias_HighMult_Full_trkCorr_no
#batchjobflag=ContMatrix_yes
#filetoprocess=correl_FULL.root

####################################################
## MC_vzhukova-EPOS_RECO_batch_RECO_PIDconfig_default
####################################################

#batchjobtag=Enigma_MC_vzhukova-EPOS_RECO_batch_RECO_PIDconfig_default_nomaxtrkCorrcut_trkCorr_yes
#batchjobflag=ContMatrix_yes
#filetoprocess=correl_analysis_1.root

########################

#batchjobtag=Fiji_MC_vzhukova-EPOS_RECO_batch_RECO_PIDconfig_default_trkCorr_yes
#batchjobflag=ContMatrix_no
#filetoprocess=correl_analysis_1.root

########################

#batchjobtag=Gilgamesh_HighMult_pPb_PIDConfig_default_trkCorr_yes
#batchjobtag=Fiji_HighMult_Full_PIDConfig_default_trkCorr_no_temp
#batchjobtag=Fiji_MinBias_HighMult_Full_trkCorr_yes
#batchjobtag=Dip_study_nEv_50000
batchjobtag=Dipstudy_HighMult_Full_PIDConfig_default_trkCorr_1nd_yes_temp
#batchjobtag=Dip_study_pPb_MC_vzhukova-EPOS_RECO_trkCorr_no_nEv_5000
#batchjobtag=Dip_study_pPb_MC_vzhukova-EPOS_RECO_trkCorr_no_nEv_20000
#batchjobtag=Dip_study_pPb_MC_vzhukova-EPOS_GENE_nEv_50000
#batchjobtag=test_nEv_10000
#batchjobtag=PtResStudy_pPb_MC_vzhukova-EPOS_RECO_batch_GENE_NoSmear_FULL_nEv_-1
#batchjobtag=Omega_MinBias_Full_PIDConfig_default_trkCorr_2nd_yes
#batchjobtag=Omega_fix_PIDscan_MinBias_dEdxminsweep_full_config_4_trkCorr_yes
#batchjobtag=Fiji_MinBias_Full_PIDConfig_default_trkCorr_yes
##batchjobtag=Fiji_MinBias_Full_2MultBins_PIDConfig_default_trkCorr_yes_temp
#batchjobflag=ContMatrix_yes
#filetoprocess=correl_FULL.root

#batchjobtag=Enigma_HighMult_Full_PIDConfig_default_trkCorr_no
#batchjobtag=EPOS_RECO_level_trkCorr_yes_nEv_20000
#batchjobtag=Fiji_MinBias_Full_ALICE_comparison_PIDConfig_default_trkCorr__no
#batchjobtag=Crosscheck_HIN14002_comparison_yes_temp
#batchjobtag=Crosscheck_charge_comparison_positive_yes_temp
#filetoprocess=correl_FULL.root
#filetoprocess=correl_analysis_0.root
#batchjobflag=ContMatrix_yes_shifted_20percent
#batchjobflag=ContMatrix_yes_Original
batchjobflag=ContMatrix_no
#batchjobflag=ContMatrix_no
filetoprocess=correl_FULL.root
#filetoprocess=correl_FULL.root
#filetoprocess=correl_analysis_0.root
#batchjobflag=null
batchjobfolder=$(batchjobtag)_$(batchjobflag)

#filetoprocess=correl_analysis_0.root
#filetoprocess=correl_analysis_1.root
#filetoprocess=correl_tempmerge.root
#filetoprocess=correl_full.root
#filetoprocess=correl_MinBiasHighMulti.root
#filetoprocess=correl_selection20.root

batchjob_contmatrix=no
#batchjob_contmatrix=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/ContMatrix/Contamination_Matrix_PIDConfig_default_EPOS_LHC_MC_Fiji/shifted_20percent/Cont_Matrix.root
#batchjob_contmatrix=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/ContMatrix/Contamination_Matrix_PIDConfig_default_EPOS_LHC_MC_Fiji/normal/Cont_Matrix.root
# Default:
#batchjob_contmatrix=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/ContMatrix/Contamination_Matrix_Study_Mult_0-120_PIDConfig_config_4_EPOS_LHC_MC_Fiji/Cont_Matrix.root
#
#
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

#EtaPhiDistr_label=EtaPhiDistr_pPb_MinBias_HIJING_MC_trkCorr_${EtaPhiDistr_dotrkCorr}
#EtaPhiDistr_label=EtaPhiDistr_pPb_MinBias_EPOS_MC_pt_0.4-0.5_trkCorr_${EtaPhiDistr_dotrkCorr}
#EtaPhiDistr_label=EtaPhiDistr_pPb_MinBias_DATA_PIDconfig_default_mtrkdedx_added_minptfix_trketafix_${EtaPhiDistr_dotrkCorr}_trkCorr
#EtaPhiDistr_label=Fabcd_EtaPhiDistr_pPb_MinBias_DATA_PIDconfig_default_${EtaPhiDistr_dotrkCorr}_trkCorr
#EtaPhiDistr_label=Helios_EtaPhiDistr_pPb_MinBias_DATA_PIDconfig_default_trkCorr_${EtaPhiDistr_dotrkCorr}
EtaPhiDistr_label=Studies_Mult_185_220_trkCorr_${EtaPhiDistr_dotrkCorr}
#EtaPhiDistr_label=EtaPhiDistr_pPb_HighMulti_DATA_PIDconfig_default_${EtaPhiDistr_dotrkCorr}_trkCorr
#EtaPhiDistr_label=EtaPhiDistr_EPOS_MC_pPb_MinBias_PIDconfig_default_${EtaPhiDistr_dotrkCorr}_trkCorr
#EtaPhiDistr_label=EtaPhiDistr_EPOS_MC_pPb_MinBias_PIDconfig_default_${EtaPhiDistr_dotrkCorr}_trkCorr

# DATA
EtaPhiDistr_inputfile=root://eoscms.cern.ch//store/group/phys_heavyions/denglert/pPb2013_HighMultiplicityForest_merged/HIRun2013-28Sep2013-v1_pPb_run_210498-210658/pPb2013_HM_28Sep2013_v1_HiForest_pPb_run_210498-210658_0.root
#EtaPhiDistr_inputfile=root://eoscms//eos/cms/store/group/phys_heavyions/denglert/pPb2013_minBiasForest_merged/HiForest_pPb2013_PromptReco_run_211313-211631_8.root
#EtaPhiDistr_inputfile=root://eoscms.cern.ch//store/group/phys_heavyions/denglert/pPb_MC_HIJING_MB_HiForest_dEdxcalib_on_500kMCEv_1.9m_mtrkdedx_added_minptfix_trketafix/pPb_MC_mergedHiForest.root
#EtaPhiDistr_inputfile=root://eoscms//eos/cms/store/group/phys_heavyions/denglert/pPb2013_minBiasForest_merged/HiForest_pPb2013_PromptReco_run_210676-211256_17.root

# MC
#EtaPhiDistr_inputfile=root://eoscms.cern.ch//store/group/phys_heavyions/denglert/pPb_MC_HIJING_MB_HiForest_dEdxcalib_on_500kMCEv_1.9m_mtrkdedx_added_minptfix_trketafix/pPb_MC_mergedHiForest.root
#EtaPhiDistr_inputfile=root://eoscms.cern.ch//eos/cms/store/group/phys_heavyions/denglert/pPb_MC_vzhukova-EPOS_RECO_batch_HiForest_trketafix/pPb_MC_HiForest_allbatch1.root

EtaPhiDistr_dotrkCorr=yes
EtaPhiDistr_trkCorrlabel=trkCorr_HIJING_PIDConfig_default_Fiji_PID_match
EtaPhiDistr_trkCorr=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/trkCorr/$(EtaPhiDistr_trkCorrlabel)/trkCorrections_0.root
EtaPhiDistr_PIDconfig=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/PIDUtils/config/config_default
EtaPhiDistr_nEvents=100000
EtaPhiDistr_jobid=0
EtaPhiDistr_tag=$(EtaPhiDistr_label)_nEv_$(EtaPhiDistr_nEvents)

######################
#### - PIDStudy - ####
######################
# commands: PIDStudy

#PIDStudy_label=pidstudy_DATA_HighMult_pt_0.5-0.6
#PIDStudy_label=pidstudy_DATA_MinBias_pt_0.5-0.6
#PIDStudy_label=pidstudy_EPOS_MinBias_pt_0.8-0.9
#PIDStudy_label=pidstudy_EPOS_MinBias_ptmin_0.3
#PIDStudy_label=pidstudy_DATA_MinBias_ptmin_0.3
PIDStudy_label=pidstudy_DATA_HighMult_ptmin_0.3
#PIDStudy_label=pidstudy_DATA_HighMult_pt_0.8-0.9
#PIDStudy_label=pidstudy_DATA_MinBias
#PIDStudy_label=pidstudy_EPOS_MinBias
PIDStudy_inputfile=root://eoscms.cern.ch//store/group/phys_heavyions/denglert/pPb2013_HighMultiplicityForest_merged/HIRun2013-28Sep2013-v1_pPb_run_210498-210658/pPb2013_HM_28Sep2013_v1_HiForest_pPb_run_210498-210658_0.root
#PIDStudy_inputfile=root://eoscms//eos/cms/store/group/phys_heavyions/denglert/pPb2013_minBiasForest_merged/HiForest_pPb2013_PromptReco_run_210676-211256_0.root
#PIDStudy_inputfile=root://eoscms.cern.ch//store/group/phys_heavyions/denglert/pPb2013_HighMultiplicityForest_merged/HIRun2013-28Sep2013-v1_pPb_run_210498-210658/pPb2013_HM_28Sep2013_v1_HiForest_pPb_run_210498-210658_0.root
#PIDStudy_inputfile=root://eoscms.cern.ch//eos/cms/store/group/phys_heavyions/denglert/pPb_MC_vzhukova-EPOS_RECO_batch_HiForest_trketafix/pPb_MC_HiForest_allbatch2.root
#PIDStudy_isMC=yes
PIDStudy_isMC=no
#PIDStudy_nEvents=300000
PIDStudy_nEvents=300000
PIDStudy_PIDconfig=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/PIDUtils/config/config_default

#############################
#### - PIDStudy_viewer - ####
#############################
# commands: PIDStudy

#PIDStudy_viewer_label=pidstudy_EPOS_MinBias
#PIDStudy_viewer_label=pidstudy_EPOS_MinBias_pt_0.5-0.6
#PIDStudy_viewer_label=pidstudy_DATA_HighMult_pt_0.5-0.6
#PIDStudy_viewer_label=pidstudy_DATA_HighMult_pt_0.8-0.9
#PIDStudy_viewer_label=pidstudy_DATA_MinBias
#PIDStudy_viewer_label=pidstudy_DATA_MinBias_pt_0.5-0.6
#PIDStudy_viewer_label=pidstudy_DATA_MinBias_pt_0.8-0.9
#PIDStudy_viewer_label=pidstudy_EPOS_MinBias_pt_0.8-0.9
#PIDStudy_viewer_label=pidstudy_EPOS_MinBias_ptmin_0.3
#PIDStudy_viewer_label=pidstudy_DATA_MinBias_ptmin_0.3
PIDStudy_viewer_label=pidstudy_DATA_HighMult_ptmin_0.3
#PIDStudy_viewer_label=pidstudy
PIDStudy_viewer_inputfile=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/PIDUtils/study/${PIDStudy_viewer_label}/PIDStudy.root
PIDStudy_viewer_PIDconfig=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/PIDUtils/config/config_default

#############################
#### - TrackCorrection - ####
#############################
# commands: TrackCorrection

#TrackCorrection_label=trkCorr_HIJING_PIDConfig_default_celes_iii
#TrackCorrection_label=trkCorr_HIJING_PIDConfig_default_Daedalus
#TrackCorrection_label=trkCorr_HIJING_PIDConfig_default_Daedalus_i
#TrackCorrection_label=trkCorr_HIJING_PIDConfig_default_Fiji_PID_match_EtaWide
TrackCorrection_label=trkCorr_HIJING_PIDConfig_default_test

#TrackCorrection_inputfileDATA=root://eoscms.cern.ch//store/group/phys_heavyions/denglert/pPb2013_HighMultiplicityForest_merged/HIRun2013-28Sep2013-v1_pPb_run_210498-210658/pPb2013_HM_28Sep2013_v1_HiForest_pPb_run_210498-210658_0.root
TrackCorrection_inputfileDATA=root://eoscms.cern.ch//store/group/phys_heavyions/denglert/pPb2013_minBiasForest_merged/HiForest_pPb2013_PromptReco_run_211313-211631_14.root
#TrackCorrection_inputfileMC=root://eoscms.cern.ch//store/group/phys_heavyions/denglert/pPb_MC_HIJING_MB_HiForest_dEdxcalib_on_500kMCEv_1.9m_mtrkdedx_added_minptfix/pPb_MC_HIJING_MB_mergedHiForest_1.9mEv.root
TrackCorrection_inputfileMC=root://eoscms.cern.ch//store/group/phys_heavyions/denglert/pPb_MC_HIJING_MB_HiForest_dEdxcalib_on_500kMCEv_1.9m_mtrkdedx_added_minptfix_trketafix/pPb_MC_mergedHiForest.root
TrackCorrection_nEventsDATA=20000
TrackCorrection_nEventsMC=20000
TrackCorrection_PIDConfig=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/PIDUtils/config/config_default
TrackCorrection_jobid=0

TrackCorrection_tag=$(TrackCorrection_label)

###################################
### - TrackCorrection_viewer - ####
###################################
# commands: TrackCorrection_viewer
#trkdir_TrackCorrection_viewer=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/trkCorr/trkCorr_HIJING_PIDConfig_default_celes_iii/
#trkdir_TrackCorrection_viewer=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/trkCorr/trkCorr_HIJING_PIDConfig_default_Fiji_PID_match/
trkdir_TrackCorrection_viewer=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/trkCorr/trkCorr_HIJING_PIDConfig_default_Fiji_PID_match/
#trkdir_TrackCorrection_viewer=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/trkCorr/TrackCorrection_singlebin_forfig/
inputfilebase_TrackCorrection_viewer=trkCorrections_0.root
inputfile_TrackCorrection_viewer=$(trkdir_TrackCorrection_viewer)$(inputfilebase_TrackCorrection_viewer)

#####################################
#### - MC_Contamination_Matrix - ####
#####################################
# commands: MC_Contamination_Matrix

#MC_Contamination_Matrix_PIDConfig_label=dEdxmin_sweep/config_0
MC_Contamination_Matrix_PIDConfig_label=dEdxmin_sweep/config_4
MC_Contamination_Matrix_label=Contamination_Matrix_Study_Mult_0-120_PIDConfig_config_4_EPOS_LHC_MC_Fiji
MC_Contamination_Matrix_inputfileDATA=root://eoscms.cern.ch//store/group/phys_heavyions/denglert/pPb2013_HighMultiplicityForest_merged/HIRun2013-28Sep2013-v1_pPb_run_210498-210658/pPb2013_HM_28Sep2013_v1_HiForest_pPb_run_210498-210658_0.root
MC_Contamination_Matrix_inputfileMC=root://eoscms.cern.ch//eos/cms/store/group/phys_heavyions/denglert/pPb_MC_vzhukova-EPOS_RECO_batch_HiForest_trketafix/pPb_MC_HiForest_allbatch1.root
#MC_Contamination_Matrix_inputfileMC=root://eoscms.cern.ch//store/group/phys_heavyions/denglert/pPb_MC_HIJING_MB_HiForest_dEdxcalib_on_500kMCEv_1.9m_mtrkdedx_added_minptfix_trketafix/pPb_MC_mergedHiForest.root
#MC_Contamination_Matrix_nEventsDATA=300000
#MC_Contamination_Matrix_nEventsMC=300000
MC_Contamination_Matrix_nEventsDATA=300000
MC_Contamination_Matrix_nEventsMC=300000
MC_Contamination_Matrix_PIDConfig=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/PIDUtils/config/${MC_Contamination_Matrix_PIDConfig_label}
MC_Contamination_Matrix_jobid=0

MC_Contamination_Matrix_tag=$(MC_Contamination_Matrix_label)

############################################
#### - MC_Contamination_Matrix_viewer - ####
############################################
# commands: MC_Contamination_Matrix_viewer

#MC_Contamination_Matrix_viewer_label=Contamination_Matrix_PIDConfig_default_HIJING_MC
#MC_Contamination_Matrix_viewer_label=Contamination_Matrix_PIDConfig_test_a3_EPOS_LHC_MC
#MC_Contamination_Matrix_viewer_label=Contamination_Matrix_Study_Mult_0-120_PIDConfig_default_EPOS_LHC_MC_Fiji
MC_Contamination_Matrix_viewer_label=Contamination_Matrix_PIDConfig_default_EPOS_LHC_MC_Fiji
MC_Contamination_Matrix_viewer_tag=shifted_20percent
#MC_Contamination_Matrix_viewer_label=Contamination_Matrix_Study_Mult_0-120_PIDConfig_config_4_EPOS_LHC_MC_Fiji
MC_Contamination_Matrix_viewer_PIDConfig=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/PIDUtils/config/config_default
#MC_Contamination_Matrix_viewer_PIDConfig=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/PIDUtils/config/dEdxmin_sweep/config_4
MC_Contamination_Matrix_viewer_inputfilename=PID_Contamination_matrix_0.root
MC_Contamination_Matrix_viewer_dir=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/ContMatrix/${MC_Contamination_Matrix_viewer_label}/
MC_Contamination_Matrix_viewer_inputfile=$(MC_Contamination_Matrix_viewer_dir)$(MC_Contamination_Matrix_viewer_inputfilename)

##############################
#### - MC_CrosscheckFig - ####
##############################
# commands: MC_CrosscheckFig

MC_CrosscheckFig_label=MC_gene_reco_level_CrossCheck_EPOS_trkCorr_no
MC_CrosscheckFig_inputfileRECO=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/results/MC_vzhukova-EPOS_RECO_batch_comparison_recolevel_2nd_chariot_trkCorr_no/dump.root
#MC_CrosscheckFig_inputfileGENE=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/results/MC_vzhukova-EPOS_RECO_batch_comparison_genelevel_2nd_full_updated/dump.root
MC_CrosscheckFig_inputfileGENE=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/results/MC_vzhukova-EPOS_RECO_batch_comparison_genelevel_2nd_beta/dump.root
#MC_CrosscheckFig_inputfileGENE=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/results/MC_vzhukova-EPOS_RECO_batch_comparison_genelevel_2nd_fullkEv_etafixed/dump.root

###########################
##### - Compare_vns - #####
###########################
# commands: Compare_vns

#Compare_vns_label=Enigma_ContMatrix_comparison_HighMult_Full_150-185_trkCorr_no
#Compare_vns_label=MC_EPOS_decont_genlevel_comparison_trkCorr_no_lol

#Compare_vns_label1=ContCorr_No
#Compare_vns_label2=ContCorr_Yes
#Compare_vns_label1=reco-cmc
#Compare_vns_label2=gene

##########################
## GENE-RECO comparison ##
##########################
#Compare_vns_label=Enigma_GENE_RECO_level_comparison_trkCorr_upd_yes_ContMatrix_yes
#Compare_vns_label1=RECO_trkC_yes_ContM_yes
#Compare_vns_label2=GENE
#Compare_vns_folder1=Enigma_MC_vzhukova-EPOS_RECO_batch_RECO_PIDconfig_default_nomaxtrkCorrcut_trkCorr_yes_ContMatrix_yes
#Compare_vns_folder2=Enigma_MC_vzhukova-EPOS_RECO_batch_GENE_original

##########################
## GENE-RECO comparison ##
##########################

#Compare_vns_label=Fiji_RECO_GEN_closure_trkCorr_yes_ContMatrix_no
#Compare_vns_label1=RECO_trkC_yes_ContM_no
#Compare_vns_label2=GENE
#Compare_vns_folder1=Fiji_MC_vzhukova-EPOS_RECO_batch_RECO_PIDconfig_default_trkCorr_yes_ContMatrix_no
#Compare_vns_folder2=Enigma_MC_vzhukova-EPOS_RECO_batch_GENE_original

#################################
## Track correction comparison ##
#################################

#Compare_vns_label=Fiji_HighMult_trkCorr_comparison_Ntrk_185-220
#Compare_vns_label1="uncorrected"
#Compare_vns_label2="eff. corrected"
#Compare_vns_folder1=Fiji_HighMult_Full_PIDConfig_default_trkCorr_no_temp_ContMatrix_no
#Compare_vns_folder2=Fiji_HighMult_Full_PIDConfig_default_trkCorr_yes_ContMatrix_no
#
#Compare_vns_inputfile1=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/results/$(Compare_vns_folder1)/dump.root
#Compare_vns_inputfile2=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/results/$(Compare_vns_folder2)/dump.root
#
#######################
## Charge comparison ##
#######################
#
#Compare_vns_label=Charge_compairson
#Compare_vns_label1="+"
#Compare_vns_label2="-"
#Compare_vns_folder1=Crosscheck_charge_comparison_positive_yes_temp_ContMatrix_no
#Compare_vns_folder2=Crosscheck_charge_comparison_negative_yes_temp_ContMatrix_no
#
#Compare_vns_inputfile1=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/results/$(Compare_vns_folder1)/dump.root
#Compare_vns_inputfile2=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/results/$(Compare_vns_folder2)/dump.root
#
##############################
## Pt Resolution Comparison ##
##############################
#
#Compare_vns_label=PtResolution
#Compare_vns_label1="gen, nosmear"
#Compare_vns_label2="gen, smeared"
#Compare_vns_folder1=PtResStudy_pPb_MC_vzhukova-EPOS_RECO_batch_GENE_NoSmear_FULL_nEv_-1_ContMatrix_no
#Compare_vns_folder2=PtResStudy_pPb_MC_vzhukova-EPOS_RECO_batch_GENE_Smeared_FULL_nEv_-1_ContMatrix_no
#
#Compare_vns_inputfile1=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/results/$(Compare_vns_folder1)/dump.root
#Compare_vns_inputfile2=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/results/$(Compare_vns_folder2)/dump.root


################################################################
## Contamination correction systematic uncertainty comparison ##
################################################################

Compare_vns_label=ContCorr_SystUnc_shift_20percent
Compare_vns_label1="Original Cont. Corr."
Compare_vns_label2="Cont. Corr +20% pion cont."
Compare_vns_folder1=Fiji_MinBias_HighMult_Full_trkCorr_yes_ContMatrix_yes_original
Compare_vns_folder2=Fiji_MinBias_HighMult_Full_trkCorr_yes_ContMatrix_yes_shifted

Compare_vns_inputfile1=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/results/$(Compare_vns_folder1)/dump.root
Compare_vns_inputfile2=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/results/$(Compare_vns_folder2)/dump.root


########################
## pPb-Pbp comparison ##
########################




#Compare_vns_label=Gilgamesh_pPb_Pbp_comparsion_Ntrk_185-220
#Compare_vns_label1=pPb
#Compare_vns_label2=Pbp
#Compare_vns_folder1=Gilgamesh_HighMult_pPb_PIDConfig_default_trkCorr_yes_ContMatrix_yes
#Compare_vns_folder2=Gilgamesh_HighMult_Pbp_PIDConfig_default_trkCorr_yes_ContMatrix_yes

#Compare_vns_label=Gilgamesh_pPb_Pbp_comparsion_Ntrk_185-220
#Compare_vns_label1=pPb
#Compare_vns_label2=Pbp
#Compare_vns_folder1=Gilgamesh_HighMult_pPb_PIDConfig_default_trkCorr_yes_ContMatrix_yes
#Compare_vns_folder2=Gilgamesh_HighMult_Pbp_PIDConfig_default_trkCorr_yes_ContMatrix_yes
#
#
#Compare_vns_inputfile1=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/results/$(Compare_vns_folder1)/dump.root
#Compare_vns_inputfile2=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/results/$(Compare_vns_folder2)/dump.root

########################

#Compare_vns_label=MC_gene_reco_level_CrossCheck_EPOS_trkCorr_yes_lol
#Compare_vns_label1=gen
#Compare_vns_label2=reco
#Compare_vns_inputfile2=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/results/MC_vzhukova-EPOS_RECO_batch_comparison_genelevel_2nd_newbin/dump.root
#
#Compare_vns_inputfile2=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/results/MC_vzhukova-EPOS_RECO_batch_recolevel_PIDconfig_default_trkCorr_yes/dump.root
 
#Compare_vns_inputfile2=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/results/MC_vzhukova-EPOS_RECO_batch_comparison_recolevel_2nd_chariot_proton_mindEdx_3.4_trkCorr_no/dump.root
#Compare_vns_inputfile2=/afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/results/MC_vzhukova-EPOS_RECO_batch_comparison_recolevel_2nd_chariot_trkCorr_no/dump.root

###############################
#### - Compare_vns_multi - ####
###############################
# commands: Compare_vns_multi

Compare_vns_multi_workdir=MultiComparsion_MinBias_dEdxminsweep_full_ContMatrix_yes

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
	@make touch
	@make build_preproc

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
	cd ./preprocessed/$(tag); ../../bin/preprocess $(inputfile) $(isMC) $(dotrkCorr) $(trkCorrFile) $(PIDconfig) $(jobid) $(nEvents);


preproc_gen : build_preproc_gen
	@rm -rf ./preprocessed/$(tag_preproc_gen); mkdir ./preprocessed/$(tag_preproc_gen); 
	@echo -e "\nPREPROCESSING."
	@echo
	@echo WORKDIR: $(tag_preproc_gen)
	@echo 
	@echo Testfile: $(inputfile_preproc_gen)
	@echo Number of events: $(nEvents_preproc_gen)
	@echo
	cd ./preprocessed/$(tag_preproc_gen); ../../bin/preprocess_genlevel $(inputfile_preproc_gen) $(jobid_preproc_gen) $(PIDconfig_preproc_gen) $(nEvents_preproc_gen);


preproc_genlevel_smearing : build_preproc_genlevel_smearing
	@rm -rf ./preprocessed/$(tag_preproc_genlevel_smearing); mkdir ./preprocessed/$(tag_preproc_genlevel_smearing); 
	@echo -e "\nPREPROCESSING."
	@echo
	@echo WORKDIR: $(tag_preproc_genlevel_smearing)
	@echo 
	@echo Testfile: $(inputfile_preproc_genlevel_smearing)
	@echo Number of events: $(nEvents_preproc_genlevel_smearing)
	@echo PtResolution Parameter file: $(ptresfile_preproc_genlevel_smearing)
	@echo
	cd ./preprocessed/$(tag_preproc_genlevel_smearing); ../../bin/preprocess_genlevel_smearing $(inputfile_preproc_genlevel_smearing) $(jobid_preproc_genlevel_smearing) $(PIDconfig_preproc_genlevel_smearing) $(ptresfile_preproc_genlevel_smearing) $(nEvents_preproc_genlevel_smearing);


preproc_genparticles : build_preproc_genparticles
	@rm -rf ./preprocessed/$(tag_preproc_genparticles); mkdir ./preprocessed/$(tag_preproc_genparticles); 
	@echo -e "\nPREPROCESSING."
	@echo
	@echo WORKDIR: $(tag_preproc_genparticles)
	@echo 
	@echo Testfile: $(inputfile_preproc_genparticles)
	@echo Number of events: $(nEvents_preproc_genparticles)
	@echo
	cd ./preprocessed/$(tag_preproc_genparticles); ../../bin/preprocess_genparticles $(inputfile_preproc_genparticles) $(jobid_preproc_genparticles) $(PIDconfig_preproc_genparticles) $(nEvents_preproc_genparticles);

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
	./bin/process ./preprocessed/$(tag)/correl_analysis_$(jobid).root $(tag) $(contmatrix)


procbatchjob : build_proc
	@rm -rf ./results/$(batchjobfolder);
	./bin/process ./preprocessed/$(batchjobtag)/$(filetoprocess) $(batchjobfolder) $(batchjob_contmatrix)


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
	@cd src; make ../bin/AnaFwTest AnalysisBinning=$(AnalysisBinning)

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
	cd ./trkCorr/$(TrackCorrection_tag); ../../bin/TrackCorrection $(TrackCorrection_inputfileDATA) $(TrackCorrection_inputfileMC) $(TrackCorrection_jobid) $(TrackCorrection_nEventsDATA) $(TrackCorrection_nEventsMC) $(TrackCorrection_PIDConfig);


######################################################
### PIDSetup
PIDSetup : build_PIDSetup
	cd PIDtest; ../bin/PIDSetup $(inputfile_PIDSetup);

build_PIDSetup : 
	@cd src; make ../bin/PIDSetup

######################################################
### PIDStudy
PIDStudy: build_PIDStudy
	cd 
	@rm -rf ./PIDUtils/study/$(PIDStudy_label); mkdir ./PIDUtils/study/$(PIDStudy_label); 
	@echo -e "\nPIDStudy."
	@echo
	@echo WORKDIR: $(PIDStudy_label)
	@echo 
	@echo Inputfile: $(PIDStudy_inputfile)
	@echo Number of events: $(PIDStudy_nEvents)
	@echo PIDconfig: $(PIDStudy_PIDconfig)
	@echo
	cd ./PIDUtils/study/$(PIDStudy_label); ../../../bin/PIDStudy $(PIDStudy_inputfile) $(PIDStudy_isMC) $(PIDStudy_nEvents) $(PIDStudy_PIDconfig);

build_PIDStudy:
	@cd src; make ../bin/PIDStudy AnalysisBinning=$(AnalysisBinning)

######################################################
### PIDStudy
PIDStudy_viewer: build_PIDStudy_viewer
	@echo WORKDIR: $(PIDStudy_viewer_label)
	@echo 
	@echo Inputfile: $(PIDStudy_viewer_inputfile)
	@echo PIDconfig: $(PIDStudy_viewer_PIDconfig)
	@echo
	cd ./PIDUtils/study/$(PIDStudy_viewer_label); ../../../bin/PIDStudy_viewer $(PIDStudy_viewer_inputfile) $(PIDStudy_viewer_PIDconfig); 

build_PIDStudy_viewer:
	@cd src; make ../bin/PIDStudy_viewer AnalysisBinning=$(AnalysisBinning)


######################################################
### TrackCorrection_viewer
TrackCorrection_viewer : build_TrackCorrection_viewer
	cd $(trkdir_TrackCorrection_viewer); rm *.png; rm *.pdf; ../../bin/TrackCorrection_viewer $(inputfile_TrackCorrection_viewer);

build_TrackCorrection_viewer : 
	@cd src; make ../bin/TrackCorrection_viewer


######################################################
### UtilityTest
utiltest : build_utiltest
	./bin/utilitytest

build_utiltest :
	@cd src; make ../bin/utilitytest

######################################################
### MC_Contamination_Matrix
MC_Contamination_Matrix : build_MC_Contamination_Matrix
	@rm -rf ./ContMatrix/$(MC_Contamination_Matrix_tag); mkdir ./ContMatrix/$(MC_Contamination_Matrix_tag); 
	@echo -e "\nMC_Contamination_Matrix."
	@echo
	@echo WORKDIR: $(MC_Contamination_Matrix_tag)
	@echo 
	@echo DATA - file: $(MC_Contamination_Matrix_inputfileDATA)
	@echo DATA - Number of events: $(MC_Contamination_Matrix_nEventsDATA)
	@echo MC - file: $(MC_Contamination_Matrix_inputfileMC)
	@echo MC - Number of events: $(MC_Contamination_Matrix_nEventsMC)
	@echo
	cd ./ContMatrix/$(MC_Contamination_Matrix_tag); ../../bin/MC_Contamination_Matrix $(MC_Contamination_Matrix_inputfileDATA) $(MC_Contamination_Matrix_inputfileMC) $(MC_Contamination_Matrix_jobid) $(MC_Contamination_Matrix_nEventsDATA) $(MC_Contamination_Matrix_nEventsMC) $(MC_Contamination_Matrix_PIDConfig);

### MC_Contamination_Matrix_viewer
MC_Contamination_Matrix_viewer : build_MC_Contamination_Matrix_viewer
	cd $(MC_Contamination_Matrix_viewer_dir); rm -rf $(MC_Contamination_Matrix_viewer_tag); mkdir  $(MC_Contamination_Matrix_viewer_tag); cd $(MC_Contamination_Matrix_viewer_tag); ../../../bin/MC_Contamination_Matrix_viewer $(MC_Contamination_Matrix_viewer_inputfile) $(MC_Contamination_Matrix_viewer_PIDConfig);

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
	@cd src; make ../bin/Compare_vns AnalysisBinning=$(AnalysisBinning)

### Compare_vns_multi
Compare_vns_multi : build_Compare_vns_multi
	@rm -rf ./results/$(Compare_vns_multi_workdir); mkdir ./results/$(Compare_vns_multi_workdir); 
	@echo -e "\nCompare_vns_multi"
	@echo
	@echo WORKDIR: $(Compare_vns_multi_workdir)
	cd ./results/$(Compare_vns_multi_workdir); ../../bin/Compare_vns_multi

build_Compare_vns_multi : 
	@cd src; make ../bin/Compare_vns_multi AnalysisBinning=$(AnalysisBinning)

######################################################
# Build
build :
	@cd src; make

build_preproc:
	@cd src; make ../bin/preprocess AnalysisBinning=$(AnalysisBinning)

build_preproc_gen:
	@cd src; make ../bin/preprocess_genlevel AnalysisBinning=$(AnalysisBinning)

build_preproc_genlevel_smearing:
	@cd src; make ../bin/preprocess_genlevel_smearing AnalysisBinning=$(AnalysisBinning)

build_preproc_genparticles:
	@cd src; make ../bin/preprocess_genparticles

build_SimplePreProc:
	@cd src; make ../bin/SimplePreProc

build_EtaPhiDistr:
	echo "vau"
	@cd src; make ../bin/EtaPhiDistr AnalysisBinning=$(AnalysisBinning)

build_MC_Contamination_Matrix:
	@cd src; make ../bin/MC_Contamination_Matrix AnalysisBinning=$(AnalysisBinning)

build_MC_Contamination_Matrix_viewer : 
	@cd src; make ../bin/MC_Contamination_Matrix_viewer AnalysisBinning=$(AnalysisBinning)

build_TrackCorrection:
	@cd src; make ../bin/TrackCorrection

build_proc:
	@cd src; make ../bin/process AnalysisBinning=$(AnalysisBinning)

####
# Touch
touch :
	@ touch ./src/SetupCustomTrackTree.cpp
	@ touch ./src/PIDUtils.cpp
	@ touch ./src/ContMatrix.cpp
	@ touch ./src/preprocess.cpp
	@ touch ./src/AnalysisFW.cpp
	@ touch ./src/CorrelationUtils.cpp
	@ touch ./src/TrackCorrection.cpp
	@ touch ./src/EvtSelection.cpp
	@ touch ./src/EvtAnalyzer.cpp

