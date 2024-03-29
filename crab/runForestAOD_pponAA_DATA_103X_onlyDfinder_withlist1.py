### HiForest Configuration
# Collisions: PbPb
# Type: Data
# Input: AOD

import FWCore.ParameterSet.Config as cms
process = cms.Process('HiForest')

###############################################################################
# HiForest labelling info
###############################################################################

process.load("HeavyIonsAnalysis.JetAnalysis.HiForest_cff")
process.HiForest.inputLines = cms.vstring("HiForest 103X")
import subprocess, os
version = subprocess.check_output(['git',
    '-C', os.path.expandvars('$CMSSW_BASE/src'), 'describe', '--tags'])
if version == '':
    version = 'no git info'
process.HiForest.HiForestVersion = cms.string(version)

###############################################################################
# Input source
###############################################################################

process.source = cms.Source("PoolSource",
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = cms.untracked.vstring(
        "file:/afs/cern.ch/work/r/rbi/public/forest/step2_t0streamer_RAW2DIGI_L1Reco_RECO.root"
        ),
		
    )

# Number of events we want to process, -1 = all events
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1)
    )

###############################################################################
# Load Global Tag, Geometry, etc.
###############################################################################

process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.Geometry.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')

process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')

from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:phase1_2018_realistic_hi', '') 
process.GlobalTag.snapshotTime = cms.string("9999-12-31 23:59:59.000")
process.GlobalTag.toGet.extend([
   cms.PSet(record = cms.string("HeavyIonRcd"),
      tag = cms.string("CentralityTable_HFtowers200_HydjetDrum5F_v1032x02_mc"),
      connect = cms.string("frontier://FrontierProd/CMS_CONDITIONS"),
      label = cms.untracked.string("HFtowers")
   ),
])


#from Configuration.AlCa.GlobalTag import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, '103X_dataRun2_Prompt_fixEcalADCToGeV_v1', '')
#process.HiForest.GlobalTagLabel = process.GlobalTag.globaltag

#print('\n\033[31m~*~ USING CENTRALITY TABLE FOR PbPb 2018 DATA ~*~\033[0m\n')
#process.GlobalTag.snapshotTime = cms.string("9999-12-31 23:59:59.000")
#process.GlobalTag.toGet.extend([
#    cms.PSet(record = cms.string("HeavyIonRcd"),
#        tag = cms.string("CentralityTable_HFtowers200_DataPbPb_periHYDJETshape_run2v1031x02_offline"),
#        connect = cms.string("frontier://FrontierProd/CMS_CONDITIONS"),
#        label = cms.untracked.string("HFtowers")
#        ),
#    ])

from HeavyIonsAnalysis.Configuration.CommonFunctions_cff import overrideJEC_PbPb5020
process = overrideJEC_PbPb5020(process)

process.load("RecoHI.HiCentralityAlgos.CentralityBin_cfi")
process.centralityBin.Centrality = cms.InputTag("hiCentrality")
process.centralityBin.centralityVariable = cms.string("HFtowers")

###############################################################################
# Define tree output
###############################################################################

process.TFileService = cms.Service("TFileService",
    fileName = cms.string("HiForestAOD.root"))

###############################################################################
# Additional Reconstruction and Analysis: Main Body
###############################################################################

#############################
# Jets
#############################
# jet reco sequence
process.load('HeavyIonsAnalysis.JetAnalysis.fullJetSequence_pponAA_data_cff')
# replace above with this one for JEC:
# process.load('HeavyIonsAnalysis.JetAnalysis.fullJetSequence_JEC_cff')

# temporary
process.akPu4Calocorr.payload = "AK4Calo"
process.akPu4PFcorr.payload = "AK4PF"
process.akCs4PFcorr.payload = "AK4PF"
process.akPu4PFJets.jetPtMin = 1

process.load('HeavyIonsAnalysis.JetAnalysis.hiFJRhoAnalyzer_cff')
process.load("HeavyIonsAnalysis.JetAnalysis.pfcandAnalyzer_cfi")
process.pfcandAnalyzer.doTrackMatching  = cms.bool(True)

