CC = g++
CFLAGS = `root-config --cflags`  
LFLAGS = -O3 -Wl,--no-as-needed `root-config --libs`
OBJS = CorrelationUtils.o CorrelationUtils_FigureTools.o PIDUtils.o AnalysisFW.o AnalysisBinning.o SetupCustomTrackTree.o PhyConst.o
CMN =  commonSetup.h

all : ../bin/preprocess ../bin/process ../bin/preprocess_minimal

###################################################################################

### Proton, kaon and pion - charged hadron correlation
# process
../bin/process : process.o $(CMN) $(OBJS)
	$(CC) $(LFLAGS) -o $@ $< $(OBJS)

process.o : process.cpp 
	$(CC) $(CFLAGS) -o $@ -c $<

# process_light
../bin/process_light : process_light.o $(CMN) $(OBJS)
	$(CC) $(LFLAGS) -o $@ $< $(OBJS)

process_light.o : process_light.cpp 
	$(CC) $(CFLAGS) -o $@ -c $<

# preprocess
../bin/preprocess : preprocess.o $(CMN) $(OBJS)
	$(CC) $(LFLAGS) -o $@ $< $(OBJS)

preprocess.o : preprocess.cpp $(CMN) $(OBJS)
	$(CC) $(CFLAGS) -o $@ -c $<

# SimplePreProc
../bin/SimplePreProc : SimplePreProc.o $(CMN) $(OBJS)
	$(CC) $(LFLAGS) -o $@ $< $(OBJS)

SimplePreProc.o : SimplePreProc.cpp $(CMN) $(OBJS)
	$(CC) $(CFLAGS) -o $@ -c $<


####################################################################################
### dEdxMap
../bin/dEdxMap : dEdxMap.o $(CMN) $(OBJS)
	$(CC) $(LFLAGS) -o $@ $< $(OBJS) 

dEdxMap.o : dEdxMap.cpp
	$(CC) $(CFLAGS) -o $@ -c $<


####################################################################################
### PIDSetup
../bin/PIDSetup : PIDSetup.o $(CMN) $(OBJS)
	$(CC) $(LFLAGS) -o $@ $< $(OBJS) 

PIDSetup.o : PIDSetup.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

####################################################################################
### EtaPhiDistr
../bin/EtaPhiDistr : EtaPhiDistr.o $(CMN) $(OBJS)
	$(CC) $(LFLAGS) -o $@ $< $(OBJS) 

EtaPhiDistr.o : EtaPhiDistr.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

####################################################################################
### TrackCorrection
../bin/TrackCorrection : TrackCorrection.o $(CMN) PIDUtils.o AnalysisBinning.o PhyConst.o
	$(CC) $(LFLAGS) -o $@ $< PIDUtils.o AnalysisBinning.o PhyConst.o 

TrackCorrection.o : TrackCorrection.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

###########################################
###  *** Framework and utility test *** ###
# AnalysisFWTest
../bin/AnaFwTest : AnaFwTest.o $(CMN) $(OBJS)
	$(CC) $(LFLAGS) -o $@ $< $(OBJS) 

AnaFwTest.o : AnaFwTest.cpp
	$(CC) $(CFLAGS)-o $@ -c $<  


# UtilityTest
../bin/utilitytest : UtilityTest.o $(CMN) $(OBJS)
	$(CC) $(LFLAGS) -o $@ $< $(OBJS) 

UtilityTest.o : UtilityTest.cpp
	$(CC) $(CFLAGS)-o $@ -c $<  

###########################################
### *** Framework classes
# AnalysisBinning
AnalysisBinning.o : AnalysisBinning.cpp AnalysisBinning.h
	$(CC) $(CFLAGS) -c $< -o $@ 

# AnalysisFW
AnalysisFW.o : AnalysisFW.cpp AnalysisFW.h
	$(CC) $(CFLAGS) -c $< -o $@ 

# PhyConst
PhyConst.o : PhyConst.cpp PhyConst.h
	$(CC) $(CFLAGS) -c $< -o $@ 

# CorrelationUtils
CorrelationUtils.o : CorrelationUtils.cpp CorrelationUtils.h
	$(CC) $(CFLAGS) -o $@ -c $<

# CorrelationUtils_FigureTools
CorrelationUtils_FigureTools.o : CorrelationUtils_FigureTools.cpp CorrelationUtils.h
	$(CC) $(CFLAGS) -o $@ -c $<

# PIDUtils
PIDUtils.o : PIDUtils.cpp PIDUtils.h
	$(CC) $(CFLAGS) -c $< -o $@ 

# SetupCustomTrackTree
SetupCustomTrackTree.o : SetupCustomTrackTree.cpp SetupCustomTrackTree.h
	$(CC) $(CFLAGS) -c $< -o $@ 
