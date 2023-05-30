﻿#pragma once

#include "GarbageCollection/TGarbageCollectionHandle.h"

template <typename T>
TGarbageCollectionHandle<T>::TGarbageCollectionHandle():
	Handle(T())
{
}

template <typename T>
TGarbageCollectionHandle<T>::TGarbageCollectionHandle(const T& InHandle):
	Handle(InHandle)
{
}

template <typename T>
TGarbageCollectionHandle<T>::operator T() const
{
	return Handle;
}

template <typename T>
TGarbageCollectionHandle<T>::operator MonoObject*() const
{
	return FCSharpEnvironment::GetEnvironment().GetDomain()->GCHandle_Get_Target_V2(Handle);
}

template <typename T>
bool TGarbageCollectionHandle<T>::operator==(const TGarbageCollectionHandle& Other) const
{
	return static_cast<MonoObject*>(*this) == static_cast<MonoObject*>(Other);
}

template <typename T>
bool TGarbageCollectionHandle<T>::operator!=(const TGarbageCollectionHandle& Other) const
{
	return !(*this == Other);
}

template <typename T>
bool TGarbageCollectionHandle<T>::IsValid() const
{
	return Handle != T();
}

template <typename T>
TGarbageCollectionHandle<T> TGarbageCollectionHandle<T>::NewRef(MonoObject* InMonoObject, const mono_bool bPinned)
{
	return FCSharpEnvironment::GetEnvironment().GetDomain()->GCHandle_New_V2(InMonoObject, bPinned);
}

template <typename T>
TGarbageCollectionHandle<T> TGarbageCollectionHandle<T>::NewWeakRef(MonoObject* InMonoObject,
                                                                    const mono_bool bTrackResurrection)
{
	return FCSharpEnvironment::GetEnvironment().GetDomain()->GCHandle_New_WeakRef_V2(InMonoObject, bTrackResurrection);
}

template <typename T>
void TGarbageCollectionHandle<T>::Free(TGarbageCollectionHandle& InGarbageCollectionHandle)
{
	FCSharpEnvironment::GetEnvironment().GetDomain()->GCHandle_Free_V2(InGarbageCollectionHandle);

	InGarbageCollectionHandle = T();
}
