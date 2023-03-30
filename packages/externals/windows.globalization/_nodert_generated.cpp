// Copyright (c) The NodeRT Contributors
// All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the ""License""); you may
// not use this file except in compliance with the License. You may obtain a
// copy of the License at http://www.apache.org/licenses/LICENSE-2.0
//
// THIS CODE IS PROVIDED ON AN  *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS
// OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY
// IMPLIED WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE,
// MERCHANTABLITY OR NON-INFRINGEMENT.
//
// See the Apache Version 2.0 License for specific language governing permissions
// and limitations under the License.

// TODO: Verify that this is is still needed..
#define NTDDI_VERSION 0x06010000

#include <v8.h>
#include "nan.h"
#include <string>
#include <ppltasks.h>
#include "CollectionsConverter.h"
#include "CollectionsWrap.h"
#include "node-async.h"
#include "NodeRtUtils.h"
#include "OpaqueWrapper.h"
#include "WrapperBase.h"

#using <Windows.WinMD>

// this undefs fixes the issues of compiling Windows.Data.Json, Windows.Storag.FileProperties, and Windows.Stroage.Search
// Some of the node header files brings windows definitions with the same names as some of the WinRT methods
#undef DocumentProperties
#undef GetObject
#undef CreateEvent
#undef FindText
#undef SendMessage

const char* REGISTRATION_TOKEN_MAP_PROPERTY_NAME = "__registrationTokenMap__";

using v8::Array;
using v8::String;
using v8::Value;
using v8::Boolean;
using v8::Integer;
using v8::FunctionTemplate;
using v8::Object;
using v8::Local;
using v8::Function;
using v8::Date;
using v8::Number;
using v8::PropertyAttribute;
using v8::Primitive;
using Nan::HandleScope;
using Nan::Persistent;
using Nan::Undefined;
using Nan::True;
using Nan::False;
using Nan::Null;
using Nan::MaybeLocal;
using Nan::EscapableHandleScope;
using Nan::HandleScope;
using Nan::TryCatch;
using namespace concurrency;

namespace NodeRT { namespace Windows { namespace Globalization { 
  v8::Local<v8::Value> WrapApplicationLanguages(::Windows::Globalization::ApplicationLanguages^ wintRtInstance);
  ::Windows::Globalization::ApplicationLanguages^ UnwrapApplicationLanguages(Local<Value> value);
  
  v8::Local<v8::Value> WrapCalendar(::Windows::Globalization::Calendar^ wintRtInstance);
  ::Windows::Globalization::Calendar^ UnwrapCalendar(Local<Value> value);
  
  v8::Local<v8::Value> WrapCalendarIdentifiers(::Windows::Globalization::CalendarIdentifiers^ wintRtInstance);
  ::Windows::Globalization::CalendarIdentifiers^ UnwrapCalendarIdentifiers(Local<Value> value);
  
  v8::Local<v8::Value> WrapClockIdentifiers(::Windows::Globalization::ClockIdentifiers^ wintRtInstance);
  ::Windows::Globalization::ClockIdentifiers^ UnwrapClockIdentifiers(Local<Value> value);
  
  v8::Local<v8::Value> WrapCurrencyAmount(::Windows::Globalization::CurrencyAmount^ wintRtInstance);
  ::Windows::Globalization::CurrencyAmount^ UnwrapCurrencyAmount(Local<Value> value);
  
  v8::Local<v8::Value> WrapCurrencyIdentifiers(::Windows::Globalization::CurrencyIdentifiers^ wintRtInstance);
  ::Windows::Globalization::CurrencyIdentifiers^ UnwrapCurrencyIdentifiers(Local<Value> value);
  
  v8::Local<v8::Value> WrapGeographicRegion(::Windows::Globalization::GeographicRegion^ wintRtInstance);
  ::Windows::Globalization::GeographicRegion^ UnwrapGeographicRegion(Local<Value> value);
  
  v8::Local<v8::Value> WrapJapanesePhoneme(::Windows::Globalization::JapanesePhoneme^ wintRtInstance);
  ::Windows::Globalization::JapanesePhoneme^ UnwrapJapanesePhoneme(Local<Value> value);
  
  v8::Local<v8::Value> WrapJapanesePhoneticAnalyzer(::Windows::Globalization::JapanesePhoneticAnalyzer^ wintRtInstance);
  ::Windows::Globalization::JapanesePhoneticAnalyzer^ UnwrapJapanesePhoneticAnalyzer(Local<Value> value);
  
  v8::Local<v8::Value> WrapLanguage(::Windows::Globalization::Language^ wintRtInstance);
  ::Windows::Globalization::Language^ UnwrapLanguage(Local<Value> value);
  
  v8::Local<v8::Value> WrapNumeralSystemIdentifiers(::Windows::Globalization::NumeralSystemIdentifiers^ wintRtInstance);
  ::Windows::Globalization::NumeralSystemIdentifiers^ UnwrapNumeralSystemIdentifiers(Local<Value> value);
  



