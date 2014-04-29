
MACRO(FIND_OPLK_QT_API_LIBRARY OPLK_QT_API_LIB_NAME )
#LIB_BUILD_TYPE
    # Set oplk library and include directory
    SET(OPLK_QT_API_LIB_DIR ${PLK_QT_BINARY_DIR})
    
    #STRING(TOUPPER "${LIB_BUILD_TYPE}" LIB_BUILD_TYPE)
    #IF("${LIB_BUILD_TYPE}" STREQUAL "DEBUG")
        #SET(LIB_BUILD_TYPE_EXT "_d")
        SET(OPLK_QT_API_LIB_DEBUG_NAME "${OPLK_QT_API_LIB_NAME}_d")
        # Search for debug library
        UNSET(OPLK_QT_API_LIB_DEBUG CACHE)
        MESSAGE(STATUS "Searching for LIBRARY ${OPLK_QT_API_LIB_DEBUG_NAME} in ${OPLK_QT_API_LIB_DIR}")
        FIND_LIBRARY(OPLK_QT_API_LIB_DEBUG NAME ${OPLK_QT_API_LIB_DEBUG_NAME}
                                            HINTS ${OPLK_QT_API_LIB_DIR} )

        IF(CMAKE_SYSTEM_NAME STREQUAL "Windows")
            UNSET(OPLK_QT_API_DLL_DEBUG CACHE)
            FIND_PROGRAM(OPLK_QT_API_DLL_DEBUG NAME ${OPLK_QT_API_LIB_DEBUG_NAME}.dll
                                                HINTS ${OPLK_QT_API_LIB_DIR})
        ENDIF(CMAKE_SYSTEM_NAME STREQUAL "Windows")
   # ELSE()
        SET(LIB_BUILD_TYPE_EXT "")
        # Search for release library
        UNSET(OPLK_QT_API_LIB CACHE)
        MESSAGE(STATUS "Searching for LIBRARY ${OPLK_QT_API_LIB_NAME} in ${OPLK_QT_API_LIB_DIR}")
        FIND_LIBRARY(OPLK_QT_API_LIB NAME ${OPLK_QT_API_LIB_NAME}
                                    HINTS ${OPLK_QT_API_LIB_DIR} )

        IF(CMAKE_SYSTEM_NAME STREQUAL "Windows")
            UNSET(OPLK_QT_API_DLL CACHE)
            FIND_PROGRAM(OPLK_QT_API_DLL NAME ${OPLK_QT_API_LIB_NAME}.dll
                                          HINTS ${OPLK_QT_API_LIB_DIR})
        ENDIF(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    #ENDIF()

ENDMACRO(FIND_OPLK_QT_API_LIBRARY)
