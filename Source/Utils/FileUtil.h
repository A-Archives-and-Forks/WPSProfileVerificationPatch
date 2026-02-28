#pragma once
#include <string>

namespace WPSProfileVerificationPatch {
    class FileUtil {
    private:
        FileUtil() = delete;

    public:
        static bool IsFileExistsA(const std::string& filePath);
        static bool IsFileExistsW(const std::wstring& filePath);
    };
}
