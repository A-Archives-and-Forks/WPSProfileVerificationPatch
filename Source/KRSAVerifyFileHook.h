#pragma once
#include <Windows.h>
#include <string>
#include "IFunctionHook.h"

namespace WPSProfileVerificationPatch {
    class KRSAVerifyFileHook : public IFunctionHook {
    public:
        static bool (*kRSAVerifyFile)(const std::string&, const std::string&, const std::string&);

        static bool KRSAVerifyFile(const std::string& publicKey, const std::string& fileHash, const std::string& fileSignature);

        void LocateTarget() override;
        PVOID* GetOriginalPointer() override;
        PVOID GetDetourFunction() override;
        const char* GetName() const override;
    };
}
