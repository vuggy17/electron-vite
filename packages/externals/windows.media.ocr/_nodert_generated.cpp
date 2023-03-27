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

namespace NodeRT { namespace Windows { namespace Media { namespace Ocr { 
  v8::Local<v8::Value> WrapOcrEngine(::Windows::Media::Ocr::OcrEngine^ wintRtInstance);
  ::Windows::Media::Ocr::OcrEngine^ UnwrapOcrEngine(Local<Value> value);
  
  v8::Local<v8::Value> WrapOcrLine(::Windows::Media::Ocr::OcrLine^ wintRtInstance);
  ::Windows::Media::Ocr::OcrLine^ UnwrapOcrLine(Local<Value> value);
  
  v8::Local<v8::Value> WrapOcrResult(::Windows::Media::Ocr::OcrResult^ wintRtInstance);
  ::Windows::Media::Ocr::OcrResult^ UnwrapOcrResult(Local<Value> value);
  
  v8::Local<v8::Value> WrapOcrWord(::Windows::Media::Ocr::OcrWord^ wintRtInstance);
  ::Windows::Media::Ocr::OcrWord^ UnwrapOcrWord(Local<Value> value);
  




  static bool IsRectJsObject(Local<Value> value) {
    if (!value->IsObject()) {
      return false;
    }

    Local<String> symbol;
    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();

    return true;
  }

  ::Windows::Foundation::Rect RectFromJsObject(Local<Value> value) {
    HandleScope scope;
    ::Windows::Foundation::Rect returnValue;

    if (!value->IsObject()) {
      Nan::ThrowError(Nan::TypeError(NodeRT::Utils::NewString(L"Unexpected type, expected an object")));
      return returnValue;
    }

    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();
    Local<String> symbol;

    return returnValue;
  }

  Local<Value> RectToJsObject(::Windows::Foundation::Rect value) {
    EscapableHandleScope scope;

    Local<Object> obj = Nan::New<Object>();


    return scope.Escape(obj);
  }

  class OcrEngine : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("OcrEngine").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);

        Local<Function> func;
        Local<FunctionTemplate> funcTemplate;


          
            Nan::SetPrototypeMethod(localRef, "recognizeAsync", RecognizeAsync);
          


          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("recognizerLanguage").ToLocalChecked(), RecognizerLanguageGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);

        Nan::SetMethod(constructor, "isLanguageSupported", IsLanguageSupported);
        Nan::SetMethod(constructor, "tryCreateFromLanguage", TryCreateFromLanguage);
        Nan::SetMethod(constructor, "tryCreateFromUserProfileLanguages", TryCreateFromUserProfileLanguages);
        Nan::SetAccessor(constructor, Nan::New<String>("availableRecognizerLanguages").ToLocalChecked(), AvailableRecognizerLanguagesGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("maxImageDimension").ToLocalChecked(), MaxImageDimensionGetter);