  static void InitDayOfWeekEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("DayOfWeek").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("sunday").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Globalization::DayOfWeek::Sunday)));
    Nan::Set(enumObject, Nan::New<String>("monday").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Globalization::DayOfWeek::Monday)));
    Nan::Set(enumObject, Nan::New<String>("tuesday").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Globalization::DayOfWeek::Tuesday)));
    Nan::Set(enumObject, Nan::New<String>("wednesday").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Globalization::DayOfWeek::Wednesday)));
    Nan::Set(enumObject, Nan::New<String>("thursday").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Globalization::DayOfWeek::Thursday)));
    Nan::Set(enumObject, Nan::New<String>("friday").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Globalization::DayOfWeek::Friday)));
    Nan::Set(enumObject, Nan::New<String>("saturday").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Globalization::DayOfWeek::Saturday)));
  }

  static void InitLanguageLayoutDirectionEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("LanguageLayoutDirection").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("ltr").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Globalization::LanguageLayoutDirection::Ltr)));
    Nan::Set(enumObject, Nan::New<String>("rtl").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Globalization::LanguageLayoutDirection::Rtl)));
    Nan::Set(enumObject, Nan::New<String>("ttbLtr").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Globalization::LanguageLayoutDirection::TtbLtr)));
    Nan::Set(enumObject, Nan::New<String>("ttbRtl").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Globalization::LanguageLayoutDirection::TtbRtl)));
  }

  static bool IsGlobalizationJapanesePhoneticAnalyzerContractJsObject(Local<Value> value) {
    if (!value->IsObject()) {
      return false;
    }

    Local<String> symbol;
    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();

    return true;
  }

  ::Windows::Globalization::GlobalizationJapanesePhoneticAnalyzerContract GlobalizationJapanesePhoneticAnalyzerContractFromJsObject(Local<Value> value) {
    HandleScope scope;
    ::Windows::Globalization::GlobalizationJapanesePhoneticAnalyzerContract returnValue;

    if (!value->IsObject()) {
      Nan::ThrowError(Nan::TypeError(NodeRT::Utils::NewString(L"Unexpected type, expected an object")));
      return returnValue;
    }

    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();
    Local<String> symbol;

    return returnValue;
  }

  Local<Value> GlobalizationJapanesePhoneticAnalyzerContractToJsObject(::Windows::Globalization::GlobalizationJapanesePhoneticAnalyzerContract value) {
    EscapableHandleScope scope;

    Local<Object> obj = Nan::New<Object>();


    return scope.Escape(obj);
  }


  class ApplicationLanguages : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("ApplicationLanguages").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);






        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);

        Nan::SetMethod(constructor, "getLanguagesForUser", GetLanguagesForUser);
        Nan::SetAccessor(constructor, Nan::New<String>("primaryLanguageOverride").ToLocalChecked(), PrimaryLanguageOverrideGetter, PrimaryLanguageOverrideSetter);
        Nan::SetAccessor(constructor, Nan::New<String>("languages").ToLocalChecked(), LanguagesGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("manifestLanguages").ToLocalChecked(), ManifestLanguagesGetter);


        Nan::Set(exports, Nan::New<String>("ApplicationLanguages").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      ApplicationLanguages(::Windows::Globalization::ApplicationLanguages^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Globalization::ApplicationLanguages^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::ApplicationLanguages^>(info[0])) {
        try {
          winRtInstance = (::Windows::Globalization::ApplicationLanguages^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      ApplicationLanguages *wrapperInstance = new ApplicationLanguages(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::ApplicationLanguages^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Globalization::ApplicationLanguages^ winRtInstance;
      try {
        winRtInstance = (::Windows::Globalization::ApplicationLanguages^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapApplicationLanguages(winRtInstance));
    }





    static void GetLanguagesForUser(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::System::User^>(info[0]))
      {
        try
        {
          ::Windows::System::User^ arg0 = dynamic_cast<::Windows::System::User^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          ::Windows::Foundation::Collections::IVectorView<::Platform::String^>^ result;
          result = ::Windows::Globalization::ApplicationLanguages::GetLanguagesForUser(arg0);
          info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Platform::String^>::CreateVectorViewWrapper(result, 
            [](::Platform::String^ val) -> Local<Value> {
              return NodeRT::Utils::NewString(val->Data());
            },
            [](Local<Value> value) -> bool {
              return value->IsString();
            },
            [](Local<Value> value) -> ::Platform::String^ {
              return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));
            }
          ));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else  {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void PrimaryLanguageOverrideGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::ApplicationLanguages::PrimaryLanguageOverride;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void PrimaryLanguageOverrideSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsString()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      try {


        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));

        ::Windows::Globalization::ApplicationLanguages::PrimaryLanguageOverride = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      

    static void LanguagesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        ::Windows::Foundation::Collections::IVectorView<::Platform::String^>^ result = ::Windows::Globalization::ApplicationLanguages::Languages;
        info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Platform::String^>::CreateVectorViewWrapper(result, 
            [](::Platform::String^ val) -> Local<Value> {
              return NodeRT::Utils::NewString(val->Data());
            },
            [](Local<Value> value) -> bool {
              return value->IsString();
            },
            [](Local<Value> value) -> ::Platform::String^ {
              return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));
            }
          ));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void ManifestLanguagesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        ::Windows::Foundation::Collections::IVectorView<::Platform::String^>^ result = ::Windows::Globalization::ApplicationLanguages::ManifestLanguages;
        info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Platform::String^>::CreateVectorViewWrapper(result, 
            [](::Platform::String^ val) -> Local<Value> {
              return NodeRT::Utils::NewString(val->Data());
            },
            [](Local<Value> value) -> bool {
              return value->IsString();
            },
            [](Local<Value> value) -> ::Platform::String^ {
              return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));
            }
          ));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    private:
      ::Windows::Globalization::ApplicationLanguages^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapApplicationLanguages(::Windows::Globalization::ApplicationLanguages^ wintRtInstance);
      friend ::Windows::Globalization::ApplicationLanguages^ UnwrapApplicationLanguages(Local<Value> value);
  };

  Persistent<FunctionTemplate> ApplicationLanguages::s_constructorTemplate;

  v8::Local<v8::Value> WrapApplicationLanguages(::Windows::Globalization::ApplicationLanguages^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(ApplicationLanguages::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Globalization::ApplicationLanguages^ UnwrapApplicationLanguages(Local<Value> value) {
     return ApplicationLanguages::Unwrap<ApplicationLanguages>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitApplicationLanguages(Local<Object> exports) {
    ApplicationLanguages::Init(exports);
  }

  class Calendar : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("Calendar").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "changeTimeZone", ChangeTimeZone);
            Nan::SetPrototypeMethod(localRef, "timeZoneAsString", TimeZoneAsString);
            Nan::SetPrototypeMethod(localRef, "addDays", AddDays);
            Nan::SetPrototypeMethod(localRef, "dayAsString", DayAsString);
            Nan::SetPrototypeMethod(localRef, "dayAsPaddedString", DayAsPaddedString);
            Nan::SetPrototypeMethod(localRef, "dayOfWeekAsString", DayOfWeekAsString);
            Nan::SetPrototypeMethod(localRef, "dayOfWeekAsSoloString", DayOfWeekAsSoloString);
            Nan::SetPrototypeMethod(localRef, "addPeriods", AddPeriods);
            Nan::SetPrototypeMethod(localRef, "periodAsString", PeriodAsString);
            Nan::SetPrototypeMethod(localRef, "addHours", AddHours);
            Nan::SetPrototypeMethod(localRef, "hourAsString", HourAsString);
            Nan::SetPrototypeMethod(localRef, "hourAsPaddedString", HourAsPaddedString);
            Nan::SetPrototypeMethod(localRef, "addMinutes", AddMinutes);
            Nan::SetPrototypeMethod(localRef, "minuteAsString", MinuteAsString);
            Nan::SetPrototypeMethod(localRef, "minuteAsPaddedString", MinuteAsPaddedString);
            Nan::SetPrototypeMethod(localRef, "addSeconds", AddSeconds);
            Nan::SetPrototypeMethod(localRef, "secondAsString", SecondAsString);
            Nan::SetPrototypeMethod(localRef, "secondAsPaddedString", SecondAsPaddedString);
            Nan::SetPrototypeMethod(localRef, "addNanoseconds", AddNanoseconds);
            Nan::SetPrototypeMethod(localRef, "nanosecondAsString", NanosecondAsString);
            Nan::SetPrototypeMethod(localRef, "nanosecondAsPaddedString", NanosecondAsPaddedString);
            Nan::SetPrototypeMethod(localRef, "compare", Compare);
            Nan::SetPrototypeMethod(localRef, "compareDateTime", CompareDateTime);
            Nan::SetPrototypeMethod(localRef, "copyTo", CopyTo);
            Nan::SetPrototypeMethod(localRef, "getTimeZone", GetTimeZone);
            Nan::SetPrototypeMethod(localRef, "clone", Clone);
            Nan::SetPrototypeMethod(localRef, "setToMin", SetToMin);
            Nan::SetPrototypeMethod(localRef, "setToMax", SetToMax);
            Nan::SetPrototypeMethod(localRef, "getCalendarSystem", GetCalendarSystem);
            Nan::SetPrototypeMethod(localRef, "changeCalendarSystem", ChangeCalendarSystem);
            Nan::SetPrototypeMethod(localRef, "getClock", GetClock);
            Nan::SetPrototypeMethod(localRef, "changeClock", ChangeClock);
            Nan::SetPrototypeMethod(localRef, "getDateTime", GetDateTime);
            Nan::SetPrototypeMethod(localRef, "setDateTime", SetDateTime);
            Nan::SetPrototypeMethod(localRef, "setToNow", SetToNow);
            Nan::SetPrototypeMethod(localRef, "addEras", AddEras);
            Nan::SetPrototypeMethod(localRef, "eraAsString", EraAsString);
            Nan::SetPrototypeMethod(localRef, "addYears", AddYears);
            Nan::SetPrototypeMethod(localRef, "yearAsString", YearAsString);
            Nan::SetPrototypeMethod(localRef, "yearAsTruncatedString", YearAsTruncatedString);
            Nan::SetPrototypeMethod(localRef, "yearAsPaddedString", YearAsPaddedString);
            Nan::SetPrototypeMethod(localRef, "addMonths", AddMonths);
            Nan::SetPrototypeMethod(localRef, "monthAsString", MonthAsString);
            Nan::SetPrototypeMethod(localRef, "monthAsSoloString", MonthAsSoloString);
            Nan::SetPrototypeMethod(localRef, "monthAsNumericString", MonthAsNumericString);
            Nan::SetPrototypeMethod(localRef, "monthAsPaddedNumericString", MonthAsPaddedNumericString);
            Nan::SetPrototypeMethod(localRef, "addWeeks", AddWeeks);
          



          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("year").ToLocalChecked(), YearGetter, YearSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("second").ToLocalChecked(), SecondGetter, SecondSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("period").ToLocalChecked(), PeriodGetter, PeriodSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nanosecond").ToLocalChecked(), NanosecondGetter, NanosecondSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("month").ToLocalChecked(), MonthGetter, MonthSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("minute").ToLocalChecked(), MinuteGetter, MinuteSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("numeralSystem").ToLocalChecked(), NumeralSystemGetter, NumeralSystemSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("era").ToLocalChecked(), EraGetter, EraSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("hour").ToLocalChecked(), HourGetter, HourSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("day").ToLocalChecked(), DayGetter, DaySetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("firstSecondInThisMinute").ToLocalChecked(), FirstSecondInThisMinuteGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("firstYearInThisEra").ToLocalChecked(), FirstYearInThisEraGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isDaylightSavingTime").ToLocalChecked(), IsDaylightSavingTimeGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("languages").ToLocalChecked(), LanguagesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("lastDayInThisMonth").ToLocalChecked(), LastDayInThisMonthGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("lastEra").ToLocalChecked(), LastEraGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("lastHourInThisPeriod").ToLocalChecked(), LastHourInThisPeriodGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("lastMinuteInThisHour").ToLocalChecked(), LastMinuteInThisHourGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("lastMonthInThisYear").ToLocalChecked(), LastMonthInThisYearGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("lastSecondInThisMinute").ToLocalChecked(), LastSecondInThisMinuteGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("lastYearInThisEra").ToLocalChecked(), LastYearInThisEraGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("dayOfWeek").ToLocalChecked(), DayOfWeekGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("firstDayInThisMonth").ToLocalChecked(), FirstDayInThisMonthGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("lastPeriodInThisDay").ToLocalChecked(), LastPeriodInThisDayGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("firstEra").ToLocalChecked(), FirstEraGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("numberOfDaysInThisMonth").ToLocalChecked(), NumberOfDaysInThisMonthGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("numberOfEras").ToLocalChecked(), NumberOfErasGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("numberOfHoursInThisPeriod").ToLocalChecked(), NumberOfHoursInThisPeriodGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("numberOfMinutesInThisHour").ToLocalChecked(), NumberOfMinutesInThisHourGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("firstHourInThisPeriod").ToLocalChecked(), FirstHourInThisPeriodGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("numberOfMonthsInThisYear").ToLocalChecked(), NumberOfMonthsInThisYearGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("numberOfPeriodsInThisDay").ToLocalChecked(), NumberOfPeriodsInThisDayGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("numberOfSecondsInThisMinute").ToLocalChecked(), NumberOfSecondsInThisMinuteGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("numberOfYearsInThisEra").ToLocalChecked(), NumberOfYearsInThisEraGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("firstMinuteInThisHour").ToLocalChecked(), FirstMinuteInThisHourGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("resolvedLanguage").ToLocalChecked(), ResolvedLanguageGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("firstMonthInThisYear").ToLocalChecked(), FirstMonthInThisYearGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("firstPeriodInThisDay").ToLocalChecked(), FirstPeriodInThisDayGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("Calendar").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      Calendar(::Windows::Globalization::Calendar^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Globalization::Calendar^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info[0])) {
        try {
          winRtInstance = (::Windows::Globalization::Calendar^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 4
        && (NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(info[0]) || info[0]->IsArray())
        && info[1]->IsString()
        && info[2]->IsString()
        && info[3]->IsString())
      {
        try {
          ::Windows::Foundation::Collections::IIterable<::Platform::String^>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Windows::Foundation::Collections::IIterable<::Platform::String^>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtVector<::Platform::String^>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return (!NodeRT::Utils::IsWinRtWrapper(value));
                 },
                 [](Local<Value> value) -> ::Platform::String^ {
                   return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));
                 }
                );
              }
              else
              {
                return dynamic_cast<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[1])));
          Platform::String^ arg2 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[2])));
          Platform::String^ arg3 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[3])));
          
          winRtInstance = ref new ::Windows::Globalization::Calendar(arg0,arg1,arg2,arg3);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 1
        && (NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(info[0]) || info[0]->IsArray()))
      {
        try {
          ::Windows::Foundation::Collections::IIterable<::Platform::String^>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Windows::Foundation::Collections::IIterable<::Platform::String^>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtVector<::Platform::String^>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return (!NodeRT::Utils::IsWinRtWrapper(value));
                 },
                 [](Local<Value> value) -> ::Platform::String^ {
                   return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));
                 }
                );
              }
              else
              {
                return dynamic_cast<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          
          winRtInstance = ref new ::Windows::Globalization::Calendar(arg0);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && (NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(info[0]) || info[0]->IsArray())
        && info[1]->IsString()
        && info[2]->IsString())
      {
        try {
          ::Windows::Foundation::Collections::IIterable<::Platform::String^>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Windows::Foundation::Collections::IIterable<::Platform::String^>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtVector<::Platform::String^>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return (!NodeRT::Utils::IsWinRtWrapper(value));
                 },
                 [](Local<Value> value) -> ::Platform::String^ {
                   return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));
                 }
                );
              }
              else
              {
                return dynamic_cast<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[1])));
          Platform::String^ arg2 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[2])));
          
          winRtInstance = ref new ::Windows::Globalization::Calendar(arg0,arg1,arg2);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 0)
      {
        try {
          winRtInstance = ref new ::Windows::Globalization::Calendar();
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      Calendar *wrapperInstance = new Calendar(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Globalization::Calendar^ winRtInstance;
      try {
        winRtInstance = (::Windows::Globalization::Calendar^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapCalendar(winRtInstance));
    }


    static void ChangeTimeZone(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          wrapper->_instance->ChangeTimeZone(arg0);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void TimeZoneAsString(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          Platform::String^ result;
          result = wrapper->_instance->TimeZoneAsString();
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          int arg0 = static_cast<int>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          Platform::String^ result;
          result = wrapper->_instance->TimeZoneAsString(arg0);
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void AddDays(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          int arg0 = static_cast<int>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          wrapper->_instance->AddDays(arg0);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void DayAsString(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          Platform::String^ result;
          result = wrapper->_instance->DayAsString();
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void DayAsPaddedString(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          int arg0 = static_cast<int>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          Platform::String^ result;
          result = wrapper->_instance->DayAsPaddedString(arg0);
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void DayOfWeekAsString(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          Platform::String^ result;
          result = wrapper->_instance->DayOfWeekAsString();
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          int arg0 = static_cast<int>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          Platform::String^ result;
          result = wrapper->_instance->DayOfWeekAsString(arg0);
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void DayOfWeekAsSoloString(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          Platform::String^ result;
          result = wrapper->_instance->DayOfWeekAsSoloString();
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          int arg0 = static_cast<int>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          Platform::String^ result;
          result = wrapper->_instance->DayOfWeekAsSoloString(arg0);
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void AddPeriods(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          int arg0 = static_cast<int>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          wrapper->_instance->AddPeriods(arg0);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void PeriodAsString(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          Platform::String^ result;
          result = wrapper->_instance->PeriodAsString();
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          int arg0 = static_cast<int>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          Platform::String^ result;
          result = wrapper->_instance->PeriodAsString(arg0);
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void AddHours(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          int arg0 = static_cast<int>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          wrapper->_instance->AddHours(arg0);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void HourAsString(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          Platform::String^ result;
          result = wrapper->_instance->HourAsString();
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void HourAsPaddedString(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          int arg0 = static_cast<int>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          Platform::String^ result;
          result = wrapper->_instance->HourAsPaddedString(arg0);
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void AddMinutes(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          int arg0 = static_cast<int>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          wrapper->_instance->AddMinutes(arg0);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void MinuteAsString(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          Platform::String^ result;
          result = wrapper->_instance->MinuteAsString();
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void MinuteAsPaddedString(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          int arg0 = static_cast<int>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          Platform::String^ result;
          result = wrapper->_instance->MinuteAsPaddedString(arg0);
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void AddSeconds(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          int arg0 = static_cast<int>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          wrapper->_instance->AddSeconds(arg0);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SecondAsString(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          Platform::String^ result;
          result = wrapper->_instance->SecondAsString();
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SecondAsPaddedString(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          int arg0 = static_cast<int>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          Platform::String^ result;
          result = wrapper->_instance->SecondAsPaddedString(arg0);
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void AddNanoseconds(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          int arg0 = static_cast<int>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          wrapper->_instance->AddNanoseconds(arg0);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void NanosecondAsString(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          Platform::String^ result;
          result = wrapper->_instance->NanosecondAsString();
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void NanosecondAsPaddedString(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          int arg0 = static_cast<int>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          Platform::String^ result;
          result = wrapper->_instance->NanosecondAsPaddedString(arg0);
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void Compare(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info[0]))
      {
        try
        {
          ::Windows::Globalization::Calendar^ arg0 = UnwrapCalendar(info[0]);
          
          int result;
          result = wrapper->_instance->Compare(arg0);
          info.GetReturnValue().Set(Nan::New<Integer>(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void CompareDateTime(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      if (info.Length() == 1
        && info[0]->IsDate())
      {
        try
        {
          ::Windows::Foundation::DateTime arg0 = NodeRT::Utils::DateTimeFromJSDate(info[0]);
          
          int result;
          result = wrapper->_instance->CompareDateTime(arg0);
          info.GetReturnValue().Set(Nan::New<Integer>(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void CopyTo(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info[0]))
      {
        try
        {
          ::Windows::Globalization::Calendar^ arg0 = UnwrapCalendar(info[0]);
          
          wrapper->_instance->CopyTo(arg0);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetTimeZone(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          Platform::String^ result;
          result = wrapper->_instance->GetTimeZone();
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void Clone(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Globalization::Calendar^ result;
          result = wrapper->_instance->Clone();
          info.GetReturnValue().Set(WrapCalendar(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SetToMin(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->SetToMin();
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SetToMax(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->SetToMax();
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetCalendarSystem(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          Platform::String^ result;
          result = wrapper->_instance->GetCalendarSystem();
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void ChangeCalendarSystem(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          wrapper->_instance->ChangeCalendarSystem(arg0);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetClock(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          Platform::String^ result;
          result = wrapper->_instance->GetClock();
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void ChangeClock(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          wrapper->_instance->ChangeClock(arg0);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetDateTime(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::DateTime result;
          result = wrapper->_instance->GetDateTime();
          info.GetReturnValue().Set(NodeRT::Utils::DateTimeToJS(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SetDateTime(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      if (info.Length() == 1
        && info[0]->IsDate())
      {
        try
        {
          ::Windows::Foundation::DateTime arg0 = NodeRT::Utils::DateTimeFromJSDate(info[0]);
          
          wrapper->_instance->SetDateTime(arg0);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SetToNow(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->SetToNow();
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void AddEras(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          int arg0 = static_cast<int>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          wrapper->_instance->AddEras(arg0);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void EraAsString(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          Platform::String^ result;
          result = wrapper->_instance->EraAsString();
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          int arg0 = static_cast<int>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          Platform::String^ result;
          result = wrapper->_instance->EraAsString(arg0);
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void AddYears(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          int arg0 = static_cast<int>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          wrapper->_instance->AddYears(arg0);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void YearAsString(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          Platform::String^ result;
          result = wrapper->_instance->YearAsString();
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void YearAsTruncatedString(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          int arg0 = static_cast<int>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          Platform::String^ result;
          result = wrapper->_instance->YearAsTruncatedString(arg0);
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void YearAsPaddedString(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          int arg0 = static_cast<int>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          Platform::String^ result;
          result = wrapper->_instance->YearAsPaddedString(arg0);
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void AddMonths(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          int arg0 = static_cast<int>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          wrapper->_instance->AddMonths(arg0);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void MonthAsString(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          Platform::String^ result;
          result = wrapper->_instance->MonthAsString();
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          int arg0 = static_cast<int>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          Platform::String^ result;
          result = wrapper->_instance->MonthAsString(arg0);
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void MonthAsSoloString(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          Platform::String^ result;
          result = wrapper->_instance->MonthAsSoloString();
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          int arg0 = static_cast<int>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          Platform::String^ result;
          result = wrapper->_instance->MonthAsSoloString(arg0);
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void MonthAsNumericString(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          Platform::String^ result;
          result = wrapper->_instance->MonthAsNumericString();
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void MonthAsPaddedNumericString(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          int arg0 = static_cast<int>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          Platform::String^ result;
          result = wrapper->_instance->MonthAsPaddedNumericString(arg0);
          info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void AddWeeks(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          int arg0 = static_cast<int>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          wrapper->_instance->AddWeeks(arg0);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void YearGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      try  {
        int result = wrapper->_instance->Year;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void YearSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsInt32()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      try {

        int winRtValue = static_cast<int>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->Year = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void SecondGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      try  {
        int result = wrapper->_instance->Second;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void SecondSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsInt32()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      try {

        int winRtValue = static_cast<int>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->Second = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void PeriodGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      try  {
        int result = wrapper->_instance->Period;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PeriodSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsInt32()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      try {

        int winRtValue = static_cast<int>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->Period = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void NanosecondGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      try  {
        int result = wrapper->_instance->Nanosecond;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NanosecondSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsInt32()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      try {

        int winRtValue = static_cast<int>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->Nanosecond = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void MonthGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      try  {
        int result = wrapper->_instance->Month;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void MonthSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsInt32()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      try {

        int winRtValue = static_cast<int>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->Month = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void MinuteGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      try  {
        int result = wrapper->_instance->Minute;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void MinuteSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsInt32()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      try {

        int winRtValue = static_cast<int>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->Minute = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void NumeralSystemGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->NumeralSystem;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NumeralSystemSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsString()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      try {

        Platform::String^ winRtValue = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));

        wrapper->_instance->NumeralSystem = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void EraGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      try  {
        int result = wrapper->_instance->Era;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void EraSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsInt32()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      try {

        int winRtValue = static_cast<int>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->Era = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void HourGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      try  {
        int result = wrapper->_instance->Hour;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void HourSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsInt32()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      try {

        int winRtValue = static_cast<int>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->Hour = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void DayGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      try  {
        int result = wrapper->_instance->Day;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void DaySetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsInt32()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      try {

        int winRtValue = static_cast<int>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->Day = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void FirstSecondInThisMinuteGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      try  {
        int result = wrapper->_instance->FirstSecondInThisMinute;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void FirstYearInThisEraGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      try  {
        int result = wrapper->_instance->FirstYearInThisEra;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void IsDaylightSavingTimeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      try  {
        bool result = wrapper->_instance->IsDaylightSavingTime;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void LanguagesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      try  {
        ::Windows::Foundation::Collections::IVectorView<::Platform::String^>^ result = wrapper->_instance->Languages;
        info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Platform::String^>::CreateVectorViewWrapper(result, 
            [](::Platform::String^ val) -> Local<Value> {
              return NodeRT::Utils::NewString(val->Data());
            },
            [](Local<Value> value) -> bool {
              return value->IsString();
            },
            [](Local<Value> value) -> ::Platform::String^ {
              return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));
            }
          ));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void LastDayInThisMonthGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      try  {
        int result = wrapper->_instance->LastDayInThisMonth;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void LastEraGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      try  {
        int result = wrapper->_instance->LastEra;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void LastHourInThisPeriodGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      try  {
        int result = wrapper->_instance->LastHourInThisPeriod;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void LastMinuteInThisHourGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      try  {
        int result = wrapper->_instance->LastMinuteInThisHour;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void LastMonthInThisYearGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      try  {
        int result = wrapper->_instance->LastMonthInThisYear;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void LastSecondInThisMinuteGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      try  {
        int result = wrapper->_instance->LastSecondInThisMinute;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void LastYearInThisEraGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      try  {
        int result = wrapper->_instance->LastYearInThisEra;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void DayOfWeekGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      try  {
        ::Windows::Globalization::DayOfWeek result = wrapper->_instance->DayOfWeek;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void FirstDayInThisMonthGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      try  {
        int result = wrapper->_instance->FirstDayInThisMonth;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void LastPeriodInThisDayGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      try  {
        int result = wrapper->_instance->LastPeriodInThisDay;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void FirstEraGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      try  {
        int result = wrapper->_instance->FirstEra;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NumberOfDaysInThisMonthGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      try  {
        int result = wrapper->_instance->NumberOfDaysInThisMonth;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NumberOfErasGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      try  {
        int result = wrapper->_instance->NumberOfEras;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NumberOfHoursInThisPeriodGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      try  {
        int result = wrapper->_instance->NumberOfHoursInThisPeriod;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NumberOfMinutesInThisHourGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      try  {
        int result = wrapper->_instance->NumberOfMinutesInThisHour;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void FirstHourInThisPeriodGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      try  {
        int result = wrapper->_instance->FirstHourInThisPeriod;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NumberOfMonthsInThisYearGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      try  {
        int result = wrapper->_instance->NumberOfMonthsInThisYear;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NumberOfPeriodsInThisDayGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      try  {
        int result = wrapper->_instance->NumberOfPeriodsInThisDay;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NumberOfSecondsInThisMinuteGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      try  {
        int result = wrapper->_instance->NumberOfSecondsInThisMinute;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NumberOfYearsInThisEraGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      try  {
        int result = wrapper->_instance->NumberOfYearsInThisEra;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void FirstMinuteInThisHourGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      try  {
        int result = wrapper->_instance->FirstMinuteInThisHour;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ResolvedLanguageGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->ResolvedLanguage;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void FirstMonthInThisYearGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      try  {
        int result = wrapper->_instance->FirstMonthInThisYear;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void FirstPeriodInThisDayGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Calendar^>(info.This())) {
        return;
      }

      Calendar *wrapper = Calendar::Unwrap<Calendar>(info.This());

      try  {
        int result = wrapper->_instance->FirstPeriodInThisDay;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Globalization::Calendar^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapCalendar(::Windows::Globalization::Calendar^ wintRtInstance);
      friend ::Windows::Globalization::Calendar^ UnwrapCalendar(Local<Value> value);
  };

  Persistent<FunctionTemplate> Calendar::s_constructorTemplate;

  v8::Local<v8::Value> WrapCalendar(::Windows::Globalization::Calendar^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(Calendar::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Globalization::Calendar^ UnwrapCalendar(Local<Value> value) {
     return Calendar::Unwrap<Calendar>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitCalendar(Local<Object> exports) {
    Calendar::Init(exports);
  }

  class CalendarIdentifiers : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("CalendarIdentifiers").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);






        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);

        Nan::SetAccessor(constructor, Nan::New<String>("julian").ToLocalChecked(), JulianGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("gregorian").ToLocalChecked(), GregorianGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("hebrew").ToLocalChecked(), HebrewGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("hijri").ToLocalChecked(), HijriGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("japanese").ToLocalChecked(), JapaneseGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("korean").ToLocalChecked(), KoreanGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("taiwan").ToLocalChecked(), TaiwanGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("thai").ToLocalChecked(), ThaiGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("umAlQura").ToLocalChecked(), UmAlQuraGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("persian").ToLocalChecked(), PersianGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("chineseLunar").ToLocalChecked(), ChineseLunarGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("vietnameseLunar").ToLocalChecked(), VietnameseLunarGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("taiwanLunar").ToLocalChecked(), TaiwanLunarGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("koreanLunar").ToLocalChecked(), KoreanLunarGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("japaneseLunar").ToLocalChecked(), JapaneseLunarGetter);


        Nan::Set(exports, Nan::New<String>("CalendarIdentifiers").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      CalendarIdentifiers(::Windows::Globalization::CalendarIdentifiers^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Globalization::CalendarIdentifiers^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::CalendarIdentifiers^>(info[0])) {
        try {
          winRtInstance = (::Windows::Globalization::CalendarIdentifiers^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      CalendarIdentifiers *wrapperInstance = new CalendarIdentifiers(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::CalendarIdentifiers^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Globalization::CalendarIdentifiers^ winRtInstance;
      try {
        winRtInstance = (::Windows::Globalization::CalendarIdentifiers^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapCalendarIdentifiers(winRtInstance));
    }







    static void JulianGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CalendarIdentifiers::Julian;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void GregorianGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CalendarIdentifiers::Gregorian;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void HebrewGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CalendarIdentifiers::Hebrew;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void HijriGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CalendarIdentifiers::Hijri;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void JapaneseGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CalendarIdentifiers::Japanese;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void KoreanGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CalendarIdentifiers::Korean;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void TaiwanGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CalendarIdentifiers::Taiwan;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void ThaiGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CalendarIdentifiers::Thai;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void UmAlQuraGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CalendarIdentifiers::UmAlQura;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void PersianGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CalendarIdentifiers::Persian;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void ChineseLunarGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CalendarIdentifiers::ChineseLunar;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void VietnameseLunarGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CalendarIdentifiers::VietnameseLunar;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void TaiwanLunarGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CalendarIdentifiers::TaiwanLunar;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void KoreanLunarGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CalendarIdentifiers::KoreanLunar;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void JapaneseLunarGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CalendarIdentifiers::JapaneseLunar;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    private:
      ::Windows::Globalization::CalendarIdentifiers^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapCalendarIdentifiers(::Windows::Globalization::CalendarIdentifiers^ wintRtInstance);
      friend ::Windows::Globalization::CalendarIdentifiers^ UnwrapCalendarIdentifiers(Local<Value> value);
  };

  Persistent<FunctionTemplate> CalendarIdentifiers::s_constructorTemplate;

  v8::Local<v8::Value> WrapCalendarIdentifiers(::Windows::Globalization::CalendarIdentifiers^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(CalendarIdentifiers::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Globalization::CalendarIdentifiers^ UnwrapCalendarIdentifiers(Local<Value> value) {
     return CalendarIdentifiers::Unwrap<CalendarIdentifiers>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitCalendarIdentifiers(Local<Object> exports) {
    CalendarIdentifiers::Init(exports);
  }

  class ClockIdentifiers : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("ClockIdentifiers").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);






        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);

        Nan::SetAccessor(constructor, Nan::New<String>("twelveHour").ToLocalChecked(), TwelveHourGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("twentyFourHour").ToLocalChecked(), TwentyFourHourGetter);


        Nan::Set(exports, Nan::New<String>("ClockIdentifiers").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      ClockIdentifiers(::Windows::Globalization::ClockIdentifiers^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Globalization::ClockIdentifiers^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::ClockIdentifiers^>(info[0])) {
        try {
          winRtInstance = (::Windows::Globalization::ClockIdentifiers^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      ClockIdentifiers *wrapperInstance = new ClockIdentifiers(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::ClockIdentifiers^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Globalization::ClockIdentifiers^ winRtInstance;
      try {
        winRtInstance = (::Windows::Globalization::ClockIdentifiers^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapClockIdentifiers(winRtInstance));
    }







    static void TwelveHourGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::ClockIdentifiers::TwelveHour;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void TwentyFourHourGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::ClockIdentifiers::TwentyFourHour;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    private:
      ::Windows::Globalization::ClockIdentifiers^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapClockIdentifiers(::Windows::Globalization::ClockIdentifiers^ wintRtInstance);
      friend ::Windows::Globalization::ClockIdentifiers^ UnwrapClockIdentifiers(Local<Value> value);
  };

  Persistent<FunctionTemplate> ClockIdentifiers::s_constructorTemplate;

  v8::Local<v8::Value> WrapClockIdentifiers(::Windows::Globalization::ClockIdentifiers^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(ClockIdentifiers::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Globalization::ClockIdentifiers^ UnwrapClockIdentifiers(Local<Value> value) {
     return ClockIdentifiers::Unwrap<ClockIdentifiers>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitClockIdentifiers(Local<Object> exports) {
    ClockIdentifiers::Init(exports);
  }

  class CurrencyAmount : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("CurrencyAmount").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("amount").ToLocalChecked(), AmountGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("currency").ToLocalChecked(), CurrencyGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("CurrencyAmount").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      CurrencyAmount(::Windows::Globalization::CurrencyAmount^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Globalization::CurrencyAmount^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::CurrencyAmount^>(info[0])) {
        try {
          winRtInstance = (::Windows::Globalization::CurrencyAmount^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 2
        && info[0]->IsString()
        && info[1]->IsString())
      {
        try {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[1])));
          
          winRtInstance = ref new ::Windows::Globalization::CurrencyAmount(arg0,arg1);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      CurrencyAmount *wrapperInstance = new CurrencyAmount(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::CurrencyAmount^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Globalization::CurrencyAmount^ winRtInstance;
      try {
        winRtInstance = (::Windows::Globalization::CurrencyAmount^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapCurrencyAmount(winRtInstance));
    }





    static void AmountGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::CurrencyAmount^>(info.This())) {
        return;
      }

      CurrencyAmount *wrapper = CurrencyAmount::Unwrap<CurrencyAmount>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Amount;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void CurrencyGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::CurrencyAmount^>(info.This())) {
        return;
      }

      CurrencyAmount *wrapper = CurrencyAmount::Unwrap<CurrencyAmount>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Currency;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Globalization::CurrencyAmount^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapCurrencyAmount(::Windows::Globalization::CurrencyAmount^ wintRtInstance);
      friend ::Windows::Globalization::CurrencyAmount^ UnwrapCurrencyAmount(Local<Value> value);
  };

  Persistent<FunctionTemplate> CurrencyAmount::s_constructorTemplate;

  v8::Local<v8::Value> WrapCurrencyAmount(::Windows::Globalization::CurrencyAmount^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(CurrencyAmount::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Globalization::CurrencyAmount^ UnwrapCurrencyAmount(Local<Value> value) {
     return CurrencyAmount::Unwrap<CurrencyAmount>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitCurrencyAmount(Local<Object> exports) {
    CurrencyAmount::Init(exports);
  }

  class CurrencyIdentifiers : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("CurrencyIdentifiers").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);






        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);

        Nan::SetAccessor(constructor, Nan::New<String>("hNL").ToLocalChecked(), HNLGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("aED").ToLocalChecked(), AEDGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("aFN").ToLocalChecked(), AFNGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("aLL").ToLocalChecked(), ALLGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("aMD").ToLocalChecked(), AMDGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("aNG").ToLocalChecked(), ANGGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("aOA").ToLocalChecked(), AOAGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("aRS").ToLocalChecked(), ARSGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("aUD").ToLocalChecked(), AUDGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("aWG").ToLocalChecked(), AWGGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("aZN").ToLocalChecked(), AZNGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("bAM").ToLocalChecked(), BAMGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("bBD").ToLocalChecked(), BBDGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("bDT").ToLocalChecked(), BDTGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("bGN").ToLocalChecked(), BGNGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("bHD").ToLocalChecked(), BHDGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("bIF").ToLocalChecked(), BIFGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("bMD").ToLocalChecked(), BMDGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("bND").ToLocalChecked(), BNDGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("bOB").ToLocalChecked(), BOBGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("bRL").ToLocalChecked(), BRLGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("bSD").ToLocalChecked(), BSDGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("bTN").ToLocalChecked(), BTNGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("bWP").ToLocalChecked(), BWPGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("bYR").ToLocalChecked(), BYRGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("bZD").ToLocalChecked(), BZDGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("cAD").ToLocalChecked(), CADGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("cDF").ToLocalChecked(), CDFGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("cHF").ToLocalChecked(), CHFGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("cLP").ToLocalChecked(), CLPGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("cNY").ToLocalChecked(), CNYGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("cOP").ToLocalChecked(), COPGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("cRC").ToLocalChecked(), CRCGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("cUP").ToLocalChecked(), CUPGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("cVE").ToLocalChecked(), CVEGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("cZK").ToLocalChecked(), CZKGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("dJF").ToLocalChecked(), DJFGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("dKK").ToLocalChecked(), DKKGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("dOP").ToLocalChecked(), DOPGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("dZD").ToLocalChecked(), DZDGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("eGP").ToLocalChecked(), EGPGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("eRN").ToLocalChecked(), ERNGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("eTB").ToLocalChecked(), ETBGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("eUR").ToLocalChecked(), EURGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("fJD").ToLocalChecked(), FJDGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("fKP").ToLocalChecked(), FKPGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("gBP").ToLocalChecked(), GBPGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("gEL").ToLocalChecked(), GELGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("gHS").ToLocalChecked(), GHSGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("gIP").ToLocalChecked(), GIPGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("gMD").ToLocalChecked(), GMDGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("gNF").ToLocalChecked(), GNFGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("gTQ").ToLocalChecked(), GTQGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("gYD").ToLocalChecked(), GYDGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("hKD").ToLocalChecked(), HKDGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("rON").ToLocalChecked(), RONGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("hRK").ToLocalChecked(), HRKGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("hTG").ToLocalChecked(), HTGGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("hUF").ToLocalChecked(), HUFGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("iDR").ToLocalChecked(), IDRGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("iLS").ToLocalChecked(), ILSGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("iNR").ToLocalChecked(), INRGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("iQD").ToLocalChecked(), IQDGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("iRR").ToLocalChecked(), IRRGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("iSK").ToLocalChecked(), ISKGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("jMD").ToLocalChecked(), JMDGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("jOD").ToLocalChecked(), JODGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("jPY").ToLocalChecked(), JPYGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("kES").ToLocalChecked(), KESGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("kGS").ToLocalChecked(), KGSGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("kHR").ToLocalChecked(), KHRGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("kMF").ToLocalChecked(), KMFGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("kPW").ToLocalChecked(), KPWGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("kRW").ToLocalChecked(), KRWGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("kWD").ToLocalChecked(), KWDGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("kYD").ToLocalChecked(), KYDGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("kZT").ToLocalChecked(), KZTGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("lAK").ToLocalChecked(), LAKGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("lBP").ToLocalChecked(), LBPGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("lKR").ToLocalChecked(), LKRGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("lRD").ToLocalChecked(), LRDGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("lSL").ToLocalChecked(), LSLGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("lTL").ToLocalChecked(), LTLGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("lVL").ToLocalChecked(), LVLGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("lYD").ToLocalChecked(), LYDGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("mAD").ToLocalChecked(), MADGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("mDL").ToLocalChecked(), MDLGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("mGA").ToLocalChecked(), MGAGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("mKD").ToLocalChecked(), MKDGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("mMK").ToLocalChecked(), MMKGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("mNT").ToLocalChecked(), MNTGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("mOP").ToLocalChecked(), MOPGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("mRO").ToLocalChecked(), MROGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("mUR").ToLocalChecked(), MURGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("mVR").ToLocalChecked(), MVRGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("mWK").ToLocalChecked(), MWKGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("mXN").ToLocalChecked(), MXNGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("mYR").ToLocalChecked(), MYRGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("mZN").ToLocalChecked(), MZNGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("nAD").ToLocalChecked(), NADGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("nGN").ToLocalChecked(), NGNGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("nIO").ToLocalChecked(), NIOGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("nOK").ToLocalChecked(), NOKGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("nPR").ToLocalChecked(), NPRGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("nZD").ToLocalChecked(), NZDGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("oMR").ToLocalChecked(), OMRGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("pAB").ToLocalChecked(), PABGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("pEN").ToLocalChecked(), PENGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("pGK").ToLocalChecked(), PGKGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("pHP").ToLocalChecked(), PHPGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("pKR").ToLocalChecked(), PKRGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("pLN").ToLocalChecked(), PLNGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("pYG").ToLocalChecked(), PYGGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("qAR").ToLocalChecked(), QARGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("rSD").ToLocalChecked(), RSDGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("rUB").ToLocalChecked(), RUBGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("rWF").ToLocalChecked(), RWFGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("sAR").ToLocalChecked(), SARGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("sBD").ToLocalChecked(), SBDGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("sCR").ToLocalChecked(), SCRGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("sDG").ToLocalChecked(), SDGGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("sEK").ToLocalChecked(), SEKGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("sGD").ToLocalChecked(), SGDGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("sHP").ToLocalChecked(), SHPGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("sLL").ToLocalChecked(), SLLGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("sOS").ToLocalChecked(), SOSGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("sRD").ToLocalChecked(), SRDGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("sTD").ToLocalChecked(), STDGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("sYP").ToLocalChecked(), SYPGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("sZL").ToLocalChecked(), SZLGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("tHB").ToLocalChecked(), THBGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("tJS").ToLocalChecked(), TJSGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("tMT").ToLocalChecked(), TMTGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("tND").ToLocalChecked(), TNDGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("tOP").ToLocalChecked(), TOPGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("tRY").ToLocalChecked(), TRYGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("tTD").ToLocalChecked(), TTDGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("tWD").ToLocalChecked(), TWDGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("tZS").ToLocalChecked(), TZSGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("uAH").ToLocalChecked(), UAHGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("uGX").ToLocalChecked(), UGXGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("uSD").ToLocalChecked(), USDGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("uYU").ToLocalChecked(), UYUGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("uZS").ToLocalChecked(), UZSGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("vEF").ToLocalChecked(), VEFGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("vND").ToLocalChecked(), VNDGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("vUV").ToLocalChecked(), VUVGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("wST").ToLocalChecked(), WSTGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("xAF").ToLocalChecked(), XAFGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("xCD").ToLocalChecked(), XCDGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("xOF").ToLocalChecked(), XOFGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("xPF").ToLocalChecked(), XPFGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("xXX").ToLocalChecked(), XXXGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("yER").ToLocalChecked(), YERGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("zAR").ToLocalChecked(), ZARGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("zMW").ToLocalChecked(), ZMWGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("zWL").ToLocalChecked(), ZWLGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("bYN").ToLocalChecked(), BYNGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("sSP").ToLocalChecked(), SSPGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("sTN").ToLocalChecked(), STNGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("vES").ToLocalChecked(), VESGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("mRU").ToLocalChecked(), MRUGetter);


        Nan::Set(exports, Nan::New<String>("CurrencyIdentifiers").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      CurrencyIdentifiers(::Windows::Globalization::CurrencyIdentifiers^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Globalization::CurrencyIdentifiers^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::CurrencyIdentifiers^>(info[0])) {
        try {
          winRtInstance = (::Windows::Globalization::CurrencyIdentifiers^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      CurrencyIdentifiers *wrapperInstance = new CurrencyIdentifiers(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::CurrencyIdentifiers^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Globalization::CurrencyIdentifiers^ winRtInstance;
      try {
        winRtInstance = (::Windows::Globalization::CurrencyIdentifiers^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapCurrencyIdentifiers(winRtInstance));
    }







    static void HNLGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::HNL;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void AEDGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::AED;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void AFNGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::AFN;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void ALLGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::ALL;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void AMDGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::AMD;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void ANGGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::ANG;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void AOAGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::AOA;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void ARSGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::ARS;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void AUDGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::AUD;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void AWGGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::AWG;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void AZNGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::AZN;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void BAMGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::BAM;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void BBDGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::BBD;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void BDTGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::BDT;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void BGNGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::BGN;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void BHDGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::BHD;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void BIFGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::BIF;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void BMDGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::BMD;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void BNDGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::BND;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void BOBGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::BOB;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void BRLGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::BRL;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void BSDGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::BSD;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void BTNGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::BTN;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void BWPGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::BWP;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void BYRGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::BYR;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void BZDGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::BZD;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void CADGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::CAD;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void CDFGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::CDF;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void CHFGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::CHF;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void CLPGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::CLP;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void CNYGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::CNY;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void COPGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::COP;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void CRCGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::CRC;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void CUPGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::CUP;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void CVEGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::CVE;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void CZKGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::CZK;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void DJFGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::DJF;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void DKKGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::DKK;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void DOPGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::DOP;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void DZDGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::DZD;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void EGPGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::EGP;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void ERNGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::ERN;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void ETBGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::ETB;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void EURGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::EUR;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void FJDGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::FJD;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void FKPGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::FKP;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void GBPGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::GBP;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void GELGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::GEL;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void GHSGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::GHS;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void GIPGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::GIP;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void GMDGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::GMD;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void GNFGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::GNF;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void GTQGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::GTQ;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void GYDGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::GYD;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void HKDGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::HKD;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void RONGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::RON;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void HRKGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::HRK;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void HTGGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::HTG;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void HUFGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::HUF;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void IDRGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::IDR;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void ILSGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::ILS;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void INRGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::INR;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void IQDGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::IQD;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void IRRGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::IRR;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void ISKGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::ISK;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void JMDGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::JMD;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void JODGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::JOD;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void JPYGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::JPY;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void KESGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::KES;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void KGSGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::KGS;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void KHRGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::KHR;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void KMFGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::KMF;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void KPWGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::KPW;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void KRWGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::KRW;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void KWDGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::KWD;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void KYDGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::KYD;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void KZTGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::KZT;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void LAKGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::LAK;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void LBPGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::LBP;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void LKRGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::LKR;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void LRDGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::LRD;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void LSLGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::LSL;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void LTLGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::LTL;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void LVLGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::LVL;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void LYDGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::LYD;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void MADGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::MAD;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void MDLGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::MDL;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void MGAGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::MGA;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void MKDGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::MKD;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void MMKGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::MMK;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void MNTGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::MNT;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void MOPGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::MOP;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void MROGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::MRO;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void MURGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::MUR;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void MVRGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::MVR;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void MWKGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::MWK;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void MXNGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::MXN;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void MYRGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::MYR;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void MZNGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::MZN;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void NADGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::NAD;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void NGNGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::NGN;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void NIOGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::NIO;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void NOKGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::NOK;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void NPRGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::NPR;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void NZDGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::NZD;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void OMRGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::OMR;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void PABGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::PAB;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void PENGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::PEN;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void PGKGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::PGK;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void PHPGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::PHP;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void PKRGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::PKR;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void PLNGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::PLN;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void PYGGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::PYG;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void QARGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::QAR;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void RSDGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::RSD;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void RUBGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::RUB;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void RWFGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::RWF;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void SARGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::SAR;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void SBDGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::SBD;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void SCRGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::SCR;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void SDGGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::SDG;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void SEKGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::SEK;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void SGDGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::SGD;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void SHPGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::SHP;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void SLLGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::SLL;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void SOSGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::SOS;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void SRDGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::SRD;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void STDGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::STD;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void SYPGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::SYP;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void SZLGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::SZL;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void THBGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::THB;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void TJSGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::TJS;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void TMTGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::TMT;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void TNDGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::TND;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void TOPGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::TOP;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void TRYGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::TRY;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void TTDGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::TTD;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void TWDGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::TWD;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void TZSGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::TZS;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void UAHGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::UAH;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void UGXGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::UGX;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void USDGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::USD;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void UYUGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::UYU;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void UZSGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::UZS;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void VEFGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::VEF;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void VNDGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::VND;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void VUVGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::VUV;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void WSTGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::WST;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void XAFGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::XAF;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void XCDGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::XCD;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void XOFGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::XOF;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void XPFGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::XPF;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void XXXGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::XXX;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void YERGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::YER;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void ZARGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::ZAR;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void ZMWGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::ZMW;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void ZWLGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::ZWL;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void BYNGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::BYN;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void SSPGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::SSP;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void STNGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::STN;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void VESGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::VES;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void MRUGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::CurrencyIdentifiers::MRU;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    private:
      ::Windows::Globalization::CurrencyIdentifiers^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapCurrencyIdentifiers(::Windows::Globalization::CurrencyIdentifiers^ wintRtInstance);
      friend ::Windows::Globalization::CurrencyIdentifiers^ UnwrapCurrencyIdentifiers(Local<Value> value);
  };

  Persistent<FunctionTemplate> CurrencyIdentifiers::s_constructorTemplate;

  v8::Local<v8::Value> WrapCurrencyIdentifiers(::Windows::Globalization::CurrencyIdentifiers^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(CurrencyIdentifiers::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Globalization::CurrencyIdentifiers^ UnwrapCurrencyIdentifiers(Local<Value> value) {
     return CurrencyIdentifiers::Unwrap<CurrencyIdentifiers>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitCurrencyIdentifiers(Local<Object> exports) {
    CurrencyIdentifiers::Init(exports);
  }

  class GeographicRegion : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("GeographicRegion").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("code").ToLocalChecked(), CodeGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("codeThreeDigit").ToLocalChecked(), CodeThreeDigitGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("codeThreeLetter").ToLocalChecked(), CodeThreeLetterGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("codeTwoLetter").ToLocalChecked(), CodeTwoLetterGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("currenciesInUse").ToLocalChecked(), CurrenciesInUseGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("displayName").ToLocalChecked(), DisplayNameGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nativeName").ToLocalChecked(), NativeNameGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);

        Nan::SetMethod(constructor, "isSupported", IsSupported);


        Nan::Set(exports, Nan::New<String>("GeographicRegion").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      GeographicRegion(::Windows::Globalization::GeographicRegion^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Globalization::GeographicRegion^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::GeographicRegion^>(info[0])) {
        try {
          winRtInstance = (::Windows::Globalization::GeographicRegion^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 1
        && info[0]->IsString())
      {
        try {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          winRtInstance = ref new ::Windows::Globalization::GeographicRegion(arg0);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 0)
      {
        try {
          winRtInstance = ref new ::Windows::Globalization::GeographicRegion();
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      GeographicRegion *wrapperInstance = new GeographicRegion(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::GeographicRegion^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Globalization::GeographicRegion^ winRtInstance;
      try {
        winRtInstance = (::Windows::Globalization::GeographicRegion^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapGeographicRegion(winRtInstance));
    }





    static void IsSupported(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          bool result;
          result = ::Windows::Globalization::GeographicRegion::IsSupported(arg0);
          info.GetReturnValue().Set(Nan::New<Boolean>(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else  {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }

    static void CodeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::GeographicRegion^>(info.This())) {
        return;
      }

      GeographicRegion *wrapper = GeographicRegion::Unwrap<GeographicRegion>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Code;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void CodeThreeDigitGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::GeographicRegion^>(info.This())) {
        return;
      }

      GeographicRegion *wrapper = GeographicRegion::Unwrap<GeographicRegion>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->CodeThreeDigit;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void CodeThreeLetterGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::GeographicRegion^>(info.This())) {
        return;
      }

      GeographicRegion *wrapper = GeographicRegion::Unwrap<GeographicRegion>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->CodeThreeLetter;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void CodeTwoLetterGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::GeographicRegion^>(info.This())) {
        return;
      }

      GeographicRegion *wrapper = GeographicRegion::Unwrap<GeographicRegion>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->CodeTwoLetter;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void CurrenciesInUseGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::GeographicRegion^>(info.This())) {
        return;
      }

      GeographicRegion *wrapper = GeographicRegion::Unwrap<GeographicRegion>(info.This());

      try  {
        ::Windows::Foundation::Collections::IVectorView<::Platform::String^>^ result = wrapper->_instance->CurrenciesInUse;
        info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Platform::String^>::CreateVectorViewWrapper(result, 
            [](::Platform::String^ val) -> Local<Value> {
              return NodeRT::Utils::NewString(val->Data());
            },
            [](Local<Value> value) -> bool {
              return value->IsString();
            },
            [](Local<Value> value) -> ::Platform::String^ {
              return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));
            }
          ));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void DisplayNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::GeographicRegion^>(info.This())) {
        return;
      }

      GeographicRegion *wrapper = GeographicRegion::Unwrap<GeographicRegion>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->DisplayName;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NativeNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::GeographicRegion^>(info.This())) {
        return;
      }

      GeographicRegion *wrapper = GeographicRegion::Unwrap<GeographicRegion>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->NativeName;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Globalization::GeographicRegion^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapGeographicRegion(::Windows::Globalization::GeographicRegion^ wintRtInstance);
      friend ::Windows::Globalization::GeographicRegion^ UnwrapGeographicRegion(Local<Value> value);
  };

  Persistent<FunctionTemplate> GeographicRegion::s_constructorTemplate;

  v8::Local<v8::Value> WrapGeographicRegion(::Windows::Globalization::GeographicRegion^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(GeographicRegion::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Globalization::GeographicRegion^ UnwrapGeographicRegion(Local<Value> value) {
     return GeographicRegion::Unwrap<GeographicRegion>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitGeographicRegion(Local<Object> exports) {
    GeographicRegion::Init(exports);
  }

  class JapanesePhoneme : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("JapanesePhoneme").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("displayText").ToLocalChecked(), DisplayTextGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isPhraseStart").ToLocalChecked(), IsPhraseStartGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("yomiText").ToLocalChecked(), YomiTextGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("JapanesePhoneme").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      JapanesePhoneme(::Windows::Globalization::JapanesePhoneme^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Globalization::JapanesePhoneme^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::JapanesePhoneme^>(info[0])) {
        try {
          winRtInstance = (::Windows::Globalization::JapanesePhoneme^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      JapanesePhoneme *wrapperInstance = new JapanesePhoneme(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::JapanesePhoneme^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Globalization::JapanesePhoneme^ winRtInstance;
      try {
        winRtInstance = (::Windows::Globalization::JapanesePhoneme^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapJapanesePhoneme(winRtInstance));
    }





    static void DisplayTextGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::JapanesePhoneme^>(info.This())) {
        return;
      }

      JapanesePhoneme *wrapper = JapanesePhoneme::Unwrap<JapanesePhoneme>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->DisplayText;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void IsPhraseStartGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::JapanesePhoneme^>(info.This())) {
        return;
      }

      JapanesePhoneme *wrapper = JapanesePhoneme::Unwrap<JapanesePhoneme>(info.This());

      try  {
        bool result = wrapper->_instance->IsPhraseStart;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void YomiTextGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::JapanesePhoneme^>(info.This())) {
        return;
      }

      JapanesePhoneme *wrapper = JapanesePhoneme::Unwrap<JapanesePhoneme>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->YomiText;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Globalization::JapanesePhoneme^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapJapanesePhoneme(::Windows::Globalization::JapanesePhoneme^ wintRtInstance);
      friend ::Windows::Globalization::JapanesePhoneme^ UnwrapJapanesePhoneme(Local<Value> value);
  };

  Persistent<FunctionTemplate> JapanesePhoneme::s_constructorTemplate;

  v8::Local<v8::Value> WrapJapanesePhoneme(::Windows::Globalization::JapanesePhoneme^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(JapanesePhoneme::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Globalization::JapanesePhoneme^ UnwrapJapanesePhoneme(Local<Value> value) {
     return JapanesePhoneme::Unwrap<JapanesePhoneme>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitJapanesePhoneme(Local<Object> exports) {
    JapanesePhoneme::Init(exports);
  }

  class JapanesePhoneticAnalyzer : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("JapanesePhoneticAnalyzer").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);






        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);

        Nan::SetMethod(constructor, "getWords", GetWords);


        Nan::Set(exports, Nan::New<String>("JapanesePhoneticAnalyzer").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      JapanesePhoneticAnalyzer(::Windows::Globalization::JapanesePhoneticAnalyzer^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Globalization::JapanesePhoneticAnalyzer^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::JapanesePhoneticAnalyzer^>(info[0])) {
        try {
          winRtInstance = (::Windows::Globalization::JapanesePhoneticAnalyzer^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      JapanesePhoneticAnalyzer *wrapperInstance = new JapanesePhoneticAnalyzer(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::JapanesePhoneticAnalyzer^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Globalization::JapanesePhoneticAnalyzer^ winRtInstance;
      try {
        winRtInstance = (::Windows::Globalization::JapanesePhoneticAnalyzer^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapJapanesePhoneticAnalyzer(winRtInstance));
    }





    static void GetWords(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          ::Windows::Foundation::Collections::IVectorView<::Windows::Globalization::JapanesePhoneme^>^ result;
          result = ::Windows::Globalization::JapanesePhoneticAnalyzer::GetWords(arg0);
          info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::Globalization::JapanesePhoneme^>::CreateVectorViewWrapper(result, 
            [](::Windows::Globalization::JapanesePhoneme^ val) -> Local<Value> {
              return WrapJapanesePhoneme(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::JapanesePhoneme^>(value);
            },
            [](Local<Value> value) -> ::Windows::Globalization::JapanesePhoneme^ {
              return UnwrapJapanesePhoneme(value);
            }
          ));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 2
        && info[0]->IsString()
        && info[1]->IsBoolean())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          bool arg1 = Nan::To<bool>(info[1]).FromMaybe(false);
          
          ::Windows::Foundation::Collections::IVectorView<::Windows::Globalization::JapanesePhoneme^>^ result;
          result = ::Windows::Globalization::JapanesePhoneticAnalyzer::GetWords(arg0, arg1);
          info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::Globalization::JapanesePhoneme^>::CreateVectorViewWrapper(result, 
            [](::Windows::Globalization::JapanesePhoneme^ val) -> Local<Value> {
              return WrapJapanesePhoneme(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::JapanesePhoneme^>(value);
            },
            [](Local<Value> value) -> ::Windows::Globalization::JapanesePhoneme^ {
              return UnwrapJapanesePhoneme(value);
            }
          ));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else  {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    private:
      ::Windows::Globalization::JapanesePhoneticAnalyzer^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapJapanesePhoneticAnalyzer(::Windows::Globalization::JapanesePhoneticAnalyzer^ wintRtInstance);
      friend ::Windows::Globalization::JapanesePhoneticAnalyzer^ UnwrapJapanesePhoneticAnalyzer(Local<Value> value);
  };

  Persistent<FunctionTemplate> JapanesePhoneticAnalyzer::s_constructorTemplate;

  v8::Local<v8::Value> WrapJapanesePhoneticAnalyzer(::Windows::Globalization::JapanesePhoneticAnalyzer^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(JapanesePhoneticAnalyzer::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Globalization::JapanesePhoneticAnalyzer^ UnwrapJapanesePhoneticAnalyzer(Local<Value> value) {
     return JapanesePhoneticAnalyzer::Unwrap<JapanesePhoneticAnalyzer>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitJapanesePhoneticAnalyzer(Local<Object> exports) {
    JapanesePhoneticAnalyzer::Init(exports);
  }

  class Language : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("Language").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "getExtensionSubtags", GetExtensionSubtags);
          



          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("displayName").ToLocalChecked(), DisplayNameGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("languageTag").ToLocalChecked(), LanguageTagGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nativeName").ToLocalChecked(), NativeNameGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("script").ToLocalChecked(), ScriptGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("layoutDirection").ToLocalChecked(), LayoutDirectionGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("abbreviatedName").ToLocalChecked(), AbbreviatedNameGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);

        Nan::SetMethod(constructor, "getMuiCompatibleLanguageListFromLanguageTags", GetMuiCompatibleLanguageListFromLanguageTags);
        Nan::SetMethod(constructor, "trySetInputMethodLanguageTag", TrySetInputMethodLanguageTag);
        Nan::SetMethod(constructor, "isWellFormed", IsWellFormed);
        Nan::SetAccessor(constructor, Nan::New<String>("currentInputMethodLanguageTag").ToLocalChecked(), CurrentInputMethodLanguageTagGetter);


        Nan::Set(exports, Nan::New<String>("Language").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      Language(::Windows::Globalization::Language^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Globalization::Language^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Language^>(info[0])) {
        try {
          winRtInstance = (::Windows::Globalization::Language^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 1
        && info[0]->IsString())
      {
        try {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          winRtInstance = ref new ::Windows::Globalization::Language(arg0);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      Language *wrapperInstance = new Language(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Language^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Globalization::Language^ winRtInstance;
      try {
        winRtInstance = (::Windows::Globalization::Language^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapLanguage(winRtInstance));
    }


    static void GetExtensionSubtags(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Language^>(info.This())) {
        return;
      }

      Language *wrapper = Language::Unwrap<Language>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          ::Windows::Foundation::Collections::IVectorView<::Platform::String^>^ result;
          result = wrapper->_instance->GetExtensionSubtags(arg0);
          info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Platform::String^>::CreateVectorViewWrapper(result, 
            [](::Platform::String^ val) -> Local<Value> {
              return NodeRT::Utils::NewString(val->Data());
            },
            [](Local<Value> value) -> bool {
              return value->IsString();
            },
            [](Local<Value> value) -> ::Platform::String^ {
              return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));
            }
          ));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void GetMuiCompatibleLanguageListFromLanguageTags(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 1
        && (NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(info[0]) || info[0]->IsArray()))
      {
        try
        {
          ::Windows::Foundation::Collections::IIterable<::Platform::String^>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Windows::Foundation::Collections::IIterable<::Platform::String^>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtVector<::Platform::String^>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return (!NodeRT::Utils::IsWinRtWrapper(value));
                 },
                 [](Local<Value> value) -> ::Platform::String^ {
                   return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));
                 }
                );
              }
              else
              {
                return dynamic_cast<::Windows::Foundation::Collections::IIterable<::Platform::String^>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          
          ::Windows::Foundation::Collections::IVector<::Platform::String^>^ result;
          result = ::Windows::Globalization::Language::GetMuiCompatibleLanguageListFromLanguageTags(arg0);
          info.GetReturnValue().Set(NodeRT::Collections::VectorWrapper<::Platform::String^>::CreateVectorWrapper(result, 
            [](::Platform::String^ val) -> Local<Value> {
              return NodeRT::Utils::NewString(val->Data());
            },
            [](Local<Value> value) -> bool {
              return value->IsString();
            },
            [](Local<Value> value) -> ::Platform::String^ {
              return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));
            }
          ));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else  {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }

    static void TrySetInputMethodLanguageTag(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          bool result;
          result = ::Windows::Globalization::Language::TrySetInputMethodLanguageTag(arg0);
          info.GetReturnValue().Set(Nan::New<Boolean>(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else  {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }

    static void IsWellFormed(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          bool result;
          result = ::Windows::Globalization::Language::IsWellFormed(arg0);
          info.GetReturnValue().Set(Nan::New<Boolean>(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else  {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }

    static void DisplayNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Language^>(info.This())) {
        return;
      }

      Language *wrapper = Language::Unwrap<Language>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->DisplayName;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void LanguageTagGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Language^>(info.This())) {
        return;
      }

      Language *wrapper = Language::Unwrap<Language>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->LanguageTag;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NativeNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Language^>(info.This())) {
        return;
      }

      Language *wrapper = Language::Unwrap<Language>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->NativeName;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ScriptGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Language^>(info.This())) {
        return;
      }

      Language *wrapper = Language::Unwrap<Language>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Script;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void LayoutDirectionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Language^>(info.This())) {
        return;
      }

      Language *wrapper = Language::Unwrap<Language>(info.This());

      try  {
        ::Windows::Globalization::LanguageLayoutDirection result = wrapper->_instance->LayoutDirection;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void AbbreviatedNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Language^>(info.This())) {
        return;
      }

      Language *wrapper = Language::Unwrap<Language>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->AbbreviatedName;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    static void CurrentInputMethodLanguageTagGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::Language::CurrentInputMethodLanguageTag;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    private:
      ::Windows::Globalization::Language^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapLanguage(::Windows::Globalization::Language^ wintRtInstance);
      friend ::Windows::Globalization::Language^ UnwrapLanguage(Local<Value> value);
  };

  Persistent<FunctionTemplate> Language::s_constructorTemplate;

  v8::Local<v8::Value> WrapLanguage(::Windows::Globalization::Language^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(Language::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Globalization::Language^ UnwrapLanguage(Local<Value> value) {
     return Language::Unwrap<Language>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitLanguage(Local<Object> exports) {
    Language::Init(exports);
  }

  class NumeralSystemIdentifiers : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("NumeralSystemIdentifiers").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);






        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);

        Nan::SetAccessor(constructor, Nan::New<String>("fullWide").ToLocalChecked(), FullWideGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("arab").ToLocalChecked(), ArabGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("arabExt").ToLocalChecked(), ArabExtGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("bali").ToLocalChecked(), BaliGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("beng").ToLocalChecked(), BengGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("cham").ToLocalChecked(), ChamGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("deva").ToLocalChecked(), DevaGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("mymrShan").ToLocalChecked(), MymrShanGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("gujr").ToLocalChecked(), GujrGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("guru").ToLocalChecked(), GuruGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("haniDec").ToLocalChecked(), HaniDecGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("java").ToLocalChecked(), JavaGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("kali").ToLocalChecked(), KaliGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("khmr").ToLocalChecked(), KhmrGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("knda").ToLocalChecked(), KndaGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("lana").ToLocalChecked(), LanaGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("lanaTham").ToLocalChecked(), LanaThamGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("laoo").ToLocalChecked(), LaooGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("latn").ToLocalChecked(), LatnGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("lepc").ToLocalChecked(), LepcGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("limb").ToLocalChecked(), LimbGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("mlym").ToLocalChecked(), MlymGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("mong").ToLocalChecked(), MongGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("mtei").ToLocalChecked(), MteiGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("mymr").ToLocalChecked(), MymrGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("nkoo").ToLocalChecked(), NkooGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("olck").ToLocalChecked(), OlckGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("orya").ToLocalChecked(), OryaGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("saur").ToLocalChecked(), SaurGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("sund").ToLocalChecked(), SundGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("talu").ToLocalChecked(), TaluGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("tamlDec").ToLocalChecked(), TamlDecGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("telu").ToLocalChecked(), TeluGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("thai").ToLocalChecked(), ThaiGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("tibt").ToLocalChecked(), TibtGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("vaii").ToLocalChecked(), VaiiGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("mathBold").ToLocalChecked(), MathBoldGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("mathDbl").ToLocalChecked(), MathDblGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("mathMono").ToLocalChecked(), MathMonoGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("mathSanb").ToLocalChecked(), MathSanbGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("mathSans").ToLocalChecked(), MathSansGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("osma").ToLocalChecked(), OsmaGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("zmthBold").ToLocalChecked(), ZmthBoldGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("zmthDbl").ToLocalChecked(), ZmthDblGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("zmthMono").ToLocalChecked(), ZmthMonoGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("zmthSanb").ToLocalChecked(), ZmthSanbGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("zmthSans").ToLocalChecked(), ZmthSansGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("brah").ToLocalChecked(), BrahGetter);


        Nan::Set(exports, Nan::New<String>("NumeralSystemIdentifiers").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      NumeralSystemIdentifiers(::Windows::Globalization::NumeralSystemIdentifiers^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Globalization::NumeralSystemIdentifiers^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::NumeralSystemIdentifiers^>(info[0])) {
        try {
          winRtInstance = (::Windows::Globalization::NumeralSystemIdentifiers^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      NumeralSystemIdentifiers *wrapperInstance = new NumeralSystemIdentifiers(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::NumeralSystemIdentifiers^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Globalization::NumeralSystemIdentifiers^ winRtInstance;
      try {
        winRtInstance = (::Windows::Globalization::NumeralSystemIdentifiers^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapNumeralSystemIdentifiers(winRtInstance));
    }







    static void FullWideGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::NumeralSystemIdentifiers::FullWide;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void ArabGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::NumeralSystemIdentifiers::Arab;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void ArabExtGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::NumeralSystemIdentifiers::ArabExt;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void BaliGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::NumeralSystemIdentifiers::Bali;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void BengGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::NumeralSystemIdentifiers::Beng;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void ChamGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::NumeralSystemIdentifiers::Cham;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void DevaGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::NumeralSystemIdentifiers::Deva;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void MymrShanGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::NumeralSystemIdentifiers::MymrShan;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void GujrGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::NumeralSystemIdentifiers::Gujr;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void GuruGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::NumeralSystemIdentifiers::Guru;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void HaniDecGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::NumeralSystemIdentifiers::HaniDec;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void JavaGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::NumeralSystemIdentifiers::Java;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void KaliGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::NumeralSystemIdentifiers::Kali;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void KhmrGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::NumeralSystemIdentifiers::Khmr;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void KndaGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::NumeralSystemIdentifiers::Knda;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void LanaGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::NumeralSystemIdentifiers::Lana;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void LanaThamGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::NumeralSystemIdentifiers::LanaTham;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void LaooGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::NumeralSystemIdentifiers::Laoo;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void LatnGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::NumeralSystemIdentifiers::Latn;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void LepcGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::NumeralSystemIdentifiers::Lepc;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void LimbGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::NumeralSystemIdentifiers::Limb;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void MlymGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::NumeralSystemIdentifiers::Mlym;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void MongGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::NumeralSystemIdentifiers::Mong;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void MteiGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::NumeralSystemIdentifiers::Mtei;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void MymrGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::NumeralSystemIdentifiers::Mymr;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void NkooGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::NumeralSystemIdentifiers::Nkoo;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void OlckGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::NumeralSystemIdentifiers::Olck;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void OryaGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::NumeralSystemIdentifiers::Orya;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void SaurGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::NumeralSystemIdentifiers::Saur;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void SundGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::NumeralSystemIdentifiers::Sund;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void TaluGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::NumeralSystemIdentifiers::Talu;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void TamlDecGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::NumeralSystemIdentifiers::TamlDec;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void TeluGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::NumeralSystemIdentifiers::Telu;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void ThaiGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::NumeralSystemIdentifiers::Thai;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void TibtGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::NumeralSystemIdentifiers::Tibt;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void VaiiGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::NumeralSystemIdentifiers::Vaii;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void MathBoldGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::NumeralSystemIdentifiers::MathBold;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void MathDblGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::NumeralSystemIdentifiers::MathDbl;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void MathMonoGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::NumeralSystemIdentifiers::MathMono;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void MathSanbGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::NumeralSystemIdentifiers::MathSanb;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void MathSansGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::NumeralSystemIdentifiers::MathSans;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void OsmaGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::NumeralSystemIdentifiers::Osma;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void ZmthBoldGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::NumeralSystemIdentifiers::ZmthBold;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void ZmthDblGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::NumeralSystemIdentifiers::ZmthDbl;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void ZmthMonoGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::NumeralSystemIdentifiers::ZmthMono;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void ZmthSanbGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::NumeralSystemIdentifiers::ZmthSanb;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void ZmthSansGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::NumeralSystemIdentifiers::ZmthSans;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void BrahGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        Platform::String^ result = ::Windows::Globalization::NumeralSystemIdentifiers::Brah;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    private:
      ::Windows::Globalization::NumeralSystemIdentifiers^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapNumeralSystemIdentifiers(::Windows::Globalization::NumeralSystemIdentifiers^ wintRtInstance);
      friend ::Windows::Globalization::NumeralSystemIdentifiers^ UnwrapNumeralSystemIdentifiers(Local<Value> value);
  };

  Persistent<FunctionTemplate> NumeralSystemIdentifiers::s_constructorTemplate;

  v8::Local<v8::Value> WrapNumeralSystemIdentifiers(::Windows::Globalization::NumeralSystemIdentifiers^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(NumeralSystemIdentifiers::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Globalization::NumeralSystemIdentifiers^ UnwrapNumeralSystemIdentifiers(Local<Value> value) {
     return NumeralSystemIdentifiers::Unwrap<NumeralSystemIdentifiers>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitNumeralSystemIdentifiers(Local<Object> exports) {
    NumeralSystemIdentifiers::Init(exports);
  }


} } } 

NAN_MODULE_INIT(init) {
  // We ignore failures for now since it probably means that
  // the initialization already happened for STA, and that's cool

  CoInitializeEx(nullptr, COINIT_MULTITHREADED);

  /*
  if (FAILED(CoInitializeEx(nullptr, COINIT_MULTITHREADED))) {
    Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"error in CoInitializeEx()")));
    return;
  }
  */

      NodeRT::Windows::Globalization::InitDayOfWeekEnum(target);
      NodeRT::Windows::Globalization::InitLanguageLayoutDirectionEnum(target);
      NodeRT::Windows::Globalization::InitApplicationLanguages(target);
      NodeRT::Windows::Globalization::InitCalendar(target);
      NodeRT::Windows::Globalization::InitCalendarIdentifiers(target);
      NodeRT::Windows::Globalization::InitClockIdentifiers(target);
      NodeRT::Windows::Globalization::InitCurrencyAmount(target);
      NodeRT::Windows::Globalization::InitCurrencyIdentifiers(target);
      NodeRT::Windows::Globalization::InitGeographicRegion(target);
      NodeRT::Windows::Globalization::InitJapanesePhoneme(target);
      NodeRT::Windows::Globalization::InitJapanesePhoneticAnalyzer(target);
      NodeRT::Windows::Globalization::InitLanguage(target);
      NodeRT::Windows::Globalization::InitNumeralSystemIdentifiers(target);


  NodeRT::Utils::RegisterNameSpace("Windows.Globalization", target);
}



NODE_MODULE(binding, init)
