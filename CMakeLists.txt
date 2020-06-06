cmake_minimum_required( VERSION 2.8 FATAL_ERROR )
set( CMAKE_VERBOSE_MAKEFILE ON )

project(ChocolataApps )

get_filename_component( CINDER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/ChocolataSliser/Cinder" ABSOLUTE )
get_filename_component( APP_PATH "${CMAKE_CURRENT_SOURCE_DIR}/ChocolataSliser" ABSOLUTE )


include( "${CINDER_PATH}/proj/cmake/modules/cinderMakeApp.cmake" )

set(SRC_CHOCOLATA_SLICER
	# Main sources
	${APP_PATH}/src/ChocolataSlicer.cpp
	${APP_PATH}/src/__string.cpp

	# DocLoader
	${APP_PATH}/DocLoader/ChocolataSlicerMesh.cpp
)
set(INC_CHOCOLATA_SLICER
	# Main include
	${APP_PATH}/include
	${APP_PATH}/Cinder/include/glfw

	# DocLoader
	${APP_PATH}/DocLoader
)

ci_make_app(
	APP_NAME    "ChocolataSlicer"
	CINDER_PATH ${CINDER_PATH}
	SOURCES     ${SRC_CHOCOLATA_SLICER}
	INCLUDES    ${INC_CHOCOLATA_SLICER}
	ASSETS_PATH	"assets"
	# LIBRARIES	"-dl"
)
