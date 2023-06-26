// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME HFMLTriggerOccupancy_Dict
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
#include "HFMLTriggerOccupancy.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static TClass *HFMLTriggerOccupancy_Dictionary();
   static void HFMLTriggerOccupancy_TClassManip(TClass*);
   static void delete_HFMLTriggerOccupancy(void *p);
   static void deleteArray_HFMLTriggerOccupancy(void *p);
   static void destruct_HFMLTriggerOccupancy(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::HFMLTriggerOccupancy*)
   {
      ::HFMLTriggerOccupancy *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::HFMLTriggerOccupancy));
      static ::ROOT::TGenericClassInfo 
         instance("HFMLTriggerOccupancy", "", 33,
                  typeid(::HFMLTriggerOccupancy), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &HFMLTriggerOccupancy_Dictionary, isa_proxy, 1,
                  sizeof(::HFMLTriggerOccupancy) );
      instance.SetDelete(&delete_HFMLTriggerOccupancy);
      instance.SetDeleteArray(&deleteArray_HFMLTriggerOccupancy);
      instance.SetDestructor(&destruct_HFMLTriggerOccupancy);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::HFMLTriggerOccupancy*)
   {
      return GenerateInitInstanceLocal((::HFMLTriggerOccupancy*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::HFMLTriggerOccupancy*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *HFMLTriggerOccupancy_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::HFMLTriggerOccupancy*)nullptr)->GetClass();
      HFMLTriggerOccupancy_TClassManip(theClass);
   return theClass;
   }

   static void HFMLTriggerOccupancy_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrapper around operator delete
   static void delete_HFMLTriggerOccupancy(void *p) {
      delete ((::HFMLTriggerOccupancy*)p);
   }
   static void deleteArray_HFMLTriggerOccupancy(void *p) {
      delete [] ((::HFMLTriggerOccupancy*)p);
   }
   static void destruct_HFMLTriggerOccupancy(void *p) {
      typedef ::HFMLTriggerOccupancy current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::HFMLTriggerOccupancy

namespace {
  void TriggerDictionaryInitialization_HFMLTriggerOccupancy_Dict_Impl() {
    static const char* headers[] = {
"0",
nullptr
    };
    static const char* includePaths[] = {
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "HFMLTriggerOccupancy_Dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class HFMLTriggerOccupancy;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "HFMLTriggerOccupancy_Dict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#ifndef __HFMLTriggerOccupancy_H__
#define __HFMLTriggerOccupancy_H__

// --- need to check all these includes...
#include <fun4all/SubsysReco.h>
#include <limits.h>
#include <cmath>
#include <fstream>  // std::fstream
#include <string>
#include <vector>
#include <trackbase/ActsGeometry.h>

class TTree;
class TFile;
class TH1F;
class TH2F;
class TH3F;

class PHCompositeNode;
class PHG4CylinderGeomContainer;
class PHG4TruthInfoContainer;
class TrkrHitSetContainer;
class SvtxEvalStack;
class PdbParameterMap;

namespace HepMC
{
class GenEvent;
}

class HFMLTriggerOccupancy : public SubsysReco
{
 public:
  HFMLTriggerOccupancy(std::string filename);

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

  TFile *_f;
  std::fstream m_jsonOut;

  std::string _foutname;

  double _eta_min;
  double _eta_max;

  //! The embedding ID for the HepMC subevent to be analyzed.
  //! positive ID is the embedded event of interest, e.g. jetty event from pythia
  //! negative IDs are backgrounds, .e.g out of time pile up collisions
  //! Usually, ID = 0 means the primary Au+Au collision background
  int _embedding_id;

  unsigned int _nlayers_maps;
  enum {kNCHip = 9};

  // eval stack
  SvtxEvalStack *_svtxevalstack;
  TrkrHitSetContainer *m_hitsetcont;
  PHG4CylinderGeomContainer *m_Geoms;
  PHG4TruthInfoContainer *m_truthInfo;
  PdbParameterMap *m_Flags;

  TH1F *m_hNorm;
  TH1F *m_hNChEta;
  TH1F *m_hVertexZ;

  TH2F *m_hitStaveLayer;
  TH2F *m_hitModuleHalfStave;
  TH2F *m_hitChipModule;

  TH3F *m_hitLayerMap;
  TH3F *m_hitPixelPhiMap;
  TH3F *m_hitPixelPhiMapHL;
  TH3F *m_hitPixelZMap;

  TH1F *m_Multiplicity;
  TH2F *m_LayerMultiplicity;
  TH3F *m_LayerChipMultiplicity;
  ActsGeometry * m_tGeometry;

};

#endif  // __HFMLTriggerOccupancy_H__

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"HFMLTriggerOccupancy", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("HFMLTriggerOccupancy_Dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_HFMLTriggerOccupancy_Dict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_HFMLTriggerOccupancy_Dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_HFMLTriggerOccupancy_Dict() {
  TriggerDictionaryInitialization_HFMLTriggerOccupancy_Dict_Impl();
}
