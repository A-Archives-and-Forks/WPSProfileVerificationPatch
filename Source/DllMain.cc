#include <Windows.h>
#include <vector>
#include <memory>
#include "ProxyLibrary.h"
#include "HookManager.h"
#include "KRSAVerifyFileHook.h"
#include "CreateFileHook.h"

static std::vector<std::unique_ptr<WPSProfileVerificationPatch::IFunctionHook>> hooks;

BOOL APIENTRY DllMain(HMODULE module, DWORD reasonForCall, LPVOID reserved) {
    switch (reasonForCall) {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(module);
            ProxyLibrary_Load();
            hooks.push_back(std::make_unique<WPSProfileVerificationPatch::KRSAVerifyFileHook>());
#if defined WP_PACKET
            hooks.push_back(std::make_unique<WPSProfileVerificationPatch::CreateFileHook>());
#endif
            WPSProfileVerificationPatch::HookManager::InstallHooks(hooks);
            break;
        case DLL_PROCESS_DETACH:
            WPSProfileVerificationPatch::HookManager::UninstallHooks(hooks);
            hooks.clear();
            ProxyLibrary_Unload();
            break;
    }
    return TRUE;
}
