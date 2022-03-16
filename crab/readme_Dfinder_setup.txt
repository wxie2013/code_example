cd private
mkdir PbPb_production_2018
cd PbPb_production_2018
export SCRAM_ARCH=slc6_amd64_gcc700
/depot/itap/singularity/cms/cmssw-slc6
export SCRAM_ARCH=slc6_amd64_gcc700
source /cvmfs/cms.cern.ch/cmsset_default.sh
cmsenv
source /cvmfs/cms.cern.ch/crab3/crab.sh
source /cvmfs/oasis.opensciencegrid.org/osg-software/osg-wn-client/3.4/current/el6-x86_64/setup.sh

cmsrel CMSSW_10_3_3_patch1
cd CMSSW_10_3_3_patch1/src
cmsenv
git cms-merge-topic -u CmsHI:forest_CMSSW_10_3_1
git remote add cmshi https://github.com/CmsHI/cmssw.git
git fetch cmshi --no-tags
git checkout -b forest_CMSSW_10_3_1 remotes/cmshi/forest_CMSSW_10_3_1
cd HeavyIonsAnalysis/JetAnalysis/python/jets
./makeJetSequences.sh
cd ../../../..
scram b -j4

Then please copy Bfinder/ and test/ to src/

scram b -j4


Then go to test/: ./submit_all.sh    (this will take a very long time)  or you could do the command in submit_all.sh line by line, since it takes a lot of quota.
