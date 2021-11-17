// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME PHG4CylinderGeomv2_Dict
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

// The generated code does not explicitly qualifies STL entities
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "PHG4CylinderGeomv2.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_PHG4CylinderGeomv2(void *p = 0);
   static void *newArray_PHG4CylinderGeomv2(Long_t size, void *p);
   static void delete_PHG4CylinderGeomv2(void *p);
   static void deleteArray_PHG4CylinderGeomv2(void *p);
   static void destruct_PHG4CylinderGeomv2(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PHG4CylinderGeomv2*)
   {
      ::PHG4CylinderGeomv2 *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PHG4CylinderGeomv2 >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PHG4CylinderGeomv2", ::PHG4CylinderGeomv2::Class_Version(), "", 17,
                  typeid(::PHG4CylinderGeomv2), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PHG4CylinderGeomv2::Dictionary, isa_proxy, 4,
                  sizeof(::PHG4CylinderGeomv2) );
      instance.SetNew(&new_PHG4CylinderGeomv2);
      instance.SetNewArray(&newArray_PHG4CylinderGeomv2);
      instance.SetDelete(&delete_PHG4CylinderGeomv2);
      instance.SetDeleteArray(&deleteArray_PHG4CylinderGeomv2);
      instance.SetDestructor(&destruct_PHG4CylinderGeomv2);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PHG4CylinderGeomv2*)
   {
      return GenerateInitInstanceLocal((::PHG4CylinderGeomv2*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::PHG4CylinderGeomv2*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr PHG4CylinderGeomv2::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PHG4CylinderGeomv2::Class_Name()
{
   return "PHG4CylinderGeomv2";
}

//______________________________________________________________________________
const char *PHG4CylinderGeomv2::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PHG4CylinderGeomv2*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PHG4CylinderGeomv2::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PHG4CylinderGeomv2*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PHG4CylinderGeomv2::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PHG4CylinderGeomv2*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PHG4CylinderGeomv2::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PHG4CylinderGeomv2*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void PHG4CylinderGeomv2::Streamer(TBuffer &R__b)
{
   // Stream an object of class PHG4CylinderGeomv2.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PHG4CylinderGeomv2::Class(),this);
   } else {
      R__b.WriteClassBuffer(PHG4CylinderGeomv2::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PHG4CylinderGeomv2(void *p) {
      return  p ? new(p) ::PHG4CylinderGeomv2 : new ::PHG4CylinderGeomv2;
   }
   static void *newArray_PHG4CylinderGeomv2(Long_t nElements, void *p) {
      return p ? new(p) ::PHG4CylinderGeomv2[nElements] : new ::PHG4CylinderGeomv2[nElements];
   }
   // Wrapper around operator delete
   static void delete_PHG4CylinderGeomv2(void *p) {
      delete ((::PHG4CylinderGeomv2*)p);
   }
   static void deleteArray_PHG4CylinderGeomv2(void *p) {
      delete [] ((::PHG4CylinderGeomv2*)p);
   }
   static void destruct_PHG4CylinderGeomv2(void *p) {
      typedef ::PHG4CylinderGeomv2 current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PHG4CylinderGeomv2

namespace {
  void TriggerDictionaryInitialization_PHG4CylinderGeomv2_Dict_Impl() {
    static const char* headers[] = {
"0",
0
    };
    static const char* includePaths[] = {
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "PHG4CylinderGeomv2_Dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class PHG4CylinderGeomv2;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "PHG4CylinderGeomv2_Dict dictionary payload"

#ifndef CGAL_DISABLE_ROUNDING_MATH_CHECK
  #define CGAL_DISABLE_ROUNDING_MATH_CHECK 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
// Tell emacs that this is a C++ source
//  -*- C++ -*-.
#ifndef G4DETECTORS_PHG4CYLINDERGEOMV2_H
#define G4DETECTORS_PHG4CYLINDERGEOMV2_H

#include "PHG4CylinderGeomv1.h"

#include <iostream>              // for cout, ostream

class PHParameters;

class PHG4CylinderGeomv2: public PHG4CylinderGeomv1
{
 public:
  PHG4CylinderGeomv2();
  PHG4CylinderGeomv2(const double r, const double zmi, const double zma, const double thickn, const int n_scint):
    PHG4CylinderGeomv1(r,zmi,zma,thickn),
    nscint(n_scint)
      {}

  ~PHG4CylinderGeomv2() override {}

// from PHObject
  void identify(std::ostream& os = std::cout) const override;

  void set_nscint(const int i) override {nscint = i;}
  int get_nscint() const override {return nscint;}

  //! load parameters from PHParameters, which interface to Database/XML/ROOT files
  void ImportParameters(const PHParameters & param) override;

 protected:
  int nscint;

  ClassDefOverride(PHG4CylinderGeomv2,1)
};

#endif

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"PHG4CylinderGeomv2", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("PHG4CylinderGeomv2_Dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_PHG4CylinderGeomv2_Dict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_PHG4CylinderGeomv2_Dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_PHG4CylinderGeomv2_Dict() {
  TriggerDictionaryInitialization_PHG4CylinderGeomv2_Dict_Impl();
}
