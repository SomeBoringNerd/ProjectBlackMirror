cmake_minimum_required(VERSION 3.25)

project(ARI-Server VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_FLAGS -pthread)

include_directories(src/include)

add_executable(ARI-Server 
    src/main.c
    src/server.h
    src/camControl.h
    src/logger.h
    src/wsServer/ws.c
    src/wsServer/base64.c
    src/wsServer/sha1.c
    src/wsServer/handshake.c
    src/wsServer/utf8.c
)


