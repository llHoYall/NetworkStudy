cmake_minimum_required (VERSION 3.5)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_C_COMPILER "/usr/bin/clang")
set (CMAKE_C_FLAGS "-std=c99 -Os -Wall -Wextra -Wshadow")


include_directories	(
	./
)

file (GLOB COMMON
	DieWithMessage.c
	AddressUtility.c
	DelimFramer.c
	VoteEncodingText.c
)

file (GLOB CLIENT_SRCS
	TCPVoteClient.c
	TCPClientUtility.c
)

file (GLOB SERVER_SRCS
	TCPVoteServer.c
	TCPServerUtility.c
)

project (client)
add_executable (client ${COMMON} ${CLIENT_SRCS})

project (server)
add_executable (server ${COMMON} ${SERVER_SRCS})
