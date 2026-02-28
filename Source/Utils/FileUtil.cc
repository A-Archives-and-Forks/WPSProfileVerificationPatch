#include <Windows.h>
#include "FileUtil.h"

namespace WPSProfileVerificationPatch {
    bool FileUtil::IsFileExistsA(const std::string& filePath) {
        DWORD attributes = GetFileAttributesA(filePath.data());
        return (attributes != INVALID_FILE_ATTRIBUTES && !(attributes & FILE_ATTRIBUTE_DIRECTORY));
    }

    bool FileUtil::IsFileExistsW(const std::wstring& filePath) {
        DWORD attributes = GetFileAttributesW(filePath.data());
        return (attributes != INVALID_FILE_ATTRIBUTES && !(attributes & FILE_ATTRIBUTE_DIRECTORY));
    }
}
