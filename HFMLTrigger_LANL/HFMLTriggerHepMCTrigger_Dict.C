// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME HFMLTriggerHepMCTrigger_Dict
#define R__NO_DEPRECATION

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Header files passed as explicit arguments
#include "HFMLTriggerHepMCTrigger.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static TClass *HFMLTriggerHepMCTrigger_Dictionary();
   static void HFMLTriggerHepMCTrigger_TClassManip(TClass*);
   static void delete_HFMLTriggerHepMCTrigger(void *p);
   static void deleteArray_HFMLTriggerHepMCTrigger(void *p);
   static void destruct_HFMLTriggerHepMCTrigger(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::HFMLTriggerHepMCTrigger*)
   {
      ::HFMLTriggerHepMCTrigger *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::HFMLTriggerHepMCTrigger));
      static ::ROOT::TGenericClassInfo 
         instance("HFMLTriggerHepMCTrigger", "", 33,
                  typeid(::HFMLTriggerHepMCTrigger), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &HFMLTriggerHepMCTrigger_Dictionary, isa_proxy, 1,
                  sizeof(::HFMLTriggerHepMCTrigger) );
      instance.SetDelete(&delete_HFMLTriggerHepMCTrigger);
      instance.SetDeleteArray(&deleteArray_HFMLTriggerHepMCTrigger);
      instance.SetDestructor(&destruct_HFMLTriggerHepMCTrigger);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::HFMLTriggerHepMCTrigger*)
   {
      return GenerateInitInstanceLocal((::HFMLTriggerHepMCTrigger*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::HFMLTriggerHepMCTrigger*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *HFMLTriggerHepMCTrigger_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::HFMLTriggerHepMCTrigger*)nullptr)->GetClass();
      HFMLTriggerHepMCTrigger_TClassManip(theClass);
   return theClass;
   }

   static void HFMLTriggerHepMCTrigger_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrapper around operator delete
   static void delete_HFMLTriggerHepMCTrigger(void *p) {
      delete ((::HFMLTriggerHepMCTrigger*)p);
   }
   static void deleteArray_HFMLTriggerHepMCTrigger(void *p) {
      delete [] ((::HFMLTriggerHepMCTrigger*)p);
   }
   static void destruct_HFMLTriggerHepMCTrigger(void *p) {
      typedef ::HFMLTriggerHepMCTrigger current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::HFMLTriggerHepMCTrigger

namespace {
  void TriggerDictionaryInitialization_HFMLTriggerHepMCTrigger_Dict_Impl() {
    static const char* headers[] = {
"0",
nullptr
    };
    static const char* includePaths[] = {
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "HFMLTriggerHepMCTrigger_Dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class HFMLTriggerHepMCTrigger;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "HFMLTriggerHepMCTrigger_Dict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#ifndef __HFMLTriggerHepMCTrigger_H__
#define __HFMLTriggerHepMCTrigger_H__

// --- need to check all these includes...
#include <fun4all/SubsysReco.h>
#include <limits.h>
#include <cmath>
#include <fstream>  // std::fstream
#include <string>
#include <vector>

#include <g4main/PHG4Particle.h>
#include <g4main/PHG4TruthInfoContainer.h>
#include <g4main/PHG4VtxPoint.h>

class TTree;
class TFile;
class TH1D;
class TH2F;
class TH3F;

class PHCompositeNode;
class PHHepMCGenEventMap;
class PdbParameterMap;

namespace HepMC
{
class GenEvent;
}

class HFMLTriggerHepMCTrigger : public SubsysReco
{
 public:
  HFMLTriggerHepMCTrigger(const std::string &moduleName, const std::string &filename, bool IsSignal, bool IsbbBar);

  int Init(PHCompositeNode *);
  int InitRun(PHCompositeNode *);
  int process_event(PHCompositeNode *);
  int End(PHCompositeNode *);

  double
  get_eta_max() const
  {
    return _eta_max;
  }

  void
  set_eta_max(double etaMax)
  {
    _eta_max = etaMax;
  }

  double
  get_eta_min() const
  {
    return _eta_min;
  }

  void
  set_eta_min(double etaMin)
  {
    _eta_min = etaMin;
  }

  void set_RejectReturnCode(int r) { m_RejectReturnCode = r; }

  //! The embedding ID for the HepMC subevent to be analyzed.
  //! embedding ID for the event
  //! positive ID is the embedded event of interest, e.g. jetty event from pythia
  //! negative IDs are backgrounds, .e.g out of time pile up collisions
  //! Usually, ID = 0 means the primary Au+Au collision background
  int get_embedding_id() const { return _embedding_id; }
  //
  //! The embedding ID for the HepMC subevent to be analyzed.
  //! embedding ID for the event
  //! positive ID is the embedded event of interest, e.g. jetty event from pythia
  //! negative IDs are backgrounds, .e.g out of time pile up collisions
  //! Usually, ID = 0 means the primary Au+Au collision background
  void set_embedding_id(int id) { _embedding_id = id; }

 private:
  int _ievent;



  int m_RejectReturnCode;

  TFile *_f;

  std::string _foutname;

  double _eta_min;
  double _eta_max;

  bool SignalSim;
  bool DobbBar;

  //! The embedding ID for the HepMC subevent to be analyzed.
  //! positive ID is the embedded event of interest, e.g. jetty event from pythia
  //! negative IDs are backgrounds, .e.g out of time pile up collisions
  //! Usually, ID = 0 means the primary Au+Au collision background
  int _embedding_id;

//  PHHepMCGenEventMap *m_Geneventmap;
  PdbParameterMap *m_Flags;

  PHG4TruthInfoContainer * m_truth_info;
  TH1D *m_hNorm;
  TH2F *m_DRapidity;
};

#endif  // __HFMLTriggerHepMCTrigger_H__

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"HFMLTriggerHepMCTrigger", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("HFMLTriggerHepMCTrigger_Dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_HFMLTriggerHepMCTrigger_Dict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_HFMLTriggerHepMCTrigger_Dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_HFMLTriggerHepMCTrigger_Dict() {
  TriggerDictionaryInitialization_HFMLTriggerHepMCTrigger_Dict_Impl();
}
