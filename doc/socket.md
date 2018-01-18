---
layout: post
title: socket
category: network
tags: [network, socket]
---



# Socket

### Create Socket

```c
#include <sys/types.h>
#include <sys.socket.h>

/**
 *	@brief		socket() creates an endpoint for communication and returns a
 *						file descriptor that refers to that endpoint.
 *	@param[in]	domain
 *							- AF_INET: IPv4 internet protocols
 *							- AF_INET6: IPv6 internet protocols
 *	@param[in]	type
 *							- SOCK_STREAM: Provides sequenced, reliable, two-way,
 *														 connection-based byte streams.
 *							- SOCK_DGRAM: Supports datagrams (connectionless, unreliable
 *														messages of a fixed maximum length).
 *	@param[in]	protocol
 *							- IPPROTO_TCP: Indicates that the TCP protocol is to be used.
 *							- IPPROTO_UDP: Indicates that the UDP protocol is to be used.
 *	@retval		On success, a file descriptor for the new socket is returned.
 *						On error, -1 is returned, and errno is set appropriately.
 */
int socket(int domain, int type, int protocol);
```

### Close Socket

```c
#include <unistd.h>

/**
 *	@brief		close() closes a file descriptor, so that it no longer refers to
 *						any file and may be refused.
 *	@param[in]	fd: file descriptor
 *	@retval		close() returns zero on success.
 *						On error, -1 is returned, and errno is set appropriately.
 */
int close(int fd);
```

### Connect Socket

```c
#include <sys/types.h>
#include <sys/socket.h>

/**
 *	@brief		Initiate a connection on a socket.
 *						Generally, connection-based protocol sockets may successfully
 *						connect() only once; connectionless protocol sockets may use
 *						connect() multiple times to change their association.
 *	@param[in]	sockfd
 *	@param[in]	addr: If the socket sockfd is of type SOCK_DGRAM, then addr is
 *										the address to which datagrams are sent by default, and
 *										the only address from which datagrams are received.
 *										If the socket is of type SOCK_STREAM or SOCK_SEQPACKET,
 *										this call attempts to make a connection to the socket
 *										that is bound to the address specified by addr.
 *	@param[in] addrlen
 *	@retval		If the connection or binding succeeds, zero is returned.
 *						On error, -1 is returned, and errno is set appropriately.
 */
int connect(int sockfd, const struct sockaddr* addr, socklen_t addrlen);
```

### Bind Socket

```c
#include <sys/types.h>
#include <sys/socket.h>

/**
 *	@brief		Bind a name to a socket.
 *	@param[in]	sockfd
 *	@param[in]	localaddr
 *	@param[in]	addrlen
 *	@retval		On success, zero is returned.
 *						On error, -1 is returned, and errno is set appropriately.
 */
int bind(int sockfd, const struct sockaddr* localaddr, socklen_t addrlen);
```

Client가 bind()를 사용하려면 connect() 호출 전에 bind()를 먼저 호출해야 한다.

INADDR\_ANY는 호스트 바이트 순서로 되어 있어서 bind()의 인자로 사용되기 위해서는 사용 전에 htonl()을 통해 네트워크 바이트 순서로 변환이 되어야 한다. In6addr\_any와 IN6ADDR\_ANY_\INIT은 네트워크 바이트 순서로 되어있다.

bind()의 포트번호에 0을 지정하면 시스템은 사용하지 않은 지역 포트를 하나 지정해서 실행한다.

### Listen Socket

```c
#include <sys/types.h>
#include <sys/socket.h>

/**
 *	@brief		Listen for connections on a socket.
 *	@param[in]	sockfd
 *	@param[in]	queueLimit
 *	@retval		On success, 0 is returned.
 *						On error, -1 is returned, and errno is set appropriately.
 */
int listen(int sockfd, int queueLimit);
```

### Accept Socket

```c
#include <sys/types.h>
#include <sys/socket.h>

/**
 *	@brief		Accept a connection on a socket.
 *	@param[in]			sockfd
 *	@param[in]			clientAddr
 *	@param[in/out]	addrLen: clientAddr의 크기로 초기화를 해야한다.
 *													 수행 후, 실제 크기가 반환된다.
 *	@retval		On success, these system calls return a nonnegative integer that
 *						is a file descriptor for the accepted socket.
 *						On error, -1 is returned, and errno is set appropriately.
 */
int accept(int sockfd, struct sockaddr* clientAddr, socklen_t* addrlen);
```

### Data Communication using Socket

```c
#include <sys/types.h>
#include <sys/socket.h>

ssize_t send(int sockfd, const void* buf, size_t len, int flags);
ssize_t recv(int sockfd, const void* buf, size_t len, int flags);
```

성공 시, 송수신한 바이트 수를 반환.

실패 시, -1을 반환. errno를 통해 확인가능

### Address Format

