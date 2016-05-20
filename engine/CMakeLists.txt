IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(HAWKEYE_PLATFORM_SRC
            src/PlatformMacOSX.mm
            src/gameplay-main-macosx.mm
            )
else(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(HAWKEYE_PLATFORM_SRC )
endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

file(GLOB HAWKEYE_SRC
    "source/*.cc"
    "source/pal/*.cc"
)

set(HAWKEYE_RES
    res/logo_black.png
    res/logo_powered_black.png
    res/logo_powered_white.png
    res/logo_white.png
)

set(HAWKEYE_RES_SHADERS
    res/shaders/colored.frag
    res/shaders/colored.vert
    res/shaders/font.frag
    res/shaders/font.vert
    res/shaders/form.frag
    res/shaders/form.vert
    res/shaders/lighting.frag
    res/shaders/lighting.vert
    res/shaders/skinning.vert
    res/shaders/skinning-none.vert
    res/shaders/sprite.frag
    res/shaders/sprite.vert
    res/shaders/terrain.frag
    res/shaders/terrain.vert
    res/shaders/textured.frag
    res/shaders/textured.vert
)

set(HAWKEYE_RES_UI
    res/ui/arial.gpb
    res/ui/default.png
    res/ui/default.theme
)

include_directories(
    "include/hawkeye"
    "include"
	${HAWKEYE_DEPS_INCLUDES}
)

IF(CMAKE_SYSTEM_NAME MATCHES "Linux")
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK2 REQUIRED gtk+-2.0)
include_directories(${GTK2_INCLUDE_DIRS})
add_definitions(${GTK2_CFLAGS_OTHER})
add_definitions(-D__linux__)
ENDIF(CMAKE_SYSTEM_NAME MATCHES "Linux")


add_library(engine STATIC ${HAWKEYE_SRC})

set_target_properties(engine PROPERTIES
    OUTPUT_NAME "hawkeye"
    CLEAN_DIRECT_OUTPUT 1
    VERSION ${HAWKEYE_VERSION}
)
