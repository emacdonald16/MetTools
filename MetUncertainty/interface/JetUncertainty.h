//
// Original Author:  Fedor Ratnikov Nov 9, 2007
// $Id: JetCorrectorParameters.h,v 1.15 2012/03/01 18:24:52 srappocc Exp $
//
// Generic parameters for Jet corrections
//
#ifndef JetUncertainty_h
#define JetUncertainty_h

#include "CondFormats/Serialization/interface/Serializable.h"
#include "CondFormats/JetMETObjects/interface/Utilities.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"

#include <string>
#include <vector>
#include <tuple>
#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include "FWCore/Utilities/interface/Exception.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"


std::ostream& operator<<(std::ostream& out, const JetCorrectorParameters::Record& fBin);


class JetUncertaintyCollection {
  //---------------- JetUncertaintyCollection class ----------------

 public:
  enum Level_t {
     Total=0,
     AbsoluteStat=1,
     AbsoluteScale=2,
     AbsoluteFlavMap=3,
     AbsoluteMPFBias=4,
     Fragmentation=5,
     SinglePionECAL=6,
     SinglePionHCAL=7,
     FlavorQCD=8,
     TimePtEta=9,
     RelativeJEREC1=10,
     RelativeJEREC2=11,
     RelativeJERHF=12,
     RelativePtBB=13,
     RelativePtEC1=14,
     RelativePtEC2=15,
     RelativePtHF=16,
     RelativeBal=17,
     RelativeFSR=18,
     RelativeStatFSR=19,
     RelativeStatEC=20,
     RelativeStatHF=21,
     PileUpDataMC=22,
     PileUpPtRef=23,
     PileUpPtBB=24,
     PileUpPtEC1=25,
     PileUpPtEC2=26,
     PileUpPtHF=27,
     PileUpMuZero=28,
     PileUpEnvelope=29,
     SubTotalPileUp=30,
     SubTotalRelative=31,
     SubTotalPt=32,
     SubTotalScale=33,
     SubTotalAbsolute=34,
     SubTotalMC=35,
     TotalNoFlavor=36,
     TotalNoTime=37,
     TotalNoFlavorNoTime=38,
     FlavorZJet=39,
     FlavorPhotonJet=40,
     FlavorPureGluon=41,
     FlavorPureQuark=42,
     FlavorPureCharm=43,
     FlavorPureBottom=44,
     TimeRunBCD=45,
     TimeRunEF=46,
     TimeRunG=47,
     TimeRunH=48,
     CorrelationGroupMPFInSitu=49,
     CorrelationGroupIntercalibration=50,
     CorrelationGroupbJES=51,
     CorrelationGroupFlavor=52,
     CorrelationGroupUncorrelated=53
  };

  enum L5_Species_t {L5_bJ=0,L5_cJ,L5_qJ,L5_gJ,L5_bT,L5_cT,L5_qT,L5_gT,N_L5_SPECIES};
  enum L7_Species_t {L7_gJ=0,L7_qJ,L7_cJ,L7_bJ,L7_jJ,L7_qT,L7_cT,L7_bT,L7_jT,N_L7_SPECIES};
  typedef int                            key_type;
  typedef std::string                    label_type;
  typedef JetCorrectorParameters         value_type;
  typedef std::pair<key_type,value_type> pair_type;
  typedef std::vector<pair_type>         collection_type;

  // Add a JetCorrectorParameter object, possibly with flavor.
  void push_back( key_type i, value_type const & j, label_type const & flav = "" );

  // Access the JetCorrectorParameter via the key k.
  // key_type is hashed to deal with the three collections
  JetCorrectorParameters const & operator[]( key_type k ) const;

  // Access the JetCorrectorParameter via a string.
  // Will find the hashed value for the label, and call via that
  // operator.
  JetCorrectorParameters const & operator[]( std::string const & label ) const {
    return operator[]( findKey(label) );
  }

  // Get a list of valid keys. These will contain hashed keys
  // that are aware of all three collections.
  void validKeys(std::vector<key_type> & keys ) const;

  // Helper method to find all of the sections in a given
  // parameters file
  static void getSections(std::string inputFile,
                          std::vector<std::string> & outputs );

  // Find the L5 bin for hashing
  static key_type getL5Bin( std::string const & flav );
  // Find the L7 bin for hashing
  static key_type getL7Bin( std::string const & flav );
  // Check if this is an L5 hashed value
  static bool isL5( key_type k );
  // Check if this is an L7 hashed value
  static bool isL7( key_type k );

  static std::string findLabel( key_type k );
  static std::string findL5Flavor( key_type k );
  static std::string findL7Parton( key_type k );


  collection_type                        corrections_;
  collection_type&                       getCorrections()   {return corrections_;}


 protected:

  // Find the key corresponding to each label
  key_type findKey( std::string const & label ) const;



 COND_SERIALIZABLE;

};


#endif
