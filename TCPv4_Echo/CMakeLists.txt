cmake_minimum_required (VERSION 3.5)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_C_COMPILER "/usr/bin/clang")
set (CMAKE_C_FLAGS "-Os -Wall -Wextra -Wshadow")


include_directories	(
	./
)

file (GLOB COMMON
	DieWithMessage.c
)

file (GLOB CLIENT_SOURCES
	TCPv4_Echo_Client.c
)

file (GLOB SERVER_SOURCES
	TCPv4_Echo_Server.c
	TCPv4ServerUtility.c
)

project (client)
add_executable (client ${COMMON} ${CLIENT_SOURCES})

project (server)
add_executable (server ${COMMON} ${SERVER_SOURCES})
