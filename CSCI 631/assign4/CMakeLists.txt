cmake_minimum_required(VERSION 3.9)
project(assign4)

set(CMAKE_CXX_STANDARD 11)

add_executable(assign4cli
        prog4cli.c
        prog4cli.h
        wrap4cli.c
        wrap4cli.h
        in-out.c
        in-out.h)

add_executable(assign4srv
        prog4srv.c
        prog4srv.h
        wrap4srv.c
        wrap4srv.h
        in-out.c
        in-out.h)
