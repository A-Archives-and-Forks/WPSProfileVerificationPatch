#include <Windows.h>
#include <memory>
#include <stdexcept>
#include "CreateFileHook.h"
#include "ModuleUtil.h"
#include "FileUtil.h"

namespace WPSProfileVerificationPatch {
    HANDLE(WINAPI* CreateFileHook::createFileW)(LPCWSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE) = nullptr;

    static bool IsProductDatW(LPCWSTR fileName) {
        if (!fileName) {
            return false;
        }

        constexpr const wchar_t target[] = L"product.dat";
        constexpr size_t targetLen = sizeof(target) / sizeof(wchar_t) - 1;

        size_t inputLen = std::wcslen(fileName);
        if (inputLen < targetLen) {
            return false;
        }

        LPCWSTR tail = fileName + (inputLen - targetLen);
        return std::wmemcmp(tail, target, targetLen) == 0;
    }

    HANDLE WINAPI CreateFileHook::CreateFileW(
        LPCWSTR lpFileName,
        DWORD dwDesiredAccess,
        DWORD dwShareMode,
        LPSECURITY_ATTRIBUTES lpSecurityAttributes,
        DWORD dwCreationDisposition,
        DWORD dwFlagsAndAttributes,
        HANDLE hTemplateFile
    ) {
        if (dwDesiredAccess & GENERIC_WRITE && IsProductDatW(lpFileName)) {
            HMODULE module = ModuleUtil::GetSelfHandle();
            std::wstring productDatPath = ModuleUtil::GetBasePathW(module) + L"product.dat";
            if (FileUtil::IsFileExistsW(productDatPath)) {
                CopyFileW(productDatPath.data(), lpFileName, FALSE);
                return INVALID_HANDLE_VALUE;
            }
        }

        return createFileW(
            lpFileName,
            dwDesiredAccess,
            dwShareMode,
            lpSecurityAttributes,
            dwCreationDisposition,
            dwFlagsAndAttributes,
            hTemplateFile
        );
    }

    void CreateFileHook::LocateTarget() {
        HMODULE kernel32 = GetModuleHandleW(L"kernel32.dll");
        if (!kernel32) {
            throw std::runtime_error("Failed to get kernel32.dll handle");
        }

        FARPROC addressW = GetProcAddress(kernel32, "CreateFileW");
        if (!addressW) {
            throw std::runtime_error("Failed to find CreateFileW");
        }

        createFileW = reinterpret_cast<decltype(createFileW)>(addressW);
    }

    PVOID* CreateFileHook::GetOriginalPointer() {
        return reinterpret_cast<PVOID*>(&createFileW);
    }

    PVOID CreateFileHook::GetDetourFunction() {
        return reinterpret_cast<PVOID>(&CreateFileW);
    }

    const char* CreateFileHook::GetName() const {
        return "CreateFile";
    }
}
