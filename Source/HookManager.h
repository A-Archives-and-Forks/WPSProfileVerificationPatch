#pragma once
#include <vector>
#include <memory>
#include "IFunctionHook.h"

namespace WPSProfileVerificationPatch {
    class HookManager {
    public:
        static size_t InstallHooks(const std::vector<std::unique_ptr<IFunctionHook>>& hooks);
        static size_t UninstallHooks(const std::vector<std::unique_ptr<IFunctionHook>>& hooks);
    };
}
