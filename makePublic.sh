#!/bin/sh
# Copies the physics results to www

tag=$1

wwwdir=$2
wwwtag=$3

charged_particle_ptbin="0.50-1.00"
charged_particle_multbin="080-100"

pion_particle_ptbin="0.60-0.80"
pion_particle_multbin="080-100"

kaon_particle_ptbin="0.60-0.80"
kaon_particle_multbin="080-100"

proton_particle_ptbin="0.60-0.80"
proton_particle_multbin="080-100"


twikiout="${wwwtag}.twiki"

homedir=$(pwd)

echo "Home directory: $homedir"

# Package the whole results directory into a tar.gz
tar -cvf "${wwwtag}.tar" ./results/$tag/
gzip "${wwwtag}".tar

# Remove the existing www directory and make a new one
rm -rf $wwwdir/$wwwtag
mkdir  $wwwdir/$wwwtag

mv "${wwwtag}".tar.gz $wwwdir/$wwwtag/"${wwwtag}".tar.gz

# Correl1D
www_correl1D=$wwwdir/$wwwtag/correl1D
rm -rf $www_correl1D
mkdir  $www_correl1D
cp -r ./results/$tag/correl1D/* $www_correl1D


# Correl2D
www_correl2D=$wwwdir/$wwwtag/correl2D
rm -rf $www_correl2D
mkdir  $www_correl2D
cp -r ./results/$tag/correl2D/* $www_correl2D


# v2
www_v2=$wwwdir/$wwwtag/v2
rm -rf $www_v2
mkdir  $www_v2
cp -r ./results/$tag/v2/* $www_v2

#######################
### Make animations ###
#######################
delaytime=160

##### - Correl2D - #####
### CParticle ###
# Correl2D signal component, nTrk dependence in the pt 0.60-1.00 window
outputbase=correl2D_signal_cpar_pt_${charged_particle_ptbin}_nTrk_dep
cd $www_correl2D
files=$(ls | grep -v "self" | grep "signal_typ_0_pt_${charged_particle_ptbin}_nTrk_*")
echo $files
convert -delay $delaytime -loop 0 $files ${outputbase}.gif
tar -cvf ${outputbase}.tar $files
gzip ${outputbase}.tar

# Correl2D backgr component, nTrk dependence in the pt 0.60-1.00 window
outputbase=correl2D_backgr_cpar_pt_${charged_particle_ptbin}_nTrk_dep
cd $www_correl2D
files=$(ls | grep -v "self" | grep "backgr_typ_0_pt_${charged_particle_ptbin}_nTrk_*")
echo $files
convert -delay $delaytime -loop 0 $files ${outputbase}.gif
tar -cvf ${outputbase}.tar $files
gzip ${outputbase}.tar

# Correl2D correlation function, nTrk dependence in the pt 0.60-1.00 window
outputbase=correl2D_functi_cpar_pt_${charged_particle_ptbin}_nTrk_dep
cd $www_correl2D
files=$(ls | grep -v "self" | grep "functi_typ_0_pt_${charged_particle_ptbin}_nTrk_*")
echo $files
convert -delay $delaytime -loop 0 $files ${outputbase}.gif
tar -cvf ${outputbase}.tar $files
gzip ${outputbase}.tar

# Correl2D signal component, nTrk dependence in the pt 0.60-1.00 window
outputbase=correl2D_signal_cpar_nTrk_${charged_particle_multbin}_pt_dep
cd $www_correl2D
files=$(ls | grep -v "self" | grep "signal_typ_0_pt_....-...._nTrk_${charged_particle_multbin}")
echo $files
convert -delay $delaytime -loop 0 $files ${outputbase}.gif
tar -cvf ${outputbase}.tar $files
gzip ${outputbase}.tar

# Correl2D backgr component, nTrk dependence in the pt 0.60-1.00 window
outputbase=correl2D_backgr_cpar_nTrk_${charged_particle_multbin}_pt_dep
cd $www_correl2D
files=$(ls | grep -v "self" | grep "backgr_typ_0_pt_....-...._nTrk_${charged_particle_multbin}")
echo $files
convert -delay $delaytime -loop 0 $files ${outputbase}.gif
tar -cvf ${outputbase}.tar $files
gzip ${outputbase}.tar

# Correl2D correlation function, nTrk dependence in the pt 0.60-1.00 window
outputbase=correl2D_functi_cpar_nTrk_${charged_particle_multbin}_pt_dep
cd $www_correl2D
files=$(ls | grep -v "self" | grep "functi_typ_0_pt_....-...._nTrk_${charged_particle_multbin}")
echo $files
convert -delay $delaytime -loop 0 $files ${outputbase}.gif
tar -cvf ${outputbase}.tar $files
gzip ${outputbase}.tar


### Pion ###
# Correl2D signal component, nTrk dependence in the pt ${pion_particle_ptbin} window
outputbase=correl2D_signal_pion_pt_${pion_particle_ptbin}_nTrk_dep
cd $www_correl2D
files=$(ls | grep -v "self" | grep "signal_typ_1_pt_${pion_particle_ptbin}_nTrk_*")
echo $files
convert -delay $delaytime -loop 0 $files ${outputbase}.gif
tar -cvf ${outputbase}.tar $files
gzip ${outputbase}.tar

# Correl2D backgr component, nTrk dependence in the pt ${pion_particle_ptbin} window
outputbase=correl2D_backgr_pion_pt_${pion_particle_ptbin}_nTrk_dep
cd $www_correl2D
files=$(ls | grep -v "self" | grep "backgr_typ_1_pt_${pion_particle_ptbin}_nTrk_*")
echo $files
convert -delay $delaytime -loop 0 $files ${outputbase}.gif
tar -cvf ${outputbase}.tar $files
gzip ${outputbase}.tar

# Correl2D correlation function, nTrk dependence in the pt ${pion_particle_ptbin} window
outputbase=correl2D_functi_pion_pt_${pion_particle_ptbin}_nTrk_dep
cd $www_correl2D
files=$(ls | grep -v "self" | grep "functi_typ_1_pt_${pion_particle_ptbin}_nTrk_*")
echo $files
convert -delay $delaytime -loop 0 $files ${outputbase}.gif
tar -cvf ${outputbase}.tar $files
gzip ${outputbase}.tar

# Correl2D signal component, nTrk dependence in the pt 0.60-0.80 window
outputbase=correl2D_signal_pion_nTrk_${pion_particle_multbin}_pt_dep
cd $www_correl2D
files=$(ls | grep -v "self" | grep "signal_typ_1_pt_....-...._nTrk_${pion_particle_multbin}")
echo $files
convert -delay $delaytime -loop 0 $files ${outputbase}.gif
tar -cvf ${outputbase}.tar $files
gzip ${outputbase}.tar

# Correl2D backgr component, nTrk dependence in the pt 0.60-0.80 window
outputbase=correl2D_backgr_pion_nTrk_${pion_particle_multbin}_pt_dep
cd $www_correl2D
files=$(ls | grep -v "self" | grep "backgr_typ_1_pt_....-...._nTrk_${pion_particle_multbin}")
echo $files
convert -delay $delaytime -loop 0 $files ${outputbase}.gif
tar -cvf ${outputbase}.tar $files
gzip ${outputbase}.tar

# Correl2D correlation function, nTrk dependence in the pt 0.60-0.80 window
outputbase=correl2D_functi_pion_nTrk_${pion_particle_multbin}_pt_dep
cd $www_correl2D
files=$(ls | grep -v "self" | grep "functi_typ_1_pt_....-...._nTrk_${pion_particle_multbin}")
echo $files
convert -delay $delaytime -loop 0 $files ${outputbase}.gif
tar -cvf ${outputbase}.tar $files
gzip ${outputbase}.tar


### Kaon ###
# Correl2D signal component, nTrk dependence in the pt ${kaon_particle_ptbin} window
outputbase=correl2D_signal_kaon_pt_${kaon_particle_ptbin}_nTrk_dep
cd $www_correl2D
files=$(ls | grep -v "self" | grep "signal_typ_2_pt_${kaon_particle_ptbin}_nTrk_*")
echo $files
convert -delay $delaytime -loop 0 $files ${outputbase}.gif
tar -cvf ${outputbase}.tar $files
gzip ${outputbase}.tar

# Correl2D backgr component, nTrk dependence in the pt ${kaon_particle_ptbin} window
outputbase=correl2D_backgr_kaon_pt_${kaon_particle_ptbin}_nTrk_dep
cd $www_correl2D
files=$(ls | grep -v "self" | grep "backgr_typ_2_pt_${kaon_particle_ptbin}_nTrk_*")
echo $files
convert -delay $delaytime -loop 0 $files ${outputbase}.gif
tar -cvf ${outputbase}.tar $files
gzip ${outputbase}.tar

# Correl2D correlation function, nTrk dependence in the pt ${kaon_particle_ptbin} window
outputbase=correl2D_functi_kaon_pt_${kaon_particle_ptbin}_nTrk_dep
cd $www_correl2D
files=$(ls | grep -v "self" | grep "functi_typ_2_pt_${kaon_particle_ptbin}_nTrk_*")
echo $files
convert -delay $delaytime -loop 0 $files ${outputbase}.gif
tar -cvf ${outputbase}.tar $files
gzip ${outputbase}.tar

# Correl2D signal component, nTrk dependence in the pt 0.60-0.80 window
outputbase=correl2D_signal_kaon_nTrk_${kaon_particle_multbin}_pt_dep
cd $www_correl2D
files=$(ls | grep -v "self" | grep "signal_typ_2_pt_....-...._nTrk_${kaon_particle_multbin}")
echo $files
convert -delay $delaytime -loop 0 $files ${outputbase}.gif
tar -cvf ${outputbase}.tar $files
gzip ${outputbase}.tar

# Correl2D backgr component, nTrk dependence in the pt 0.60-0.80 window
outputbase=correl2D_backgr_kaon_nTrk_${kaon_particle_multbin}_pt_dep
cd $www_correl2D
files=$(ls | grep -v "self" | grep "backgr_typ_2_pt_....-...._nTrk_${kaon_particle_multbin}")
echo $files
convert -delay $delaytime -loop 0 $files ${outputbase}.gif
tar -cvf ${outputbase}.tar $files
gzip ${outputbase}.tar

# Correl2D correlation function, nTrk dependence in the pt 0.60-0.80 window
outputbase=correl2D_functi_kaon_nTrk_${kaon_particle_multbin}_pt_dep
cd $www_correl2D
files=$(ls | grep -v "self" | grep "functi_typ_2_pt_....-...._nTrk_${kaon_particle_multbin}")
echo $files
convert -delay $delaytime -loop 0 $files ${outputbase}.gif
tar -cvf ${outputbase}.tar $files
gzip ${outputbase}.tar


### Proton ###
# Correl2D signal component, nTrk dependence in the pt ${proton_particle_ptbin} window
outputbase=correl2D_signal_prot_pt_${proton_particle_ptbin}_nTrk_dep
cd $www_correl2D
files=$(ls | grep -v "self" | grep "signal_typ_3_pt_${proton_particle_ptbin}_nTrk_*")
echo $files
convert -delay $delaytime -loop 0 $files ${outputbase}.gif
tar -cvf ${outputbase}.tar $files
gzip ${outputbase}.tar

# Correl2D backgr component, nTrk dependence in the pt ${proton_particle_ptbin} window
outputbase=correl2D_backgr_prot_pt_${proton_particle_ptbin}_nTrk_dep
cd $www_correl2D
files=$(ls | grep -v "self" | grep "backgr_typ_3_pt_${proton_particle_ptbin}_nTrk_*")
echo $files
convert -delay $delaytime -loop 0 $files ${outputbase}.gif
tar -cvf ${outputbase}.tar $files
gzip ${outputbase}.tar

# Correl2D correlation function, nTrk dependence in the pt ${proton_particle_ptbin} window
outputbase=correl2D_functi_prot_pt_${proton_particle_ptbin}_nTrk_dep
cd $www_correl2D
files=$(ls | grep -v "self" | grep "functi_typ_3_pt_${proton_particle_ptbin}_nTrk_*")
echo $files
convert -delay $delaytime -loop 0 $files ${outputbase}.gif
tar -cvf ${outputbase}.tar $files
gzip ${outputbase}.tar

# Correl2D signal component, nTrk dependence in the pt 0.60-0.80 window
outputbase=correl2D_signal_prot_nTrk_${proton_particle_multbin}_pt_dep
cd $www_correl2D
files=$(ls | grep -v "self" | grep "signal_typ_3_pt_....-...._nTrk_${proton_particle_multbin}")
echo $files
convert -delay $delaytime -loop 0 $files ${outputbase}.gif
tar -cvf ${outputbase}.tar $files
gzip ${outputbase}.tar

# Correl2D backgr component, nTrk dependence in the pt 0.60-0.80 window
outputbase=correl2D_backgr_prot_nTrk_${proton_particle_multbin}_pt_dep
cd $www_correl2D
files=$(ls | grep -v "self" | grep "backgr_typ_3_pt_....-...._nTrk_${proton_particle_multbin}")
echo $files
convert -delay $delaytime -loop 0 $files ${outputbase}.gif
tar -cvf ${outputbase}.tar $files
gzip ${outputbase}.tar

# Correl2D correlation function, nTrk dependence in the pt 0.60-0.80 window
outputbase=correl2D_functi_prot_nTrk_${proton_particle_multbin}_pt_dep
cd $www_correl2D
files=$(ls | grep -v "self" | grep "functi_typ_3_pt_....-...._nTrk_${proton_particle_multbin}")
echo $files
convert -delay $delaytime -loop 0 $files ${outputbase}.gif
tar -cvf ${outputbase}.tar $files
gzip ${outputbase}.tar

##### - Correl1D - #####
### CPar ###
outputbase=correl1D_cpar_pt_${charged_particle_ptbin}_nTrk_dep
cd $www_correl1D
files=$(ls | grep -v "self" | grep "typ_0_pt_${charged_particle_ptbin}_nTrk_")
echo $files
convert -delay $delaytime -loop 0 $files ${outputbase}.gif
tar -cvf ${outputbase}.tar $files
gzip ${outputbase}.tar

outputbase=correl1D_cpar_nTrk_${charged_particle_multbin}_pt_dep
cd $www_correl1D
files=$(ls | grep -v "self" | grep "typ_0_pt_....-...._nTrk_${charged_particle_multbin}")
echo $files
convert -delay $delaytime -loop 0 $files ${outputbase}.gif
tar -cvf ${outputbase}.tar $files
gzip ${outputbase}.tar

### Pion ###
outputbase=correl1D_pion_pt_${pion_particle_ptbin}_nTrk_dep
cd $www_correl1D
files=$(ls | grep -v "self" | grep "typ_1_pt_${pion_particle_ptbin}_nTrk_")
echo $files
convert -delay $delaytime -loop 0 $files ${outputbase}.gif
tar -cvf ${outputbase}.tar $files
gzip ${outputbase}.tar

outputbase=correl1D_pion_nTrk_${pion_particle_multbin}_pt_dep
cd $www_correl1D
files=$(ls | grep -v "self" | grep "typ_1_pt_....-...._nTrk_${pion_particle_multbin}")
echo $files
convert -delay $delaytime -loop 0 $files ${outputbase}.gif
tar -cvf ${outputbase}.tar $files
gzip ${outputbase}.tar

### Kaon ###
outputbase=correl1D_kaon_pt_${kaon_particle_ptbin}_nTrk_dep
cd $www_correl1D
files=$(ls | grep -v "self" | grep "typ_2_pt_${kaon_particle_ptbin}_nTrk_")
echo $files
convert -delay $delaytime -loop 0 $files ${outputbase}.gif
tar -cvf ${outputbase}.tar $files
gzip ${outputbase}.tar

outputbase=correl1D_kaon_nTrk_${kaon_particle_multbin}_pt_dep
cd $www_correl1D
files=$(ls | grep -v "self" | grep "typ_2_pt_....-...._nTrk_${kaon_particle_multbin}")
echo $files
convert -delay $delaytime -loop 0 $files ${outputbase}.gif
tar -cvf ${outputbase}.tar $files
gzip ${outputbase}.tar

### Prot ###
outputbase=correl1D_prot_pt_${proton_particle_ptbin}_nTrk_dep
cd $www_correl1D
files=$(ls | grep -v "self" | grep "typ_3_pt_${proton_particle_ptbin}_nTrk_")
echo $files
convert -delay $delaytime -loop 0 $files ${outputbase}.gif
tar -cvf ${outputbase}.tar $files
gzip ${outputbase}.tar

outputbase=correl1D_prot_nTrk_${proton_particle_multbin}_pt_dep
cd $www_correl1D
files=$(ls | grep -v "self" | grep "typ_3_pt_....-...._nTrk_${proton_particle_multbin}")
echo $files
convert -delay $delaytime -loop 0 $files ${outputbase}.gif
tar -cvf ${outputbase}.tar $files
gzip ${outputbase}.tar


##### - v2 vs pt - #####
outputbase=v2vspt_all_nTrk_dep
cd $www_v2
files=$(ls | grep -v "self" | grep "v2vspt_all_nTrk_...-...\.png")
echo $files
convert -delay $delaytime -loop 0 $files ${outputbase}.gif
tar -cvf ${outputbase}.tar $files
gzip ${outputbase}.tar


#######################
### Make Twiki code ###
#######################

cd $homedir
cp twiki_template $twikiout

sed -i "s/DIRECTORY/${wwwtag}/g" $twikiout

sed -i "s/charged_particle_ptbin/${charged_particle_ptbin}/g"     $twikiout
sed -i "s/charged_particle_multbin/${charged_particle_multbin}/g" $twikiout

sed -i "s/pion_particle_ptbin/${pion_particle_ptbin}/g"           $twikiout
sed -i "s/pion_particle_multbin/${pion_particle_multbin}/g"       $twikiout

sed -i "s/kaon_particle_ptbin/${kaon_particle_ptbin}/g"           $twikiout
sed -i "s/kaon_particle_multbin/${kaon_particle_multbin}/g"       $twikiout

sed -i "s/proton_particle_ptbin/${proton_particle_ptbin}/g"       $twikiout
sed -i "s/proton_particle_multbin/${proton_particle_multbin}/g"   $twikiout 

gedit $twikiout

cp $twikiout "$wwwdir/$wwwtag/"