```c
/**
 *	@brief		The sockaddr structure varies depending on the protocol selected.
 */
struct sockaddr {
	sa_family_t sa_family;	/**< address family: AF_INET, AF_INET6 */
	char sa_data[14];
};

struct sockaddr_in {
	sa_family_t sin_family;		/**< address family: AF_INET */
	in_port_t sin_port;				/**< port in network byte order */
	struct in_addr sin_addr;	/**< internet address */
	char sin_zero[8];					/**< Not used */
};

struct in_addr {
	uint32_t s_addr;	/**< address in network byte order */
};

struct sockaddr_in6 {
	sa_family_t sin6_family;		/**< address family: AF_INET6 */
	in_port_t sin6_port;				/**< port number */
	uint32_t sin6_flowinfo;			/**< IPv6 flow information */
	struct in6_addr sin6_addr;	/**< IPv6 address */
	uint32_t sin6_scope_id;			/**< Scope ID */
};

struct in6_addr {
	uint32_t s_addr[16];	/**< IPv6 address */
};

/**
 *	@brief		This type is suitable to accommodate all supported domain-specific
 *						socket address structures; it is large enough and is aligned
 *						properly. The sockaddr_storage structure is useful in programs
 *						that must handle socket addresses in a generic way.
 */
struct sockaddr_storage {
	sa_family_t ss_family;
	...
};

#include <arpa/inet.h>
/**
 *	@brief		Convert IPv4 and IPv6 addresses from text to binary form.
 *						(printable to numeric)
 *	@param[in]	addressFamily
 *							- AF_INET: src points to a character string containing an IPv4
 *												 network address in dotted-decimal format.
 *												 The address is converted to a struct in_addr and
 *												 copied to dst.
 *							- AF_INET6: src points to a character string containing an IPv6
 *													network address. The address is converted to a
 *													struct in6_addr and copied to dst.
 *	@retval		inet_pton() returns 1 on success (network address was successfully
 *												converted. 0 is returned if src does not contain a
 *												character string representing a valid network address
 *												in the specified address family. If addressFamily does
 *												not contain a valid address family, -1 is returned and
 *												errno is set to EAFNOSUPPORT.
 */
int inet_pton(int addressFamily, const char* src, void* dst);

#include <arpa/inet.h>
/**
 *	@brief		Convert IPv4 and IPv6 addresses from binary to text form.
 *						(numeric to printable)
 *	@param[in]	addressFamily
 *							- AF_INET: src points to a struct in_addr (in network byte
 *												 order) which is converted to an IPv4 network address
 *												 in the dotted-decimal format. THe buffer dst must be
 *												 at least INET_ADDRSTRLEN bytes long.
 *							- AF_INET6: src points to a struct in6_addr (in network byte
 *													order) which is converted to a representation of
 *													this address in the most appropriate IPv6 network
 *													address	format for this address. The buffer dst
 *													must be at least INET6_ADDRSTRLEN bytes long.
 *	@retval		On success, inet_ntop() returns a non-null pointer to dst. NULL
 *						is returned if there was an error, with errno set to indicate the
 *						error.
 */
const char* inet_ntop(int addressFamily, const void* src, char* dst,
					  socklen_t dstBytes);

#include <sys/socket.h>
/**
 *	@brief		Get name of connected peer socket.
 *	@param[in]			sockfd
 *	@param[out]			remoteAddress
 *	@param[in/out]	addrlen: The addrlen argument should be initialized to
 *													 indicate the amount of space pointed to by addr.
 *													 On return it contains the actual size of the name
 *													 returned (in bytes).
 *													 The returned address is truncated if the buffer
 *													 provided is too small; in this case, addrlen will
 *													 return a value greater than was supplied to the
 *													 call.
 *	@retval		On success, zero is returned.
 *						On error, -1 is returned, and errno is set appropriately.
 */
int getpeername(int sockfd, struct sockaddr* remoteAddress, 
                socklen_t* addrlen);

#include <sys/socket.h>
/**
 *	@brief		Get socket name.
 *	@param[in]			sockfd
 *	@param[out]			localAddress
 *	@param[in/out]	addrlen: The addrlen argument should be initialized to
 *													 indicate the amount of space (in bytes) pointed to
 *													 by addr. On return it contains the actual size of
 *													 the socket address.
 *	@retval		On success, zero is returned.
 *						On error, -1 is returned, and errno is set appropriately.
 */
int getsockname(int sockfd, struct sockaddr* localAddress, 
                socklen_t* addrlen);
```

### UDP Communication

```c
#include <sys/types.h>
#include <sys/socket.h>

ssize_t sendto(int sockfd, const void* buf, size_t len, int flags,
               const struct sockaddr* dst_addr, socklen_t addrlen);

ssize_t recvfrom(int sockfd, void* buf, size_t len, int flags,
                 struct sockaddr* src_addr, socklen_t* addrlen);
```

##### sendto()

- sockfd
- buf
- len: buf 길이.
- flags
- dst_addr
- addrlen: dst_addr 길이.

##### recvfrom()

- sockfd
- buf
- len: buf 길이.
- flags
- src_addr
- addrlen: src_addr 길이.