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

namespace NodeRT { namespace Windows { namespace Graphics { namespace Imaging { 
  v8::Local<v8::Value> WrapBitmapBuffer(::Windows::Graphics::Imaging::BitmapBuffer^ wintRtInstance);
  ::Windows::Graphics::Imaging::BitmapBuffer^ UnwrapBitmapBuffer(Local<Value> value);
  
  v8::Local<v8::Value> WrapBitmapCodecInformation(::Windows::Graphics::Imaging::BitmapCodecInformation^ wintRtInstance);
  ::Windows::Graphics::Imaging::BitmapCodecInformation^ UnwrapBitmapCodecInformation(Local<Value> value);
  
  v8::Local<v8::Value> WrapBitmapDecoder(::Windows::Graphics::Imaging::BitmapDecoder^ wintRtInstance);
  ::Windows::Graphics::Imaging::BitmapDecoder^ UnwrapBitmapDecoder(Local<Value> value);
  
  v8::Local<v8::Value> WrapBitmapEncoder(::Windows::Graphics::Imaging::BitmapEncoder^ wintRtInstance);
  ::Windows::Graphics::Imaging::BitmapEncoder^ UnwrapBitmapEncoder(Local<Value> value);
  
  v8::Local<v8::Value> WrapBitmapFrame(::Windows::Graphics::Imaging::BitmapFrame^ wintRtInstance);
  ::Windows::Graphics::Imaging::BitmapFrame^ UnwrapBitmapFrame(Local<Value> value);
  
  v8::Local<v8::Value> WrapBitmapProperties(::Windows::Graphics::Imaging::BitmapProperties^ wintRtInstance);
  ::Windows::Graphics::Imaging::BitmapProperties^ UnwrapBitmapProperties(Local<Value> value);
  
  v8::Local<v8::Value> WrapBitmapPropertiesView(::Windows::Graphics::Imaging::BitmapPropertiesView^ wintRtInstance);
  ::Windows::Graphics::Imaging::BitmapPropertiesView^ UnwrapBitmapPropertiesView(Local<Value> value);
  
  v8::Local<v8::Value> WrapBitmapPropertySet(::Windows::Graphics::Imaging::BitmapPropertySet^ wintRtInstance);
  ::Windows::Graphics::Imaging::BitmapPropertySet^ UnwrapBitmapPropertySet(Local<Value> value);
  
  v8::Local<v8::Value> WrapBitmapTransform(::Windows::Graphics::Imaging::BitmapTransform^ wintRtInstance);
  ::Windows::Graphics::Imaging::BitmapTransform^ UnwrapBitmapTransform(Local<Value> value);
  
  v8::Local<v8::Value> WrapBitmapTypedValue(::Windows::Graphics::Imaging::BitmapTypedValue^ wintRtInstance);
  ::Windows::Graphics::Imaging::BitmapTypedValue^ UnwrapBitmapTypedValue(Local<Value> value);
  
  v8::Local<v8::Value> WrapIBitmapFrame(::Windows::Graphics::Imaging::IBitmapFrame^ wintRtInstance);
  ::Windows::Graphics::Imaging::IBitmapFrame^ UnwrapIBitmapFrame(Local<Value> value);
  
  v8::Local<v8::Value> WrapIBitmapFrameWithSoftwareBitmap(::Windows::Graphics::Imaging::IBitmapFrameWithSoftwareBitmap^ wintRtInstance);
  ::Windows::Graphics::Imaging::IBitmapFrameWithSoftwareBitmap^ UnwrapIBitmapFrameWithSoftwareBitmap(Local<Value> value);
  
  v8::Local<v8::Value> WrapIBitmapPropertiesView(::Windows::Graphics::Imaging::IBitmapPropertiesView^ wintRtInstance);
  ::Windows::Graphics::Imaging::IBitmapPropertiesView^ UnwrapIBitmapPropertiesView(Local<Value> value);
  
  v8::Local<v8::Value> WrapImageStream(::Windows::Graphics::Imaging::ImageStream^ wintRtInstance);
  ::Windows::Graphics::Imaging::ImageStream^ UnwrapImageStream(Local<Value> value);
  
  v8::Local<v8::Value> WrapPixelDataProvider(::Windows::Graphics::Imaging::PixelDataProvider^ wintRtInstance);
  ::Windows::Graphics::Imaging::PixelDataProvider^ UnwrapPixelDataProvider(Local<Value> value);
  
  v8::Local<v8::Value> WrapSoftwareBitmap(::Windows::Graphics::Imaging::SoftwareBitmap^ wintRtInstance);
  ::Windows::Graphics::Imaging::SoftwareBitmap^ UnwrapSoftwareBitmap(Local<Value> value);
  



  static void InitBitmapAlphaModeEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("BitmapAlphaMode").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("premultiplied").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Graphics::Imaging::BitmapAlphaMode::Premultiplied)));
    Nan::Set(enumObject, Nan::New<String>("straight").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Graphics::Imaging::BitmapAlphaMode::Straight)));
    Nan::Set(enumObject, Nan::New<String>("ignore").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Graphics::Imaging::BitmapAlphaMode::Ignore)));
  }

  static void InitBitmapBufferAccessModeEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("BitmapBufferAccessMode").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("read").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Graphics::Imaging::BitmapBufferAccessMode::Read)));
    Nan::Set(enumObject, Nan::New<String>("readWrite").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Graphics::Imaging::BitmapBufferAccessMode::ReadWrite)));
    Nan::Set(enumObject, Nan::New<String>("write").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Graphics::Imaging::BitmapBufferAccessMode::Write)));
  }

  static void InitBitmapFlipEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("BitmapFlip").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("none").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Graphics::Imaging::BitmapFlip::None)));
    Nan::Set(enumObject, Nan::New<String>("horizontal").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Graphics::Imaging::BitmapFlip::Horizontal)));
    Nan::Set(enumObject, Nan::New<String>("vertical").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Graphics::Imaging::BitmapFlip::Vertical)));
  }

  static void InitBitmapInterpolationModeEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("BitmapInterpolationMode").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("nearestNeighbor").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Graphics::Imaging::BitmapInterpolationMode::NearestNeighbor)));
    Nan::Set(enumObject, Nan::New<String>("linear").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Graphics::Imaging::BitmapInterpolationMode::Linear)));
    Nan::Set(enumObject, Nan::New<String>("cubic").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Graphics::Imaging::BitmapInterpolationMode::Cubic)));
    Nan::Set(enumObject, Nan::New<String>("fant").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Graphics::Imaging::BitmapInterpolationMode::Fant)));
  }

  static void InitBitmapPixelFormatEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("BitmapPixelFormat").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("unknown").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Graphics::Imaging::BitmapPixelFormat::Unknown)));
    Nan::Set(enumObject, Nan::New<String>("rgba16").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Graphics::Imaging::BitmapPixelFormat::Rgba16)));
    Nan::Set(enumObject, Nan::New<String>("rgba8").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Graphics::Imaging::BitmapPixelFormat::Rgba8)));
    Nan::Set(enumObject, Nan::New<String>("gray16").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Graphics::Imaging::BitmapPixelFormat::Gray16)));
    Nan::Set(enumObject, Nan::New<String>("gray8").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Graphics::Imaging::BitmapPixelFormat::Gray8)));
    Nan::Set(enumObject, Nan::New<String>("bgra8").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Graphics::Imaging::BitmapPixelFormat::Bgra8)));
    Nan::Set(enumObject, Nan::New<String>("nv12").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Graphics::Imaging::BitmapPixelFormat::Nv12)));
    Nan::Set(enumObject, Nan::New<String>("p010").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Graphics::Imaging::BitmapPixelFormat::P010)));
    Nan::Set(enumObject, Nan::New<String>("yuy2").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Graphics::Imaging::BitmapPixelFormat::Yuy2)));
  }

  static void InitBitmapRotationEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("BitmapRotation").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("none").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Graphics::Imaging::BitmapRotation::None)));
    Nan::Set(enumObject, Nan::New<String>("clockwise90Degrees").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Graphics::Imaging::BitmapRotation::Clockwise90Degrees)));
    Nan::Set(enumObject, Nan::New<String>("clockwise180Degrees").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Graphics::Imaging::BitmapRotation::Clockwise180Degrees)));
    Nan::Set(enumObject, Nan::New<String>("clockwise270Degrees").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Graphics::Imaging::BitmapRotation::Clockwise270Degrees)));
  }

  static void InitColorManagementModeEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("ColorManagementMode").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("doNotColorManage").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Graphics::Imaging::ColorManagementMode::DoNotColorManage)));
    Nan::Set(enumObject, Nan::New<String>("colorManageToSRgb").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Graphics::Imaging::ColorManagementMode::ColorManageToSRgb)));
  }

  static void InitExifOrientationModeEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("ExifOrientationMode").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("ignoreExifOrientation").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Graphics::Imaging::ExifOrientationMode::IgnoreExifOrientation)));
    Nan::Set(enumObject, Nan::New<String>("respectExifOrientation").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Graphics::Imaging::ExifOrientationMode::RespectExifOrientation)));
  }

  static void InitJpegSubsamplingModeEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("JpegSubsamplingMode").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("default").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Graphics::Imaging::JpegSubsamplingMode::Default)));
    Nan::Set(enumObject, Nan::New<String>("y4Cb2Cr0").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Graphics::Imaging::JpegSubsamplingMode::Y4Cb2Cr0)));
    Nan::Set(enumObject, Nan::New<String>("y4Cb2Cr2").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Graphics::Imaging::JpegSubsamplingMode::Y4Cb2Cr2)));
    Nan::Set(enumObject, Nan::New<String>("y4Cb4Cr4").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Graphics::Imaging::JpegSubsamplingMode::Y4Cb4Cr4)));
  }

  static void InitPngFilterModeEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("PngFilterMode").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("automatic").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Graphics::Imaging::PngFilterMode::Automatic)));
    Nan::Set(enumObject, Nan::New<String>("none").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Graphics::Imaging::PngFilterMode::None)));
    Nan::Set(enumObject, Nan::New<String>("sub").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Graphics::Imaging::PngFilterMode::Sub)));
    Nan::Set(enumObject, Nan::New<String>("up").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Graphics::Imaging::PngFilterMode::Up)));
    Nan::Set(enumObject, Nan::New<String>("average").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Graphics::Imaging::PngFilterMode::Average)));
    Nan::Set(enumObject, Nan::New<String>("paeth").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Graphics::Imaging::PngFilterMode::Paeth)));
    Nan::Set(enumObject, Nan::New<String>("adaptive").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Graphics::Imaging::PngFilterMode::Adaptive)));
  }

  static void InitTiffCompressionModeEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("TiffCompressionMode").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("automatic").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Graphics::Imaging::TiffCompressionMode::Automatic)));
    Nan::Set(enumObject, Nan::New<String>("none").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Graphics::Imaging::TiffCompressionMode::None)));
    Nan::Set(enumObject, Nan::New<String>("ccitt3").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Graphics::Imaging::TiffCompressionMode::Ccitt3)));
    Nan::Set(enumObject, Nan::New<String>("ccitt4").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Graphics::Imaging::TiffCompressionMode::Ccitt4)));
    Nan::Set(enumObject, Nan::New<String>("lzw").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Graphics::Imaging::TiffCompressionMode::Lzw)));
    Nan::Set(enumObject, Nan::New<String>("rle").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Graphics::Imaging::TiffCompressionMode::Rle)));
    Nan::Set(enumObject, Nan::New<String>("zip").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Graphics::Imaging::TiffCompressionMode::Zip)));
    Nan::Set(enumObject, Nan::New<String>("lzwhDifferencing").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Graphics::Imaging::TiffCompressionMode::LzwhDifferencing)));
  }

  static bool IsBitmapBoundsJsObject(Local<Value> value) {
    if (!value->IsObject()) {
      return false;
    }

    Local<String> symbol;
    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();

    symbol = Nan::New<String>("x").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      if (!Nan::Get(obj,symbol).ToLocalChecked()->IsUint32()) {
        return false;
      }
    }
    
    symbol = Nan::New<String>("y").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      if (!Nan::Get(obj,symbol).ToLocalChecked()->IsUint32()) {
        return false;
      }
    }
    
    symbol = Nan::New<String>("width").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      if (!Nan::Get(obj,symbol).ToLocalChecked()->IsUint32()) {
        return false;
      }
    }
    
    symbol = Nan::New<String>("height").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      if (!Nan::Get(obj,symbol).ToLocalChecked()->IsUint32()) {
        return false;
      }
    }
    
    return true;
  }

  ::Windows::Graphics::Imaging::BitmapBounds BitmapBoundsFromJsObject(Local<Value> value) {
    HandleScope scope;
    ::Windows::Graphics::Imaging::BitmapBounds returnValue;

    if (!value->IsObject()) {
      Nan::ThrowError(Nan::TypeError(NodeRT::Utils::NewString(L"Unexpected type, expected an object")));
      return returnValue;
    }

    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();
    Local<String> symbol;

    symbol = Nan::New<String>("x").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      returnValue.X = static_cast<unsigned int>(Nan::To<uint32_t>(Nan::Get(obj,symbol).ToLocalChecked()).FromMaybe(0));
    }
    
    symbol = Nan::New<String>("y").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      returnValue.Y = static_cast<unsigned int>(Nan::To<uint32_t>(Nan::Get(obj,symbol).ToLocalChecked()).FromMaybe(0));
    }
    
    symbol = Nan::New<String>("width").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      returnValue.Width = static_cast<unsigned int>(Nan::To<uint32_t>(Nan::Get(obj,symbol).ToLocalChecked()).FromMaybe(0));
    }
    
    symbol = Nan::New<String>("height").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      returnValue.Height = static_cast<unsigned int>(Nan::To<uint32_t>(Nan::Get(obj,symbol).ToLocalChecked()).FromMaybe(0));
    }
    
    return returnValue;
  }

  Local<Value> BitmapBoundsToJsObject(::Windows::Graphics::Imaging::BitmapBounds value) {
    EscapableHandleScope scope;

    Local<Object> obj = Nan::New<Object>();

    Nan::Set(obj, Nan::New<String>("x").ToLocalChecked(), Nan::New<Integer>(value.X));
    Nan::Set(obj, Nan::New<String>("y").ToLocalChecked(), Nan::New<Integer>(value.Y));
    Nan::Set(obj, Nan::New<String>("width").ToLocalChecked(), Nan::New<Integer>(value.Width));
    Nan::Set(obj, Nan::New<String>("height").ToLocalChecked(), Nan::New<Integer>(value.Height));

    return scope.Escape(obj);
  }
  static bool IsBitmapPlaneDescriptionJsObject(Local<Value> value) {
    if (!value->IsObject()) {
      return false;
    }

    Local<String> symbol;
    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();

    symbol = Nan::New<String>("startIndex").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      if (!Nan::Get(obj,symbol).ToLocalChecked()->IsInt32()) {
        return false;
      }
    }
    
    symbol = Nan::New<String>("width").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      if (!Nan::Get(obj,symbol).ToLocalChecked()->IsInt32()) {
        return false;
      }
    }
    
    symbol = Nan::New<String>("height").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      if (!Nan::Get(obj,symbol).ToLocalChecked()->IsInt32()) {
        return false;
      }
    }
    
    symbol = Nan::New<String>("stride").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      if (!Nan::Get(obj,symbol).ToLocalChecked()->IsInt32()) {
        return false;
      }
    }
    
    return true;
  }

  ::Windows::Graphics::Imaging::BitmapPlaneDescription BitmapPlaneDescriptionFromJsObject(Local<Value> value) {
    HandleScope scope;
    ::Windows::Graphics::Imaging::BitmapPlaneDescription returnValue;

    if (!value->IsObject()) {
      Nan::ThrowError(Nan::TypeError(NodeRT::Utils::NewString(L"Unexpected type, expected an object")));
      return returnValue;
    }

    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();
    Local<String> symbol;

    symbol = Nan::New<String>("startIndex").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      returnValue.StartIndex = static_cast<int>(Nan::To<int32_t>(Nan::Get(obj,symbol).ToLocalChecked()).FromMaybe(0));
    }
    
    symbol = Nan::New<String>("width").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      returnValue.Width = static_cast<int>(Nan::To<int32_t>(Nan::Get(obj,symbol).ToLocalChecked()).FromMaybe(0));
    }
    
    symbol = Nan::New<String>("height").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      returnValue.Height = static_cast<int>(Nan::To<int32_t>(Nan::Get(obj,symbol).ToLocalChecked()).FromMaybe(0));
    }
    
    symbol = Nan::New<String>("stride").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      returnValue.Stride = static_cast<int>(Nan::To<int32_t>(Nan::Get(obj,symbol).ToLocalChecked()).FromMaybe(0));
    }
    
    return returnValue;
  }

  Local<Value> BitmapPlaneDescriptionToJsObject(::Windows::Graphics::Imaging::BitmapPlaneDescription value) {
    EscapableHandleScope scope;

    Local<Object> obj = Nan::New<Object>();

    Nan::Set(obj, Nan::New<String>("startIndex").ToLocalChecked(), Nan::New<Integer>(value.StartIndex));
    Nan::Set(obj, Nan::New<String>("width").ToLocalChecked(), Nan::New<Integer>(value.Width));
    Nan::Set(obj, Nan::New<String>("height").ToLocalChecked(), Nan::New<Integer>(value.Height));
    Nan::Set(obj, Nan::New<String>("stride").ToLocalChecked(), Nan::New<Integer>(value.Stride));

    return scope.Escape(obj);
  }
  static bool IsBitmapSizeJsObject(Local<Value> value) {
    if (!value->IsObject()) {
      return false;
    }

    Local<String> symbol;
    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();

    symbol = Nan::New<String>("width").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      if (!Nan::Get(obj,symbol).ToLocalChecked()->IsUint32()) {
        return false;
      }
    }
    
    symbol = Nan::New<String>("height").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      if (!Nan::Get(obj,symbol).ToLocalChecked()->IsUint32()) {
        return false;
      }
    }
    
    return true;
  }

  ::Windows::Graphics::Imaging::BitmapSize BitmapSizeFromJsObject(Local<Value> value) {
    HandleScope scope;
    ::Windows::Graphics::Imaging::BitmapSize returnValue;

    if (!value->IsObject()) {
      Nan::ThrowError(Nan::TypeError(NodeRT::Utils::NewString(L"Unexpected type, expected an object")));
      return returnValue;
    }

    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();
    Local<String> symbol;

    symbol = Nan::New<String>("width").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      returnValue.Width = static_cast<unsigned int>(Nan::To<uint32_t>(Nan::Get(obj,symbol).ToLocalChecked()).FromMaybe(0));
    }
    
    symbol = Nan::New<String>("height").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      returnValue.Height = static_cast<unsigned int>(Nan::To<uint32_t>(Nan::Get(obj,symbol).ToLocalChecked()).FromMaybe(0));
    }
    
    return returnValue;
  }

  Local<Value> BitmapSizeToJsObject(::Windows::Graphics::Imaging::BitmapSize value) {
    EscapableHandleScope scope;

    Local<Object> obj = Nan::New<Object>();

    Nan::Set(obj, Nan::New<String>("width").ToLocalChecked(), Nan::New<Integer>(value.Width));
    Nan::Set(obj, Nan::New<String>("height").ToLocalChecked(), Nan::New<Integer>(value.Height));

    return scope.Escape(obj);
  }


  class BitmapBuffer : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("BitmapBuffer").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "getPlaneCount", GetPlaneCount);
            Nan::SetPrototypeMethod(localRef, "getPlaneDescription", GetPlaneDescription);
            Nan::SetPrototypeMethod(localRef, "createReference", CreateReference);
            Nan::SetPrototypeMethod(localRef, "close", Close);
          




        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("BitmapBuffer").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      BitmapBuffer(::Windows::Graphics::Imaging::BitmapBuffer^ instance) {
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

      ::Windows::Graphics::Imaging::BitmapBuffer^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapBuffer^>(info[0])) {
        try {
          winRtInstance = (::Windows::Graphics::Imaging::BitmapBuffer^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      BitmapBuffer *wrapperInstance = new BitmapBuffer(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapBuffer^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Graphics::Imaging::BitmapBuffer^ winRtInstance;
      try {
        winRtInstance = (::Windows::Graphics::Imaging::BitmapBuffer^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapBitmapBuffer(winRtInstance));
    }


    static void GetPlaneCount(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapBuffer^>(info.This())) {
        return;
      }

      BitmapBuffer *wrapper = BitmapBuffer::Unwrap<BitmapBuffer>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          int result;
          result = wrapper->_instance->GetPlaneCount();
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
    static void GetPlaneDescription(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapBuffer^>(info.This())) {
        return;
      }

      BitmapBuffer *wrapper = BitmapBuffer::Unwrap<BitmapBuffer>(info.This());

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          int arg0 = static_cast<int>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          ::Windows::Graphics::Imaging::BitmapPlaneDescription result;
          result = wrapper->_instance->GetPlaneDescription(arg0);
          info.GetReturnValue().Set(BitmapPlaneDescriptionToJsObject(result));
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
    static void CreateReference(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapBuffer^>(info.This())) {
        return;
      }

      BitmapBuffer *wrapper = BitmapBuffer::Unwrap<BitmapBuffer>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::IMemoryBufferReference^ result;
          result = wrapper->_instance->CreateReference();
          info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation", "IMemoryBufferReference", result));
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

    static void Close(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapBuffer^>(info.This())) {
        return;
      }

      BitmapBuffer *wrapper = BitmapBuffer::Unwrap<BitmapBuffer>(info.This());

      if (info.Length() == 0) {
        try {
          delete wrapper->_instance;
          wrapper->_instance = nullptr;
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      } else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }





    private:
      ::Windows::Graphics::Imaging::BitmapBuffer^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapBitmapBuffer(::Windows::Graphics::Imaging::BitmapBuffer^ wintRtInstance);
      friend ::Windows::Graphics::Imaging::BitmapBuffer^ UnwrapBitmapBuffer(Local<Value> value);
  };

  Persistent<FunctionTemplate> BitmapBuffer::s_constructorTemplate;

  v8::Local<v8::Value> WrapBitmapBuffer(::Windows::Graphics::Imaging::BitmapBuffer^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(BitmapBuffer::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Graphics::Imaging::BitmapBuffer^ UnwrapBitmapBuffer(Local<Value> value) {
     return BitmapBuffer::Unwrap<BitmapBuffer>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitBitmapBuffer(Local<Object> exports) {
    BitmapBuffer::Init(exports);
  }

  class BitmapCodecInformation : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("BitmapCodecInformation").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("codecId").ToLocalChecked(), CodecIdGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("fileExtensions").ToLocalChecked(), FileExtensionsGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("friendlyName").ToLocalChecked(), FriendlyNameGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("mimeTypes").ToLocalChecked(), MimeTypesGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("BitmapCodecInformation").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      BitmapCodecInformation(::Windows::Graphics::Imaging::BitmapCodecInformation^ instance) {
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

      ::Windows::Graphics::Imaging::BitmapCodecInformation^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapCodecInformation^>(info[0])) {
        try {
          winRtInstance = (::Windows::Graphics::Imaging::BitmapCodecInformation^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      BitmapCodecInformation *wrapperInstance = new BitmapCodecInformation(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapCodecInformation^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Graphics::Imaging::BitmapCodecInformation^ winRtInstance;
      try {
        winRtInstance = (::Windows::Graphics::Imaging::BitmapCodecInformation^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapBitmapCodecInformation(winRtInstance));
    }





    static void CodecIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapCodecInformation^>(info.This())) {
        return;
      }

      BitmapCodecInformation *wrapper = BitmapCodecInformation::Unwrap<BitmapCodecInformation>(info.This());

      try  {
        ::Platform::Guid result = wrapper->_instance->CodecId;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void FileExtensionsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapCodecInformation^>(info.This())) {
        return;
      }

      BitmapCodecInformation *wrapper = BitmapCodecInformation::Unwrap<BitmapCodecInformation>(info.This());

      try  {
        ::Windows::Foundation::Collections::IVectorView<::Platform::String^>^ result = wrapper->_instance->FileExtensions;
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
      
    static void FriendlyNameGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapCodecInformation^>(info.This())) {
        return;
      }

      BitmapCodecInformation *wrapper = BitmapCodecInformation::Unwrap<BitmapCodecInformation>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->FriendlyName;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void MimeTypesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapCodecInformation^>(info.This())) {
        return;
      }

      BitmapCodecInformation *wrapper = BitmapCodecInformation::Unwrap<BitmapCodecInformation>(info.This());

      try  {
        ::Windows::Foundation::Collections::IVectorView<::Platform::String^>^ result = wrapper->_instance->MimeTypes;
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
      ::Windows::Graphics::Imaging::BitmapCodecInformation^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapBitmapCodecInformation(::Windows::Graphics::Imaging::BitmapCodecInformation^ wintRtInstance);
      friend ::Windows::Graphics::Imaging::BitmapCodecInformation^ UnwrapBitmapCodecInformation(Local<Value> value);
  };

  Persistent<FunctionTemplate> BitmapCodecInformation::s_constructorTemplate;

  v8::Local<v8::Value> WrapBitmapCodecInformation(::Windows::Graphics::Imaging::BitmapCodecInformation^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(BitmapCodecInformation::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Graphics::Imaging::BitmapCodecInformation^ UnwrapBitmapCodecInformation(Local<Value> value) {
     return BitmapCodecInformation::Unwrap<BitmapCodecInformation>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitBitmapCodecInformation(Local<Object> exports) {
    BitmapCodecInformation::Init(exports);
  }

  class BitmapDecoder : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("BitmapDecoder").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);

        Local<Function> func;
        Local<FunctionTemplate> funcTemplate;


          
            Nan::SetPrototypeMethod(localRef, "getPreviewAsync", GetPreviewAsync);
            Nan::SetPrototypeMethod(localRef, "getFrameAsync", GetFrameAsync);
            Nan::SetPrototypeMethod(localRef, "getThumbnailAsync", GetThumbnailAsync);
            Nan::SetPrototypeMethod(localRef, "getPixelDataAsync", GetPixelDataAsync);
            Nan::SetPrototypeMethod(localRef, "getSoftwareBitmapAsync", GetSoftwareBitmapAsync);
          


          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("bitmapContainerProperties").ToLocalChecked(), BitmapContainerPropertiesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("decoderInformation").ToLocalChecked(), DecoderInformationGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("frameCount").ToLocalChecked(), FrameCountGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("bitmapAlphaMode").ToLocalChecked(), BitmapAlphaModeGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("bitmapPixelFormat").ToLocalChecked(), BitmapPixelFormatGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("bitmapProperties").ToLocalChecked(), BitmapPropertiesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("dpiX").ToLocalChecked(), DpiXGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("dpiY").ToLocalChecked(), DpiYGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("orientedPixelHeight").ToLocalChecked(), OrientedPixelHeightGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("orientedPixelWidth").ToLocalChecked(), OrientedPixelWidthGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("pixelHeight").ToLocalChecked(), PixelHeightGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("pixelWidth").ToLocalChecked(), PixelWidthGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);

        Nan::SetMethod(constructor, "getDecoderInformationEnumerator", GetDecoderInformationEnumerator);
        func = Nan::GetFunction(Nan::New<FunctionTemplate>(CreateAsync)).ToLocalChecked();
        Nan::Set(constructor, Nan::New<String>("createAsync").ToLocalChecked(), func);
        Nan::SetAccessor(constructor, Nan::New<String>("bmpDecoderId").ToLocalChecked(), BmpDecoderIdGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("gifDecoderId").ToLocalChecked(), GifDecoderIdGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("icoDecoderId").ToLocalChecked(), IcoDecoderIdGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("jpegDecoderId").ToLocalChecked(), JpegDecoderIdGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("jpegXRDecoderId").ToLocalChecked(), JpegXRDecoderIdGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("pngDecoderId").ToLocalChecked(), PngDecoderIdGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("tiffDecoderId").ToLocalChecked(), TiffDecoderIdGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("heifDecoderId").ToLocalChecked(), HeifDecoderIdGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("webpDecoderId").ToLocalChecked(), WebpDecoderIdGetter);


        Nan::Set(exports, Nan::New<String>("BitmapDecoder").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      BitmapDecoder(::Windows::Graphics::Imaging::BitmapDecoder^ instance) {
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

      ::Windows::Graphics::Imaging::BitmapDecoder^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapDecoder^>(info[0])) {
        try {
          winRtInstance = (::Windows::Graphics::Imaging::BitmapDecoder^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      BitmapDecoder *wrapperInstance = new BitmapDecoder(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapDecoder^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Graphics::Imaging::BitmapDecoder^ winRtInstance;
      try {
        winRtInstance = (::Windows::Graphics::Imaging::BitmapDecoder^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapBitmapDecoder(winRtInstance));
    }

    static void GetPreviewAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapDecoder^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      BitmapDecoder *wrapper = BitmapDecoder::Unwrap<BitmapDecoder>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Graphics::Imaging::ImageStream^>^ op;


      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->GetPreviewAsync();
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

      opTask.then( [asyncToken] (task<::Windows::Graphics::Imaging::ImageStream^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapImageStream(result);
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
    static void GetFrameAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapDecoder^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      BitmapDecoder *wrapper = BitmapDecoder::Unwrap<BitmapDecoder>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Graphics::Imaging::BitmapFrame^>^ op;


      if (info.Length() == 2
        && info[0]->IsUint32())
      {
        try
        {
          unsigned int arg0 = static_cast<unsigned int>(Nan::To<uint32_t>(info[0]).FromMaybe(0));
          
          op = wrapper->_instance->GetFrameAsync(arg0);
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

      opTask.then( [asyncToken] (task<::Windows::Graphics::Imaging::BitmapFrame^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapBitmapFrame(result);
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
    static void GetThumbnailAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapDecoder^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      BitmapDecoder *wrapper = BitmapDecoder::Unwrap<BitmapDecoder>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Graphics::Imaging::ImageStream^>^ op;


      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->GetThumbnailAsync();
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

      opTask.then( [asyncToken] (task<::Windows::Graphics::Imaging::ImageStream^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapImageStream(result);
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
    static void GetPixelDataAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapDecoder^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      BitmapDecoder *wrapper = BitmapDecoder::Unwrap<BitmapDecoder>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Graphics::Imaging::PixelDataProvider^>^ op;


      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->GetPixelDataAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 6
        && info[0]->IsInt32()
        && info[1]->IsInt32()
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapTransform^>(info[2])
        && info[3]->IsInt32()
        && info[4]->IsInt32())
      {
        try
        {
          ::Windows::Graphics::Imaging::BitmapPixelFormat arg0 = static_cast<::Windows::Graphics::Imaging::BitmapPixelFormat>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          ::Windows::Graphics::Imaging::BitmapAlphaMode arg1 = static_cast<::Windows::Graphics::Imaging::BitmapAlphaMode>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          ::Windows::Graphics::Imaging::BitmapTransform^ arg2 = UnwrapBitmapTransform(info[2]);
          ::Windows::Graphics::Imaging::ExifOrientationMode arg3 = static_cast<::Windows::Graphics::Imaging::ExifOrientationMode>(Nan::To<int32_t>(info[3]).FromMaybe(0));
          ::Windows::Graphics::Imaging::ColorManagementMode arg4 = static_cast<::Windows::Graphics::Imaging::ColorManagementMode>(Nan::To<int32_t>(info[4]).FromMaybe(0));
          
          op = wrapper->_instance->GetPixelDataAsync(arg0,arg1,arg2,arg3,arg4);
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

      opTask.then( [asyncToken] (task<::Windows::Graphics::Imaging::PixelDataProvider^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapPixelDataProvider(result);
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
    static void GetSoftwareBitmapAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapDecoder^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      BitmapDecoder *wrapper = BitmapDecoder::Unwrap<BitmapDecoder>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Graphics::Imaging::SoftwareBitmap^>^ op;


      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->GetSoftwareBitmapAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && info[0]->IsInt32()
        && info[1]->IsInt32())
      {
        try
        {
          ::Windows::Graphics::Imaging::BitmapPixelFormat arg0 = static_cast<::Windows::Graphics::Imaging::BitmapPixelFormat>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          ::Windows::Graphics::Imaging::BitmapAlphaMode arg1 = static_cast<::Windows::Graphics::Imaging::BitmapAlphaMode>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          
          op = wrapper->_instance->GetSoftwareBitmapAsync(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 6
        && info[0]->IsInt32()
        && info[1]->IsInt32()
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapTransform^>(info[2])
        && info[3]->IsInt32()
        && info[4]->IsInt32())
      {
        try
        {
          ::Windows::Graphics::Imaging::BitmapPixelFormat arg0 = static_cast<::Windows::Graphics::Imaging::BitmapPixelFormat>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          ::Windows::Graphics::Imaging::BitmapAlphaMode arg1 = static_cast<::Windows::Graphics::Imaging::BitmapAlphaMode>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          ::Windows::Graphics::Imaging::BitmapTransform^ arg2 = UnwrapBitmapTransform(info[2]);
          ::Windows::Graphics::Imaging::ExifOrientationMode arg3 = static_cast<::Windows::Graphics::Imaging::ExifOrientationMode>(Nan::To<int32_t>(info[3]).FromMaybe(0));
          ::Windows::Graphics::Imaging::ColorManagementMode arg4 = static_cast<::Windows::Graphics::Imaging::ColorManagementMode>(Nan::To<int32_t>(info[4]).FromMaybe(0));
          
          op = wrapper->_instance->GetSoftwareBitmapAsync(arg0,arg1,arg2,arg3,arg4);
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

      opTask.then( [asyncToken] (task<::Windows::Graphics::Imaging::SoftwareBitmap^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapSoftwareBitmap(result);
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



    static void CreateAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::Graphics::Imaging::BitmapDecoder^>^ op;


      if (info.Length() == 2
          && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IRandomAccessStream^>(info[0]))
      {
        try
        {
          ::Windows::Storage::Streams::IRandomAccessStream^ arg0 = dynamic_cast<::Windows::Storage::Streams::IRandomAccessStream^>(NodeRT::Utils::GetObjectInstance(info[0]));
            
          op = ::Windows::Graphics::Imaging::BitmapDecoder::CreateAsync(arg0);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
      else if (info.Length() == 3
          && NodeRT::Utils::IsGuid(info[0])
          && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IRandomAccessStream^>(info[1]))
      {
        try
        {
          ::Platform::Guid arg0 = NodeRT::Utils::GuidFromJs(info[0]);
          ::Windows::Storage::Streams::IRandomAccessStream^ arg1 = dynamic_cast<::Windows::Storage::Streams::IRandomAccessStream^>(NodeRT::Utils::GetObjectInstance(info[1]));
            
          op = ::Windows::Graphics::Imaging::BitmapDecoder::CreateAsync(arg0,arg1);
        } catch (Platform::Exception ^exception) {
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

      opTask.then( [asyncToken] (task<::Windows::Graphics::Imaging::BitmapDecoder^> t)
      {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapBitmapDecoder(result);
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
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }


    static void GetDecoderInformationEnumerator(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::Collections::IVectorView<::Windows::Graphics::Imaging::BitmapCodecInformation^>^ result;
          result = ::Windows::Graphics::Imaging::BitmapDecoder::GetDecoderInformationEnumerator();
          info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::Graphics::Imaging::BitmapCodecInformation^>::CreateVectorViewWrapper(result, 
            [](::Windows::Graphics::Imaging::BitmapCodecInformation^ val) -> Local<Value> {
              return WrapBitmapCodecInformation(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapCodecInformation^>(value);
            },
            [](Local<Value> value) -> ::Windows::Graphics::Imaging::BitmapCodecInformation^ {
              return UnwrapBitmapCodecInformation(value);
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

    static void BitmapContainerPropertiesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapDecoder^>(info.This())) {
        return;
      }

      BitmapDecoder *wrapper = BitmapDecoder::Unwrap<BitmapDecoder>(info.This());

      try  {
        ::Windows::Graphics::Imaging::BitmapPropertiesView^ result = wrapper->_instance->BitmapContainerProperties;
        info.GetReturnValue().Set(WrapBitmapPropertiesView(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void DecoderInformationGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapDecoder^>(info.This())) {
        return;
      }

      BitmapDecoder *wrapper = BitmapDecoder::Unwrap<BitmapDecoder>(info.This());

      try  {
        ::Windows::Graphics::Imaging::BitmapCodecInformation^ result = wrapper->_instance->DecoderInformation;
        info.GetReturnValue().Set(WrapBitmapCodecInformation(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void FrameCountGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapDecoder^>(info.This())) {
        return;
      }

      BitmapDecoder *wrapper = BitmapDecoder::Unwrap<BitmapDecoder>(info.This());

      try  {
        unsigned int result = wrapper->_instance->FrameCount;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void BitmapAlphaModeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapDecoder^>(info.This())) {
        return;
      }

      BitmapDecoder *wrapper = BitmapDecoder::Unwrap<BitmapDecoder>(info.This());

      try  {
        ::Windows::Graphics::Imaging::BitmapAlphaMode result = wrapper->_instance->BitmapAlphaMode;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void BitmapPixelFormatGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapDecoder^>(info.This())) {
        return;
      }

      BitmapDecoder *wrapper = BitmapDecoder::Unwrap<BitmapDecoder>(info.This());

      try  {
        ::Windows::Graphics::Imaging::BitmapPixelFormat result = wrapper->_instance->BitmapPixelFormat;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void BitmapPropertiesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapDecoder^>(info.This())) {
        return;
      }

      BitmapDecoder *wrapper = BitmapDecoder::Unwrap<BitmapDecoder>(info.This());

      try  {
        ::Windows::Graphics::Imaging::BitmapPropertiesView^ result = wrapper->_instance->BitmapProperties;
        info.GetReturnValue().Set(WrapBitmapPropertiesView(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void DpiXGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapDecoder^>(info.This())) {
        return;
      }

      BitmapDecoder *wrapper = BitmapDecoder::Unwrap<BitmapDecoder>(info.This());

      try  {
        double result = wrapper->_instance->DpiX;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void DpiYGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapDecoder^>(info.This())) {
        return;
      }

      BitmapDecoder *wrapper = BitmapDecoder::Unwrap<BitmapDecoder>(info.This());

      try  {
        double result = wrapper->_instance->DpiY;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void OrientedPixelHeightGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapDecoder^>(info.This())) {
        return;
      }

      BitmapDecoder *wrapper = BitmapDecoder::Unwrap<BitmapDecoder>(info.This());

      try  {
        unsigned int result = wrapper->_instance->OrientedPixelHeight;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void OrientedPixelWidthGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapDecoder^>(info.This())) {
        return;
      }

      BitmapDecoder *wrapper = BitmapDecoder::Unwrap<BitmapDecoder>(info.This());

      try  {
        unsigned int result = wrapper->_instance->OrientedPixelWidth;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PixelHeightGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapDecoder^>(info.This())) {
        return;
      }

      BitmapDecoder *wrapper = BitmapDecoder::Unwrap<BitmapDecoder>(info.This());

      try  {
        unsigned int result = wrapper->_instance->PixelHeight;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PixelWidthGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapDecoder^>(info.This())) {
        return;
      }

      BitmapDecoder *wrapper = BitmapDecoder::Unwrap<BitmapDecoder>(info.This());

      try  {
        unsigned int result = wrapper->_instance->PixelWidth;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    static void BmpDecoderIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        ::Platform::Guid result = ::Windows::Graphics::Imaging::BitmapDecoder::BmpDecoderId;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void GifDecoderIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        ::Platform::Guid result = ::Windows::Graphics::Imaging::BitmapDecoder::GifDecoderId;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void IcoDecoderIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        ::Platform::Guid result = ::Windows::Graphics::Imaging::BitmapDecoder::IcoDecoderId;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void JpegDecoderIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        ::Platform::Guid result = ::Windows::Graphics::Imaging::BitmapDecoder::JpegDecoderId;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void JpegXRDecoderIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        ::Platform::Guid result = ::Windows::Graphics::Imaging::BitmapDecoder::JpegXRDecoderId;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void PngDecoderIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        ::Platform::Guid result = ::Windows::Graphics::Imaging::BitmapDecoder::PngDecoderId;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void TiffDecoderIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        ::Platform::Guid result = ::Windows::Graphics::Imaging::BitmapDecoder::TiffDecoderId;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void HeifDecoderIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        ::Platform::Guid result = ::Windows::Graphics::Imaging::BitmapDecoder::HeifDecoderId;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void WebpDecoderIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        ::Platform::Guid result = ::Windows::Graphics::Imaging::BitmapDecoder::WebpDecoderId;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    private:
      ::Windows::Graphics::Imaging::BitmapDecoder^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapBitmapDecoder(::Windows::Graphics::Imaging::BitmapDecoder^ wintRtInstance);
      friend ::Windows::Graphics::Imaging::BitmapDecoder^ UnwrapBitmapDecoder(Local<Value> value);
  };

  Persistent<FunctionTemplate> BitmapDecoder::s_constructorTemplate;

  v8::Local<v8::Value> WrapBitmapDecoder(::Windows::Graphics::Imaging::BitmapDecoder^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(BitmapDecoder::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Graphics::Imaging::BitmapDecoder^ UnwrapBitmapDecoder(Local<Value> value) {
     return BitmapDecoder::Unwrap<BitmapDecoder>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitBitmapDecoder(Local<Object> exports) {
    BitmapDecoder::Init(exports);
  }

  class BitmapEncoder : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("BitmapEncoder").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);

        Local<Function> func;
        Local<FunctionTemplate> funcTemplate;

          
            Nan::SetPrototypeMethod(localRef, "setPixelData", SetPixelData);
            Nan::SetPrototypeMethod(localRef, "setSoftwareBitmap", SetSoftwareBitmap);
          

          
            Nan::SetPrototypeMethod(localRef, "goToNextFrameAsync", GoToNextFrameAsync);
            Nan::SetPrototypeMethod(localRef, "flushAsync", FlushAsync);
          


          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isThumbnailGenerated").ToLocalChecked(), IsThumbnailGeneratedGetter, IsThumbnailGeneratedSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("generatedThumbnailWidth").ToLocalChecked(), GeneratedThumbnailWidthGetter, GeneratedThumbnailWidthSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("generatedThumbnailHeight").ToLocalChecked(), GeneratedThumbnailHeightGetter, GeneratedThumbnailHeightSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("bitmapContainerProperties").ToLocalChecked(), BitmapContainerPropertiesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("bitmapProperties").ToLocalChecked(), BitmapPropertiesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("bitmapTransform").ToLocalChecked(), BitmapTransformGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("encoderInformation").ToLocalChecked(), EncoderInformationGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);

        Nan::SetMethod(constructor, "getEncoderInformationEnumerator", GetEncoderInformationEnumerator);
        func = Nan::GetFunction(Nan::New<FunctionTemplate>(CreateAsync)).ToLocalChecked();
        Nan::Set(constructor, Nan::New<String>("createAsync").ToLocalChecked(), func);
        func = Nan::GetFunction(Nan::New<FunctionTemplate>(CreateForTranscodingAsync)).ToLocalChecked();
        Nan::Set(constructor, Nan::New<String>("createForTranscodingAsync").ToLocalChecked(), func);
        func = Nan::GetFunction(Nan::New<FunctionTemplate>(CreateForInPlacePropertyEncodingAsync)).ToLocalChecked();
        Nan::Set(constructor, Nan::New<String>("createForInPlacePropertyEncodingAsync").ToLocalChecked(), func);
        Nan::SetAccessor(constructor, Nan::New<String>("bmpEncoderId").ToLocalChecked(), BmpEncoderIdGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("gifEncoderId").ToLocalChecked(), GifEncoderIdGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("jpegEncoderId").ToLocalChecked(), JpegEncoderIdGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("jpegXREncoderId").ToLocalChecked(), JpegXREncoderIdGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("pngEncoderId").ToLocalChecked(), PngEncoderIdGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("tiffEncoderId").ToLocalChecked(), TiffEncoderIdGetter);
        Nan::SetAccessor(constructor, Nan::New<String>("heifEncoderId").ToLocalChecked(), HeifEncoderIdGetter);


        Nan::Set(exports, Nan::New<String>("BitmapEncoder").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      BitmapEncoder(::Windows::Graphics::Imaging::BitmapEncoder^ instance) {
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

      ::Windows::Graphics::Imaging::BitmapEncoder^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapEncoder^>(info[0])) {
        try {
          winRtInstance = (::Windows::Graphics::Imaging::BitmapEncoder^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      BitmapEncoder *wrapperInstance = new BitmapEncoder(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapEncoder^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Graphics::Imaging::BitmapEncoder^ winRtInstance;
      try {
        winRtInstance = (::Windows::Graphics::Imaging::BitmapEncoder^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapBitmapEncoder(winRtInstance));
    }

    static void GoToNextFrameAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapEncoder^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      BitmapEncoder *wrapper = BitmapEncoder::Unwrap<BitmapEncoder>(info.This());

      ::Windows::Foundation::IAsyncAction^ op;


      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->GoToNextFrameAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 2
        && (NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IIterable<::Windows::Foundation::Collections::IKeyValuePair<::Platform::String^, ::Windows::Graphics::Imaging::BitmapTypedValue^>^>^>(info[0]) || info[0]->IsObject()))
      {
        try
        {
          ::Windows::Foundation::Collections::IIterable<::Windows::Foundation::Collections::IKeyValuePair<::Platform::String^, ::Windows::Graphics::Imaging::BitmapTypedValue^>^>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Windows::Foundation::Collections::IIterable<::Windows::Foundation::Collections::IKeyValuePair<::Platform::String^, ::Windows::Graphics::Imaging::BitmapTypedValue^>^>^
            {
              if (value->IsObject())
              {
                return NodeRT::Collections::JsObjectToWinrtMap<::Windows::Graphics::Imaging::BitmapTypedValue^>(value.As<Object>(), 
                 [](Local<Value> value) -> bool {
                   return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapTypedValue^>(value);
                 },
                 [](Local<Value> value) -> ::Windows::Graphics::Imaging::BitmapTypedValue^ {
                   return UnwrapBitmapTypedValue(value);
                 }
                );
              }
              else
              {
                return dynamic_cast<::Windows::Foundation::Collections::IIterable<::Windows::Foundation::Collections::IKeyValuePair<::Platform::String^, ::Windows::Graphics::Imaging::BitmapTypedValue^>^>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          
          op = wrapper->_instance->GoToNextFrameAsync(arg0);
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

      opTask.then( [asyncToken] (task<void> t) {
        try {
          t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> args[] = {Undefined()};


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
    static void FlushAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapEncoder^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      BitmapEncoder *wrapper = BitmapEncoder::Unwrap<BitmapEncoder>(info.This());

      ::Windows::Foundation::IAsyncAction^ op;


      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->FlushAsync();
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

      opTask.then( [asyncToken] (task<void> t) {
        try {
          t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> args[] = {Undefined()};


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

    static void SetPixelData(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapEncoder^>(info.This())) {
        return;
      }

      BitmapEncoder *wrapper = BitmapEncoder::Unwrap<BitmapEncoder>(info.This());

      if (info.Length() == 7
        && info[0]->IsInt32()
        && info[1]->IsInt32()
        && info[2]->IsUint32()
        && info[3]->IsUint32()
        && info[4]->IsNumber()
        && info[5]->IsNumber()
        && (NodeRT::Utils::IsWinRtWrapperOf<::Platform::Array<unsigned char>^>(info[6]) || info[6]->IsArray()))
      {
        try
        {
          ::Windows::Graphics::Imaging::BitmapPixelFormat arg0 = static_cast<::Windows::Graphics::Imaging::BitmapPixelFormat>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          ::Windows::Graphics::Imaging::BitmapAlphaMode arg1 = static_cast<::Windows::Graphics::Imaging::BitmapAlphaMode>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          unsigned int arg2 = static_cast<unsigned int>(Nan::To<uint32_t>(info[2]).FromMaybe(0));
          unsigned int arg3 = static_cast<unsigned int>(Nan::To<uint32_t>(info[3]).FromMaybe(0));
          double arg4 = Nan::To<double>(info[4]).FromMaybe(0.0);
          double arg5 = Nan::To<double>(info[5]).FromMaybe(0.0);
          ::Platform::Array<unsigned char>^ arg6 = 
            [] (v8::Local<v8::Value> value) -> ::Platform::Array<unsigned char>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtArray<unsigned char>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return value->IsInt32();
                 },
                 [](Local<Value> value) -> unsigned char {
                   return static_cast<unsigned char>(Nan::To<int32_t>(value).FromMaybe(0));
                 }
                );
              }
              else
              {
                return dynamic_cast<::Platform::Array<unsigned char>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[6]);
          
          wrapper->_instance->SetPixelData(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
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
    static void SetSoftwareBitmap(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapEncoder^>(info.This())) {
        return;
      }

      BitmapEncoder *wrapper = BitmapEncoder::Unwrap<BitmapEncoder>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::SoftwareBitmap^>(info[0]))
      {
        try
        {
          ::Windows::Graphics::Imaging::SoftwareBitmap^ arg0 = UnwrapSoftwareBitmap(info[0]);
          
          wrapper->_instance->SetSoftwareBitmap(arg0);
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


    static void CreateAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::Graphics::Imaging::BitmapEncoder^>^ op;


      if (info.Length() == 3
          && NodeRT::Utils::IsGuid(info[0])
          && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IRandomAccessStream^>(info[1]))
      {
        try
        {
          ::Platform::Guid arg0 = NodeRT::Utils::GuidFromJs(info[0]);
          ::Windows::Storage::Streams::IRandomAccessStream^ arg1 = dynamic_cast<::Windows::Storage::Streams::IRandomAccessStream^>(NodeRT::Utils::GetObjectInstance(info[1]));
            
          op = ::Windows::Graphics::Imaging::BitmapEncoder::CreateAsync(arg0,arg1);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
      else if (info.Length() == 4
          && NodeRT::Utils::IsGuid(info[0])
          && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IRandomAccessStream^>(info[1])
          && (NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IIterable<::Windows::Foundation::Collections::IKeyValuePair<::Platform::String^, ::Windows::Graphics::Imaging::BitmapTypedValue^>^>^>(info[2]) || info[2]->IsObject()))
      {
        try
        {
          ::Platform::Guid arg0 = NodeRT::Utils::GuidFromJs(info[0]);
          ::Windows::Storage::Streams::IRandomAccessStream^ arg1 = dynamic_cast<::Windows::Storage::Streams::IRandomAccessStream^>(NodeRT::Utils::GetObjectInstance(info[1]));
          ::Windows::Foundation::Collections::IIterable<::Windows::Foundation::Collections::IKeyValuePair<::Platform::String^, ::Windows::Graphics::Imaging::BitmapTypedValue^>^>^ arg2 = 
            [] (v8::Local<v8::Value> value) -> ::Windows::Foundation::Collections::IIterable<::Windows::Foundation::Collections::IKeyValuePair<::Platform::String^, ::Windows::Graphics::Imaging::BitmapTypedValue^>^>^
            {
              if (value->IsObject())
              {
                return NodeRT::Collections::JsObjectToWinrtMap<::Windows::Graphics::Imaging::BitmapTypedValue^>(value.As<Object>(), 
                 [](Local<Value> value) -> bool {
                   return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapTypedValue^>(value);
                 },
                 [](Local<Value> value) -> ::Windows::Graphics::Imaging::BitmapTypedValue^ {
                   return UnwrapBitmapTypedValue(value);
                 }
                );
              }
              else
              {
                return dynamic_cast<::Windows::Foundation::Collections::IIterable<::Windows::Foundation::Collections::IKeyValuePair<::Platform::String^, ::Windows::Graphics::Imaging::BitmapTypedValue^>^>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[2]);
            
          op = ::Windows::Graphics::Imaging::BitmapEncoder::CreateAsync(arg0,arg1,arg2);
        } catch (Platform::Exception ^exception) {
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

      opTask.then( [asyncToken] (task<::Windows::Graphics::Imaging::BitmapEncoder^> t)
      {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapBitmapEncoder(result);
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
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }

    static void CreateForTranscodingAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::Graphics::Imaging::BitmapEncoder^>^ op;


      if (info.Length() == 3
          && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IRandomAccessStream^>(info[0])
          && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapDecoder^>(info[1]))
      {
        try
        {
          ::Windows::Storage::Streams::IRandomAccessStream^ arg0 = dynamic_cast<::Windows::Storage::Streams::IRandomAccessStream^>(NodeRT::Utils::GetObjectInstance(info[0]));
          ::Windows::Graphics::Imaging::BitmapDecoder^ arg1 = UnwrapBitmapDecoder(info[1]);
            
          op = ::Windows::Graphics::Imaging::BitmapEncoder::CreateForTranscodingAsync(arg0,arg1);
        } catch (Platform::Exception ^exception) {
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

      opTask.then( [asyncToken] (task<::Windows::Graphics::Imaging::BitmapEncoder^> t)
      {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapBitmapEncoder(result);
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
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }

    static void CreateForInPlacePropertyEncodingAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::Graphics::Imaging::BitmapEncoder^>^ op;


      if (info.Length() == 2
          && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapDecoder^>(info[0]))
      {
        try
        {
          ::Windows::Graphics::Imaging::BitmapDecoder^ arg0 = UnwrapBitmapDecoder(info[0]);
            
          op = ::Windows::Graphics::Imaging::BitmapEncoder::CreateForInPlacePropertyEncodingAsync(arg0);
        } catch (Platform::Exception ^exception) {
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

      opTask.then( [asyncToken] (task<::Windows::Graphics::Imaging::BitmapEncoder^> t)
      {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapBitmapEncoder(result);
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
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }


    static void GetEncoderInformationEnumerator(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::Collections::IVectorView<::Windows::Graphics::Imaging::BitmapCodecInformation^>^ result;
          result = ::Windows::Graphics::Imaging::BitmapEncoder::GetEncoderInformationEnumerator();
          info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::Graphics::Imaging::BitmapCodecInformation^>::CreateVectorViewWrapper(result, 
            [](::Windows::Graphics::Imaging::BitmapCodecInformation^ val) -> Local<Value> {
              return WrapBitmapCodecInformation(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapCodecInformation^>(value);
            },
            [](Local<Value> value) -> ::Windows::Graphics::Imaging::BitmapCodecInformation^ {
              return UnwrapBitmapCodecInformation(value);
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

    static void IsThumbnailGeneratedGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapEncoder^>(info.This())) {
        return;
      }

      BitmapEncoder *wrapper = BitmapEncoder::Unwrap<BitmapEncoder>(info.This());

      try  {
        bool result = wrapper->_instance->IsThumbnailGenerated;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void IsThumbnailGeneratedSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsBoolean()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapEncoder^>(info.This())) {
        return;
      }

      BitmapEncoder *wrapper = BitmapEncoder::Unwrap<BitmapEncoder>(info.This());

      try {

        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->IsThumbnailGenerated = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void GeneratedThumbnailWidthGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapEncoder^>(info.This())) {
        return;
      }

      BitmapEncoder *wrapper = BitmapEncoder::Unwrap<BitmapEncoder>(info.This());

      try  {
        unsigned int result = wrapper->_instance->GeneratedThumbnailWidth;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void GeneratedThumbnailWidthSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsUint32()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapEncoder^>(info.This())) {
        return;
      }

      BitmapEncoder *wrapper = BitmapEncoder::Unwrap<BitmapEncoder>(info.This());

      try {

        unsigned int winRtValue = static_cast<unsigned int>(Nan::To<uint32_t>(value).FromMaybe(0));

        wrapper->_instance->GeneratedThumbnailWidth = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void GeneratedThumbnailHeightGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapEncoder^>(info.This())) {
        return;
      }

      BitmapEncoder *wrapper = BitmapEncoder::Unwrap<BitmapEncoder>(info.This());

      try  {
        unsigned int result = wrapper->_instance->GeneratedThumbnailHeight;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void GeneratedThumbnailHeightSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsUint32()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapEncoder^>(info.This())) {
        return;
      }

      BitmapEncoder *wrapper = BitmapEncoder::Unwrap<BitmapEncoder>(info.This());

      try {

        unsigned int winRtValue = static_cast<unsigned int>(Nan::To<uint32_t>(value).FromMaybe(0));

        wrapper->_instance->GeneratedThumbnailHeight = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void BitmapContainerPropertiesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapEncoder^>(info.This())) {
        return;
      }

      BitmapEncoder *wrapper = BitmapEncoder::Unwrap<BitmapEncoder>(info.This());

      try  {
        ::Windows::Graphics::Imaging::BitmapProperties^ result = wrapper->_instance->BitmapContainerProperties;
        info.GetReturnValue().Set(WrapBitmapProperties(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void BitmapPropertiesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapEncoder^>(info.This())) {
        return;
      }

      BitmapEncoder *wrapper = BitmapEncoder::Unwrap<BitmapEncoder>(info.This());

      try  {
        ::Windows::Graphics::Imaging::BitmapProperties^ result = wrapper->_instance->BitmapProperties;
        info.GetReturnValue().Set(WrapBitmapProperties(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void BitmapTransformGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapEncoder^>(info.This())) {
        return;
      }

      BitmapEncoder *wrapper = BitmapEncoder::Unwrap<BitmapEncoder>(info.This());

      try  {
        ::Windows::Graphics::Imaging::BitmapTransform^ result = wrapper->_instance->BitmapTransform;
        info.GetReturnValue().Set(WrapBitmapTransform(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void EncoderInformationGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapEncoder^>(info.This())) {
        return;
      }

      BitmapEncoder *wrapper = BitmapEncoder::Unwrap<BitmapEncoder>(info.This());

      try  {
        ::Windows::Graphics::Imaging::BitmapCodecInformation^ result = wrapper->_instance->EncoderInformation;
        info.GetReturnValue().Set(WrapBitmapCodecInformation(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    static void BmpEncoderIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        ::Platform::Guid result = ::Windows::Graphics::Imaging::BitmapEncoder::BmpEncoderId;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void GifEncoderIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        ::Platform::Guid result = ::Windows::Graphics::Imaging::BitmapEncoder::GifEncoderId;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void JpegEncoderIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        ::Platform::Guid result = ::Windows::Graphics::Imaging::BitmapEncoder::JpegEncoderId;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void JpegXREncoderIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        ::Platform::Guid result = ::Windows::Graphics::Imaging::BitmapEncoder::JpegXREncoderId;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void PngEncoderIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        ::Platform::Guid result = ::Windows::Graphics::Imaging::BitmapEncoder::PngEncoderId;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void TiffEncoderIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        ::Platform::Guid result = ::Windows::Graphics::Imaging::BitmapEncoder::TiffEncoderId;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void HeifEncoderIdGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        ::Platform::Guid result = ::Windows::Graphics::Imaging::BitmapEncoder::HeifEncoderId;
        info.GetReturnValue().Set(NodeRT::Utils::GuidToJs(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    private:
      ::Windows::Graphics::Imaging::BitmapEncoder^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapBitmapEncoder(::Windows::Graphics::Imaging::BitmapEncoder^ wintRtInstance);
      friend ::Windows::Graphics::Imaging::BitmapEncoder^ UnwrapBitmapEncoder(Local<Value> value);
  };

  Persistent<FunctionTemplate> BitmapEncoder::s_constructorTemplate;

  v8::Local<v8::Value> WrapBitmapEncoder(::Windows::Graphics::Imaging::BitmapEncoder^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(BitmapEncoder::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Graphics::Imaging::BitmapEncoder^ UnwrapBitmapEncoder(Local<Value> value) {
     return BitmapEncoder::Unwrap<BitmapEncoder>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitBitmapEncoder(Local<Object> exports) {
    BitmapEncoder::Init(exports);
  }

  class BitmapFrame : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("BitmapFrame").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);

        Local<Function> func;
        Local<FunctionTemplate> funcTemplate;


          
            Nan::SetPrototypeMethod(localRef, "getThumbnailAsync", GetThumbnailAsync);
            Nan::SetPrototypeMethod(localRef, "getPixelDataAsync", GetPixelDataAsync);
            Nan::SetPrototypeMethod(localRef, "getSoftwareBitmapAsync", GetSoftwareBitmapAsync);
          


          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("bitmapAlphaMode").ToLocalChecked(), BitmapAlphaModeGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("bitmapPixelFormat").ToLocalChecked(), BitmapPixelFormatGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("bitmapProperties").ToLocalChecked(), BitmapPropertiesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("dpiX").ToLocalChecked(), DpiXGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("dpiY").ToLocalChecked(), DpiYGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("orientedPixelHeight").ToLocalChecked(), OrientedPixelHeightGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("orientedPixelWidth").ToLocalChecked(), OrientedPixelWidthGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("pixelHeight").ToLocalChecked(), PixelHeightGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("pixelWidth").ToLocalChecked(), PixelWidthGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("BitmapFrame").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      BitmapFrame(::Windows::Graphics::Imaging::BitmapFrame^ instance) {
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

      ::Windows::Graphics::Imaging::BitmapFrame^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapFrame^>(info[0])) {
        try {
          winRtInstance = (::Windows::Graphics::Imaging::BitmapFrame^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      BitmapFrame *wrapperInstance = new BitmapFrame(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapFrame^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Graphics::Imaging::BitmapFrame^ winRtInstance;
      try {
        winRtInstance = (::Windows::Graphics::Imaging::BitmapFrame^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapBitmapFrame(winRtInstance));
    }

    static void GetThumbnailAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapFrame^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      BitmapFrame *wrapper = BitmapFrame::Unwrap<BitmapFrame>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Graphics::Imaging::ImageStream^>^ op;


      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->GetThumbnailAsync();
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

      opTask.then( [asyncToken] (task<::Windows::Graphics::Imaging::ImageStream^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapImageStream(result);
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
    static void GetPixelDataAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapFrame^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      BitmapFrame *wrapper = BitmapFrame::Unwrap<BitmapFrame>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Graphics::Imaging::PixelDataProvider^>^ op;


      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->GetPixelDataAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 6
        && info[0]->IsInt32()
        && info[1]->IsInt32()
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapTransform^>(info[2])
        && info[3]->IsInt32()
        && info[4]->IsInt32())
      {
        try
        {
          ::Windows::Graphics::Imaging::BitmapPixelFormat arg0 = static_cast<::Windows::Graphics::Imaging::BitmapPixelFormat>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          ::Windows::Graphics::Imaging::BitmapAlphaMode arg1 = static_cast<::Windows::Graphics::Imaging::BitmapAlphaMode>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          ::Windows::Graphics::Imaging::BitmapTransform^ arg2 = UnwrapBitmapTransform(info[2]);
          ::Windows::Graphics::Imaging::ExifOrientationMode arg3 = static_cast<::Windows::Graphics::Imaging::ExifOrientationMode>(Nan::To<int32_t>(info[3]).FromMaybe(0));
          ::Windows::Graphics::Imaging::ColorManagementMode arg4 = static_cast<::Windows::Graphics::Imaging::ColorManagementMode>(Nan::To<int32_t>(info[4]).FromMaybe(0));
          
          op = wrapper->_instance->GetPixelDataAsync(arg0,arg1,arg2,arg3,arg4);
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

      opTask.then( [asyncToken] (task<::Windows::Graphics::Imaging::PixelDataProvider^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapPixelDataProvider(result);
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
    static void GetSoftwareBitmapAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapFrame^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      BitmapFrame *wrapper = BitmapFrame::Unwrap<BitmapFrame>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Graphics::Imaging::SoftwareBitmap^>^ op;


      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->GetSoftwareBitmapAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && info[0]->IsInt32()
        && info[1]->IsInt32())
      {
        try
        {
          ::Windows::Graphics::Imaging::BitmapPixelFormat arg0 = static_cast<::Windows::Graphics::Imaging::BitmapPixelFormat>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          ::Windows::Graphics::Imaging::BitmapAlphaMode arg1 = static_cast<::Windows::Graphics::Imaging::BitmapAlphaMode>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          
          op = wrapper->_instance->GetSoftwareBitmapAsync(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 6
        && info[0]->IsInt32()
        && info[1]->IsInt32()
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapTransform^>(info[2])
        && info[3]->IsInt32()
        && info[4]->IsInt32())
      {
        try
        {
          ::Windows::Graphics::Imaging::BitmapPixelFormat arg0 = static_cast<::Windows::Graphics::Imaging::BitmapPixelFormat>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          ::Windows::Graphics::Imaging::BitmapAlphaMode arg1 = static_cast<::Windows::Graphics::Imaging::BitmapAlphaMode>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          ::Windows::Graphics::Imaging::BitmapTransform^ arg2 = UnwrapBitmapTransform(info[2]);
          ::Windows::Graphics::Imaging::ExifOrientationMode arg3 = static_cast<::Windows::Graphics::Imaging::ExifOrientationMode>(Nan::To<int32_t>(info[3]).FromMaybe(0));
          ::Windows::Graphics::Imaging::ColorManagementMode arg4 = static_cast<::Windows::Graphics::Imaging::ColorManagementMode>(Nan::To<int32_t>(info[4]).FromMaybe(0));
          
          op = wrapper->_instance->GetSoftwareBitmapAsync(arg0,arg1,arg2,arg3,arg4);
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

      opTask.then( [asyncToken] (task<::Windows::Graphics::Imaging::SoftwareBitmap^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapSoftwareBitmap(result);
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




    static void BitmapAlphaModeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapFrame^>(info.This())) {
        return;
      }

      BitmapFrame *wrapper = BitmapFrame::Unwrap<BitmapFrame>(info.This());

      try  {
        ::Windows::Graphics::Imaging::BitmapAlphaMode result = wrapper->_instance->BitmapAlphaMode;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void BitmapPixelFormatGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapFrame^>(info.This())) {
        return;
      }

      BitmapFrame *wrapper = BitmapFrame::Unwrap<BitmapFrame>(info.This());

      try  {
        ::Windows::Graphics::Imaging::BitmapPixelFormat result = wrapper->_instance->BitmapPixelFormat;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void BitmapPropertiesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapFrame^>(info.This())) {
        return;
      }

      BitmapFrame *wrapper = BitmapFrame::Unwrap<BitmapFrame>(info.This());

      try  {
        ::Windows::Graphics::Imaging::BitmapPropertiesView^ result = wrapper->_instance->BitmapProperties;
        info.GetReturnValue().Set(WrapBitmapPropertiesView(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void DpiXGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapFrame^>(info.This())) {
        return;
      }

      BitmapFrame *wrapper = BitmapFrame::Unwrap<BitmapFrame>(info.This());

      try  {
        double result = wrapper->_instance->DpiX;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void DpiYGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapFrame^>(info.This())) {
        return;
      }

      BitmapFrame *wrapper = BitmapFrame::Unwrap<BitmapFrame>(info.This());

      try  {
        double result = wrapper->_instance->DpiY;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void OrientedPixelHeightGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapFrame^>(info.This())) {
        return;
      }

      BitmapFrame *wrapper = BitmapFrame::Unwrap<BitmapFrame>(info.This());

      try  {
        unsigned int result = wrapper->_instance->OrientedPixelHeight;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void OrientedPixelWidthGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapFrame^>(info.This())) {
        return;
      }

      BitmapFrame *wrapper = BitmapFrame::Unwrap<BitmapFrame>(info.This());

      try  {
        unsigned int result = wrapper->_instance->OrientedPixelWidth;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PixelHeightGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapFrame^>(info.This())) {
        return;
      }

      BitmapFrame *wrapper = BitmapFrame::Unwrap<BitmapFrame>(info.This());

      try  {
        unsigned int result = wrapper->_instance->PixelHeight;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PixelWidthGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapFrame^>(info.This())) {
        return;
      }

      BitmapFrame *wrapper = BitmapFrame::Unwrap<BitmapFrame>(info.This());

      try  {
        unsigned int result = wrapper->_instance->PixelWidth;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Graphics::Imaging::BitmapFrame^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapBitmapFrame(::Windows::Graphics::Imaging::BitmapFrame^ wintRtInstance);
      friend ::Windows::Graphics::Imaging::BitmapFrame^ UnwrapBitmapFrame(Local<Value> value);
  };

  Persistent<FunctionTemplate> BitmapFrame::s_constructorTemplate;

  v8::Local<v8::Value> WrapBitmapFrame(::Windows::Graphics::Imaging::BitmapFrame^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(BitmapFrame::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Graphics::Imaging::BitmapFrame^ UnwrapBitmapFrame(Local<Value> value) {
     return BitmapFrame::Unwrap<BitmapFrame>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitBitmapFrame(Local<Object> exports) {
    BitmapFrame::Init(exports);
  }

  class BitmapProperties : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("BitmapProperties").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);

        Local<Function> func;
        Local<FunctionTemplate> funcTemplate;


          
            Nan::SetPrototypeMethod(localRef, "setPropertiesAsync", SetPropertiesAsync);
            Nan::SetPrototypeMethod(localRef, "getPropertiesAsync", GetPropertiesAsync);
          



        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("BitmapProperties").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      BitmapProperties(::Windows::Graphics::Imaging::BitmapProperties^ instance) {
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

      ::Windows::Graphics::Imaging::BitmapProperties^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapProperties^>(info[0])) {
        try {
          winRtInstance = (::Windows::Graphics::Imaging::BitmapProperties^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      BitmapProperties *wrapperInstance = new BitmapProperties(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapProperties^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Graphics::Imaging::BitmapProperties^ winRtInstance;
      try {
        winRtInstance = (::Windows::Graphics::Imaging::BitmapProperties^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapBitmapProperties(winRtInstance));
    }

    static void SetPropertiesAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapProperties^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      BitmapProperties *wrapper = BitmapProperties::Unwrap<BitmapProperties>(info.This());

      ::Windows::Foundation::IAsyncAction^ op;


      if (info.Length() == 2
        && (NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IIterable<::Windows::Foundation::Collections::IKeyValuePair<::Platform::String^, ::Windows::Graphics::Imaging::BitmapTypedValue^>^>^>(info[0]) || info[0]->IsObject()))
      {
        try
        {
          ::Windows::Foundation::Collections::IIterable<::Windows::Foundation::Collections::IKeyValuePair<::Platform::String^, ::Windows::Graphics::Imaging::BitmapTypedValue^>^>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Windows::Foundation::Collections::IIterable<::Windows::Foundation::Collections::IKeyValuePair<::Platform::String^, ::Windows::Graphics::Imaging::BitmapTypedValue^>^>^
            {
              if (value->IsObject())
              {
                return NodeRT::Collections::JsObjectToWinrtMap<::Windows::Graphics::Imaging::BitmapTypedValue^>(value.As<Object>(), 
                 [](Local<Value> value) -> bool {
                   return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapTypedValue^>(value);
                 },
                 [](Local<Value> value) -> ::Windows::Graphics::Imaging::BitmapTypedValue^ {
                   return UnwrapBitmapTypedValue(value);
                 }
                );
              }
              else
              {
                return dynamic_cast<::Windows::Foundation::Collections::IIterable<::Windows::Foundation::Collections::IKeyValuePair<::Platform::String^, ::Windows::Graphics::Imaging::BitmapTypedValue^>^>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          
          op = wrapper->_instance->SetPropertiesAsync(arg0);
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

      opTask.then( [asyncToken] (task<void> t) {
        try {
          t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> args[] = {Undefined()};


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
    static void GetPropertiesAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapProperties^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      BitmapProperties *wrapper = BitmapProperties::Unwrap<BitmapProperties>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Graphics::Imaging::BitmapPropertySet^>^ op;


      if (info.Length() == 2
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
          
          op = wrapper->_instance->GetPropertiesAsync(arg0);
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

      opTask.then( [asyncToken] (task<::Windows::Graphics::Imaging::BitmapPropertySet^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapBitmapPropertySet(result);
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






    private:
      ::Windows::Graphics::Imaging::BitmapProperties^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapBitmapProperties(::Windows::Graphics::Imaging::BitmapProperties^ wintRtInstance);
      friend ::Windows::Graphics::Imaging::BitmapProperties^ UnwrapBitmapProperties(Local<Value> value);
  };

  Persistent<FunctionTemplate> BitmapProperties::s_constructorTemplate;

  v8::Local<v8::Value> WrapBitmapProperties(::Windows::Graphics::Imaging::BitmapProperties^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(BitmapProperties::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Graphics::Imaging::BitmapProperties^ UnwrapBitmapProperties(Local<Value> value) {
     return BitmapProperties::Unwrap<BitmapProperties>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitBitmapProperties(Local<Object> exports) {
    BitmapProperties::Init(exports);
  }

  class BitmapPropertiesView : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("BitmapPropertiesView").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);

        Local<Function> func;
        Local<FunctionTemplate> funcTemplate;


          
            Nan::SetPrototypeMethod(localRef, "getPropertiesAsync", GetPropertiesAsync);
          



        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("BitmapPropertiesView").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      BitmapPropertiesView(::Windows::Graphics::Imaging::BitmapPropertiesView^ instance) {
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

      ::Windows::Graphics::Imaging::BitmapPropertiesView^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapPropertiesView^>(info[0])) {
        try {
          winRtInstance = (::Windows::Graphics::Imaging::BitmapPropertiesView^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      BitmapPropertiesView *wrapperInstance = new BitmapPropertiesView(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapPropertiesView^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Graphics::Imaging::BitmapPropertiesView^ winRtInstance;
      try {
        winRtInstance = (::Windows::Graphics::Imaging::BitmapPropertiesView^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapBitmapPropertiesView(winRtInstance));
    }

    static void GetPropertiesAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapPropertiesView^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      BitmapPropertiesView *wrapper = BitmapPropertiesView::Unwrap<BitmapPropertiesView>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Graphics::Imaging::BitmapPropertySet^>^ op;


      if (info.Length() == 2
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
          
          op = wrapper->_instance->GetPropertiesAsync(arg0);
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

      opTask.then( [asyncToken] (task<::Windows::Graphics::Imaging::BitmapPropertySet^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapBitmapPropertySet(result);
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






    private:
      ::Windows::Graphics::Imaging::BitmapPropertiesView^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapBitmapPropertiesView(::Windows::Graphics::Imaging::BitmapPropertiesView^ wintRtInstance);
      friend ::Windows::Graphics::Imaging::BitmapPropertiesView^ UnwrapBitmapPropertiesView(Local<Value> value);
  };

  Persistent<FunctionTemplate> BitmapPropertiesView::s_constructorTemplate;

  v8::Local<v8::Value> WrapBitmapPropertiesView(::Windows::Graphics::Imaging::BitmapPropertiesView^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(BitmapPropertiesView::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Graphics::Imaging::BitmapPropertiesView^ UnwrapBitmapPropertiesView(Local<Value> value) {
     return BitmapPropertiesView::Unwrap<BitmapPropertiesView>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitBitmapPropertiesView(Local<Object> exports) {
    BitmapPropertiesView::Init(exports);
  }

  class BitmapPropertySet : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("BitmapPropertySet").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "lookup", Lookup);
            Nan::SetPrototypeMethod(localRef, "hasKey", HasKey);
            Nan::SetPrototypeMethod(localRef, "getView", GetView);
            Nan::SetPrototypeMethod(localRef, "insert", Insert);
            Nan::SetPrototypeMethod(localRef, "remove", Remove);
            Nan::SetPrototypeMethod(localRef, "clear", Clear);
            Nan::SetPrototypeMethod(localRef, "first", First);
          




        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("BitmapPropertySet").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      BitmapPropertySet(::Windows::Graphics::Imaging::BitmapPropertySet^ instance) {
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

      ::Windows::Graphics::Imaging::BitmapPropertySet^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapPropertySet^>(info[0])) {
        try {
          winRtInstance = (::Windows::Graphics::Imaging::BitmapPropertySet^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 0)
      {
        try {
          winRtInstance = ref new ::Windows::Graphics::Imaging::BitmapPropertySet();
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

      BitmapPropertySet *wrapperInstance = new BitmapPropertySet(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapPropertySet^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Graphics::Imaging::BitmapPropertySet^ winRtInstance;
      try {
        winRtInstance = (::Windows::Graphics::Imaging::BitmapPropertySet^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapBitmapPropertySet(winRtInstance));
    }


    static void Lookup(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapPropertySet^>(info.This())) {
        return;
      }

      BitmapPropertySet *wrapper = BitmapPropertySet::Unwrap<BitmapPropertySet>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          ::Windows::Graphics::Imaging::BitmapTypedValue^ result;
          result = wrapper->_instance->Lookup(arg0);
          info.GetReturnValue().Set(WrapBitmapTypedValue(result));
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
    static void HasKey(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapPropertySet^>(info.This())) {
        return;
      }

      BitmapPropertySet *wrapper = BitmapPropertySet::Unwrap<BitmapPropertySet>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          bool result;
          result = wrapper->_instance->HasKey(arg0);
          info.GetReturnValue().Set(Nan::New<Boolean>(result));
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
    static void GetView(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapPropertySet^>(info.This())) {
        return;
      }

      BitmapPropertySet *wrapper = BitmapPropertySet::Unwrap<BitmapPropertySet>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::Collections::IMapView<::Platform::String^, ::Windows::Graphics::Imaging::BitmapTypedValue^>^ result;
          result = wrapper->_instance->GetView();
          info.GetReturnValue().Set(NodeRT::Collections::MapViewWrapper<::Platform::String^,::Windows::Graphics::Imaging::BitmapTypedValue^>::CreateMapViewWrapper(result, 
            [](::Platform::String^ val) -> Local<Value> {
              return NodeRT::Utils::NewString(val->Data());
            },
            [](Local<Value> value) -> bool {
              return value->IsString();
            },
            [](Local<Value> value) -> ::Platform::String^ {
              return ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), value)));
            },
            [](::Windows::Graphics::Imaging::BitmapTypedValue^ val) -> Local<Value> {
              return WrapBitmapTypedValue(val);
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
    static void Insert(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapPropertySet^>(info.This())) {
        return;
      }

      BitmapPropertySet *wrapper = BitmapPropertySet::Unwrap<BitmapPropertySet>(info.This());

      if (info.Length() == 2
        && info[0]->IsString()
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapTypedValue^>(info[1]))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          ::Windows::Graphics::Imaging::BitmapTypedValue^ arg1 = UnwrapBitmapTypedValue(info[1]);
          
          bool result;
          result = wrapper->_instance->Insert(arg0, arg1);
          info.GetReturnValue().Set(Nan::New<Boolean>(result));
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
    static void Remove(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapPropertySet^>(info.This())) {
        return;
      }

      BitmapPropertySet *wrapper = BitmapPropertySet::Unwrap<BitmapPropertySet>(info.This());

      if (info.Length() == 1
        && info[0]->IsString())
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          
          wrapper->_instance->Remove(arg0);
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
    static void Clear(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapPropertySet^>(info.This())) {
        return;
      }

      BitmapPropertySet *wrapper = BitmapPropertySet::Unwrap<BitmapPropertySet>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->Clear();
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
    static void First(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapPropertySet^>(info.This())) {
        return;
      }

      BitmapPropertySet *wrapper = BitmapPropertySet::Unwrap<BitmapPropertySet>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::Collections::IIterator<::Windows::Foundation::Collections::IKeyValuePair<::Platform::String^, ::Windows::Graphics::Imaging::BitmapTypedValue^>^>^ result;
          result = wrapper->_instance->First();
          info.GetReturnValue().Set(NodeRT::Collections::IteratorWrapper<::Windows::Foundation::Collections::IKeyValuePair<::Platform::String^, ::Windows::Graphics::Imaging::BitmapTypedValue^>^>::CreateIteratorWrapper(result, 
            [](::Windows::Foundation::Collections::IKeyValuePair<::Platform::String^, ::Windows::Graphics::Imaging::BitmapTypedValue^>^ val) -> Local<Value> {
              return NodeRT::Collections::KeyValuePairWrapper<::Platform::String^,::Windows::Graphics::Imaging::BitmapTypedValue^>::CreateKeyValuePairWrapper(val, 
            [](::Platform::String^ val) -> Local<Value> {
              return NodeRT::Utils::NewString(val->Data());
            },
            [](::Windows::Graphics::Imaging::BitmapTypedValue^ val) -> Local<Value> {
              return WrapBitmapTypedValue(val);
            }
          );
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





    private:
      ::Windows::Graphics::Imaging::BitmapPropertySet^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapBitmapPropertySet(::Windows::Graphics::Imaging::BitmapPropertySet^ wintRtInstance);
      friend ::Windows::Graphics::Imaging::BitmapPropertySet^ UnwrapBitmapPropertySet(Local<Value> value);
  };

  Persistent<FunctionTemplate> BitmapPropertySet::s_constructorTemplate;

  v8::Local<v8::Value> WrapBitmapPropertySet(::Windows::Graphics::Imaging::BitmapPropertySet^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(BitmapPropertySet::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Graphics::Imaging::BitmapPropertySet^ UnwrapBitmapPropertySet(Local<Value> value) {
     return BitmapPropertySet::Unwrap<BitmapPropertySet>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitBitmapPropertySet(Local<Object> exports) {
    BitmapPropertySet::Init(exports);
  }

  class BitmapTransform : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("BitmapTransform").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("scaledWidth").ToLocalChecked(), ScaledWidthGetter, ScaledWidthSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("scaledHeight").ToLocalChecked(), ScaledHeightGetter, ScaledHeightSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("rotation").ToLocalChecked(), RotationGetter, RotationSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("interpolationMode").ToLocalChecked(), InterpolationModeGetter, InterpolationModeSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("flip").ToLocalChecked(), FlipGetter, FlipSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("bounds").ToLocalChecked(), BoundsGetter, BoundsSetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("BitmapTransform").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      BitmapTransform(::Windows::Graphics::Imaging::BitmapTransform^ instance) {
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

      ::Windows::Graphics::Imaging::BitmapTransform^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapTransform^>(info[0])) {
        try {
          winRtInstance = (::Windows::Graphics::Imaging::BitmapTransform^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 0)
      {
        try {
          winRtInstance = ref new ::Windows::Graphics::Imaging::BitmapTransform();
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

      BitmapTransform *wrapperInstance = new BitmapTransform(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapTransform^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Graphics::Imaging::BitmapTransform^ winRtInstance;
      try {
        winRtInstance = (::Windows::Graphics::Imaging::BitmapTransform^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapBitmapTransform(winRtInstance));
    }





    static void ScaledWidthGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapTransform^>(info.This())) {
        return;
      }

      BitmapTransform *wrapper = BitmapTransform::Unwrap<BitmapTransform>(info.This());

      try  {
        unsigned int result = wrapper->_instance->ScaledWidth;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ScaledWidthSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsUint32()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapTransform^>(info.This())) {
        return;
      }

      BitmapTransform *wrapper = BitmapTransform::Unwrap<BitmapTransform>(info.This());

      try {

        unsigned int winRtValue = static_cast<unsigned int>(Nan::To<uint32_t>(value).FromMaybe(0));

        wrapper->_instance->ScaledWidth = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void ScaledHeightGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapTransform^>(info.This())) {
        return;
      }

      BitmapTransform *wrapper = BitmapTransform::Unwrap<BitmapTransform>(info.This());

      try  {
        unsigned int result = wrapper->_instance->ScaledHeight;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ScaledHeightSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsUint32()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapTransform^>(info.This())) {
        return;
      }

      BitmapTransform *wrapper = BitmapTransform::Unwrap<BitmapTransform>(info.This());

      try {

        unsigned int winRtValue = static_cast<unsigned int>(Nan::To<uint32_t>(value).FromMaybe(0));

        wrapper->_instance->ScaledHeight = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void RotationGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapTransform^>(info.This())) {
        return;
      }

      BitmapTransform *wrapper = BitmapTransform::Unwrap<BitmapTransform>(info.This());

      try  {
        ::Windows::Graphics::Imaging::BitmapRotation result = wrapper->_instance->Rotation;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void RotationSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsInt32()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapTransform^>(info.This())) {
        return;
      }

      BitmapTransform *wrapper = BitmapTransform::Unwrap<BitmapTransform>(info.This());

      try {

        ::Windows::Graphics::Imaging::BitmapRotation winRtValue = static_cast<::Windows::Graphics::Imaging::BitmapRotation>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->Rotation = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void InterpolationModeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapTransform^>(info.This())) {
        return;
      }

      BitmapTransform *wrapper = BitmapTransform::Unwrap<BitmapTransform>(info.This());

      try  {
        ::Windows::Graphics::Imaging::BitmapInterpolationMode result = wrapper->_instance->InterpolationMode;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void InterpolationModeSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsInt32()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapTransform^>(info.This())) {
        return;
      }

      BitmapTransform *wrapper = BitmapTransform::Unwrap<BitmapTransform>(info.This());

      try {

        ::Windows::Graphics::Imaging::BitmapInterpolationMode winRtValue = static_cast<::Windows::Graphics::Imaging::BitmapInterpolationMode>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->InterpolationMode = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void FlipGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapTransform^>(info.This())) {
        return;
      }

      BitmapTransform *wrapper = BitmapTransform::Unwrap<BitmapTransform>(info.This());

      try  {
        ::Windows::Graphics::Imaging::BitmapFlip result = wrapper->_instance->Flip;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void FlipSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsInt32()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapTransform^>(info.This())) {
        return;
      }

      BitmapTransform *wrapper = BitmapTransform::Unwrap<BitmapTransform>(info.This());

      try {

        ::Windows::Graphics::Imaging::BitmapFlip winRtValue = static_cast<::Windows::Graphics::Imaging::BitmapFlip>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->Flip = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void BoundsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapTransform^>(info.This())) {
        return;
      }

      BitmapTransform *wrapper = BitmapTransform::Unwrap<BitmapTransform>(info.This());

      try  {
        ::Windows::Graphics::Imaging::BitmapBounds result = wrapper->_instance->Bounds;
        info.GetReturnValue().Set(BitmapBoundsToJsObject(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void BoundsSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!IsBitmapBoundsJsObject(value)) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapTransform^>(info.This())) {
        return;
      }

      BitmapTransform *wrapper = BitmapTransform::Unwrap<BitmapTransform>(info.This());

      try {

        ::Windows::Graphics::Imaging::BitmapBounds winRtValue = BitmapBoundsFromJsObject(value);

        wrapper->_instance->Bounds = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      


    private:
      ::Windows::Graphics::Imaging::BitmapTransform^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapBitmapTransform(::Windows::Graphics::Imaging::BitmapTransform^ wintRtInstance);
      friend ::Windows::Graphics::Imaging::BitmapTransform^ UnwrapBitmapTransform(Local<Value> value);
  };

  Persistent<FunctionTemplate> BitmapTransform::s_constructorTemplate;

  v8::Local<v8::Value> WrapBitmapTransform(::Windows::Graphics::Imaging::BitmapTransform^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(BitmapTransform::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Graphics::Imaging::BitmapTransform^ UnwrapBitmapTransform(Local<Value> value) {
     return BitmapTransform::Unwrap<BitmapTransform>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitBitmapTransform(Local<Object> exports) {
    BitmapTransform::Init(exports);
  }

  class BitmapTypedValue : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("BitmapTypedValue").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("type").ToLocalChecked(), TypeGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("value").ToLocalChecked(), ValueGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("BitmapTypedValue").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      BitmapTypedValue(::Windows::Graphics::Imaging::BitmapTypedValue^ instance) {
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

      ::Windows::Graphics::Imaging::BitmapTypedValue^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapTypedValue^>(info[0])) {
        try {
          winRtInstance = (::Windows::Graphics::Imaging::BitmapTypedValue^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Platform::Object^>(info[0])
        && info[1]->IsInt32())
      {
        try {
          ::Platform::Object^ arg0 = dynamic_cast<::Platform::Object^>(NodeRT::Utils::GetObjectInstance(info[0]));
          ::Windows::Foundation::PropertyType arg1 = static_cast<::Windows::Foundation::PropertyType>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          
          winRtInstance = ref new ::Windows::Graphics::Imaging::BitmapTypedValue(arg0,arg1);
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

      BitmapTypedValue *wrapperInstance = new BitmapTypedValue(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapTypedValue^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Graphics::Imaging::BitmapTypedValue^ winRtInstance;
      try {
        winRtInstance = (::Windows::Graphics::Imaging::BitmapTypedValue^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapBitmapTypedValue(winRtInstance));
    }





    static void TypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapTypedValue^>(info.This())) {
        return;
      }

      BitmapTypedValue *wrapper = BitmapTypedValue::Unwrap<BitmapTypedValue>(info.This());

      try  {
        ::Windows::Foundation::PropertyType result = wrapper->_instance->Type;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ValueGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapTypedValue^>(info.This())) {
        return;
      }

      BitmapTypedValue *wrapper = BitmapTypedValue::Unwrap<BitmapTypedValue>(info.This());

      try  {
        ::Platform::Object^ result = wrapper->_instance->Value;
        info.GetReturnValue().Set(CreateOpaqueWrapper(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Graphics::Imaging::BitmapTypedValue^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapBitmapTypedValue(::Windows::Graphics::Imaging::BitmapTypedValue^ wintRtInstance);
      friend ::Windows::Graphics::Imaging::BitmapTypedValue^ UnwrapBitmapTypedValue(Local<Value> value);
  };

  Persistent<FunctionTemplate> BitmapTypedValue::s_constructorTemplate;

  v8::Local<v8::Value> WrapBitmapTypedValue(::Windows::Graphics::Imaging::BitmapTypedValue^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(BitmapTypedValue::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Graphics::Imaging::BitmapTypedValue^ UnwrapBitmapTypedValue(Local<Value> value) {
     return BitmapTypedValue::Unwrap<BitmapTypedValue>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitBitmapTypedValue(Local<Object> exports) {
    BitmapTypedValue::Init(exports);
  }

  class IBitmapFrame : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("IBitmapFrame").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);

        Local<Function> func;
        Local<FunctionTemplate> funcTemplate;


          
            Nan::SetPrototypeMethod(localRef, "getThumbnailAsync", GetThumbnailAsync);
            Nan::SetPrototypeMethod(localRef, "getPixelDataAsync", GetPixelDataAsync);
          


          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("bitmapAlphaMode").ToLocalChecked(), BitmapAlphaModeGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("bitmapPixelFormat").ToLocalChecked(), BitmapPixelFormatGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("bitmapProperties").ToLocalChecked(), BitmapPropertiesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("dpiX").ToLocalChecked(), DpiXGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("dpiY").ToLocalChecked(), DpiYGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("orientedPixelHeight").ToLocalChecked(), OrientedPixelHeightGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("orientedPixelWidth").ToLocalChecked(), OrientedPixelWidthGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("pixelHeight").ToLocalChecked(), PixelHeightGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("pixelWidth").ToLocalChecked(), PixelWidthGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("IBitmapFrame").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      IBitmapFrame(::Windows::Graphics::Imaging::IBitmapFrame^ instance) {
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

      ::Windows::Graphics::Imaging::IBitmapFrame^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::IBitmapFrame^>(info[0])) {
        try {
          winRtInstance = (::Windows::Graphics::Imaging::IBitmapFrame^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      IBitmapFrame *wrapperInstance = new IBitmapFrame(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::IBitmapFrame^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Graphics::Imaging::IBitmapFrame^ winRtInstance;
      try {
        winRtInstance = (::Windows::Graphics::Imaging::IBitmapFrame^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapIBitmapFrame(winRtInstance));
    }

    static void GetThumbnailAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::IBitmapFrame^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      IBitmapFrame *wrapper = IBitmapFrame::Unwrap<IBitmapFrame>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Graphics::Imaging::ImageStream^>^ op;


      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->GetThumbnailAsync();
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

      opTask.then( [asyncToken] (task<::Windows::Graphics::Imaging::ImageStream^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapImageStream(result);
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
    static void GetPixelDataAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::IBitmapFrame^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      IBitmapFrame *wrapper = IBitmapFrame::Unwrap<IBitmapFrame>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Graphics::Imaging::PixelDataProvider^>^ op;


      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->GetPixelDataAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 6
        && info[0]->IsInt32()
        && info[1]->IsInt32()
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapTransform^>(info[2])
        && info[3]->IsInt32()
        && info[4]->IsInt32())
      {
        try
        {
          ::Windows::Graphics::Imaging::BitmapPixelFormat arg0 = static_cast<::Windows::Graphics::Imaging::BitmapPixelFormat>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          ::Windows::Graphics::Imaging::BitmapAlphaMode arg1 = static_cast<::Windows::Graphics::Imaging::BitmapAlphaMode>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          ::Windows::Graphics::Imaging::BitmapTransform^ arg2 = UnwrapBitmapTransform(info[2]);
          ::Windows::Graphics::Imaging::ExifOrientationMode arg3 = static_cast<::Windows::Graphics::Imaging::ExifOrientationMode>(Nan::To<int32_t>(info[3]).FromMaybe(0));
          ::Windows::Graphics::Imaging::ColorManagementMode arg4 = static_cast<::Windows::Graphics::Imaging::ColorManagementMode>(Nan::To<int32_t>(info[4]).FromMaybe(0));
          
          op = wrapper->_instance->GetPixelDataAsync(arg0,arg1,arg2,arg3,arg4);
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

      opTask.then( [asyncToken] (task<::Windows::Graphics::Imaging::PixelDataProvider^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapPixelDataProvider(result);
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




    static void BitmapAlphaModeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::IBitmapFrame^>(info.This())) {
        return;
      }

      IBitmapFrame *wrapper = IBitmapFrame::Unwrap<IBitmapFrame>(info.This());

      try  {
        ::Windows::Graphics::Imaging::BitmapAlphaMode result = wrapper->_instance->BitmapAlphaMode;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void BitmapPixelFormatGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::IBitmapFrame^>(info.This())) {
        return;
      }

      IBitmapFrame *wrapper = IBitmapFrame::Unwrap<IBitmapFrame>(info.This());

      try  {
        ::Windows::Graphics::Imaging::BitmapPixelFormat result = wrapper->_instance->BitmapPixelFormat;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void BitmapPropertiesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::IBitmapFrame^>(info.This())) {
        return;
      }

      IBitmapFrame *wrapper = IBitmapFrame::Unwrap<IBitmapFrame>(info.This());

      try  {
        ::Windows::Graphics::Imaging::BitmapPropertiesView^ result = wrapper->_instance->BitmapProperties;
        info.GetReturnValue().Set(WrapBitmapPropertiesView(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void DpiXGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::IBitmapFrame^>(info.This())) {
        return;
      }

      IBitmapFrame *wrapper = IBitmapFrame::Unwrap<IBitmapFrame>(info.This());

      try  {
        double result = wrapper->_instance->DpiX;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void DpiYGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::IBitmapFrame^>(info.This())) {
        return;
      }

      IBitmapFrame *wrapper = IBitmapFrame::Unwrap<IBitmapFrame>(info.This());

      try  {
        double result = wrapper->_instance->DpiY;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void OrientedPixelHeightGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::IBitmapFrame^>(info.This())) {
        return;
      }

      IBitmapFrame *wrapper = IBitmapFrame::Unwrap<IBitmapFrame>(info.This());

      try  {
        unsigned int result = wrapper->_instance->OrientedPixelHeight;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void OrientedPixelWidthGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::IBitmapFrame^>(info.This())) {
        return;
      }

      IBitmapFrame *wrapper = IBitmapFrame::Unwrap<IBitmapFrame>(info.This());

      try  {
        unsigned int result = wrapper->_instance->OrientedPixelWidth;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PixelHeightGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::IBitmapFrame^>(info.This())) {
        return;
      }

      IBitmapFrame *wrapper = IBitmapFrame::Unwrap<IBitmapFrame>(info.This());

      try  {
        unsigned int result = wrapper->_instance->PixelHeight;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PixelWidthGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::IBitmapFrame^>(info.This())) {
        return;
      }

      IBitmapFrame *wrapper = IBitmapFrame::Unwrap<IBitmapFrame>(info.This());

      try  {
        unsigned int result = wrapper->_instance->PixelWidth;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Graphics::Imaging::IBitmapFrame^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapIBitmapFrame(::Windows::Graphics::Imaging::IBitmapFrame^ wintRtInstance);
      friend ::Windows::Graphics::Imaging::IBitmapFrame^ UnwrapIBitmapFrame(Local<Value> value);
  };

  Persistent<FunctionTemplate> IBitmapFrame::s_constructorTemplate;

  v8::Local<v8::Value> WrapIBitmapFrame(::Windows::Graphics::Imaging::IBitmapFrame^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(IBitmapFrame::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Graphics::Imaging::IBitmapFrame^ UnwrapIBitmapFrame(Local<Value> value) {
     return IBitmapFrame::Unwrap<IBitmapFrame>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitIBitmapFrame(Local<Object> exports) {
    IBitmapFrame::Init(exports);
  }

  class IBitmapFrameWithSoftwareBitmap : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("IBitmapFrameWithSoftwareBitmap").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);

        Local<Function> func;
        Local<FunctionTemplate> funcTemplate;


          
            Nan::SetPrototypeMethod(localRef, "getSoftwareBitmapAsync", GetSoftwareBitmapAsync);
          



        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("IBitmapFrameWithSoftwareBitmap").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      IBitmapFrameWithSoftwareBitmap(::Windows::Graphics::Imaging::IBitmapFrameWithSoftwareBitmap^ instance) {
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

      ::Windows::Graphics::Imaging::IBitmapFrameWithSoftwareBitmap^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::IBitmapFrameWithSoftwareBitmap^>(info[0])) {
        try {
          winRtInstance = (::Windows::Graphics::Imaging::IBitmapFrameWithSoftwareBitmap^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      IBitmapFrameWithSoftwareBitmap *wrapperInstance = new IBitmapFrameWithSoftwareBitmap(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::IBitmapFrameWithSoftwareBitmap^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Graphics::Imaging::IBitmapFrameWithSoftwareBitmap^ winRtInstance;
      try {
        winRtInstance = (::Windows::Graphics::Imaging::IBitmapFrameWithSoftwareBitmap^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapIBitmapFrameWithSoftwareBitmap(winRtInstance));
    }

    static void GetSoftwareBitmapAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::IBitmapFrameWithSoftwareBitmap^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      IBitmapFrameWithSoftwareBitmap *wrapper = IBitmapFrameWithSoftwareBitmap::Unwrap<IBitmapFrameWithSoftwareBitmap>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Graphics::Imaging::SoftwareBitmap^>^ op;


      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->GetSoftwareBitmapAsync();
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && info[0]->IsInt32()
        && info[1]->IsInt32())
      {
        try
        {
          ::Windows::Graphics::Imaging::BitmapPixelFormat arg0 = static_cast<::Windows::Graphics::Imaging::BitmapPixelFormat>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          ::Windows::Graphics::Imaging::BitmapAlphaMode arg1 = static_cast<::Windows::Graphics::Imaging::BitmapAlphaMode>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          
          op = wrapper->_instance->GetSoftwareBitmapAsync(arg0,arg1);
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 6
        && info[0]->IsInt32()
        && info[1]->IsInt32()
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::BitmapTransform^>(info[2])
        && info[3]->IsInt32()
        && info[4]->IsInt32())
      {
        try
        {
          ::Windows::Graphics::Imaging::BitmapPixelFormat arg0 = static_cast<::Windows::Graphics::Imaging::BitmapPixelFormat>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          ::Windows::Graphics::Imaging::BitmapAlphaMode arg1 = static_cast<::Windows::Graphics::Imaging::BitmapAlphaMode>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          ::Windows::Graphics::Imaging::BitmapTransform^ arg2 = UnwrapBitmapTransform(info[2]);
          ::Windows::Graphics::Imaging::ExifOrientationMode arg3 = static_cast<::Windows::Graphics::Imaging::ExifOrientationMode>(Nan::To<int32_t>(info[3]).FromMaybe(0));
          ::Windows::Graphics::Imaging::ColorManagementMode arg4 = static_cast<::Windows::Graphics::Imaging::ColorManagementMode>(Nan::To<int32_t>(info[4]).FromMaybe(0));
          
          op = wrapper->_instance->GetSoftwareBitmapAsync(arg0,arg1,arg2,arg3,arg4);
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

      opTask.then( [asyncToken] (task<::Windows::Graphics::Imaging::SoftwareBitmap^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapSoftwareBitmap(result);
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






    private:
      ::Windows::Graphics::Imaging::IBitmapFrameWithSoftwareBitmap^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapIBitmapFrameWithSoftwareBitmap(::Windows::Graphics::Imaging::IBitmapFrameWithSoftwareBitmap^ wintRtInstance);
      friend ::Windows::Graphics::Imaging::IBitmapFrameWithSoftwareBitmap^ UnwrapIBitmapFrameWithSoftwareBitmap(Local<Value> value);
  };

  Persistent<FunctionTemplate> IBitmapFrameWithSoftwareBitmap::s_constructorTemplate;

  v8::Local<v8::Value> WrapIBitmapFrameWithSoftwareBitmap(::Windows::Graphics::Imaging::IBitmapFrameWithSoftwareBitmap^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(IBitmapFrameWithSoftwareBitmap::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Graphics::Imaging::IBitmapFrameWithSoftwareBitmap^ UnwrapIBitmapFrameWithSoftwareBitmap(Local<Value> value) {
     return IBitmapFrameWithSoftwareBitmap::Unwrap<IBitmapFrameWithSoftwareBitmap>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitIBitmapFrameWithSoftwareBitmap(Local<Object> exports) {
    IBitmapFrameWithSoftwareBitmap::Init(exports);
  }

  class IBitmapPropertiesView : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("IBitmapPropertiesView").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);

        Local<Function> func;
        Local<FunctionTemplate> funcTemplate;


          
            Nan::SetPrototypeMethod(localRef, "getPropertiesAsync", GetPropertiesAsync);
          



        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("IBitmapPropertiesView").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      IBitmapPropertiesView(::Windows::Graphics::Imaging::IBitmapPropertiesView^ instance) {
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

      ::Windows::Graphics::Imaging::IBitmapPropertiesView^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::IBitmapPropertiesView^>(info[0])) {
        try {
          winRtInstance = (::Windows::Graphics::Imaging::IBitmapPropertiesView^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      IBitmapPropertiesView *wrapperInstance = new IBitmapPropertiesView(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::IBitmapPropertiesView^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Graphics::Imaging::IBitmapPropertiesView^ winRtInstance;
      try {
        winRtInstance = (::Windows::Graphics::Imaging::IBitmapPropertiesView^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapIBitmapPropertiesView(winRtInstance));
    }

    static void GetPropertiesAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::IBitmapPropertiesView^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      IBitmapPropertiesView *wrapper = IBitmapPropertiesView::Unwrap<IBitmapPropertiesView>(info.This());

      ::Windows::Foundation::IAsyncOperation<::Windows::Graphics::Imaging::BitmapPropertySet^>^ op;


      if (info.Length() == 2
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
          
          op = wrapper->_instance->GetPropertiesAsync(arg0);
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

      opTask.then( [asyncToken] (task<::Windows::Graphics::Imaging::BitmapPropertySet^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapBitmapPropertySet(result);
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






    private:
      ::Windows::Graphics::Imaging::IBitmapPropertiesView^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapIBitmapPropertiesView(::Windows::Graphics::Imaging::IBitmapPropertiesView^ wintRtInstance);
      friend ::Windows::Graphics::Imaging::IBitmapPropertiesView^ UnwrapIBitmapPropertiesView(Local<Value> value);
  };

  Persistent<FunctionTemplate> IBitmapPropertiesView::s_constructorTemplate;

  v8::Local<v8::Value> WrapIBitmapPropertiesView(::Windows::Graphics::Imaging::IBitmapPropertiesView^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(IBitmapPropertiesView::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Graphics::Imaging::IBitmapPropertiesView^ UnwrapIBitmapPropertiesView(Local<Value> value) {
     return IBitmapPropertiesView::Unwrap<IBitmapPropertiesView>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitIBitmapPropertiesView(Local<Object> exports) {
    IBitmapPropertiesView::Init(exports);
  }

  class ImageStream : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("ImageStream").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);

        Local<Function> func;
        Local<FunctionTemplate> funcTemplate;

          
            Nan::SetPrototypeMethod(localRef, "getInputStreamAt", GetInputStreamAt);
            Nan::SetPrototypeMethod(localRef, "getOutputStreamAt", GetOutputStreamAt);
            Nan::SetPrototypeMethod(localRef, "seek", Seek);
            Nan::SetPrototypeMethod(localRef, "cloneStream", CloneStream);
            Nan::SetPrototypeMethod(localRef, "close", Close);
          

          
            Nan::SetPrototypeMethod(localRef, "readAsync", ReadAsync);
            Nan::SetPrototypeMethod(localRef, "writeAsync", WriteAsync);
            Nan::SetPrototypeMethod(localRef, "flushAsync", FlushAsync);
          


          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("contentType").ToLocalChecked(), ContentTypeGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("size").ToLocalChecked(), SizeGetter, SizeSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("canRead").ToLocalChecked(), CanReadGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("canWrite").ToLocalChecked(), CanWriteGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("position").ToLocalChecked(), PositionGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("ImageStream").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      ImageStream(::Windows::Graphics::Imaging::ImageStream^ instance) {
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

      ::Windows::Graphics::Imaging::ImageStream^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::ImageStream^>(info[0])) {
        try {
          winRtInstance = (::Windows::Graphics::Imaging::ImageStream^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      ImageStream *wrapperInstance = new ImageStream(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::ImageStream^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Graphics::Imaging::ImageStream^ winRtInstance;
      try {
        winRtInstance = (::Windows::Graphics::Imaging::ImageStream^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapImageStream(winRtInstance));
    }

    static void ReadAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::ImageStream^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      ImageStream *wrapper = ImageStream::Unwrap<ImageStream>(info.This());

      ::Windows::Foundation::IAsyncOperationWithProgress<::Windows::Storage::Streams::IBuffer^, unsigned int>^ op;


      if (info.Length() == 4
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(info[0])
        && info[1]->IsUint32()
        && info[2]->IsInt32())
      {
        try
        {
          ::Windows::Storage::Streams::IBuffer^ arg0 = dynamic_cast<::Windows::Storage::Streams::IBuffer^>(NodeRT::Utils::GetObjectInstance(info[0]));
          unsigned int arg1 = static_cast<unsigned int>(Nan::To<uint32_t>(info[1]).FromMaybe(0));
          ::Windows::Storage::Streams::InputStreamOptions arg2 = static_cast<::Windows::Storage::Streams::InputStreamOptions>(Nan::To<int32_t>(info[2]).FromMaybe(0));
          
          op = wrapper->_instance->ReadAsync(arg0,arg1,arg2);
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

      opTask.then( [asyncToken] (task<::Windows::Storage::Streams::IBuffer^> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.Streams", "IBuffer", result);
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
    static void WriteAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::ImageStream^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      ImageStream *wrapper = ImageStream::Unwrap<ImageStream>(info.This());

      ::Windows::Foundation::IAsyncOperationWithProgress<unsigned int, unsigned int>^ op;


      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(info[0]))
      {
        try
        {
          ::Windows::Storage::Streams::IBuffer^ arg0 = dynamic_cast<::Windows::Storage::Streams::IBuffer^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          op = wrapper->_instance->WriteAsync(arg0);
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

      opTask.then( [asyncToken] (task<unsigned int> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = Nan::New<Integer>(result);
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
    static void FlushAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::ImageStream^>(info.This())) {
        return;
      }

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      ImageStream *wrapper = ImageStream::Unwrap<ImageStream>(info.This());

      ::Windows::Foundation::IAsyncOperation<bool>^ op;


      if (info.Length() == 1)
      {
        try
        {
          op = wrapper->_instance->FlushAsync();
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

      opTask.then( [asyncToken] (task<bool> t) {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = Nan::New<Boolean>(result);
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

    static void GetInputStreamAt(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::ImageStream^>(info.This())) {
        return;
      }

      ImageStream *wrapper = ImageStream::Unwrap<ImageStream>(info.This());

      if (info.Length() == 1
        && info[0]->IsNumber())
      {
        try
        {
          unsigned __int64 arg0 = static_cast<unsigned __int64>(Nan::To<int64_t>(info[0]).FromMaybe(0));
          
          ::Windows::Storage::Streams::IInputStream^ result;
          result = wrapper->_instance->GetInputStreamAt(arg0);
          info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.Streams", "IInputStream", result));
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
    static void GetOutputStreamAt(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::ImageStream^>(info.This())) {
        return;
      }

      ImageStream *wrapper = ImageStream::Unwrap<ImageStream>(info.This());

      if (info.Length() == 1
        && info[0]->IsNumber())
      {
        try
        {
          unsigned __int64 arg0 = static_cast<unsigned __int64>(Nan::To<int64_t>(info[0]).FromMaybe(0));
          
          ::Windows::Storage::Streams::IOutputStream^ result;
          result = wrapper->_instance->GetOutputStreamAt(arg0);
          info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.Streams", "IOutputStream", result));
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
    static void Seek(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::ImageStream^>(info.This())) {
        return;
      }

      ImageStream *wrapper = ImageStream::Unwrap<ImageStream>(info.This());

      if (info.Length() == 1
        && info[0]->IsNumber())
      {
        try
        {
          unsigned __int64 arg0 = static_cast<unsigned __int64>(Nan::To<int64_t>(info[0]).FromMaybe(0));
          
          wrapper->_instance->Seek(arg0);
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
    static void CloneStream(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::ImageStream^>(info.This())) {
        return;
      }

      ImageStream *wrapper = ImageStream::Unwrap<ImageStream>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Storage::Streams::IRandomAccessStream^ result;
          result = wrapper->_instance->CloneStream();
          info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.Streams", "IRandomAccessStream", result));
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

    static void Close(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::ImageStream^>(info.This())) {
        return;
      }

      ImageStream *wrapper = ImageStream::Unwrap<ImageStream>(info.This());

      if (info.Length() == 0) {
        try {
          delete wrapper->_instance;
          wrapper->_instance = nullptr;
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      } else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void ContentTypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::ImageStream^>(info.This())) {
        return;
      }

      ImageStream *wrapper = ImageStream::Unwrap<ImageStream>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->ContentType;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void SizeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::ImageStream^>(info.This())) {
        return;
      }

      ImageStream *wrapper = ImageStream::Unwrap<ImageStream>(info.This());

      try  {
        unsigned __int64 result = wrapper->_instance->Size;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void SizeSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsNumber()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::ImageStream^>(info.This())) {
        return;
      }

      ImageStream *wrapper = ImageStream::Unwrap<ImageStream>(info.This());

      try {

        unsigned __int64 winRtValue = static_cast<unsigned __int64>(Nan::To<int64_t>(value).FromMaybe(0));

        wrapper->_instance->Size = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void CanReadGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::ImageStream^>(info.This())) {
        return;
      }

      ImageStream *wrapper = ImageStream::Unwrap<ImageStream>(info.This());

      try  {
        bool result = wrapper->_instance->CanRead;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void CanWriteGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::ImageStream^>(info.This())) {
        return;
      }

      ImageStream *wrapper = ImageStream::Unwrap<ImageStream>(info.This());

      try  {
        bool result = wrapper->_instance->CanWrite;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PositionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::ImageStream^>(info.This())) {
        return;
      }

      ImageStream *wrapper = ImageStream::Unwrap<ImageStream>(info.This());

      try  {
        unsigned __int64 result = wrapper->_instance->Position;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Graphics::Imaging::ImageStream^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapImageStream(::Windows::Graphics::Imaging::ImageStream^ wintRtInstance);
      friend ::Windows::Graphics::Imaging::ImageStream^ UnwrapImageStream(Local<Value> value);
  };

  Persistent<FunctionTemplate> ImageStream::s_constructorTemplate;

  v8::Local<v8::Value> WrapImageStream(::Windows::Graphics::Imaging::ImageStream^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(ImageStream::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Graphics::Imaging::ImageStream^ UnwrapImageStream(Local<Value> value) {
     return ImageStream::Unwrap<ImageStream>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitImageStream(Local<Object> exports) {
    ImageStream::Init(exports);
  }

  class PixelDataProvider : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("PixelDataProvider").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "detachPixelData", DetachPixelData);
          




        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("PixelDataProvider").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      PixelDataProvider(::Windows::Graphics::Imaging::PixelDataProvider^ instance) {
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

      ::Windows::Graphics::Imaging::PixelDataProvider^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::PixelDataProvider^>(info[0])) {
        try {
          winRtInstance = (::Windows::Graphics::Imaging::PixelDataProvider^) NodeRT::Utils::GetObjectInstance(info[0]);
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

      PixelDataProvider *wrapperInstance = new PixelDataProvider(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::PixelDataProvider^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Graphics::Imaging::PixelDataProvider^ winRtInstance;
      try {
        winRtInstance = (::Windows::Graphics::Imaging::PixelDataProvider^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapPixelDataProvider(winRtInstance));
    }


    static void DetachPixelData(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::PixelDataProvider^>(info.This())) {
        return;
      }

      PixelDataProvider *wrapper = PixelDataProvider::Unwrap<PixelDataProvider>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Platform::Array<unsigned char>^ result;
          result = wrapper->_instance->DetachPixelData();
          info.GetReturnValue().Set(NodeRT::Collections::ArrayWrapper<unsigned char>::CreateArrayWrapper(result, 
            [](unsigned char val) -> Local<Value> {
              return Nan::New<Integer>(val);
            },
            [](Local<Value> value) -> bool {
              return value->IsInt32();
            },
            [](Local<Value> value) -> unsigned char {
              return static_cast<unsigned char>(Nan::To<int32_t>(value).FromMaybe(0));
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





    private:
      ::Windows::Graphics::Imaging::PixelDataProvider^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapPixelDataProvider(::Windows::Graphics::Imaging::PixelDataProvider^ wintRtInstance);
      friend ::Windows::Graphics::Imaging::PixelDataProvider^ UnwrapPixelDataProvider(Local<Value> value);
  };

  Persistent<FunctionTemplate> PixelDataProvider::s_constructorTemplate;

  v8::Local<v8::Value> WrapPixelDataProvider(::Windows::Graphics::Imaging::PixelDataProvider^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(PixelDataProvider::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Graphics::Imaging::PixelDataProvider^ UnwrapPixelDataProvider(Local<Value> value) {
     return PixelDataProvider::Unwrap<PixelDataProvider>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitPixelDataProvider(Local<Object> exports) {
    PixelDataProvider::Init(exports);
  }

  class SoftwareBitmap : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("SoftwareBitmap").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);

        Local<Function> func;
        Local<FunctionTemplate> funcTemplate;

          
            Nan::SetPrototypeMethod(localRef, "lockBuffer", LockBuffer);
            Nan::SetPrototypeMethod(localRef, "copyTo", CopyTo);
            Nan::SetPrototypeMethod(localRef, "copyFromBuffer", CopyFromBuffer);
            Nan::SetPrototypeMethod(localRef, "copyToBuffer", CopyToBuffer);
            Nan::SetPrototypeMethod(localRef, "getReadOnlyView", GetReadOnlyView);
            Nan::SetPrototypeMethod(localRef, "close", Close);
          



          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("dpiY").ToLocalChecked(), DpiYGetter, DpiYSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("dpiX").ToLocalChecked(), DpiXGetter, DpiXSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("bitmapAlphaMode").ToLocalChecked(), BitmapAlphaModeGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("bitmapPixelFormat").ToLocalChecked(), BitmapPixelFormatGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isReadOnly").ToLocalChecked(), IsReadOnlyGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("pixelHeight").ToLocalChecked(), PixelHeightGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("pixelWidth").ToLocalChecked(), PixelWidthGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);

        Nan::SetMethod(constructor, "copy", Copy);
        Nan::SetMethod(constructor, "convert", Convert);
        Nan::SetMethod(constructor, "createCopyFromBuffer", CreateCopyFromBuffer);
        func = Nan::GetFunction(Nan::New<FunctionTemplate>(CreateCopyFromSurfaceAsync)).ToLocalChecked();
        Nan::Set(constructor, Nan::New<String>("createCopyFromSurfaceAsync").ToLocalChecked(), func);


        Nan::Set(exports, Nan::New<String>("SoftwareBitmap").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      SoftwareBitmap(::Windows::Graphics::Imaging::SoftwareBitmap^ instance) {
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

      ::Windows::Graphics::Imaging::SoftwareBitmap^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::SoftwareBitmap^>(info[0])) {
        try {
          winRtInstance = (::Windows::Graphics::Imaging::SoftwareBitmap^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && info[0]->IsInt32()
        && info[1]->IsInt32()
        && info[2]->IsInt32())
      {
        try {
          ::Windows::Graphics::Imaging::BitmapPixelFormat arg0 = static_cast<::Windows::Graphics::Imaging::BitmapPixelFormat>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          int arg1 = static_cast<int>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          int arg2 = static_cast<int>(Nan::To<int32_t>(info[2]).FromMaybe(0));
          
          winRtInstance = ref new ::Windows::Graphics::Imaging::SoftwareBitmap(arg0,arg1,arg2);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 4
        && info[0]->IsInt32()
        && info[1]->IsInt32()
        && info[2]->IsInt32()
        && info[3]->IsInt32())
      {
        try {
          ::Windows::Graphics::Imaging::BitmapPixelFormat arg0 = static_cast<::Windows::Graphics::Imaging::BitmapPixelFormat>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          int arg1 = static_cast<int>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          int arg2 = static_cast<int>(Nan::To<int32_t>(info[2]).FromMaybe(0));
          ::Windows::Graphics::Imaging::BitmapAlphaMode arg3 = static_cast<::Windows::Graphics::Imaging::BitmapAlphaMode>(Nan::To<int32_t>(info[3]).FromMaybe(0));
          
          winRtInstance = ref new ::Windows::Graphics::Imaging::SoftwareBitmap(arg0,arg1,arg2,arg3);
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

      SoftwareBitmap *wrapperInstance = new SoftwareBitmap(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::SoftwareBitmap^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Graphics::Imaging::SoftwareBitmap^ winRtInstance;
      try {
        winRtInstance = (::Windows::Graphics::Imaging::SoftwareBitmap^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapSoftwareBitmap(winRtInstance));
    }


    static void LockBuffer(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::SoftwareBitmap^>(info.This())) {
        return;
      }

      SoftwareBitmap *wrapper = SoftwareBitmap::Unwrap<SoftwareBitmap>(info.This());

      if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try
        {
          ::Windows::Graphics::Imaging::BitmapBufferAccessMode arg0 = static_cast<::Windows::Graphics::Imaging::BitmapBufferAccessMode>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          ::Windows::Graphics::Imaging::BitmapBuffer^ result;
          result = wrapper->_instance->LockBuffer(arg0);
          info.GetReturnValue().Set(WrapBitmapBuffer(result));
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

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::SoftwareBitmap^>(info.This())) {
        return;
      }

      SoftwareBitmap *wrapper = SoftwareBitmap::Unwrap<SoftwareBitmap>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::SoftwareBitmap^>(info[0]))
      {
        try
        {
          ::Windows::Graphics::Imaging::SoftwareBitmap^ arg0 = UnwrapSoftwareBitmap(info[0]);
          
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
    static void CopyFromBuffer(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::SoftwareBitmap^>(info.This())) {
        return;
      }

      SoftwareBitmap *wrapper = SoftwareBitmap::Unwrap<SoftwareBitmap>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(info[0]))
      {
        try
        {
          ::Windows::Storage::Streams::IBuffer^ arg0 = dynamic_cast<::Windows::Storage::Streams::IBuffer^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          wrapper->_instance->CopyFromBuffer(arg0);
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
    static void CopyToBuffer(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::SoftwareBitmap^>(info.This())) {
        return;
      }

      SoftwareBitmap *wrapper = SoftwareBitmap::Unwrap<SoftwareBitmap>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(info[0]))
      {
        try
        {
          ::Windows::Storage::Streams::IBuffer^ arg0 = dynamic_cast<::Windows::Storage::Streams::IBuffer^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          wrapper->_instance->CopyToBuffer(arg0);
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
    static void GetReadOnlyView(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::SoftwareBitmap^>(info.This())) {
        return;
      }

      SoftwareBitmap *wrapper = SoftwareBitmap::Unwrap<SoftwareBitmap>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Graphics::Imaging::SoftwareBitmap^ result;
          result = wrapper->_instance->GetReadOnlyView();
          info.GetReturnValue().Set(WrapSoftwareBitmap(result));
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

    static void Close(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::SoftwareBitmap^>(info.This())) {
        return;
      }

      SoftwareBitmap *wrapper = SoftwareBitmap::Unwrap<SoftwareBitmap>(info.This());

      if (info.Length() == 0) {
        try {
          delete wrapper->_instance;
          wrapper->_instance = nullptr;
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      } else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }


    static void CreateCopyFromSurfaceAsync(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 0 || !info[info.Length() -1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: No callback was given")));
        return;
      }

      ::Windows::Foundation::IAsyncOperation<::Windows::Graphics::Imaging::SoftwareBitmap^>^ op;


      if (info.Length() == 2
          && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::DirectX::Direct3D11::IDirect3DSurface^>(info[0]))
      {
        try
        {
          ::Windows::Graphics::DirectX::Direct3D11::IDirect3DSurface^ arg0 = dynamic_cast<::Windows::Graphics::DirectX::Direct3D11::IDirect3DSurface^>(NodeRT::Utils::GetObjectInstance(info[0]));
            
          op = ::Windows::Graphics::Imaging::SoftwareBitmap::CreateCopyFromSurfaceAsync(arg0);
        } catch (Platform::Exception ^exception) {
            NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
            return;
        }
      }
      else if (info.Length() == 3
          && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::DirectX::Direct3D11::IDirect3DSurface^>(info[0])
          && info[1]->IsInt32())
      {
        try
        {
          ::Windows::Graphics::DirectX::Direct3D11::IDirect3DSurface^ arg0 = dynamic_cast<::Windows::Graphics::DirectX::Direct3D11::IDirect3DSurface^>(NodeRT::Utils::GetObjectInstance(info[0]));
          ::Windows::Graphics::Imaging::BitmapAlphaMode arg1 = static_cast<::Windows::Graphics::Imaging::BitmapAlphaMode>(Nan::To<int32_t>(info[1]).FromMaybe(0));
            
          op = ::Windows::Graphics::Imaging::SoftwareBitmap::CreateCopyFromSurfaceAsync(arg0,arg1);
        } catch (Platform::Exception ^exception) {
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

      opTask.then( [asyncToken] (task<::Windows::Graphics::Imaging::SoftwareBitmap^> t)
      {
        try {
          auto result = t.get();
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [result](NodeUtils::InvokeCallbackDelegate invokeCallback) {


            Local<Value> error;
            Local<Value> arg1;
            {
              TryCatch tryCatch;
              arg1 = WrapSoftwareBitmap(result);
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
        }
        catch (Platform::Exception^ exception)
        {
          NodeUtils::Async::RunCallbackOnMain(asyncToken, [exception](NodeUtils::InvokeCallbackDelegate invokeCallback) {

            Local<Value> error = NodeRT::Utils::WinRtExceptionToJsError(exception);

            Local<Value> args[] = {error};
            invokeCallback(_countof(args), args);
          });
        }
      });
    }


    static void Copy(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::SoftwareBitmap^>(info[0]))
      {
        try
        {
          ::Windows::Graphics::Imaging::SoftwareBitmap^ arg0 = UnwrapSoftwareBitmap(info[0]);
          
          ::Windows::Graphics::Imaging::SoftwareBitmap^ result;
          result = ::Windows::Graphics::Imaging::SoftwareBitmap::Copy(arg0);
          info.GetReturnValue().Set(WrapSoftwareBitmap(result));
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

    static void Convert(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::SoftwareBitmap^>(info[0])
        && info[1]->IsInt32())
      {
        try
        {
          ::Windows::Graphics::Imaging::SoftwareBitmap^ arg0 = UnwrapSoftwareBitmap(info[0]);
          ::Windows::Graphics::Imaging::BitmapPixelFormat arg1 = static_cast<::Windows::Graphics::Imaging::BitmapPixelFormat>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          
          ::Windows::Graphics::Imaging::SoftwareBitmap^ result;
          result = ::Windows::Graphics::Imaging::SoftwareBitmap::Convert(arg0, arg1);
          info.GetReturnValue().Set(WrapSoftwareBitmap(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::SoftwareBitmap^>(info[0])
        && info[1]->IsInt32()
        && info[2]->IsInt32())
      {
        try
        {
          ::Windows::Graphics::Imaging::SoftwareBitmap^ arg0 = UnwrapSoftwareBitmap(info[0]);
          ::Windows::Graphics::Imaging::BitmapPixelFormat arg1 = static_cast<::Windows::Graphics::Imaging::BitmapPixelFormat>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          ::Windows::Graphics::Imaging::BitmapAlphaMode arg2 = static_cast<::Windows::Graphics::Imaging::BitmapAlphaMode>(Nan::To<int32_t>(info[2]).FromMaybe(0));
          
          ::Windows::Graphics::Imaging::SoftwareBitmap^ result;
          result = ::Windows::Graphics::Imaging::SoftwareBitmap::Convert(arg0, arg1, arg2);
          info.GetReturnValue().Set(WrapSoftwareBitmap(result));
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

    static void CreateCopyFromBuffer(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 4
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(info[0])
        && info[1]->IsInt32()
        && info[2]->IsInt32()
        && info[3]->IsInt32())
      {
        try
        {
          ::Windows::Storage::Streams::IBuffer^ arg0 = dynamic_cast<::Windows::Storage::Streams::IBuffer^>(NodeRT::Utils::GetObjectInstance(info[0]));
          ::Windows::Graphics::Imaging::BitmapPixelFormat arg1 = static_cast<::Windows::Graphics::Imaging::BitmapPixelFormat>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          int arg2 = static_cast<int>(Nan::To<int32_t>(info[2]).FromMaybe(0));
          int arg3 = static_cast<int>(Nan::To<int32_t>(info[3]).FromMaybe(0));
          
          ::Windows::Graphics::Imaging::SoftwareBitmap^ result;
          result = ::Windows::Graphics::Imaging::SoftwareBitmap::CreateCopyFromBuffer(arg0, arg1, arg2, arg3);
          info.GetReturnValue().Set(WrapSoftwareBitmap(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 5
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IBuffer^>(info[0])
        && info[1]->IsInt32()
        && info[2]->IsInt32()
        && info[3]->IsInt32()
        && info[4]->IsInt32())
      {
        try
        {
          ::Windows::Storage::Streams::IBuffer^ arg0 = dynamic_cast<::Windows::Storage::Streams::IBuffer^>(NodeRT::Utils::GetObjectInstance(info[0]));
          ::Windows::Graphics::Imaging::BitmapPixelFormat arg1 = static_cast<::Windows::Graphics::Imaging::BitmapPixelFormat>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          int arg2 = static_cast<int>(Nan::To<int32_t>(info[2]).FromMaybe(0));
          int arg3 = static_cast<int>(Nan::To<int32_t>(info[3]).FromMaybe(0));
          ::Windows::Graphics::Imaging::BitmapAlphaMode arg4 = static_cast<::Windows::Graphics::Imaging::BitmapAlphaMode>(Nan::To<int32_t>(info[4]).FromMaybe(0));
          
          ::Windows::Graphics::Imaging::SoftwareBitmap^ result;
          result = ::Windows::Graphics::Imaging::SoftwareBitmap::CreateCopyFromBuffer(arg0, arg1, arg2, arg3, arg4);
          info.GetReturnValue().Set(WrapSoftwareBitmap(result));
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

    static void DpiYGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::SoftwareBitmap^>(info.This())) {
        return;
      }

      SoftwareBitmap *wrapper = SoftwareBitmap::Unwrap<SoftwareBitmap>(info.This());

      try  {
        double result = wrapper->_instance->DpiY;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void DpiYSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsNumber()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::SoftwareBitmap^>(info.This())) {
        return;
      }

      SoftwareBitmap *wrapper = SoftwareBitmap::Unwrap<SoftwareBitmap>(info.This());

      try {

        double winRtValue = Nan::To<double>(value).FromMaybe(0.0);

        wrapper->_instance->DpiY = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void DpiXGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::SoftwareBitmap^>(info.This())) {
        return;
      }

      SoftwareBitmap *wrapper = SoftwareBitmap::Unwrap<SoftwareBitmap>(info.This());

      try  {
        double result = wrapper->_instance->DpiX;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void DpiXSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsNumber()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::SoftwareBitmap^>(info.This())) {
        return;
      }

      SoftwareBitmap *wrapper = SoftwareBitmap::Unwrap<SoftwareBitmap>(info.This());

      try {

        double winRtValue = Nan::To<double>(value).FromMaybe(0.0);

        wrapper->_instance->DpiX = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void BitmapAlphaModeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::SoftwareBitmap^>(info.This())) {
        return;
      }

      SoftwareBitmap *wrapper = SoftwareBitmap::Unwrap<SoftwareBitmap>(info.This());

      try  {
        ::Windows::Graphics::Imaging::BitmapAlphaMode result = wrapper->_instance->BitmapAlphaMode;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void BitmapPixelFormatGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::SoftwareBitmap^>(info.This())) {
        return;
      }

      SoftwareBitmap *wrapper = SoftwareBitmap::Unwrap<SoftwareBitmap>(info.This());

      try  {
        ::Windows::Graphics::Imaging::BitmapPixelFormat result = wrapper->_instance->BitmapPixelFormat;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void IsReadOnlyGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::SoftwareBitmap^>(info.This())) {
        return;
      }

      SoftwareBitmap *wrapper = SoftwareBitmap::Unwrap<SoftwareBitmap>(info.This());

      try  {
        bool result = wrapper->_instance->IsReadOnly;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PixelHeightGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::SoftwareBitmap^>(info.This())) {
        return;
      }

      SoftwareBitmap *wrapper = SoftwareBitmap::Unwrap<SoftwareBitmap>(info.This());

      try  {
        int result = wrapper->_instance->PixelHeight;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PixelWidthGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::Imaging::SoftwareBitmap^>(info.This())) {
        return;
      }

      SoftwareBitmap *wrapper = SoftwareBitmap::Unwrap<SoftwareBitmap>(info.This());

      try  {
        int result = wrapper->_instance->PixelWidth;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Graphics::Imaging::SoftwareBitmap^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapSoftwareBitmap(::Windows::Graphics::Imaging::SoftwareBitmap^ wintRtInstance);
      friend ::Windows::Graphics::Imaging::SoftwareBitmap^ UnwrapSoftwareBitmap(Local<Value> value);
  };

  Persistent<FunctionTemplate> SoftwareBitmap::s_constructorTemplate;

  v8::Local<v8::Value> WrapSoftwareBitmap(::Windows::Graphics::Imaging::SoftwareBitmap^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(SoftwareBitmap::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Graphics::Imaging::SoftwareBitmap^ UnwrapSoftwareBitmap(Local<Value> value) {
     return SoftwareBitmap::Unwrap<SoftwareBitmap>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitSoftwareBitmap(Local<Object> exports) {
    SoftwareBitmap::Init(exports);
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

      NodeRT::Windows::Graphics::Imaging::InitBitmapAlphaModeEnum(target);
      NodeRT::Windows::Graphics::Imaging::InitBitmapBufferAccessModeEnum(target);
      NodeRT::Windows::Graphics::Imaging::InitBitmapFlipEnum(target);
      NodeRT::Windows::Graphics::Imaging::InitBitmapInterpolationModeEnum(target);
      NodeRT::Windows::Graphics::Imaging::InitBitmapPixelFormatEnum(target);
      NodeRT::Windows::Graphics::Imaging::InitBitmapRotationEnum(target);
      NodeRT::Windows::Graphics::Imaging::InitColorManagementModeEnum(target);
      NodeRT::Windows::Graphics::Imaging::InitExifOrientationModeEnum(target);
      NodeRT::Windows::Graphics::Imaging::InitJpegSubsamplingModeEnum(target);
      NodeRT::Windows::Graphics::Imaging::InitPngFilterModeEnum(target);
      NodeRT::Windows::Graphics::Imaging::InitTiffCompressionModeEnum(target);
      NodeRT::Windows::Graphics::Imaging::InitBitmapBuffer(target);
      NodeRT::Windows::Graphics::Imaging::InitBitmapCodecInformation(target);
      NodeRT::Windows::Graphics::Imaging::InitBitmapDecoder(target);
      NodeRT::Windows::Graphics::Imaging::InitBitmapEncoder(target);
      NodeRT::Windows::Graphics::Imaging::InitBitmapFrame(target);
      NodeRT::Windows::Graphics::Imaging::InitBitmapProperties(target);
      NodeRT::Windows::Graphics::Imaging::InitBitmapPropertiesView(target);
      NodeRT::Windows::Graphics::Imaging::InitBitmapPropertySet(target);
      NodeRT::Windows::Graphics::Imaging::InitBitmapTransform(target);
      NodeRT::Windows::Graphics::Imaging::InitBitmapTypedValue(target);
      NodeRT::Windows::Graphics::Imaging::InitIBitmapFrame(target);
      NodeRT::Windows::Graphics::Imaging::InitIBitmapFrameWithSoftwareBitmap(target);
      NodeRT::Windows::Graphics::Imaging::InitIBitmapPropertiesView(target);
      NodeRT::Windows::Graphics::Imaging::InitImageStream(target);
      NodeRT::Windows::Graphics::Imaging::InitPixelDataProvider(target);
      NodeRT::Windows::Graphics::Imaging::InitSoftwareBitmap(target);


  NodeRT::Utils::RegisterNameSpace("Windows.Graphics.Imaging", target);
}



NODE_MODULE(binding, init)
