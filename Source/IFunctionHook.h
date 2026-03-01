#pragma once
#include <Windows.h>
#include <string>

namespace WPSProfileVerificationPatch {
    struct IFunctionHook {
        virtual void LocateTarget() const = 0;
        virtual PVOID* GetOriginalPointer() const = 0;
        virtual PVOID GetDetourFunction() const = 0;
        virtual const char* GetName() const = 0;
    };
}
