/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef mozilla_RegistryMessageUtils_h
#define mozilla_RegistryMessageUtils_h

#include "ipc/IPCMessageUtils.h"
#include "nsStringGlue.h"

struct SerializedURI
{
  nsCString spec;
  nsCString charset;
};

struct ChromePackage
{
  nsCString package;
  SerializedURI contentBaseURI;
  SerializedURI localeBaseURI;
  SerializedURI skinBaseURI;
  uint32_t flags;
};

struct ResourceMapping
{
  nsCString resource;
  SerializedURI resolvedURI;
};

struct OverrideMapping
{
  SerializedURI originalURI;
  SerializedURI overrideURI;
};

namespace IPC {

template<>
struct ParamTraits<SerializedURI>
{
  typedef SerializedURI paramType;

  static void Write(Message* aMsg, const paramType& aParam)
  {
    WriteParam(aMsg, aParam.spec);
    WriteParam(aMsg, aParam.charset);
  }

  static bool Read(const Message* aMsg, void** aIter, paramType* aResult)
  {
    nsCString spec, charset;
    if (ReadParam(aMsg, aIter, &spec) &&
        ReadParam(aMsg, aIter, &charset)) {
      aResult->spec = spec;
      aResult->charset = charset;
      return true;
    }
    return false;
  }
};
  
template <>
struct ParamTraits<ChromePackage>
{
  typedef ChromePackage paramType;
  
  static void Write(Message* aMsg, const paramType& aParam)
  {
    WriteParam(aMsg, aParam.package);
    WriteParam(aMsg, aParam.contentBaseURI);
    WriteParam(aMsg, aParam.localeBaseURI);
    WriteParam(aMsg, aParam.skinBaseURI);
    WriteParam(aMsg, aParam.flags);
  }
  
  static bool Read(const Message* aMsg, void** aIter, paramType* aResult)
  {
    nsCString package;
    SerializedURI contentBaseURI, localeBaseURI, skinBaseURI;
    uint32_t flags;
    
    if (ReadParam(aMsg, aIter, &package) &&
        ReadParam(aMsg, aIter, &contentBaseURI) &&
        ReadParam(aMsg, aIter, &localeBaseURI) &&
        ReadParam(aMsg, aIter, &skinBaseURI) &&
        ReadParam(aMsg, aIter, &flags)) {
      aResult->package = package;
      aResult->contentBaseURI = contentBaseURI;
      aResult->localeBaseURI = localeBaseURI;
      aResult->skinBaseURI = skinBaseURI;
      aResult->flags = flags;
      return true;
    }
    return false;
  }

  static void Log(const paramType& aParam, std::wstring* aLog)
  {
    aLog->append(StringPrintf(L"[%s, %s, %s, %s, %u]", aParam.package.get(),
                             aParam.contentBaseURI.spec.get(),
                             aParam.localeBaseURI.spec.get(),
                             aParam.skinBaseURI.spec.get(), aParam.flags));
  }
};

template <>
struct ParamTraits<ResourceMapping>
{
  typedef ResourceMapping paramType;
  
  static void Write(Message* aMsg, const paramType& aParam)
  {
    WriteParam(aMsg, aParam.resource);
    WriteParam(aMsg, aParam.resolvedURI);
  }
  
  static bool Read(const Message* aMsg, void** aIter, paramType* aResult)
  {
    nsCString resource;
    SerializedURI resolvedURI;
    
    if (ReadParam(aMsg, aIter, &resource) &&
        ReadParam(aMsg, aIter, &resolvedURI)) {
      aResult->resource = resource;
      aResult->resolvedURI = resolvedURI;
      return true;
    }
    return false;
  }

  static void Log(const paramType& aParam, std::wstring* aLog)
  {
    aLog->append(StringPrintf(L"[%s, %s, %u]", aParam.resource.get(),
                             aParam.resolvedURI.spec.get()));
  }
};

template <>
struct ParamTraits<OverrideMapping>
{
  typedef OverrideMapping paramType;
  
  static void Write(Message* aMsg, const paramType& aParam)
  {
    WriteParam(aMsg, aParam.originalURI);
    WriteParam(aMsg, aParam.overrideURI);
  }
  
  static bool Read(const Message* aMsg, void** aIter, paramType* aResult)
  {
    SerializedURI originalURI;
    SerializedURI overrideURI;
    
    if (ReadParam(aMsg, aIter, &originalURI) &&
        ReadParam(aMsg, aIter, &overrideURI)) {
      aResult->originalURI = originalURI;
      aResult->overrideURI = overrideURI;
      return true;
    }
    return false;
  }

  static void Log(const paramType& aParam, std::wstring* aLog)
  {
    aLog->append(StringPrintf(L"[%s, %s, %u]", aParam.originalURI.spec.get(),
                             aParam.overrideURI.spec.get()));
  }
};

}

#endif // RegistryMessageUtils_h
