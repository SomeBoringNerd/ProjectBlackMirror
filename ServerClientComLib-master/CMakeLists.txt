cmake_minimum_required(VERSION 3.25)

project(ServerClientComModule VERSION 0.1.0 LANGUAGES C)

add_executable(ServerClientComModule 
    src/main.c
    src/logger.h
)