###############################################################################

############################
# Event Analysis
############################
process.load('HeavyIonsAnalysis.EventAnalysis.hievtanalyzer_data_cfi')
process.load('HeavyIonsAnalysis.EventAnalysis.hltanalysis_cfi')
process.load('HeavyIonsAnalysis.EventAnalysis.skimanalysis_cfi')
process.load('HeavyIonsAnalysis.EventAnalysis.hltobject_cfi')
process.load('HeavyIonsAnalysis.EventAnalysis.l1object_cfi')

###############################################################################

#########################
# Track Analyzer
#########################
process.load('HeavyIonsAnalysis.TrackAnalysis.ExtraTrackReco_cff')
process.load('HeavyIonsAnalysis.TrackAnalysis.TrkAnalyzers_cff')

# Use this instead for track corrections
# process.load('HeavyIonsAnalysis.TrackAnalysis.TrkAnalyzers_Corr_cff')

###############################################################################

#####################
# Photons
#####################
process.load('HeavyIonsAnalysis.PhotonAnalysis.ggHiNtuplizer_cfi')
process.ggHiNtuplizer.doGenParticles = False
process.ggHiNtuplizerGED.doGenParticles = False

###############################################################################

#######################
# B-tagging
######################
# replace pp CSVv2 with PbPb CSVv2 (positive and negative taggers unchanged!)
process.load('RecoBTag.CSVscikit.csvscikitTagJetTags_cfi')
process.load('RecoBTag.CSVscikit.csvscikitTaggerProducer_cfi')
process.akPu4PFCombinedSecondaryVertexV2BJetTags = process.pfCSVscikitJetTags.clone()
process.akPu4PFCombinedSecondaryVertexV2BJetTags.tagInfos = cms.VInputTag(
    cms.InputTag("akPu4PFImpactParameterTagInfos"),
    cms.InputTag("akPu4PFSecondaryVertexTagInfos"))
process.akCs4PFCombinedSecondaryVertexV2BJetTags = process.pfCSVscikitJetTags.clone()
process.akCs4PFCombinedSecondaryVertexV2BJetTags.tagInfos = cms.VInputTag(
    cms.InputTag("akCs4PFImpactParameterTagInfos"),
    cms.InputTag("akCs4PFSecondaryVertexTagInfos"))
process.akPu4CaloCombinedSecondaryVertexV2BJetTags = process.pfCSVscikitJetTags.clone()
process.akPu4CaloCombinedSecondaryVertexV2BJetTags.tagInfos = cms.VInputTag(
    cms.InputTag("akPu4CaloImpactParameterTagInfos"),
    cms.InputTag("akPu4CaloSecondaryVertexTagInfos"))

# trained on CS jets
process.CSVscikitTags.weightFile = cms.FileInPath(
    'HeavyIonsAnalysis/JetAnalysis/data/TMVA_Btag_CsJets_PbPb_BDTG.weights.xml')

###############################################################################

#########################
# RecHits & pfTowers (HF, Castor & ZDC)
#########################
# ZDC RecHit Producer
process.load('RecoHI.ZDCRecHit.QWZDC2018Producer_cfi')
process.load('RecoHI.ZDCRecHit.QWZDC2018RecHit_cfi')

process.load('HeavyIonsAnalysis.JetAnalysis.rechitanalyzer_cfi')
process.rechitanalyzerpp.doZDCRecHit = True
process.rechitanalyzerpp.zdcRecHitSrc = cms.InputTag("QWzdcreco")
process.pfTowerspp.doHF = False

###############################################################################
#Recover peripheral primary vertices
#https://twiki.cern.ch/twiki/bin/view/CMS/HITracking2018PbPb#Peripheral%20Vertex%20Recovery
process.load("RecoVertex.PrimaryVertexProducer.OfflinePrimaryVerticesRecovery_cfi")


#########################
# Main analysis list
#########################

