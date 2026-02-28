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

        void LocateTarget() override;
        PVOID* GetOriginalPointer() override;
        PVOID GetDetourFunction() override;
        const char* GetName() const override;
    };
}
