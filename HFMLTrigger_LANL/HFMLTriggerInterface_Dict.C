// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME HFMLTriggerInterface_Dict
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
#include "HFMLTriggerInterface.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static TClass *HFMLTriggerInterface_Dictionary();
   static void HFMLTriggerInterface_TClassManip(TClass*);
   static void delete_HFMLTriggerInterface(void *p);
   static void deleteArray_HFMLTriggerInterface(void *p);
   static void destruct_HFMLTriggerInterface(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::HFMLTriggerInterface*)
   {
      ::HFMLTriggerInterface *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::HFMLTriggerInterface));
      static ::ROOT::TGenericClassInfo 
         instance("HFMLTriggerInterface", "", 40,
                  typeid(::HFMLTriggerInterface), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &HFMLTriggerInterface_Dictionary, isa_proxy, 1,
                  sizeof(::HFMLTriggerInterface) );
      instance.SetDelete(&delete_HFMLTriggerInterface);
      instance.SetDeleteArray(&deleteArray_HFMLTriggerInterface);
      instance.SetDestructor(&destruct_HFMLTriggerInterface);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::HFMLTriggerInterface*)
   {
      return GenerateInitInstanceLocal((::HFMLTriggerInterface*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::HFMLTriggerInterface*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *HFMLTriggerInterface_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::HFMLTriggerInterface*)nullptr)->GetClass();
      HFMLTriggerInterface_TClassManip(theClass);
   return theClass;
   }

   static void HFMLTriggerInterface_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrapper around operator delete
   static void delete_HFMLTriggerInterface(void *p) {
      delete ((::HFMLTriggerInterface*)p);
   }
   static void deleteArray_HFMLTriggerInterface(void *p) {
      delete [] ((::HFMLTriggerInterface*)p);
   }
   static void destruct_HFMLTriggerInterface(void *p) {
      typedef ::HFMLTriggerInterface current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::HFMLTriggerInterface

namespace {
  void TriggerDictionaryInitialization_HFMLTriggerInterface_Dict_Impl() {
    static const char* headers[] = {
"0",
nullptr
    };
    static const char* includePaths[] = {
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "HFMLTriggerInterface_Dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class HFMLTriggerInterface;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "HFMLTriggerInterface_Dict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#ifndef __HFMLTriggerInterface_H__
#define __HFMLTriggerInterface_H__

// --- need to check all these includes...
#include <fun4all/SubsysReco.h>
#include <limits.h>
#include <cmath>
#include <fstream>  // std::fstream
#include <string>
#include <vector>
#include <map>
#include <g4main/PHG4VtxPoint.h>
#include <trackbase/ActsGeometry.h>


class TTree;
class TFile;
class TH2F;
class TH3F;

class PdbParameterMap;
class PHCompositeNode;
class PHG4CylinderGeomContainer;
class PHG4HitContainer;
class PHHepMCGenEventMap;
class PHG4TruthInfoContainer;
class PHG4Hit;
class SvtxEvalStack;
//class TrkrClusterHitAssoc;
class TrkrHitSetContainer;
class TrkrHitTruthAssoc;

namespace HepMC
{
class GenEvent;
}

class HFMLTriggerInterface : public SubsysReco
{
 public:
  HFMLTriggerInterface(std::string filename);

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

  int load_nodes(PHCompositeNode* topNode);

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
  PHG4VtxPoint* vtx = nullptr;

  // eval stack

  TrkrHitSetContainer *m_hitsets;

  PHHepMCGenEventMap *m_GenEventMap;
  PHG4TruthInfoContainer *m_truthInfo;
  PHG4HitContainer *m_g4hits_mvtx;
  PHG4HitContainer *m_g4hits_intt;
	
  //SvtxEvalStack *_svtxevalstack;

  TrkrHitTruthAssoc   *m_hit_truth_map;
  //TrkrClusterHitAssoc *m_cluster_hit_map;

  PdbParameterMap *m_Flags;
  ActsGeometry * m_tGeometry;

  PHG4CylinderGeomContainer *m_Geoms;
  PHG4CylinderGeomContainer *m_Geoms2;

  TH2F *m_hitStaveLayer;
  TH2F *m_hitModuleHalfStave;
  TH2F *m_hitChipModule;

  TH3F *m_hitLayerMap;
  TH3F *m_hitPixelPhiMap;
  TH3F *m_hitPixelPhiMapHL;
  TH3F *m_hitPixelZMap;
  
};

#endif  // __HFMLTriggerInterface_H__

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"HFMLTriggerInterface", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("HFMLTriggerInterface_Dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_HFMLTriggerInterface_Dict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_HFMLTriggerInterface_Dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_HFMLTriggerInterface_Dict() {
  TriggerDictionaryInitialization_HFMLTriggerInterface_Dict_Impl();
}
