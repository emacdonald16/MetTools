import FWCore.ParameterSet.Config as cms

def JetDepot(process, JetTag, JetType, jecUncDir=0, doSmear=True, jerUncDir=0):
    # starting value
    # for now, assume JECs have already been updated
    JetTagOut = JetTag
    
    ## ----------------------------------------------------------------------------------------------
    ## JEC uncertainty variations
    ## ----------------------------------------------------------------------------------------------

    from TreeMaker.Utils.jetuncertainty_cfi import JetUncertaintyProducer

    if jecUncDir!=0:
        #JEC unc up or down
        patJetsJEC = JetUncertaintyProducer.clone(
            JetTag = JetTagOut,
            JetType = cms.string(JetType),
            jecUncDir = cms.int32(jecUncDir)
        )
        dir = "up" if jecUncDir>0 else "down"
        JetTagOut = cms.InputTag(JetTagOut.value()+"JEC"+dir)
        setattr(process,JetTagOut.value(),patJetsJEC)

    ## ----------------------------------------------------------------------------------------------
    ## JER smearing + uncertainty variations
    ## ----------------------------------------------------------------------------------------------
    
    from TreeMaker.Utils.smearedpatjet_cfi import SmearedPATJetProducer
    
    if doSmear:
        patSmearedJets = SmearedPATJetProducer.clone(
            src = cms.InputTag(JetTagOut.value()),
            enabled = cms.bool(True),
            rho = cms.InputTag("fixedGridRhoFastjetAll"),
            skipGenMatching = cms.bool(False),
            # Read from GT
            algopt = cms.string(JetType+'_pt'),
            algo = cms.string(JetType),
            # Gen jet matching
            genJets = cms.InputTag("slimmedGenJets"),
            dRMax = cms.double(0.2),
            dPtMaxFactor = cms.double(3),
            variation = cms.int32(jerUncDir),
            seed = cms.uint32(37428479),
            debug = cms.untracked.bool(False)
        )
        dir = "" if jerUncDir==0 else ("up" if jerUncDir>0 else "down")
        JetTagOut = cms.InputTag(JetTagOut.value()+"JER"+dir)
        setattr(process,JetTagOut.value(),patSmearedJets)
    
    return (process, JetTagOut)
