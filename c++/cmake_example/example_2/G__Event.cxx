// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME G__Event

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

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "/home/wxie/AI/code_example/cmake_example/example_2/Event.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_Track(void *p = 0);
   static void *newArray_Track(Long_t size, void *p);
   static void delete_Track(void *p);
   static void deleteArray_Track(void *p);
   static void destruct_Track(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Track*)
   {
      ::Track *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Track >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Track", ::Track::Class_Version(), "Event.h", 23,
                  typeid(::Track), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Track::Dictionary, isa_proxy, 4,
                  sizeof(::Track) );
      instance.SetNew(&new_Track);
      instance.SetNewArray(&newArray_Track);
      instance.SetDelete(&delete_Track);
      instance.SetDeleteArray(&deleteArray_Track);
      instance.SetDestructor(&destruct_Track);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Track*)
   {
      return GenerateInitInstanceLocal((::Track*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Track*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_EventHeader(void *p = 0);
   static void *newArray_EventHeader(Long_t size, void *p);
   static void delete_EventHeader(void *p);
   static void deleteArray_EventHeader(void *p);
   static void destruct_EventHeader(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::EventHeader*)
   {
      ::EventHeader *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::EventHeader >(0);
      static ::ROOT::TGenericClassInfo 
         instance("EventHeader", ::EventHeader::Class_Version(), "Event.h", 84,
                  typeid(::EventHeader), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::EventHeader::Dictionary, isa_proxy, 4,
                  sizeof(::EventHeader) );
      instance.SetNew(&new_EventHeader);
      instance.SetNewArray(&newArray_EventHeader);
      instance.SetDelete(&delete_EventHeader);
      instance.SetDeleteArray(&deleteArray_EventHeader);
      instance.SetDestructor(&destruct_EventHeader);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::EventHeader*)
   {
      return GenerateInitInstanceLocal((::EventHeader*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::EventHeader*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_Event(void *p = 0);
   static void *newArray_Event(Long_t size, void *p);
   static void delete_Event(void *p);
   static void deleteArray_Event(void *p);
   static void destruct_Event(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Event*)
   {
      ::Event *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Event >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Event", ::Event::Class_Version(), "Event.h", 103,
                  typeid(::Event), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Event::Dictionary, isa_proxy, 4,
                  sizeof(::Event) );
      instance.SetNew(&new_Event);
      instance.SetNewArray(&newArray_Event);
      instance.SetDelete(&delete_Event);
      instance.SetDeleteArray(&deleteArray_Event);
      instance.SetDestructor(&destruct_Event);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Event*)
   {
      return GenerateInitInstanceLocal((::Event*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Event*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_HistogramManager(void *p);
   static void deleteArray_HistogramManager(void *p);
   static void destruct_HistogramManager(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::HistogramManager*)
   {
      ::HistogramManager *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::HistogramManager >(0);
      static ::ROOT::TGenericClassInfo 
         instance("HistogramManager", ::HistogramManager::Class_Version(), "Event.h", 174,
                  typeid(::HistogramManager), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::HistogramManager::Dictionary, isa_proxy, 4,
                  sizeof(::HistogramManager) );
      instance.SetDelete(&delete_HistogramManager);
      instance.SetDeleteArray(&deleteArray_HistogramManager);
      instance.SetDestructor(&destruct_HistogramManager);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::HistogramManager*)
   {
      return GenerateInitInstanceLocal((::HistogramManager*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::HistogramManager*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr Track::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Track::Class_Name()
{
   return "Track";
}

//______________________________________________________________________________
const char *Track::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Track*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Track::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Track*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Track::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Track*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Track::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Track*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr EventHeader::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *EventHeader::Class_Name()
{
   return "EventHeader";
}

//______________________________________________________________________________
const char *EventHeader::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::EventHeader*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int EventHeader::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::EventHeader*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *EventHeader::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::EventHeader*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *EventHeader::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::EventHeader*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr Event::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Event::Class_Name()
{
   return "Event";
}

//______________________________________________________________________________
const char *Event::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Event*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Event::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Event*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Event::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Event*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Event::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Event*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr HistogramManager::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *HistogramManager::Class_Name()
{
   return "HistogramManager";
}

//______________________________________________________________________________
const char *HistogramManager::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::HistogramManager*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int HistogramManager::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::HistogramManager*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *HistogramManager::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::HistogramManager*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *HistogramManager::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::HistogramManager*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void Track::Streamer(TBuffer &R__b)
{
   // Stream an object of class Track.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Track::Class(),this);
   } else {
      R__b.WriteClassBuffer(Track::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Track(void *p) {
      return  p ? new(p) ::Track : new ::Track;
   }
   static void *newArray_Track(Long_t nElements, void *p) {
      return p ? new(p) ::Track[nElements] : new ::Track[nElements];
   }
   // Wrapper around operator delete
   static void delete_Track(void *p) {
      delete ((::Track*)p);
   }
   static void deleteArray_Track(void *p) {
      delete [] ((::Track*)p);
   }
   static void destruct_Track(void *p) {
      typedef ::Track current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Track

//______________________________________________________________________________
void EventHeader::Streamer(TBuffer &R__b)
{
   // Stream an object of class EventHeader.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(EventHeader::Class(),this);
   } else {
      R__b.WriteClassBuffer(EventHeader::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_EventHeader(void *p) {
      return  p ? new(p) ::EventHeader : new ::EventHeader;
   }
   static void *newArray_EventHeader(Long_t nElements, void *p) {
      return p ? new(p) ::EventHeader[nElements] : new ::EventHeader[nElements];
   }
   // Wrapper around operator delete
   static void delete_EventHeader(void *p) {
      delete ((::EventHeader*)p);
   }
   static void deleteArray_EventHeader(void *p) {
      delete [] ((::EventHeader*)p);
   }
   static void destruct_EventHeader(void *p) {
      typedef ::EventHeader current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::EventHeader

//______________________________________________________________________________
void Event::Streamer(TBuffer &R__b)
{
   // Stream an object of class Event.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Event::Class(),this);
   } else {
      R__b.WriteClassBuffer(Event::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Event(void *p) {
      return  p ? new(p) ::Event : new ::Event;
   }
   static void *newArray_Event(Long_t nElements, void *p) {
      return p ? new(p) ::Event[nElements] : new ::Event[nElements];
   }
   // Wrapper around operator delete
   static void delete_Event(void *p) {
      delete ((::Event*)p);
   }
   static void deleteArray_Event(void *p) {
      delete [] ((::Event*)p);
   }
   static void destruct_Event(void *p) {
      typedef ::Event current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Event

//______________________________________________________________________________
void HistogramManager::Streamer(TBuffer &R__b)
{
   // Stream an object of class HistogramManager.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(HistogramManager::Class(),this);
   } else {
      R__b.WriteClassBuffer(HistogramManager::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_HistogramManager(void *p) {
      delete ((::HistogramManager*)p);
   }
   static void deleteArray_HistogramManager(void *p) {
      delete [] ((::HistogramManager*)p);
   }
   static void destruct_HistogramManager(void *p) {
      typedef ::HistogramManager current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::HistogramManager

namespace {
  void TriggerDictionaryInitialization_libEvent_Impl() {
    static const char* headers[] = {
"Event.h",
0
    };
    static const char* includePaths[] = {
"/home/root/include",
"/home/root/include",
"/home/wxie/AI/code_example/cmake_example/example_2/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "libEvent dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate(R"ATTRDUMP(A track segment)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$Event.h")))  Track;
class __attribute__((annotate(R"ATTRDUMP(Event Header)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$Event.h")))  EventHeader;
class __attribute__((annotate(R"ATTRDUMP(Event structure)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$Event.h")))  Event;
class __attribute__((annotate(R"ATTRDUMP(Manages all histograms)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$Event.h")))  HistogramManager;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "libEvent dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "Event.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"Event", payloadCode, "@",
"EventHeader", payloadCode, "@",
"HistogramManager", payloadCode, "@",
"Track", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("libEvent",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_libEvent_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_libEvent_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_libEvent() {
  TriggerDictionaryInitialization_libEvent_Impl();
}
