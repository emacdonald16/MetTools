#include "MetTools/MetUncertainty/interface/JetCorrectionUncertainty.hh"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <algorithm>
#include <cmath>
#include <iterator>


namespace {
const std::vector<std::string> labels_ = {
     "Total",
     "AbsoluteStat",
     "AbsoluteScale",
     "AbsoluteFlavMap",
     "AbsoluteMPFBias",
     "Fragmentation",
     "SinglePionECAL",
     "SinglePionHCAL",
     "FlavorQCD",
     "TimePtEta",
     "RelativeJEREC1",
     "RelativeJEREC2",
     "RelativeJERHF",
     "RelativePtBB",
     "RelativePtEC1",
     "RelativePtEC2",
     "RelativePtHF",
     "RelativeBal",
     "RelativeFSR",
     "RelativeStatFSR",
     "RelativeStatEC",
     "RelativeStatHF",
     "PileUpDataMC",
     "PileUpPtRef",
     "PileUpPtBB",
     "PileUpPtEC1",
     "PileUpPtEC2",
     "PileUpPtHF",
     "PileUpMuZero",
     "PileUpEnvelope",
     "SubTotalPileUp",
     "SubTotalRelative",
     "SubTotalPt",
     "SubTotalScale",
     "SubTotalAbsolute",
     "SubTotalMC",
     "TotalNoFlavor",
     "TotalNoTime",
     "TotalNoFlavorNoTime",
     "FlavorZJet",
     "FlavorPhotonJet",
     "FlavorPureGluon",
     "FlavorPureQuark",
     "FlavorPureCharm",
     "FlavorPureBottom",
     "TimeRunBCD",
     "TimeRunEF",
     "TimeRunG",
     "TimeRunH",
     "CorrelationGroupMPFInSitu",
     "CorrelationGroupIntercalibration",
     "CorrelationGroupbJES",
     "CorrelationGroupFlavor",
     "CorrelationGroupUncorrelated"
 };
}

JetCorrectorParametersCollection::JetCorrectorParametersCollection( std::vector<label_type> chosen_sections ) {
	corrections_.clear();
}

std::string
JetCorrectorParametersCollection::findLabel( key_type k ){
   return labels_[k];
}

void JetCorrectionUncertaintyCollection::getSections(std::string inputFile,
                                                   std::vector<std::string> & outputs )
{
  outputs.clear();
  std::ifstream input( inputFile.c_str() );
  while( !input.eof() ) {
    char buff[10000];
    input.getline(buff,10000);
    std::string in(buff);
    if ( in[0] == '[' ) {
      std::string tok = getSection(in);
      if ( tok != "" ) {
        outputs.push_back( tok );
      }
    }
  }
  std::cout << "Found these sections for file: " << std::endl;
  copy(outputs.begin(),outputs.end(), std::ostream_iterator<std::string>(std::cout, "\n") );
}


// Add a JetCorrectorParameter object, possibly with flavor.
void JetCorrectionUncertaintyCollection::push_back( key_type i, value_type const & j) {
  std::cout << "i    = " << i << std::endl;
  uncertainties_.push_back( pair_type(i,j) );
}

// Access the JetCorrectorParameter via the key k.
// key_type is hashed to deal with the three collections
JetCorrectorParameters const & JetCorrectionUncertaintyCollection::operator[]( key_type k ) const {
  collection_type::const_iterator ibegin = uncertainties_.begin(), iend = uncertainties_.end(), i = ibegin;
  for ( ; i != iend; ++i ) {
    if ( k == i->first ) return i->second;
  }
  throw cms::Exception("InvalidInput") << " cannot find key " << static_cast<int>(k)
                                       << " in the JEC payload, this usually means you have to change the global tag" << std::endl;
}

// Get a list of valid keys. These will contain hashed keys
// that are aware of all three collections.
void JetCorrectionUncertaintyCollection::validKeys(std::vector<key_type> & keys ) const {
  keys.clear();
  for ( collection_type::const_iterator ibegin = uncertainties_.begin(),
        iend = uncertainties_.end(), i = ibegin; i != iend; ++i ) {
    keys.push_back( i->first );
  }
}

// Find the key corresponding to each label
JetCorrectionUncertaintyCollection::key_type
JetCorrectionUncertaintyCollection::findKey( std::string const & label ) const {
  // Check the default uncertainties
  std::vector<std::string>::const_iterator found =
    find( labels_.begin(), labels_.end(), label );
  if ( found != labels_.end() ) {
    return static_cast<key_type>(found - labels_.begin());
  }

  // Didn't find default uncertainties, throw exception
  throw cms::Exception("InvalidInput") << " Cannot find label " << label << std::endl;

}

#include "FWCore/Utilities/interface/typelookup.h"

TYPELOOKUP_DATA_REG(JetCorrectionUncertaintyCollection);