process.ana_step = cms.Path(
    process.offlinePrimaryVerticesRecovery +
    process.HiForest +
    process.hltanalysis +
    process.hltobject +
    #process.l1object +
    process.centralityBin +
    process.hiEvtAnalyzer +
    process.jetSequence +
    process.ggHiNtuplizer +
    process.ggHiNtuplizerGED +
    process.hiFJRhoAnalyzer +
    process.pfcandAnalyzer +
    process.pfcandAnalyzerCS +
    process.trackSequencesPP +
    process.zdcdigi +
    process.QWzdcreco +
    process.rechitanalyzerpp
    )

# # edm output for debugging purposes
# process.output = cms.OutputModule(
#     "PoolOutputModule",
#     fileName = cms.untracked.string('HiForestEDM.root'),
#     outputCommands = cms.untracked.vstring(
#         'keep *',
#         # drop aliased products
#         'drop *_akULPu3PFJets_*_*',
#         'drop *_akULPu4PFJets_*_*',
#         )
#     )

# process.output_path = cms.EndPath(process.output)

###############################################################################

#########################
# Event Selection
#########################

#process.load('HeavyIonsAnalysis.Configuration.collisionEventSelection_cff')
#process.pclusterCompatibilityFilter = cms.Path(process.clusterCompatibilityFilter)
#process.pprimaryVertexFilter = cms.Path(process.primaryVertexFilter)
#process.pBeamScrapingFilter = cms.Path(process.beamScrapingFilter)
#process.collisionEventSelectionAOD = cms.Path(process.collisionEventSelectionAOD)
#process.collisionEventSelectionAODv2 = cms.Path(process.collisionEventSelectionAODv2)

#process.load('HeavyIonsAnalysis.Configuration.hfCoincFilter_cff')
#process.phfCoincFilter1Th3 = cms.Path(process.hfCoincFilterTh3)
#process.phfCoincFilter2Th3 = cms.Path(process.hfCoincFilter2Th3)
#process.phfCoincFilter3Th3 = cms.Path(process.hfCoincFilter3Th3)
#process.phfCoincFilter4Th3 = cms.Path(process.hfCoincFilter4Th3)
#process.phfCoincFilter5Th3 = cms.Path(process.hfCoincFilter5Th3)
#process.phfCoincFilter1Th4 = cms.Path(process.hfCoincFilterTh4)
#process.phfCoincFilter2Th4 = cms.Path(process.hfCoincFilter2Th4)
#process.phfCoincFilter3Th4 = cms.Path(process.hfCoincFilter3Th4)
#process.phfCoincFilter4Th4 = cms.Path(process.hfCoincFilter4Th4)
#process.phfCoincFilter5Th4 = cms.Path(process.hfCoincFilter5Th4)
#process.phfCoincFilter1Th5 = cms.Path(process.hfCoincFilterTh5)
#process.phfCoincFilter4Th2 = cms.Path(process.hfCoincFilter4Th2)

#process.load("HeavyIonsAnalysis.VertexAnalysis.PAPileUpVertexFilter_cff")
#process.pVertexFilterCutG = cms.Path(process.pileupVertexFilterCutG)
#process.pVertexFilterCutGloose = cms.Path(process.pileupVertexFilterCutGloose)
#process.pVertexFilterCutGtight = cms.Path(process.pileupVertexFilterCutGtight)
#process.pVertexFilterCutGplus = cms.Path(process.pileupVertexFilterCutGplus)
#process.pVertexFilterCutE = cms.Path(process.pileupVertexFilterCutE)
#process.pVertexFilterCutEandG = cms.Path(process.pileupVertexFilterCutEandG)

#process.load('HeavyIonsAnalysis.JetAnalysis.EventSelection_cff')
#process.pHBHENoiseFilterResultProducer = cms.Path(process.HBHENoiseFilterResultProducer)
#process.HBHENoiseFilterResult = cms.Path(process.fHBHENoiseFilterResult)
#process.HBHENoiseFilterResultRun1 = cms.Path(process.fHBHENoiseFilterResultRun1)
#process.HBHENoiseFilterResultRun2Loose = cms.Path(process.fHBHENoiseFilterResultRun2Loose)
#process.HBHENoiseFilterResultRun2Tight = cms.Path(process.fHBHENoiseFilterResultRun2Tight)
#process.HBHEIsoNoiseFilterResult = cms.Path(process.fHBHEIsoNoiseFilterResult)

