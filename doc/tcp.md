---
layout: post
title: tcp
category: network
tags: [network, tcp]
---



# TCP (Transmission Control Protocol)

### File Stream

TCP 소켓을 FILE stream처럼 wrap 하여 사용한다. 오직 TCP 소켓에서만 사용할 수 있다.

```c
#include <stdio.h>

FILE* fdopen(int socketfd, const char* mode);
size_t fread(void* ptr, size_t size, size_t nmemb, FILE* stream);
size_t fwrite(const void* ptr, size_t size, size_t nmemb, FILE* stream);
int fflush(FILE* stream);
int fclose(FILE* stream);
```

##### fread()

Stream에서 nmemb 크기씩 size번 읽고, ptr에 쓴다.

##### fwrite()

ptr에서 nmemb 크기씩 size번 읽고, stream에 쓴다.

##### fflush()

Stream에 버퍼링 되어있는 데이터를 소켓으로 전송하고 비운다..

