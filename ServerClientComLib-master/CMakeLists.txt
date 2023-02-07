cmake_minimum_required(VERSION 3.25)

project(ServerClientComModule VERSION 0.1.0 LANGUAGES C)

include_directories(src/include)

add_executable(ServerClientComModule 
    src/main.c
    src/logger.h
    src/wsServer/ws.c
    src/wsServer/base64.c
    src/wsServer/sha1.c
    src/wsServer/handshake.c
    src/wsServer/utf8.c
)