process.pAna = cms.EndPath(process.skimanalysis)

from HLTrigger.Configuration.CustomConfigs import MassReplaceInputTag
process = MassReplaceInputTag(process,"offlinePrimaryVertices","offlinePrimaryVerticesRecovery")
process.offlinePrimaryVerticesRecovery.oldVertexLabel = "offlinePrimaryVertices"

###############################################################################

# Customization

process.ana_step = cms.Path( 
    process.offlinePrimaryVerticesRecovery + 
    #process.HiForest + 
    process.hltanalysis + 
    #process.hltobject + 
    process.centralityBin + 
    process.hiEvtAnalyzer  
    ) 

#################### D/B finder ################# 
AddCaloMuon = False 
runOnMC = True 
HIFormat = False 
UseGenPlusSim = False 
VtxLabel = "offlinePrimaryVerticesRecovery" 
TrkLabel = "generalTracks" 

from Bfinder.finderMaker.finderMaker_75X_cff import finderMaker_75X
finderMaker_75X(process, AddCaloMuon, runOnMC, HIFormat, UseGenPlusSim, VtxLabel, TrkLabel)
process.Dfinder.MVAMapLabel = cms.InputTag(TrkLabel,"MVAValues")
process.Dfinder.makeDntuple = cms.bool(True)
process.Dfinder.printInfo = cms.bool(False)
process.Dfinder.readDedx = cms.bool(False)
process.Dfinder.tkPtCut = cms.double(1.0)#before fit
process.Dfinder.tkEtaCut = cms.double(1.2)
process.Dfinder.dPtCut = cms.vdouble(1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 5.0, 5.0)#before fit
process.Dfinder.dCutSeparating_PtVal = cms.vdouble(5., 5., 5., 5., 5., 5., 5., 5., 5., 5., 5., 5., 5., 5., 8., 8.) 
process.Dfinder.Dchannel = cms.vint32(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1)
process.Dfinder.alphaCut = cms.vdouble(999.0, 999.0, 999.0, 999.0, 999.0, 999.0, 999.0, 999.0, 999.0, 999.0, 999.0, 999.0, 999.0, 999.0, 0.2, 0.2)
process.Dfinder.dRapidityCut = cms.vdouble(10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 1.1, 1.1)
process.Dfinder.VtxChiProbCut = cms.vdouble(0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.05, 0.05)
process.Dfinder.svpvDistanceCut_highptD = cms.vdouble(2.5, 2.5, 2.5, 2.5, 2.5, 2.5, 2.5, 2.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 2.0, 2.0)
process.Dfinder.svpvDistanceCut_lowptD = cms.vdouble(2.5, 2.5, 2.5, 2.5, 2.5, 2.5, 2.5, 2.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 2.0, 2.0)



process.dfinder = cms.Path(process.DfinderSequence)


###############################
import FWCore.ParameterSet.VarParsing as VarParsing
ivars = VarParsing.VarParsing('analysis')

ivars.maxEvents = -1
ivars.outputFile='HiForestAOD_delet_files_0426_whole.root'
ivars.inputFiles='/store/himc/HINPbPbAutumn18DR/LambdaCtoPKaonPi_pThat-0_TuneCP5_HydjetDrumMB_PtGT4_5p02TeV_Pythia8/AODSIM/mva98_103X_upgrade2018_realistic_HI_v11-v2/110000/0189F64B-6151-A84C-B1EF-9449BC51A695.root'
ivars.parseArguments()# get and parse the command line arguments


process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(ivars.inputFiles),
#	eventsToProcess = events1,
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(ivars.maxEvents)
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string(ivars.outputFile))

