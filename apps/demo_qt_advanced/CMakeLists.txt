PROJECT (demo_mn_qt_advanced CXX) 

CMAKE_MINIMUM_REQUIRED (VERSION 2.8.11)

INCLUDE(../common/cmake/options.cmake)

SET(DEMO_PLK_QT_LIB_DIR ${CMAKE_SOURCE_DIR}/plk_qt_api)
SET(DEMO_PLK_QT_GUI_DIR ${CMAKE_SOURCE_DIR}/plk_qt_gui)

SET(DEMO_PLK_QT_LIB_INCLUDE_DIR ${DEMO_PLK_QT_LIB_DIR}/include)
SET(DEMO_PLK_QT_LIB_SOURCE_DIR ${DEMO_PLK_QT_LIB_DIR}/src)
SET(DEMO_PLK_QT_GUI_INCLUDE_DIR ${DEMO_PLK_QT_GUI_DIR}/include)
SET(DEMO_PLK_QT_GUI_SOURCE_DIR ${DEMO_PLK_QT_GUI_DIR}/src)

SET(CMAKE_PREFIX_PATH "C:\\Qt\\Qt5.2.0\\5.2.0\\msvc2010")

#TODO should be in GUI?
FIND_OPLK_LIBRARY("mn")             # Find suitable openPOWERLINK library

################################################################################
# Setup the architecture specific definitions
#TODO add after separating files.
#IF(CMAKE_SYSTEM_NAME STREQUAL "Linux")
#    include(linux.cmake)
#ELSEIF(CMAKE_SYSTEM_NAME STREQUAL "Windows")
#    include (windows.cmake)
#ELSE()
#    MESSAGE(FATAL_ERROR "System ${CMAKE_SYSTEM_NAME} is not supported!")
#ENDIF()

MESSAGE( STATUS "CMAKE_CXX_FLAGS: " ${CMAKE_CXX_FLAGS} )

IF (MSVC)
	SET(CMAKE_CXX_FLAGS "/nologo /W4 /WX-")                               # General
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D_CRT_SECURE_NO_WARNINGS ")  # Preprocessor
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Gm- /EHsc ")                 # Code-Generation
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:wchar_t /GR-")            # Language
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Gd /TP /errorReport:queue ") # Advanced
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w34100 /w34189 /Zm200 ")     # from Qt-Creator build

	SET(CMAKE_CXX_FLAGS_DEBUG            "/MDd /Od /Ob0 /GS  /fp:precise /D_DEBUG /Zi")
	SET(CMAKE_CXX_FLAGS_RELEASE          "/MD  /O2 /Ob2 /GS- /fp:fast    /DNDEBUG")
	SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO   "/MD  /O2 /Ob2 /GS- /fp:fast    /DNDEBUG /Zi")
	SET(CMAKE_CXX_FLAGS_MINSIZEREL       "/MD  /O1 /Ob1 /GS- /fp:fast    /DNDEBUG")
ENDIF (MSVC)

OPTION (OPLK_QT_API_LIB "Build OPLK QT API library" ON)
OPTION (OPLK_QT_MN_GUI  "Build OPLK QT GUI" ON)

IF (WIN32)
	ADD_DEFINITIONS (${QT_DEFINITIONS} -DWIN32)
ELSE(WIN32)
	#TODO
ENDIF (WIN32)

SET(OPLK_QT_API_DOC_DIR ${OPLK_ROOT_DIR}/doc/examples/demo_qt_advanced)
FIND_PACKAGE(Doxygen)
IF(DOXYGEN_FOUND)
CONFIGURE_FILE(${OPLK_QT_API_DOC_DIR}/doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
ADD_CUSTOM_TARGET(DOCUMENTATION ALL
${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
WORKING_DIRECTORY ${OPLK_QT_API_DOC_DIR}
COMMENT "Generating API documentation with Doxygen" VERBATIM
)
ENDIF(DOXYGEN_FOUND)


IF(${OPLK_QT_API_LIB})
ADD_SUBDIRECTORY(plk_qt_api)
ENDIF(${OPLK_QT_API_LIB})

IF(${OPLK_QT_MN_GUI})
	ADD_SUBDIRECTORY(plk_qt_gui)
ENDIF(${OPLK_QT_MN_GUI})
