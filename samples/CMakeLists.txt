include(BuildHelpers.CMakeLists.txt)

include_directories(
	"${CMAKE_SOURCE_DIR}/engine/include"
	"${CMAKE_SOURCE_DIR}/3rd-party/include")


if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    find_package(OpenGL REQUIRED)
    FIND_LIBRARY(AGL_LIBRARY AGL)
    FIND_LIBRARY(APP_SERVICES_LIBRARY ApplicationServices )
    FIND_LIBRARY(ATBOX_LIBRARY AudioToolbox)
    FIND_LIBRARY(CARBON_LIBRARY Carbon)
    FIND_LIBRARY(CAUDIO_LIBRARY CoreAudio)
    FIND_LIBRARY(COREVIDEO_LIBRARY CoreVideo)
    FIND_LIBRARY(CFOUNDATION_LIBRARY CoreFoundation)
    FIND_LIBRARY(CSERVICES_LIBRARY CoreServices)
    FIND_LIBRARY(OPENGL_LIBRARY OpenGL)
    FIND_LIBRARY(QUICKTIME_LIBRARY QuickTime )
    FIND_LIBRARY(IOKIT_LIBRARY IOKit )
    FIND_LIBRARY(AVF_LIBRARY AVFoundation)
    FIND_LIBRARY(OAL_LIBRARY OpenAL)
    FIND_LIBRARY(GKIT_LIBRARY GameKit)
    SET(FRAMEWORK_LIBRS
            ${AGL_LIBRARY}
            ${APP_SERVICES_LIBRARY}
            ${ATBOX_LIBRARY}
            ${CARBON_LIBRARY}
            ${CAUDIO_LIBRARY}
            ${COREVIDEO_LIBRARY}
            ${CFOUNDATION_LIBRARY}
            ${CSERVICES_LIBRARY}
            ${OAL_LIBRARY}
            ${OPENGL_LIBRARIES}
            ${GKIT_LIBRARY}
            ${IOKIT_LIBRARY}
            "-framework Foundation"
            "-framework Cocoa")
    link_directories(${CMAKE_SOURCE_DIR}/external-deps/lib/macosx/x86_64)
    set(GAMEPLAY_LIBRARIES
            stdc++
            hawkeye
            gameplay-deps
            m
            dl
            pthread
            ${FRAMEWORK_LIBRS}
            )
ELSE(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    add_definitions(-D__linux__)

    IF(ARCH_DIR STREQUAL "x64")
        link_directories("${CMAKE_CURRENT_BINARY_DIR}/../engine")
        link_directories("${CMAKE_CURRENT_BINARY_DIR}/..")
    ELSE()
        link_directories("${CMAKE_CURRENT_BINARY_DIR}/../engine")
        link_directories("${CMAKE_CURRENT_BINARY_DIR}/..")
    ENDIF()

    set(GAMEPLAY_LIBRARIES
            stdc++
            engine
            hawkeye-deps
            m
            GL
            rt
            dl
            X11
            pthread
            glib-2.0
            )
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

add_subdirectory(browser)
