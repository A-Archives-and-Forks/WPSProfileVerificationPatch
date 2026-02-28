#include <Windows.h>
#include <detours.h>
#include <stdexcept>
#include <sstream>
#include "HookManager.h"

namespace WPSProfileVerificationPatch {
    void HookManager::InstallHooks(const std::vector<std::unique_ptr<IFunctionHook>>& hooks) {
        if (hooks.size() == 0) {
            return;
        }

        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());

        for (auto& hook : hooks) {
            try {
                hook->LocateTarget();
            } catch (const std::exception& e) {
#if defined WP_DEBUG
                MessageBoxA(nullptr, e.what(), (std::string("Hook Locate Failed: ") + hook->GetName()).c_str(), MB_ICONSTOP);
#endif
                continue;
            }

            PVOID* originalPointer = hook->GetOriginalPointer();

            if (*originalPointer == nullptr) {
                continue;
            }

            DetourAttach(originalPointer, hook->GetDetourFunction());
        }

        LONG result = DetourTransactionCommit();

        if (result != NO_ERROR) {
#if defined WP_DEBUG
            std::stringstream ss;
            ss << "Failed to install hooks, error: " << result;
            MessageBoxA(nullptr, ss.str().c_str(), "Hook Install Failed", MB_ICONSTOP);
#endif
        }
    }

    void HookManager::UninstallHooks(const std::vector<std::unique_ptr<IFunctionHook>>& hooks) {
        if (hooks.size() == 0) {
            return;
        }

        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());

        for (auto& hook : hooks) {
            PVOID* originalPointer = hook->GetOriginalPointer();

            if (*originalPointer == nullptr) {
                continue;
            }

            DetourDetach(originalPointer, hook->GetDetourFunction());
        }

        LONG result = DetourTransactionCommit();

        if (result != NO_ERROR) {
#if defined WP_DEBUG
            std::stringstream ss;
            ss << "Failed to uninstall hooks, error: " << result;
            MessageBoxA(nullptr, ss.str().c_str(), "Hook Uninstall Failed", MB_ICONSTOP);
#endif
        }
    }
}
