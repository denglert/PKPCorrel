PKPCorrel
=========

Pion, kaon and proton correlation code

# Setup HOW-TO 

Creating CMSSW environment:
* `mkdir <projectname>; cd <projectname>`
* `cmsrel CMSSW_5_3_20`
* `mkdir CMSSW_5_3_20/src/<directory>`
* `git clone git@github.com:denglert/PKPCorrel.git`
* `cd CMSSW_5_3_20/src/<directory>/PKPCorrel`

# Usage

The analysis has two-steps: **preprocessing** and **processing**.

## Preprocessing

Has the following output:
- TH2D *correl2D_signal_meas[TypBin][ptBin][multBin]; (measured signal correlation function)
- TH2D *correl2D_signal_meas[TypBin][ptBin][multBin]; (measured backgr correlation function)
- TH1D *nEvents_Processed_signal[TypBin][ptBin][multBin]; (number of events)
- TH1D *nEvents_Processed_backgr[TypBin][ptBin][multBin]; (number of events)

## Processing



## Commands

Interactive:

1. `make preproc`

  Note: You have to setup the `Makefile` ['PREPROCESS'](https://github.com/denglert/PKPCorrel/blob/master/Makefile#L17) section accordingly
2. `make procbatcjob`

  Note: You have to setup the `Makefile` ['PROCESS BATCHJOB'](https://github.com/denglert/PKPCorrel/blob/master/Makefile#L93) section accordingly

Lxbatch jobs:

1. Setup lxbatch jobs.

  See /batch/ folder for job submission macros.
2. `make procbatchjob`

  Note: You have to setup the `Makefile` ['PROCESS BATCHJOB' section](https://github.com/denglert/PKPCorrel/blob/master/Makefile#L93) accordingly


# Classes and files in /src
- AnalysisBinning_*.
- AnalysisFW
- ContMatrix
- CorrelationUtils
- EvtAnalyzer
- EvtSelection
- GraphStyles
- GraphTools
- MC_Contamination_Matrix
- ...
