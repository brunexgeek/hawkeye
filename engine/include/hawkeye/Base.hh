#ifndef BASE_H_
#define BASE_H_

// Common
#ifndef NULL
#define NULL     0
#endif

namespace hawkeye
{
/**
 * Print logging (implemented per platform).
 * @script{ignore}
 */
extern void print(const char* format, ...);

// Define a platform-independent case-insensitive ASCII string comparison function.
extern int strcmpnocase(const char* s1, const char* s2);
}

// Current function macro.
#ifdef WIN32
#define __current__func__ __FUNCTION__
#else
#define __current__func__ __func__
#endif

// Assert macros.
#ifdef _DEBUG
#define GP_ASSERT(expression) assert(expression)
#else
#define GP_ASSERT(expression)
#endif

#if defined(WIN32) && defined(_MSC_VER)
#define DEBUG_BREAK() __debugbreak()
#else
#define DEBUG_BREAK()
#endif

// Error macro.
#ifdef GP_ERRORS_AS_WARNINGS
#define GP_ERROR GP_WARN
#else
#define GP_ERROR(...) do \
    { \
        hawkeye::Logger::log(hawkeye::Logger::LEVEL_ERROR, "%s -- ", __current__func__); \
        hawkeye::Logger::log(hawkeye::Logger::LEVEL_ERROR, __VA_ARGS__); \
        hawkeye::Logger::log(hawkeye::Logger::LEVEL_ERROR, "\n"); \
        DEBUG_BREAK(); \
        assert(0); \
        std::exit(-1); \
    } while (0)
#endif

// Warning macro.
#define GP_WARN(...) do \
    { \
        hawkeye::Logger::log(hawkeye::Logger::LEVEL_WARN, "%s -- ", __current__func__); \
        hawkeye::Logger::log(hawkeye::Logger::LEVEL_WARN, __VA_ARGS__); \
        hawkeye::Logger::log(hawkeye::Logger::LEVEL_WARN, "\n"); \
    } while (0)

#if defined(WIN32)
    #pragma warning( disable : 4005 )
    #pragma warning( disable : 4172 )
    #pragma warning( disable : 4244 )
    #pragma warning( disable : 4267 )
    #pragma warning( disable : 4311 )
    #pragma warning( disable : 4316 )
    #pragma warning( disable : 4390 )
    #pragma warning( disable : 4800 )
    #pragma warning( disable : 4996 )
#endif


// Debug new for memory leak detection
//#include <hawkeye/DebugNew.hh>

// Object deletion macro
#define SAFE_DELETE(x) \
    { \
        delete x; \
        x = NULL; \
    }

// Array deletion macro
#define SAFE_DELETE_ARRAY(x) \
    { \
        delete[] x; \
        x = NULL; \
    }

// Ref cleanup macro
#define SAFE_RELEASE(x) \
    if (x) \
    { \
        (x)->release(); \
        x = NULL; \
    }

// Math
#define MATH_DEG_TO_RAD(x)          ((x) * 0.0174532925f)
#define MATH_RAD_TO_DEG(x)          ((x)* 57.29577951f)
#define MATH_RANDOM_MINUS1_1()      ((2.0f*((float)rand()/RAND_MAX))-1.0f)      // Returns a random float between -1 and 1.
#define MATH_RANDOM_0_1()           ((float)rand()/RAND_MAX)                    // Returns a random float between 0 and 1.
#define MATH_FLOAT_SMALL            1.0e-37f
#define MATH_TOLERANCE              2e-37f
#define MATH_E                      2.71828182845904523536f
#define MATH_LOG10E                 0.4342944819032518f
#define MATH_LOG2E                  1.442695040888963387f
#define MATH_PI                     3.14159265358979323846f
#define MATH_PIOVER2                1.57079632679489661923f
#define MATH_PIOVER4                0.785398163397448309616f
#define MATH_PIX2                   6.28318530717958647693f
#define MATH_EPSILON                0.000001f
#define MATH_CLAMP(x, lo, hi)       ((x < lo) ? lo : ((x > hi) ? hi : x))
#ifndef M_1_PI
#define M_1_PI                      0.31830988618379067154
#endif

// NOMINMAX makes sure that windef.h doesn't add macros min and max
#ifdef WIN32
    #define NOMINMAX
#endif


#define WINDOW_VSYNC        1

// Hardware buffer
namespace hawkeye
{
/** Gamepad handle */
#ifdef __ANDROID__
typedef unsigned int GamepadHandle;
#else
typedef unsigned long GamepadHandle;
#endif
}


#endif
