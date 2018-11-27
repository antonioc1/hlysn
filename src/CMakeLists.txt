# Author: Alec Foster, Antonio Cervantes, Colter Ogden
# NetID: sirslush, antonioc1, jcogden
# Date: 11/4/2018
# Project 2

# Check if windows file 

	if(MSVC)

# Sets the compilation flags to report warnings through Level 4.

		set( CMAKE_CXX_FLAGS "-W4" )
    		set(CMAKE_DEBUG_POSTFIX "d")
    		add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
    		add_definitions(-D_CRT_NONSTDC_NO_DEPRECATE)
	else()
# debug information for all other OSs

   		add_definitions(-Wall -g)
    		link_libraries(m)
	endif()

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
if(COMPILER_SUPPORTS_CXX11)
message(STATUS "${COMPILER_SUPPORTS_CXX11}")
else(COMPILER_SUPPORTS_CXX11)
message(FATAL_ERROR "${COMPILER_SUPPORTS_CXX11}")
endif(COMPILER_SUPPORTS_CXX11)

set(CMAKE_CXX_FLAGS "-std=c++11")
file( GLOB SRCS *.cpp *.h )

add_executable( hlysn ${SRCS} )
