
from CRABClient.UserUtilities import config
config = config()

config.General.requestName = 'pkpi_pT30'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'runForestAOD_pponAA_DATA_103X_onlyDfinder_withlist1.py'

config.Data.inputDataset = '/LambdaCtoPKaonPi_pThat-0_TuneCP5_HydjetDrumMB_PtGT4_5p02TeV_Pythia8/HINPbPbAutumn18DR-mva98_103X_upgrade2018_realistic_HI_v11-v2/AODSIM'
config.Data.inputDBS ='global'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 3
config.Data.outLFNDirBase = '/store/user/mstojano/Lc_PbPb_MC'

config.Data.publication = False
config.Site.storageSite = 'T2_US_Purdue'  # or T2_CH_CERN

#config.section_("Debug")
#config.Debug.extraJDL = ['+CMS_ALLOW_OVERFLOW=False']


