cmake_minimum_required(VERSION 2.8)

set(HAWKEYE_DEPS_INCLUDES
	"${CMAKE_CURRENT_SOURCE_DIR}/glew-1.10.0/include"
	"${CMAKE_CURRENT_SOURCE_DIR}/bullet-2.82-r2704/src"
	"${CMAKE_CURRENT_SOURCE_DIR}/vorbis-1.3.4/include"
	"${CMAKE_CURRENT_SOURCE_DIR}/ogg-1.3.2/include"
	"${CMAKE_CURRENT_SOURCE_DIR}/base64-1.0.0"
#	"${CMAKE_CURRENT_SOURCE_DIR}/libjson-7.6.1"
	"${CMAKE_CURRENT_SOURCE_DIR}/png-1.6.15"
	"${CMAKE_CURRENT_SOURCE_DIR}/zlib-1.2.8/"
	"${CMAKE_CURRENT_SOURCE_DIR}/openal-1.16.0/include" CACHE STRING "Dependencies includes")


if (CMAKE_SYSTEM_NAME STREQUAL "Linux" AND NOT ANDROID)
	SET(LINUX 1)
endif()


# JSON
add_subdirectory(libjson-7.6.1)
# OpenAL
if (NOT APPLE)
	add_subdirectory(openal-1.16.0)
endif(NOT APPLE)
# OpenGL
if (NOT APPLE AND NOT ANDROID)
	add_subdirectory(glew-1.10.0)
endif (NOT APPLE AND NOT ANDROID)
# zlib (required by png)
add_subdirectory(zlib-1.2.8)
# PNG
add_subdirectory(png-1.6.15)
# OGG and Vorbis
add_subdirectory(ogg-1.3.2)
add_subdirectory(vorbis-1.3.4)
# Bullet Physics
add_subdirectory(bullet-2.82-r2704)
# Base64
add_subdirectory(base64-1.0.0)

# builds the dependecy list
set(BUILD_TARGETS
	BulletDynamics
	LinearMath
	BulletCollision
	vorbisfile
	vorbisenc
	vorbis
	ogg
	png_static
	zlibstatic
#	json
	base64)
if (NOT APPLE)
	list(APPEND BUILD_TARGETS GLEW)
	IF(WIN32)
		list(APPEND BUILD_TARGETS OpenAL32)
	ELSE(WIN32)
		list(APPEND BUILD_TARGETS openal)
	ENDIF(WIN32)
endif(NOT APPLE)


if(WIN32)
	set(GAMEPLAY_DEPS libhawkeye-deps.lib)
else(WIN32)
	set(GAMEPLAY_DEPS libhawkeye-deps.a)
endif(WIN32)

if(LINUX OR ANDROID)
	add_custom_command(
		OUTPUT ${GAMEPLAY_DEPS}
		COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/cmake/gnu-amalgamate.sh ${CMAKE_AR} ${LIBRARY_OUTPUT_PATH}
	)
elseif(APPLE)
	add_custom_command(
		OUTPUT ${GAMEPLAY_DEPS}
		COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/cmake/xcode-amalgamate.sh ${LIBRARY_OUTPUT_PATH}
	)
else()
	# Windows
	add_custom_command(
		OUTPUT ${GAMEPLAY_DEPS}
	COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/cmake/msvc-amalgamate.bat ${LIBRARY_OUTPUT_PATH}/${CMAKE_CFG_INTDIR}
	)
endif(LINUX OR ANDROID)

add_custom_target(engine-deps ALL DEPENDS ${GAMEPLAY_DEPS})
add_dependencies(engine-deps ${BUILD_TARGETS})

set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES ${LIBRARY_OUTPUT_PATH}/${GAMEPLAY_DEPS})
