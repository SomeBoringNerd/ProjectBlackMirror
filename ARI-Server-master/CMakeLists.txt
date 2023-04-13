cmake_minimum_required(VERSION 3.25) # version de cmake pour compiler

project(ARI-Server VERSION 0.1.0)

set(CMAKE_C_FLAGS -pthread) # pthread permet d'utiliser le multithread pour nos routines

# inclusion des librairies 
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )


# code pour installer mysql header 
# note : j'ai envie de crever ceci est un appel a l'aide que personne ne peut voir ou entendre
# vu que je vais devoir enlever ce commentaire avant de rendre le repos publique
find_package(mysqlclient 1.1.9 QUIET)
if (NOT mysqlclient_FOUND)
  include(FetchContent)
  FetchContent_Declare(
    mysqlclient
    URL https://cdn.mysql.com//archives/mysql-connector-c++/mysql-connector-c++-1.1.9.tar.gz
  )
  FetchContent_GetProperties(mysqlclient)
  if (NOT mysqlclient_POPULATED)
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(mysqlclient)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    add_subdirectory(${mysqlclient_SOURCE_DIR} ${mysqlclient_BINARY_DIR})
  endif()
endif()



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
target_link_libraries(ARI-Server ${OpenCV_LIBS} mysqlclient -llept -ltesseract)
