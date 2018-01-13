cmake_minimum_required (VERSION 3.5)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_C_COMPILER "/usr/bin/clang")
set (CMAKE_C_FLAGS "-Os -Wall -Wextra -Wshadow")


include_directories	(
	./
)

file (GLOB COMMON
	DieWithMessage.c
	AddressUtility.c
)

file (GLOB SOURCES
	GetAddrInfo.c
)

project (GetAddrInfo)
add_executable (GetAddrInfo ${COMMON} ${SOURCES})
