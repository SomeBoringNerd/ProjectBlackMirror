cmake_minimum_required(VERSION 3.25)

project(ARI-Server VERSION 0.1.0)

set(CMAKE_C_FLAGS -pthread)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

include_directories(src/include)
add_executable(ARI-Server 
    src/main.cpp
    src/server.hpp
    src/camControl.hpp
    src/logger.hpp
    src/imgUtil.hpp
    src/wsServer/ws.c
    src/wsServer/base64.c
    src/wsServer/sha1.c
    src/wsServer/handshake.c
    src/wsServer/utf8.c
)

target_link_libraries(ARI-Server ${OpenCV_LIBS} -llept -ltesseract)