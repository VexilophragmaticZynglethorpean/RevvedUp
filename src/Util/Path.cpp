#include <Util/Path.h>

#ifdef _WIN32
#include <windows.h>
#elif __APPLE__
#include <mach-o/dyld.h>
#elif __linux__
#include <unistd.h>
#include <limits.h>
#endif

std::filesystem::path Util::getExecutablePath() {
    char path[1024];

#ifdef _WIN32
    GetModuleFileNameA(NULL, path, sizeof(path));
#elif __APPLE__
    uint32_t size = sizeof(path);
    if (_NSGetExecutablePath(path, &size) != 0) {
        return "";
    }
#elif __linux__
    ssize_t count = readlink("/proc/self/exe", path, sizeof(path) - 1);
    if (count == -1) {
        return "";
    }
    path[count] = '\0';
#endif

    return std::filesystem::path(path).parent_path();
}
