set(GAME_NAME sample-browser)

file(GLOB GAME_SRC
    "src/*.cc"
)


include_directories(
	"../../engine/include/hawkeye"
	"../../3rd-party/glew-1.10.0/include"
    "../../3rd-party/bullet-2.82-r2704/src"
    "../../3rd-party/vorbis-1.3.4/include"
    "../../3rd-party/ogg-1.3.2/include"
    "../../3rd-party/base64-1.0.0"
    "../../3rd-party/libjson-7.6.1"
    "../../3rd-party/png-1.6.15"
	"../../3rd-party/zlib-1.2.8/"
	"../../3rd-party/openal-1.16.0/include")


if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    MESSAGE("Game name is ${GAME_NAME}")
    COPY_RES_MAC(GAME_RES ${CMAKE_SOURCE_DIR}/samples/browser res/*)
    COPY_RES_MAC(GAMEPLAY_RES ${CMAKE_SOURCE_DIR}/gameplay
            res/shaders/* res/ui/* res/logo_powered_white.png)
    set(Apple_Resources
            ${GAME_RES}
            ${GAMEPLAY_RES}
            game.config)
    SET(EXEC_TYPE MACOSX_BUNDLE)

    SET_SOURCE_FILES_PROPERTIES(
            game.config
            PROPERTIES
            MACOSX_PACKAGE_LOCATION Resources
    )
    set( MACOSX_BUNDLE_INFO_STRING "\"${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}\",\nCopyright 2016 gameplay3d contributors" )
    set( MACOSX_BUNDLE_SHORT_VERSION_STRING "${VERSION_MAJOR}.${VERSION_MINOR}" )
    set( MACOSX_BUNDLE_LONG_VERSION_STRING "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}" )
    set( MACOSX_BUNDLE_BUNDLE_VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}" )
    set( MACOSX_BUNDLE_COPYRIGHT "(C) gameplay3d contributors" )
    set( PLIST_TEMPLATE ${GAME_NAME}-macosx.plist )
endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

add_executable(${GAME_NAME} ${EXEC_TYPE}
        ${GAME_SRC}
        ${Apple_Resources}
        )

target_link_libraries(${GAME_NAME} ${GAMEPLAY_LIBRARIES})


set_target_properties(${GAME_NAME} PROPERTIES
    OUTPUT_NAME "${GAME_NAME}"
    CLEAN_DIRECT_OUTPUT 1
)

if(NOT ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

    source_group(res FILES ${GAME_RES} ${GAMEPLAY_RES} ${GAMEPLAY_RES_SHADERS} ${GAMEPLAY_RES_UI})
    source_group(src FILES ${GAME_SRC})

    COPY_RES( ${GAME_NAME} )
    COPY_RES_EXTRA( ${GAME_NAME} ${CMAKE_SOURCE_DIR}/engine
            res/logo_powered_white.png
            res/shaders/*
            res/ui/*
            )
endif(NOT ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
