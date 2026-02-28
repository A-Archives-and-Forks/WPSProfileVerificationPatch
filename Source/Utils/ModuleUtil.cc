#include <Windows.h>
#include <Psapi.h>
#include <stdexcept>
#include "ModuleUtil.h"

namespace WPSProfileVerificationPatch {
    HMODULE ModuleUtil::GetHandleA(const std::optional<const std::string>& moduleName) {
        HMODULE module = GetModuleHandleA(moduleName ? moduleName->data() : nullptr);
        if (module == nullptr) {
            throw std::runtime_error("Failed to get module handle");
        }
        return module;
    }

    HMODULE ModuleUtil::GetHandleW(const std::optional<const std::wstring>& moduleName) {
        HMODULE module = GetModuleHandleW(moduleName ? moduleName->data() : nullptr);
        if (module == nullptr) {
            throw std::runtime_error("Failed to get module handle");
        }
        return module;
    }

    HMODULE ModuleUtil::GetSelfHandle() {
        MEMORY_BASIC_INFORMATION memoryBasicInfo;
        if (!VirtualQuery(ModuleUtil::GetSelfHandle, &memoryBasicInfo, sizeof(memoryBasicInfo))) {
            throw std::runtime_error("Failed to get self module handle");
        }
        return reinterpret_cast<HMODULE>(memoryBasicInfo.AllocationBase);
    }

    uint32_t ModuleUtil::GetSizeOfMemory(HMODULE module) {
        if (module == nullptr) {
            module = GetHandleW(std::nullopt);
        }
        MODULEINFO moduleInfo;
        if (!GetModuleInformation(GetCurrentProcess(), module, &moduleInfo, sizeof(moduleInfo))) {
            throw std::runtime_error("Failed to get module information");
        }
        return moduleInfo.SizeOfImage;
    }

    std::string ModuleUtil::GetFileNameA(HMODULE module) {
        std::string buffer(MAX_PATH, 0);
        DWORD retSize = GetModuleFileNameA(module, buffer.data(), MAX_PATH);
        if (retSize == 0 || retSize >= MAX_PATH) {
            throw std::runtime_error("Failed to get program file name");
        }
        buffer.resize(retSize);
        return buffer;
    }

    std::wstring ModuleUtil::GetFileNameW(HMODULE module) {
        std::wstring buffer(MAX_PATH, 0);
        DWORD retSize = GetModuleFileNameW(module, buffer.data(), MAX_PATH);
        if (retSize == 0 || retSize >= MAX_PATH) {
            throw std::runtime_error("Failed to get program file name");
        }
        buffer.resize(retSize);
        return buffer;
    }

    std::string ModuleUtil::GetBasePathA(HMODULE module) {
        std::string fileName = GetFileNameA(module);
        size_t position = fileName.find_last_of("\\");
        if (position == std::string::npos) {
            throw std::runtime_error("Failed to get program base path");
        }
        fileName.resize(position + 1);
        return fileName;
    }

    std::wstring ModuleUtil::GetBasePathW(HMODULE module) {
        std::wstring fileName = GetFileNameW(module);
        size_t position = fileName.find_last_of(L"\\");
        if (position == std::wstring::npos) {
            throw std::runtime_error("Failed to get program base path");
        }
        fileName.resize(position + 1);
        return fileName;
    }
}
