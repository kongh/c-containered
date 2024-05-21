cmake_minimum_required(VERSION 3.16)
project(cc C)

set(CMAKE_C_STANDARD 11)



add_executable(main main.c
        chroot.c
        chroot.h
        execv.c
        execv.h)