        Nan::Set(exports, Nan::New<String>("OcrEngine").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      OcrEngine(::Windows::Media::Ocr::OcrEngine^ instance) {
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

      ::Windows::Media::Ocr::OcrEngine^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Ocr::OcrEngine^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::Ocr::OcrEngine^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      OcrEngine *wrapperInstance = new OcrEngine(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Ocr::OcrEngine^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::Ocr::OcrEngine^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::Ocr::OcrEngine^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapOcrEngine(winRtInstance));
    }

    static void RecognizeAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Ocr::OcrEngine^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      OcrEngine *wrapper = OcrEngine::Unwrap<OcrEngine>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Media::Ocr::OcrResult^>^ op;


      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::SoftwareBitmap^>(info[0]))
      {
        try
        {
          ::Windows::Graphics::Imaging::SoftwareBitmap^ arg0 = dynamic_cast<::Windows::Graphics::Imaging::SoftwareBitmap^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          op = wrapper->_instance->RecognizeAsync(arg0);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }

      auto opTask = create_task(op);
      uv_async_t* asyncToken = NodeUtils::Async::GetAsyncToken(info[info.Length() -1].As<Function>());

      opTask.then( [asyncToken] (task<::Windows::Media::Ocr::OcrResult^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapOcrResult(result);
              if (tryCatch.HasCaught())
              {
                error = Nan::To<Object>(tryCatch.Exception()).ToLocalChecked();
              }
              else
              {
                error = Undefined();
              }
              if (arg1.IsEmpty()) arg1 = Undefined();
            }
            Local<Value> args[] = {error, arg1};


            invokeCallback(_countof(args), args);
          });
        } catch (Platform::Exception^ exception) {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {
            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }




    static void IsLanguageSupported(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Language^>(info[0]))
      {
        try
        {
          ::Windows::Globalization::Language^ arg0 = dynamic_cast<::Windows::Globalization::Language^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          bool result;
          result = ::Windows::Media::Ocr::OcrEngine::IsLanguageSupported(arg0);
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

    static void TryCreateFromLanguage(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Language^>(info[0]))
      {
        try
        {
          ::Windows::Globalization::Language^ arg0 = dynamic_cast<::Windows::Globalization::Language^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          ::Windows::Media::Ocr::OcrEngine^ result;
          result = ::Windows::Media::Ocr::OcrEngine::TryCreateFromLanguage(arg0);
          info.GetReturnValue().Set(WrapOcrEngine(result));
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

    static void TryCreateFromUserProfileLanguages(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Media::Ocr::OcrEngine^ result;
          result = ::Windows::Media::Ocr::OcrEngine::TryCreateFromUserProfileLanguages();
          info.GetReturnValue().Set(WrapOcrEngine(result));
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

    static void RecognizerLanguageGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Ocr::OcrEngine^>(info.This())) {
        return;
      }

      OcrEngine *wrapper = OcrEngine::Unwrap<OcrEngine>(info.This());

      try  {
        ::Windows::Globalization::Language^ result = wrapper->_instance->RecognizerLanguage;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Globalization", "Language", result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    static void AvailableRecognizerLanguagesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        ::Windows::Foundation::Collections::IVectorView<::Windows::Globalization::Language^>^ result = ::Windows::Media::Ocr::OcrEngine::AvailableRecognizerLanguages;
        info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::Globalization::Language^>::CreateVectorViewWrapper(result, 
            [](::Windows::Globalization::Language^ val) -> Local<Value> {
              return NodeRT::Utils::CreateExternalWinRTObject("Windows.Globalization", "Language", val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Globalization::Language^>(value);
            },
            [](Local<Value> value) -> ::Windows::Globalization::Language^ {
              return dynamic_cast<::Windows::Globalization::Language^>(NodeRT::Utils::GetObjectInstance(value));
            }
          ));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void MaxImageDimensionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        unsigned int result = ::Windows::Media::Ocr::OcrEngine::MaxImageDimension;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    private:
      ::Windows::Media::Ocr::OcrEngine^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapOcrEngine(::Windows::Media::Ocr::OcrEngine^ wintRtInstance);
      friend ::Windows::Media::Ocr::OcrEngine^ UnwrapOcrEngine(Local<Value> value);
  };

  Persistent<FunctionTemplate> OcrEngine::s_constructorTemplate;

  v8::Local<v8::Value> WrapOcrEngine(::Windows::Media::Ocr::OcrEngine^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(OcrEngine::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::Ocr::OcrEngine^ UnwrapOcrEngine(Local<Value> value) {
     return OcrEngine::Unwrap<OcrEngine>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitOcrEngine(Local<Object> exports) {
    OcrEngine::Init(exports);
  }

  class OcrLine : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("OcrLine").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("text").ToLocalChecked(), TextGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("words").ToLocalChecked(), WordsGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("OcrLine").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      OcrLine(::Windows::Media::Ocr::OcrLine^ instance) {
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

      ::Windows::Media::Ocr::OcrLine^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Ocr::OcrLine^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::Ocr::OcrLine^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      OcrLine *wrapperInstance = new OcrLine(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Ocr::OcrLine^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::Ocr::OcrLine^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::Ocr::OcrLine^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapOcrLine(winRtInstance));
    }





    static void TextGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Ocr::OcrLine^>(info.This())) {
        return;
      }

      OcrLine *wrapper = OcrLine::Unwrap<OcrLine>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Text;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void WordsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Ocr::OcrLine^>(info.This())) {
        return;
      }

      OcrLine *wrapper = OcrLine::Unwrap<OcrLine>(info.This());

      try  {
        ::Windows::Foundation::Collections::IVectorView<::Windows::Media::Ocr::OcrWord^>^ result = wrapper->_instance->Words;
        info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::Media::Ocr::OcrWord^>::CreateVectorViewWrapper(result, 
            [](::Windows::Media::Ocr::OcrWord^ val) -> Local<Value> {
              return WrapOcrWord(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Ocr::OcrWord^>(value);
            },
            [](Local<Value> value) -> ::Windows::Media::Ocr::OcrWord^ {
              return UnwrapOcrWord(value);
            }
          ));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Media::Ocr::OcrLine^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapOcrLine(::Windows::Media::Ocr::OcrLine^ wintRtInstance);
      friend ::Windows::Media::Ocr::OcrLine^ UnwrapOcrLine(Local<Value> value);
  };

  Persistent<FunctionTemplate> OcrLine::s_constructorTemplate;

  v8::Local<v8::Value> WrapOcrLine(::Windows::Media::Ocr::OcrLine^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(OcrLine::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::Ocr::OcrLine^ UnwrapOcrLine(Local<Value> value) {
     return OcrLine::Unwrap<OcrLine>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitOcrLine(Local<Object> exports) {
    OcrLine::Init(exports);
  }

  class OcrResult : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("OcrResult").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("lines").ToLocalChecked(), LinesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("text").ToLocalChecked(), TextGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("textAngle").ToLocalChecked(), TextAngleGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("OcrResult").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      OcrResult(::Windows::Media::Ocr::OcrResult^ instance) {
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

      ::Windows::Media::Ocr::OcrResult^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Ocr::OcrResult^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::Ocr::OcrResult^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      OcrResult *wrapperInstance = new OcrResult(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Ocr::OcrResult^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::Ocr::OcrResult^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::Ocr::OcrResult^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapOcrResult(winRtInstance));
    }





    static void LinesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Ocr::OcrResult^>(info.This())) {
        return;
      }

      OcrResult *wrapper = OcrResult::Unwrap<OcrResult>(info.This());

      try  {
        ::Windows::Foundation::Collections::IVectorView<::Windows::Media::Ocr::OcrLine^>^ result = wrapper->_instance->Lines;
        info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::Media::Ocr::OcrLine^>::CreateVectorViewWrapper(result, 
            [](::Windows::Media::Ocr::OcrLine^ val) -> Local<Value> {
              return WrapOcrLine(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Ocr::OcrLine^>(value);
            },
            [](Local<Value> value) -> ::Windows::Media::Ocr::OcrLine^ {
              return UnwrapOcrLine(value);
            }
          ));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void TextGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Ocr::OcrResult^>(info.This())) {
        return;
      }

      OcrResult *wrapper = OcrResult::Unwrap<OcrResult>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Text;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void TextAngleGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Ocr::OcrResult^>(info.This())) {
        return;
      }

      OcrResult *wrapper = OcrResult::Unwrap<OcrResult>(info.This());

      try  {
        ::Platform::IBox<double>^ result = wrapper->_instance->TextAngle;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(Nan::New<Number>(static_cast<double>(result->Value))) : Undefined());
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Media::Ocr::OcrResult^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapOcrResult(::Windows::Media::Ocr::OcrResult^ wintRtInstance);
      friend ::Windows::Media::Ocr::OcrResult^ UnwrapOcrResult(Local<Value> value);
  };

  Persistent<FunctionTemplate> OcrResult::s_constructorTemplate;

  v8::Local<v8::Value> WrapOcrResult(::Windows::Media::Ocr::OcrResult^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(OcrResult::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::Ocr::OcrResult^ UnwrapOcrResult(Local<Value> value) {
     return OcrResult::Unwrap<OcrResult>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitOcrResult(Local<Object> exports) {
    OcrResult::Init(exports);
  }

  class OcrWord : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("OcrWord").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("boundingRect").ToLocalChecked(), BoundingRectGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("text").ToLocalChecked(), TextGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("OcrWord").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      OcrWord(::Windows::Media::Ocr::OcrWord^ instance) {
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

      ::Windows::Media::Ocr::OcrWord^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Ocr::OcrWord^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::Ocr::OcrWord^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      OcrWord *wrapperInstance = new OcrWord(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Ocr::OcrWord^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::Ocr::OcrWord^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::Ocr::OcrWord^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapOcrWord(winRtInstance));
    }





    static void BoundingRectGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Ocr::OcrWord^>(info.This())) {
        return;
      }

      OcrWord *wrapper = OcrWord::Unwrap<OcrWord>(info.This());

      try  {
        ::Windows::Foundation::Rect result = wrapper->_instance->BoundingRect;
        info.GetReturnValue().Set(NodeRT::Utils::RectToJs(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void TextGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Ocr::OcrWord^>(info.This())) {
        return;
      }

      OcrWord *wrapper = OcrWord::Unwrap<OcrWord>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Text;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Media::Ocr::OcrWord^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapOcrWord(::Windows::Media::Ocr::OcrWord^ wintRtInstance);
      friend ::Windows::Media::Ocr::OcrWord^ UnwrapOcrWord(Local<Value> value);
  };

  Persistent<FunctionTemplate> OcrWord::s_constructorTemplate;

  v8::Local<v8::Value> WrapOcrWord(::Windows::Media::Ocr::OcrWord^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(OcrWord::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::Ocr::OcrWord^ UnwrapOcrWord(Local<Value> value) {
     return OcrWord::Unwrap<OcrWord>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitOcrWord(Local<Object> exports) {
    OcrWord::Init(exports);
  }


} } } } 

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

      NodeRT::Windows::Media::Ocr::InitOcrEngine(target);
      NodeRT::Windows::Media::Ocr::InitOcrLine(target);
      NodeRT::Windows::Media::Ocr::InitOcrResult(target);
      NodeRT::Windows::Media::Ocr::InitOcrWord(target);


  NodeRT::Utils::RegisterNameSpace("Windows.Media.Ocr", target);
}



NODE_MODULE(binding, init)
