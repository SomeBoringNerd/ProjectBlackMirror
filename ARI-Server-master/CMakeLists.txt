cmake_minimum_required(VERSION 3.25) # version de cmake pour compiler

project(ARI-Server VERSION 0.1.0)

set(CMAKE_C_FLAGS -pthread) # pthread permet d'utiliser le multithread pour nos routines

# inclusion des librairies 
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

include_directories( /usr/include/ )


# ajoute WServer dans l'executable
include_directories(src/include)

# ajoute notre code
add_executable(ARI-Server 
    src/main.cpp
    src/mini/ini.h
    src/server.hpp
    src/camControl.hpp
    src/logger.hpp
    src/imgUtil.hpp
    src/dataBase.hpp
    src/wsServer/ws.c
    src/wsServer/base64.c
    src/wsServer/sha1.c
    src/wsServer/handshake.c
    src/wsServer/utf8.c
)

# lie les librairies au lieu de les inclure, ça rend le code plus leger mais demande 
# d'installer les headers sur la machine source
target_link_libraries(ARI-Server ${OpenCV_LIBS} -lleptonica -ltesseract)