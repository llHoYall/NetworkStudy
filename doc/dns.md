---
layout: post
title: DNS
category: network
tags: [network, dns]
---



# DNS (Domain Name Service)

### Methods

```c
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

struct addrinfo {
  int ai_flags;
  int ai_family;
  int ai_socktype;
  int ai_protocol;
  socklen_t ai_addrlen;
  struct sockaddr* ai_addr;
  char* ai_canonname;
  struct addrinfo* ai_next;
};

int getaddrinfo(const char* host, const char* service, 
                const struct addrinfo* hints, struct addrinfo **results);

void freeaddrinfo(struct addrinfo* addrList);

const char* gai_strerror(int errcode);
```

##### getaddrinfo()

호스트 이름과 서비스 이름에 해당하는 주소 정보를 얻는다.

- host: 호스트 이름이나 IP 주소를 null로 끝나는 문자열로 입력한다.
- service: 서비스 이름이나 포트 번호를 null로 끝나는 문자열로 입력한다.
- hints: 얻고자 하는 정보의 형태를 입력한다.
- results: 입력받은 정보에 해당하는 주소 정보를 동적으로 할당된 linked list로 출력된다.

성공 시 0, 실패 시 에러코드를 반환한다.

##### freeaddrinfo()

getaddrinfo()의 결과로 생성된 linked list의 메모리를 해제한다.

- addrList: getaddrinfo()의 결과로 생성된 linked list를 입력한다.

##### gai_strerror()

에러 코드를 보다 자세한 문장으로 출력해준다.

- errcode: getaddrinfo() 함수에서 발생한 에러코드를 입력한다.

##### struct addrinfo

- ai_flags: 각 비트에 설정된 값에 따라 의미가 다르다. 원하는 플래그들을 '|'로 결합하여 사용한다.
  - AI_PASSIVE: 이 플래그가 설정되면 host가 NULL이면 반환되는 addrinfo들은 INADDR_ANY 또는 IN6ADDR_ANY_INIT과 같은 와일드 카드 주소 형태로 반환된다.
  - AI_CANONNAME: 하나의 이름 주소에 여러 개의 숫자 주소가 연관될 수 있는 것처럼 여러 개의 이름 주소가 하나의 숫자 주소에 연관될 수 있다. 보통 이 중 하나의 주소가 정규(canonical) 이름 주소로 사용된다. 이 플래그가 설정되면 linked list의 첫 번째 addrinfo의 ai_canonname 필드에 canonical 이름 정보를 넣어서 반환한다.
  - AI_NUMERICHOST: 이 플래그가 설정되면 host가 잘못된 형식의 숫자 주소를 참조한다면 에러를 반환한다. 이 플래그가 설정되지 않고 host가 잘못된 형식의 숫자 주소를 참조한다면 시스템은 DNS에게 resolve 요청을 수행한다. 이 플래그가 설정이 되고 주어진 주소가 올바른 형식이면 inet_pton()과 같이 변환되어 반환된다.
  - AI_ADDRCONFIG: 이 플래그가 설정되면 getaddrinfo()는 시스템의 인터페이스에 할당된 특정 주소 집합체와 같은 형식으로만 주소를 반환한다. 즉, IPv4 주소들은 시스템의 인터페이스가 IPv4 주소를 갖고 있을때만 반환이 가능하고, IPv6도 마찬가지다.
  - AI_V4MAPPED: ai_family 필드가 AF_INET6로 설정되어 있고 이에 따른 IPv6 주소들이 존재하지 않을 경우, getaddrinfo()는 IPv4-mapped IPv6 주소들을 반환한다. 이 기법은 IPv4만 지원 가능한 IPv6 호스트들 간의 제한된 상호연결을 위해 쓰일 수 있다.
- ai_family: AF_INET, AF_INET6, AF_UNSPEC.
- ai_socktype: SOCK_STREAM, SOCK_DGRAM.
- ai_protocol: IPPROTO_TCP, 0은 any protocol.
- ai_addrlen: ai_addr 길이.
- ai_addr
- ai_canonname: Canonical name.
- ai_next: Linked list에서 다음 addrinfo의 위치.

