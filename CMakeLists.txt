cmake_minimum_required( VERSION 2.8 FATAL_ERROR )
set( CMAKE_VERBOSE_MAKEFILE ON )

project(ChocolataApps )

get_filename_component( CINDER_PATH "$ENV{HOME}/Cinder" ABSOLUTE )
get_filename_component( APP_PATH "${CMAKE_CURRENT_SOURCE_DIR}/ChocolataSliser" ABSOLUTE )


include( "${CINDER_PATH}/proj/cmake/modules/cinderMakeApp.cmake" )

set(SRC_CHOCOLATA_SLICER
	# Main sources
	${APP_PATH}/ChocolataSlicer.cpp
	${APP_PATH}/ShaderTree.cpp
	${APP_PATH}/ContentTree.cpp
	${APP_PATH}/ObjectPicker.cpp
	${APP_PATH}/config/cstringFunctions.cpp
	${APP_PATH}/config/jsonConfig.cpp
	# ${APP_PATH}/config/configs.cpp

	# DocLoader
	${APP_PATH}/docLoader/ChocolataSlicerMesh.cpp
	${APP_PATH}/fileSelector/FileSelector.cpp

	# Context
	${APP_PATH}/context/printingContext.cpp
	${APP_PATH}/context/SerialHard/SerialHard.cpp
	${APP_PATH}/context/Communicator/Transmitter.cpp
	${APP_PATH}/context/Communicator/Receiver.cpp

	# UI
	${APP_PATH}/ui/uiWindiw.cpp
	${APP_PATH}/ui/uiViewport.cpp
	${APP_PATH}/ui/uiWindowHandler.cpp
	${APP_PATH}/ui/Notification/Notification.cpp

	${APP_PATH}/ui/BarWindows/uiAbout.cpp

)
set(INC_CHOCOLATA_SLICER
	# Main include
	${CINDER_PATH}/include
	${APP_PATH}/
	${APP_PATH}/config
	${APP_PATH}/fileSelector

	# DocLoader
	${APP_PATH}/docLoader
	
	# Contenxt
	${APP_PATH}/context

	# UI
	${APP_PATH}/ui
	
)

ci_make_app(
	APP_NAME    "ChocolataSlicer"
	CINDER_PATH ${CINDER_PATH}
	SOURCES     ${SRC_CHOCOLATA_SLICER}
	INCLUDES    ${INC_CHOCOLATA_SLICER}
	ASSETS_PATH	"assets"
)
