#pragma once
#include <Windows.h>
#include <string>

namespace WPSProfileVerificationPatch {
    struct IFunctionHook {
        virtual void LocateTarget() = 0;
        virtual PVOID* GetOriginalPointer() = 0;
        virtual PVOID GetDetourFunction() = 0;
        virtual const char* GetName() const = 0;
    };
}
