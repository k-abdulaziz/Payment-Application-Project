cmake_minimum_required(VERSION 3.23)
project(Payment_Application_Project C)

set(CMAKE_C_STANDARD 11)

include_directories(Application)
include_directories(Card)
include_directories(Server)
include_directories(Terminal)

add_executable(Payment_Application_Project
        Card/card.c
        Card/card.h
        Terminal/terminal.c
        Terminal/terminal.h
        Server/server.c
        Server/server.h
        Application/app.c
        Application/app.h)
