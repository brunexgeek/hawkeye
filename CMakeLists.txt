cmake_minimum_required(VERSION 2.8)

project(Hawkeye)

set(HAWKEYE_VERSION 1.0.0)
set(CMAKE_C_COMPILER_INIT g++)

# debug
message( "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}" )
if ( "${CMAKE_BUILD_TYPE}" STREQUAL "DEBUG" )
    add_definitions(-D_DEBUG)
endif()

# architecture
if ( CMAKE_SIZEOF_VOID_P EQUAL 8 )
set(ARCH_DIR "x64")
else()
set(ARCH_DIR "x86")
endif()

if (UNIX)
    set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -Wl,--no-undefined -fPIC -Werror=return-type -Werror=implicit-function-declaration -std=gnu99")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--no-undefined -fPIC -Werror=return-type -Werror=implicit-function-declaration -std=c++11")
    # Parâmetros para o modo Release
    set(CMAKE_C_FLAGS_RELEASE  "${CMAKE_C_FLAGS_RELEASE} -g -O3")
    set(CMAKE_CXX_FLAGS_RELEASE  "${CMAKE_CXX_FLAGS_RELEASE} -g -O3")
	# Parâmetros para o modo Debug
    set(CMAKE_C_FLAGS_DEBUG  "${CMAKE_C_FLAGS_DEBUG} -O0")
    set(CMAKE_CXX_FLAGS_DEBUG  "${CMAKE_CXX_FLAGS_DEBUG} -O0")
endif()

add_subdirectory(engine)
add_subdirectory(samples)


message("")
message("  ======== Compilation =======")
message("      Root directory: ${ROOT_DIRECTORY}")

if (CMAKE_CXX_COMPILER_VERSION)
    set(TEMP_COMPILER_STR "${CMAKE_CXX_COMPILER} ${CMAKE_CXX_COMPILER_ARG1} (ver ${CMAKE_CXX_COMPILER_VERSION})")
elseif(CMAKE_COMPILER_IS_CLANGCXX)
    set(TEMP_COMPILER_STR "${CMAKE_CXX_COMPILER} ${CMAKE_CXX_COMPILER_ARG1} (ver ${CMAKE_CLANG_REGEX_VERSION})")
elseif(CMAKE_COMPILER_IS_GNUCXX)
    set(TEMP_COMPILER_STR "${CMAKE_CXX_COMPILER} ${CMAKE_CXX_COMPILER_ARG1} (ver ${CMAKE_GCC_REGEX_VERSION})")
else()
    set(TEMP_COMPILER_STR "${CMAKE_CXX_COMPILER} ${CMAKE_CXX_COMPILER_ARG1}")
endif()
string(STRIP "${TEMP_COMPILER_STR}" TEMP_COMPILER_STR)
message("        C++ Compiler:  ${TEMP_COMPILER_STR}")
message(" C++ flags (Release):  ${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE}")
message("   C++ flags (Debug):   ${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG}")
message("          C Compiler:  ${CMAKE_C_COMPILER} ${CMAKE_C_COMPILER_ARG1}")
message("   C flags (Release):  ${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_RELEASE}")
message("     C flags (Debug):  ${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_DEBUG}")
if(WIN32)
    message("  LD flags (Release): ${CMAKE_EXE_LINKER_FLAGS} ${CMAKE_EXE_LINKER_FLAGS_RELEASE}")
    message("    LD flags (Debug):   ${CMAKE_EXE_LINKER_FLAGS} ${CMAKE_EXE_LINKER_FLAGS_DEBUG}")
else()
    message("  LD flags (Release): ${CMAKE_SHARED_LINKER_FLAGS} ${CMAKE_SHARED_LINKER_FLAGS_RELEASE}")
    message("    LD flags (Debug):   ${CMAKE_SHARED_LINKER_FLAGS} ${CMAKE_SHARED_LINKER_FLAGS_DEBUG}")
endif()
message("")
