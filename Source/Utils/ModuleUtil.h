#pragma once
#include <optional>
#include <cstdint>
#include <string>

namespace WPSProfileVerificationPatch {
    class ModuleUtil {
    private:
        ModuleUtil() = delete;

    public:
        static HMODULE GetHandleA(const std::optional<const std::string>& moduleName = std::nullopt);
        static HMODULE GetHandleW(const std::optional<const std::wstring>& moduleName = std::nullopt);
        static HMODULE GetSelfHandle();
        static uint32_t GetSizeOfMemory(HMODULE module = nullptr);
        static std::string GetFileNameA(HMODULE module = nullptr);
        static std::wstring GetFileNameW(HMODULE module = nullptr);
        static std::string GetBasePathA(HMODULE module = nullptr);
        static std::wstring GetBasePathW(HMODULE module = nullptr);
    };
}
