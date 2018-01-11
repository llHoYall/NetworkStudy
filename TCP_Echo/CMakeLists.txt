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

file (GLOB SERVER4_SOURCES
	TCPv4_Echo_Server.c
	TCPServerUtility.c
)

file (GLOB SERVER6_SOURCES
	TCPv6_Echo_Server.c
	TCPServerUtility.c
)

project (client)
add_executable (client ${COMMON} ${CLIENT_SOURCES})

project (server4)
add_executable (server4 ${COMMON} ${SERVER4_SOURCES})

project (server6)
add_executable (server6 ${COMMON} ${SERVER6_SOURCES})
