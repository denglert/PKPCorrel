##################
### Process MC ###
##################
# Command: Process

AnalysisBinning = AnalysisBinning_HIN15007_MinBias
#AnalysisBinning = AnalysisBinning_test

#inputfile = root://eoscms.cern.ch//eos/cms/store/group/phys_heavyions/denglert/pPb_MC_HIJING_MB_HiForest_dEdxcalib_on_500kMCEv_1.9m_mtrkdedx_added_minptfix_trketafix/pPb_MC_HiForest_9_1_cNQ.root
inputfile = root://eoscms.cern.ch//eos/cms/store/group/phys_heavyions/denglert/pPb_MC_HIJING_MB_HiForest_dEdxcalib_on_500kMCEv_1.9m_mtrkdedx_added_minptfix_trketafix/pPb_MC_mergedHiForest.root
tag       = HIJING_FULL_pt_0.2-3.0
#tag       = HIJING_10k
nEvents   = -1
#nEvents   = 10000
PIDconfig = /afs/cern.ch/work/d/denglert/public/projects/PKPCorrelation_SLC6/CMSSW_5_3_20/src/denglert/PKPCorrelationAna/PIDUtils/config/config_default

###########
### Fit ###
###########
# Command: Fit

fit_tag       = HIJING_FULL_pt_0.2-3.0
#fit_tag       = HIJING_10k
fit_inputfile = PtResolutions_$(fit_tag).root

##########################################
all:

process : build
	@rm -rf ./$(tag); mkdir ./$(tag); 
	@echo -e "\nPROCESSING."
	@echo
	@echo WORKDIR: $(tag)
	@echo 
	@echo Inputfile: $(inputfile)
	@echo Number of events: $(nEvents)
	@echo PIDconfig: $(PIDconfig)
	@echo
	cd ./$(tag); ../../../bin/PtResolutionStudy_Process $(inputfile) $(tag) $(nEvents) $(PIDconfig);

fit : build
	@echo Inputfile: $(fit_inputfile)
	@echo
	@cd $(fit_tag); \
	rm -rf figures; mkdir figures; \
	../../../bin/PtResolutionStudy_Fit $(fit_inputfile) $(fit_tag);


build :
	@cd ../../src; make build_PtResolutionStudy AnalysisBinning=$(AnalysisBinning); 

