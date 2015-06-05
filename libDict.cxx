// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME libDict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
#include "include/BaselineFinder.hh"
#include "include/CfgReader.hh"
#include "include/Converter.hh"
#include "include/DAQheader.hh"
#include "include/EventData.hh"
#include "include/Integrator.hh"
#include "include/LEDfitfunc.hh"
#include "include/ProcessedPlotter.hh"
#include "include/PulseFinder.hh"
#include "include/RootGraphix.hh"
#include "include/SumChannel.hh"
#include "include/ZeroSuppressor.hh"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_EventData(void *p = 0);
   static void *newArray_EventData(Long_t size, void *p);
   static void delete_EventData(void *p);
   static void deleteArray_EventData(void *p);
   static void destruct_EventData(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::EventData*)
   {
      ::EventData *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::EventData >(0);
      static ::ROOT::TGenericClassInfo 
         instance("EventData", ::EventData::Class_Version(), "include/EventData.hh", 24,
                  typeid(::EventData), DefineBehavior(ptr, ptr),
                  &::EventData::Dictionary, isa_proxy, 4,
                  sizeof(::EventData) );
      instance.SetNew(&new_EventData);
      instance.SetNewArray(&newArray_EventData);
      instance.SetDelete(&delete_EventData);
      instance.SetDeleteArray(&deleteArray_EventData);
      instance.SetDestructor(&destruct_EventData);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::EventData*)
   {
      return GenerateInitInstanceLocal((::EventData*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::EventData*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
TClass *EventData::fgIsA = 0;  // static to hold class pointer

//______________________________________________________________________________
const char *EventData::Class_Name()
{
   return "EventData";
}

//______________________________________________________________________________
const char *EventData::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::EventData*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int EventData::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::EventData*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
void EventData::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::EventData*)0x0)->GetClass();
}

