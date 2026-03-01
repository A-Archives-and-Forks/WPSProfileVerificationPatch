#pragma once
#include <string>
#include "IFunctionHook.h"

namespace WPSProfileVerificationPatch {
    class CreateFileHook : public IFunctionHook {
    public:
        static HANDLE(WINAPI* createFileW)(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);

        static HANDLE WINAPI CreateFileW(
            LPCWSTR lpFileName,
            DWORD dwDesiredAccess,
            DWORD dwShareMode,
            LPSECURITY_ATTRIBUTES lpSecurityAttributes,
            DWORD dwCreationDisposition,
            DWORD dwFlagsAndAttributes,
            HANDLE hTemplateFile
        );

        void LocateTarget() const override;
        PVOID* GetOriginalPointer() const override;
        PVOID GetDetourFunction() const override;
        const char* GetName() const override;
    };
}
