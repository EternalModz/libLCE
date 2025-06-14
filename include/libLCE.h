//
// Created by DexrnZacAttack on 12/31/2024.
//
#pragma once

#include <cstdint>
#include <iostream>
#include <string>
#include <chrono>

namespace lce::system {
    inline std::uint64_t getTimestamp() {
        auto now = std::chrono::system_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
        return ms;
    }
}

#ifdef __EMSCRIPTEN__
    #define LIBLCE_API
    #define NO_DISCARD __attribute__((used))
#elif defined(LIBLCE_EXPORTS)
    #if defined(__GNUC__) || defined(__clang__)
        #define NO_DISCARD __attribute__((used))
        #define LIBLCE_API __attribute__((visibility("default")))
    #else
        #define NO_DISCARD __declspec(noinline)
        #define LIBLCE_API __declspec(dllexport)
    #endif
#else
    #if defined(__GNUC__) || defined(__clang__)
        #define NO_DISCARD __attribute__((used))
        #define LIBLCE_API __attribute__((visibility("default")))
    #else
        #define NO_DISCARD __declspec(noinline)
        #define LIBLCE_API __declspec(dllimport)
    #endif
#endif

/// FAKE 24 BIT TYPE
typedef uint32_t uint24_t;
/// SIGNED FAKE 24 BIT TYPE
typedef int32_t int24_t;

#ifdef CMAKE_BUILD_DEBUG
/* Only gets the filename instead of full file path */
#define FILE_NAME (__FILE__ + std::string(__FILE__).find_last_of("\\/") + 1)
/* Logs only when built in Debug, includes filename, function, and line number. IDEs such as CLion will let you click on the filename:line to jump to that line in the file. */
#define DebugLog(...) std::cout << "[" << __func__ << " - " << FILE_NAME << ":" << __LINE__ << "] " << __VA_ARGS__ << std::endl
/* Logs only when built in Debug, includes filename, function, and line number. IDEs such as CLion will let you click on the filename:line to jump to that line in the file. */
#define DebugLogW(...) std::wcout << L"[" << __func__ << L" - " << FILE_NAME << L":" << __LINE__ << L"] " << __VA_ARGS__ << std::endl
/* Logs only when built in Debug, includes filename, function, and line number. IDEs such as CLion will let you click on the filename:line to jump to that line in the file. */
#define DebugErrLog(...) std::cerr << "[" << __func__ << " - " << FILE_NAME << ":" << __LINE__ << "] " << __VA_ARGS__ << std::endl
/* Logs only when built in Debug, includes filename, function, and line number. IDEs such as CLion will let you click on the filename:line to jump to that line in the file. */
#define DebugErrLogW(...) std::wcerr << L"[" << __func__ << L" - " << FILE_NAME << L":" << __LINE__ << L"] " << __VA_ARGS__ << std::endl
#else
/* Logs only when built in Debug, includes filename, function, and line number. IDEs such as CLion will let you click on the filename:line to jump to that line in the file. */
#define DebugLog(...)
/* Logs only when built in Debug, includes filename, function, and line number. IDEs such as CLion will let you click on the filename:line to jump to that line in the file. */
#define DebugLogW(...)
/* Logs only when built in Debug, includes filename, function, and line number. IDEs such as CLion will let you click on the filename:line to jump to that line in the file. */
#define DebugErrLog(...)
/* Logs only when built in Debug, includes filename, function, and line number. IDEs such as CLion will let you click on the filename:line to jump to that line in the file. */
#define DebugErrLogW(...)
#endif
