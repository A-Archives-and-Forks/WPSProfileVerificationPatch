#pragma once
#include <vector>
#include <memory>
#include "IFunctionHook.h"

namespace WPSProfileVerificationPatch {
    class HookManager {
    public:
        static void InstallHooks(const std::vector<std::unique_ptr<IFunctionHook>>& hooks);
        static void UninstallHooks(const std::vector<std::unique_ptr<IFunctionHook>>& hooks);
    };
}
