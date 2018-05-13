cmake_minimum_required(VERSION 3.1...3.11)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_VERSION})
endif()

if (DEFINED ARCH)
    if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/arch/${ARCH}")
        message("Generating build for ${ARCH}")
    else()
        unset(ARCH CACHE)
        message(FATAL_ERROR "Invalid platform!")
    endif()
else()
    unset(ARCH CACHE)
    message(FATAL_ERROR "Need to specify platform!")
endif()