//______________________________________________________________________________
TClass *EventData::Class()
{
   if (!fgIsA) fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::EventData*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
void EventData::Streamer(TBuffer &R__b)
{
   // Stream an object of class EventData.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(EventData::Class(),this);
   } else {
      R__b.WriteClassBuffer(EventData::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_EventData(void *p) {
      return  p ? new(p) ::EventData : new ::EventData;
   }
   static void *newArray_EventData(Long_t nElements, void *p) {
      return p ? new(p) ::EventData[nElements] : new ::EventData[nElements];
   }
   // Wrapper around operator delete
   static void delete_EventData(void *p) {
      delete ((::EventData*)p);
   }
   static void deleteArray_EventData(void *p) {
      delete [] ((::EventData*)p);
   }
   static void destruct_EventData(void *p) {
      typedef ::EventData current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::EventData

namespace ROOT {
   static void vectorlEvectorlEdoublegRsPgR_Dictionary();
   static void vectorlEvectorlEdoublegRsPgR_TClassManip(TClass*);
   static void *new_vectorlEvectorlEdoublegRsPgR(void *p = 0);
   static void *newArray_vectorlEvectorlEdoublegRsPgR(Long_t size, void *p);
   static void delete_vectorlEvectorlEdoublegRsPgR(void *p);
   static void deleteArray_vectorlEvectorlEdoublegRsPgR(void *p);
   static void destruct_vectorlEvectorlEdoublegRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<vector<double> >*)
   {
      vector<vector<double> > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<vector<double> >),0);
      static ::ROOT::TGenericClassInfo 
         instance("vector<vector<double> >", -2, "vector", 484,
                  typeid(vector<vector<double> >), DefineBehavior(ptr, ptr),
                  &vectorlEvectorlEdoublegRsPgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<vector<double> >) );
      instance.SetNew(&new_vectorlEvectorlEdoublegRsPgR);
      instance.SetNewArray(&newArray_vectorlEvectorlEdoublegRsPgR);
      instance.SetDelete(&delete_vectorlEvectorlEdoublegRsPgR);
      instance.SetDeleteArray(&deleteArray_vectorlEvectorlEdoublegRsPgR);
      instance.SetDestructor(&destruct_vectorlEvectorlEdoublegRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<vector<double> > >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<vector<double> >*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static void vectorlEvectorlEdoublegRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<vector<double> >*)0x0)->GetClass();
      vectorlEvectorlEdoublegRsPgR_TClassManip(theClass);
   }

   static void vectorlEvectorlEdoublegRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEvectorlEdoublegRsPgR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<vector<double> > : new vector<vector<double> >;
   }
   static void *newArray_vectorlEvectorlEdoublegRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<vector<double> >[nElements] : new vector<vector<double> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEvectorlEdoublegRsPgR(void *p) {
      delete ((vector<vector<double> >*)p);
   }
   static void deleteArray_vectorlEvectorlEdoublegRsPgR(void *p) {
      delete [] ((vector<vector<double> >*)p);
   }
   static void destruct_vectorlEvectorlEdoublegRsPgR(void *p) {
      typedef vector<vector<double> > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<vector<double> >

namespace ROOT {
   static void vectorlEintgR_Dictionary();
   static void vectorlEintgR_TClassManip(TClass*);
   static void *new_vectorlEintgR(void *p = 0);
   static void *newArray_vectorlEintgR(Long_t size, void *p);
   static void delete_vectorlEintgR(void *p);
   static void deleteArray_vectorlEintgR(void *p);
   static void destruct_vectorlEintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<int>*)
   {
      vector<int> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<int>),0);
      static ::ROOT::TGenericClassInfo 
         instance("vector<int>", -2, "vector", 484,
                  typeid(vector<int>), DefineBehavior(ptr, ptr),
                  &vectorlEintgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<int>) );
      instance.SetNew(&new_vectorlEintgR);
      instance.SetNewArray(&newArray_vectorlEintgR);
      instance.SetDelete(&delete_vectorlEintgR);
      instance.SetDeleteArray(&deleteArray_vectorlEintgR);
      instance.SetDestructor(&destruct_vectorlEintgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<int> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<int>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static void vectorlEintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<int>*)0x0)->GetClass();
      vectorlEintgR_TClassManip(theClass);
   }

   static void vectorlEintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEintgR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<int> : new vector<int>;
   }
   static void *newArray_vectorlEintgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<int>[nElements] : new vector<int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEintgR(void *p) {
      delete ((vector<int>*)p);
   }
   static void deleteArray_vectorlEintgR(void *p) {
      delete [] ((vector<int>*)p);
   }
   static void destruct_vectorlEintgR(void *p) {
      typedef vector<int> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<int>

namespace ROOT {
   static void vectorlEdoublegR_Dictionary();
   static void vectorlEdoublegR_TClassManip(TClass*);
   static void *new_vectorlEdoublegR(void *p = 0);
   static void *newArray_vectorlEdoublegR(Long_t size, void *p);
   static void delete_vectorlEdoublegR(void *p);
   static void deleteArray_vectorlEdoublegR(void *p);
   static void destruct_vectorlEdoublegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<double>*)
   {
      vector<double> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<double>),0);
      static ::ROOT::TGenericClassInfo 
         instance("vector<double>", -2, "vector", 484,
                  typeid(vector<double>), DefineBehavior(ptr, ptr),
                  &vectorlEdoublegR_Dictionary, isa_proxy, 0,
                  sizeof(vector<double>) );
      instance.SetNew(&new_vectorlEdoublegR);
      instance.SetNewArray(&newArray_vectorlEdoublegR);
      instance.SetDelete(&delete_vectorlEdoublegR);
      instance.SetDeleteArray(&deleteArray_vectorlEdoublegR);
      instance.SetDestructor(&destruct_vectorlEdoublegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<double> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<double>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static void vectorlEdoublegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<double>*)0x0)->GetClass();
      vectorlEdoublegR_TClassManip(theClass);
   }

   static void vectorlEdoublegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEdoublegR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<double> : new vector<double>;
   }
   static void *newArray_vectorlEdoublegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<double>[nElements] : new vector<double>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEdoublegR(void *p) {
      delete ((vector<double>*)p);
   }
   static void deleteArray_vectorlEdoublegR(void *p) {
      delete [] ((vector<double>*)p);
   }
   static void destruct_vectorlEdoublegR(void *p) {
      typedef vector<double> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<double>

namespace ROOT {
   static void vectorlEboolgR_Dictionary();
   static void vectorlEboolgR_TClassManip(TClass*);
   static void *new_vectorlEboolgR(void *p = 0);
   static void *newArray_vectorlEboolgR(Long_t size, void *p);
   static void delete_vectorlEboolgR(void *p);
   static void deleteArray_vectorlEboolgR(void *p);
   static void destruct_vectorlEboolgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<bool>*)
   {
      vector<bool> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<bool>),0);
      static ::ROOT::TGenericClassInfo 
         instance("vector<bool>", -2, "vector", 1967,
                  typeid(vector<bool>), DefineBehavior(ptr, ptr),
                  &vectorlEboolgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<bool>) );
      instance.SetNew(&new_vectorlEboolgR);
      instance.SetNewArray(&newArray_vectorlEboolgR);
      instance.SetDelete(&delete_vectorlEboolgR);
      instance.SetDeleteArray(&deleteArray_vectorlEboolgR);
      instance.SetDestructor(&destruct_vectorlEboolgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<bool> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<bool>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static void vectorlEboolgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<bool>*)0x0)->GetClass();
      vectorlEboolgR_TClassManip(theClass);
   }

   static void vectorlEboolgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEboolgR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<bool> : new vector<bool>;
   }
   static void *newArray_vectorlEboolgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<bool>[nElements] : new vector<bool>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEboolgR(void *p) {
      delete ((vector<bool>*)p);
   }
   static void deleteArray_vectorlEboolgR(void *p) {
      delete [] ((vector<bool>*)p);
   }
   static void destruct_vectorlEboolgR(void *p) {
      typedef vector<bool> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<bool>

namespace {
  void TriggerDictionaryInitialization_libDict_Impl() {
    static const char* headers[] = {
"include/BaselineFinder.hh",
"include/CfgReader.hh",
"include/Converter.hh",
"include/DAQheader.hh",
"include/EventData.hh",
"include/Integrator.hh",
"include/LEDfitfunc.hh",
"include/ProcessedPlotter.hh",
"include/PulseFinder.hh",
"include/RootGraphix.hh",
"include/SumChannel.hh",
"include/ZeroSuppressor.hh",
0
    };
    static const char* allHeaders[] = {
// Content file skipped for reproducibility
// Umbrella file skipped for reproducibility
"./LinkDef.h",
"./include/BaselineFinder.hh",
"./include/CfgReader.hh",
"./include/Converter.hh",
"./include/DAQheader.hh",
"./include/EventData.hh",
"./include/Integrator.hh",
"./include/LEDfitfunc.hh",
"./include/ProcessedPlotter.hh",
"./include/PulseFinder.hh",
"./include/RootGraphix.hh",
"./include/SumChannel.hh",
"./include/ZeroSuppressor.hh",
"/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/c++/v1/__bit_reference",
"/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/c++/v1/__config",
"/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/c++/v1/__functional_base",
"/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/c++/v1/__locale",
"/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/c++/v1/__mutex_base",
"/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/c++/v1/__split_buffer",
"/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/c++/v1/__tree",
"/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/c++/v1/__tuple",
"/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/c++/v1/__undef_min_max",
"/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/c++/v1/algorithm",
"/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/c++/v1/atomic",
"/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/c++/v1/bitset",
"/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/c++/v1/cctype",
"/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/c++/v1/cerrno",
"/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/c++/v1/chrono",
"/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/c++/v1/climits",
"/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/c++/v1/cmath",
"/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/c++/v1/cstddef",
"/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/c++/v1/cstdint",
"/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/c++/v1/cstdio",
"/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/c++/v1/cstdlib",
"/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/c++/v1/cstring",
"/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/c++/v1/ctime",
"/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/c++/v1/cwchar",
"/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/c++/v1/cwctype",
"/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/c++/v1/exception",
"/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/c++/v1/fstream",
"/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/c++/v1/functional",
"/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/c++/v1/initializer_list",
"/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/c++/v1/ios",
"/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/c++/v1/iosfwd",
"/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/c++/v1/iostream",
"/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/c++/v1/istream",
"/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/c++/v1/iterator",
"/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/c++/v1/limits",
"/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/c++/v1/locale",
"/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/c++/v1/map",
"/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/c++/v1/memory",
"/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/c++/v1/mutex",
"/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/c++/v1/new",
"/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/c++/v1/ostream",
"/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/c++/v1/ratio",
"/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/c++/v1/sstream",
"/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/c++/v1/stdexcept",
"/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/c++/v1/streambuf",
"/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/c++/v1/string",
"/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/c++/v1/system_error",
"/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/c++/v1/tuple",
"/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/c++/v1/type_traits",
"/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/c++/v1/typeinfo",
"/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/c++/v1/utility",
"/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/c++/v1/vector",
"/Users/yixiongmeng/Software/root/etc/cling/Interpreter/RuntimeException.h",
"/Users/yixiongmeng/Software/root/etc/cling/Interpreter/RuntimeUniverse.h",
"/Users/yixiongmeng/Software/root/etc/cling/Interpreter/ValuePrinter.h",
"/Users/yixiongmeng/Software/root/etc/cling/Interpreter/ValuePrinterInfo.h",
"/Users/yixiongmeng/Software/root/etc/cling/lib/clang/3.5/include/float.h",
"/Users/yixiongmeng/Software/root/etc/cling/lib/clang/3.5/include/limits.h",
"/Users/yixiongmeng/Software/root/etc/cling/lib/clang/3.5/include/stdarg.h",
"/Users/yixiongmeng/Software/root/etc/cling/lib/clang/3.5/include/stddef.h",
"/Users/yixiongmeng/Software/root/etc/cling/lib/clang/3.5/include/stdint.h",
"/Users/yixiongmeng/Software/root/include/Buttons.h",
"/Users/yixiongmeng/Software/root/include/DllImport.h",
"/Users/yixiongmeng/Software/root/include/Foption.h",
"/Users/yixiongmeng/Software/root/include/GuiTypes.h",
"/Users/yixiongmeng/Software/root/include/RConfig.h",
"/Users/yixiongmeng/Software/root/include/RVersion.h",
"/Users/yixiongmeng/Software/root/include/Riosfwd.h",
"/Users/yixiongmeng/Software/root/include/Rtypeinfo.h",
"/Users/yixiongmeng/Software/root/include/Rtypes.h",
"/Users/yixiongmeng/Software/root/include/TApplication.h",
"/Users/yixiongmeng/Software/root/include/TApplicationImp.h",
"/Users/yixiongmeng/Software/root/include/TArray.h",
"/Users/yixiongmeng/Software/root/include/TArrayC.h",
"/Users/yixiongmeng/Software/root/include/TArrayD.h",
"/Users/yixiongmeng/Software/root/include/TArrayF.h",
"/Users/yixiongmeng/Software/root/include/TArrayI.h",
"/Users/yixiongmeng/Software/root/include/TArrayS.h",
"/Users/yixiongmeng/Software/root/include/TAttAxis.h",
"/Users/yixiongmeng/Software/root/include/TAttCanvas.h",
"/Users/yixiongmeng/Software/root/include/TAttFill.h",
"/Users/yixiongmeng/Software/root/include/TAttLine.h",
"/Users/yixiongmeng/Software/root/include/TAttMarker.h",
"/Users/yixiongmeng/Software/root/include/TAttPad.h",
"/Users/yixiongmeng/Software/root/include/TAttText.h",
"/Users/yixiongmeng/Software/root/include/TAxis.h",
"/Users/yixiongmeng/Software/root/include/TBuffer.h",
"/Users/yixiongmeng/Software/root/include/TCanvas.h",
"/Users/yixiongmeng/Software/root/include/TCanvasImp.h",
"/Users/yixiongmeng/Software/root/include/TClingRuntime.h",
"/Users/yixiongmeng/Software/root/include/TCondition.h",
"/Users/yixiongmeng/Software/root/include/TConditionImp.h",
"/Users/yixiongmeng/Software/root/include/TFitResultPtr.h",
"/Users/yixiongmeng/Software/root/include/TGenericClassInfo.h",
"/Users/yixiongmeng/Software/root/include/TH1.h",
"/Users/yixiongmeng/Software/root/include/TH1F.h",
"/Users/yixiongmeng/Software/root/include/TInetAddress.h",
"/Users/yixiongmeng/Software/root/include/TMathBase.h",
"/Users/yixiongmeng/Software/root/include/TMutex.h",
"/Users/yixiongmeng/Software/root/include/TMutexImp.h",
"/Users/yixiongmeng/Software/root/include/TNamed.h",
"/Users/yixiongmeng/Software/root/include/TObject.h",
"/Users/yixiongmeng/Software/root/include/TPad.h",
"/Users/yixiongmeng/Software/root/include/TQObject.h",
"/Users/yixiongmeng/Software/root/include/TSchemaHelper.h",
"/Users/yixiongmeng/Software/root/include/TStorage.h",
"/Users/yixiongmeng/Software/root/include/TString.h",
"/Users/yixiongmeng/Software/root/include/TSysEvtHandler.h",
"/Users/yixiongmeng/Software/root/include/TSystem.h",
"/Users/yixiongmeng/Software/root/include/TThread.h",
"/Users/yixiongmeng/Software/root/include/TThreadSlots.h",
"/Users/yixiongmeng/Software/root/include/TTime.h",
"/Users/yixiongmeng/Software/root/include/TTimer.h",
"/Users/yixiongmeng/Software/root/include/TVectorDfwd.h",
"/Users/yixiongmeng/Software/root/include/TVectorFfwd.h",
"/Users/yixiongmeng/Software/root/include/TVersionCheck.h",
"/Users/yixiongmeng/Software/root/include/TVirtualMutex.h",
"/Users/yixiongmeng/Software/root/include/TVirtualPad.h",
"/Users/yixiongmeng/Software/root/include/TVirtualX.h",
"/Users/yixiongmeng/Software/root/include/Varargs.h",
"/Users/yixiongmeng/Software/root/include/snprintf.h",
"/Users/yixiongmeng/Software/root/include/strlcpy.h",
"/usr/include/Availability.h",
"/usr/include/AvailabilityInternal.h",
"/usr/include/AvailabilityMacros.h",
"/usr/include/TargetConditionals.h",
"/usr/include/_locale.h",
"/usr/include/_structs.h",
"/usr/include/_types.h",
"/usr/include/_types/_intmax_t.h",
"/usr/include/_types/_nl_item.h",
"/usr/include/_types/_uint16_t.h",
"/usr/include/_types/_uint32_t.h",
"/usr/include/_types/_uint64_t.h",
"/usr/include/_types/_uint8_t.h",
"/usr/include/_types/_uintmax_t.h",
"/usr/include/_types/_wctrans_t.h",
"/usr/include/_types/_wctype_t.h",
"/usr/include/_wctype.h",
"/usr/include/_xlocale.h",
"/usr/include/alloca.h",
"/usr/include/assert.h",
"/usr/include/ctype.h",
"/usr/include/errno.h",
"/usr/include/fcntl.h",
"/usr/include/gethostuuid.h",
"/usr/include/i386/_limits.h",
"/usr/include/i386/_mcontext.h",
"/usr/include/i386/_types.h",
"/usr/include/i386/endian.h",
"/usr/include/i386/limits.h",
"/usr/include/i386/signal.h",
"/usr/include/i386/types.h",
"/usr/include/libkern/_OSByteOrder.h",
"/usr/include/libkern/i386/_OSByteOrder.h",
"/usr/include/limits.h",
"/usr/include/locale.h",
"/usr/include/mach/i386/_structs.h",
"/usr/include/machine/_mcontext.h",
"/usr/include/machine/_types.h",
"/usr/include/machine/endian.h",
"/usr/include/machine/limits.h",
"/usr/include/machine/signal.h",
"/usr/include/machine/types.h",
"/usr/include/math.h",
"/usr/include/nl_types.h",
"/usr/include/pthread.h",
"/usr/include/pthread_impl.h",
"/usr/include/runetype.h",
"/usr/include/sched.h",
"/usr/include/stdint.h",
"/usr/include/stdio.h",
"/usr/include/stdlib.h",
"/usr/include/string.h",
"/usr/include/strings.h",
"/usr/include/sys/_endian.h",
"/usr/include/sys/_posix_availability.h",
"/usr/include/sys/_select.h",
"/usr/include/sys/_structs.h",
"/usr/include/sys/_symbol_aliasing.h",
"/usr/include/sys/_types.h",
"/usr/include/sys/_types/___offsetof.h",
"/usr/include/sys/_types/_blkcnt_t.h",
"/usr/include/sys/_types/_blksize_t.h",
"/usr/include/sys/_types/_clock_t.h",
"/usr/include/sys/_types/_ct_rune_t.h",
"/usr/include/sys/_types/_dev_t.h",
"/usr/include/sys/_types/_errno_t.h",
"/usr/include/sys/_types/_fd_clr.h",
"/usr/include/sys/_types/_fd_copy.h",
"/usr/include/sys/_types/_fd_def.h",
"/usr/include/sys/_types/_fd_isset.h",
"/usr/include/sys/_types/_fd_set.h",
"/usr/include/sys/_types/_fd_setsize.h",
"/usr/include/sys/_types/_fd_zero.h",
"/usr/include/sys/_types/_filesec_t.h",
"/usr/include/sys/_types/_fsblkcnt_t.h",
"/usr/include/sys/_types/_fsfilcnt_t.h",
"/usr/include/sys/_types/_gid_t.h",
"/usr/include/sys/_types/_id_t.h",
"/usr/include/sys/_types/_in_addr_t.h",
"/usr/include/sys/_types/_in_port_t.h",
"/usr/include/sys/_types/_ino64_t.h",
"/usr/include/sys/_types/_ino_t.h",
"/usr/include/sys/_types/_int16_t.h",
"/usr/include/sys/_types/_int32_t.h",
"/usr/include/sys/_types/_int64_t.h",
"/usr/include/sys/_types/_int8_t.h",
"/usr/include/sys/_types/_intptr_t.h",
"/usr/include/sys/_types/_key_t.h",
"/usr/include/sys/_types/_mach_port_t.h",
"/usr/include/sys/_types/_mbstate_t.h",
"/usr/include/sys/_types/_mode_t.h",
"/usr/include/sys/_types/_nlink_t.h",
"/usr/include/sys/_types/_null.h",
"/usr/include/sys/_types/_o_dsync.h",
"/usr/include/sys/_types/_o_sync.h",
"/usr/include/sys/_types/_off_t.h",
"/usr/include/sys/_types/_pid_t.h",
"/usr/include/sys/_types/_posix_vdisable.h",
"/usr/include/sys/_types/_pthread_attr_t.h",
"/usr/include/sys/_types/_pthread_cond_t.h",
"/usr/include/sys/_types/_pthread_condattr_t.h",
"/usr/include/sys/_types/_pthread_key_t.h",
"/usr/include/sys/_types/_pthread_mutex_t.h",
"/usr/include/sys/_types/_pthread_mutexattr_t.h",
"/usr/include/sys/_types/_pthread_once_t.h",
"/usr/include/sys/_types/_pthread_rwlock_t.h",
"/usr/include/sys/_types/_pthread_rwlockattr_t.h",
"/usr/include/sys/_types/_pthread_t.h",
"/usr/include/sys/_types/_rsize_t.h",
"/usr/include/sys/_types/_rune_t.h",
"/usr/include/sys/_types/_s_ifmt.h",
"/usr/include/sys/_types/_seek_set.h",
"/usr/include/sys/_types/_sigaltstack.h",
"/usr/include/sys/_types/_sigset_t.h",
"/usr/include/sys/_types/_size_t.h",
"/usr/include/sys/_types/_ssize_t.h",
"/usr/include/sys/_types/_suseconds_t.h",
"/usr/include/sys/_types/_time_t.h",
"/usr/include/sys/_types/_timespec.h",
"/usr/include/sys/_types/_timeval.h",
"/usr/include/sys/_types/_ucontext.h",
"/usr/include/sys/_types/_uid_t.h",
"/usr/include/sys/_types/_uintptr_t.h",
"/usr/include/sys/_types/_useconds_t.h",
"/usr/include/sys/_types/_uuid_t.h",
"/usr/include/sys/_types/_va_list.h",
"/usr/include/sys/_types/_wchar_t.h",
"/usr/include/sys/_types/_wint_t.h",
"/usr/include/sys/appleapiopts.h",
"/usr/include/sys/cdefs.h",
"/usr/include/sys/errno.h",
"/usr/include/sys/fcntl.h",
"/usr/include/sys/resource.h",
"/usr/include/sys/select.h",
"/usr/include/sys/signal.h",
"/usr/include/sys/syslimits.h",
"/usr/include/sys/types.h",
"/usr/include/sys/unistd.h",
"/usr/include/sys/wait.h",
"/usr/include/time.h",
"/usr/include/unistd.h",
"/usr/include/wchar.h",
"/usr/include/wctype.h",
"/usr/include/xlocale.h",
"/usr/include/xlocale/__wctype.h",
"/usr/include/xlocale/_ctype.h",
"/usr/include/xlocale/_stdio.h",
"/usr/include/xlocale/_stdlib.h",
"/usr/include/xlocale/_string.h",
"/usr/include/xlocale/_time.h",
"/usr/include/xlocale/_wchar.h",
"/usr/include/xlocale/_wctype.h",
"libDict.cxx.h",
0
    };
    static const char* includePaths[] = {
"/Users/yixiongmeng/Software/root/include",
"/Users/yixiongmeng/UCLA_XenonChamber/exact/",
0
    };
    static const char* payloadCode = 
"\n"
"#ifndef G__VECTOR_HAS_CLASS_ITERATOR\n"
"  #define G__VECTOR_HAS_CLASS_ITERATOR\n"
"#endif\n"
"\n"
;
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("libDict",
        headers, allHeaders, includePaths, payloadCode,
        TriggerDictionaryInitialization_libDict_Impl, {});
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_libDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_libDict() {
  TriggerDictionaryInitialization_libDict_Impl();
}
