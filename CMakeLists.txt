cmake_minimum_required(VERSION 4.0)
project(Kursova)

set(CMAKE_CXX_STANDARD 20)

add_executable(Kursova main.cpp
        Student.cpp
        Student.h
        Subject.cpp
        Subject.h
        IPrint.cpp
        IPrint.h
        DatabaseManager.cpp
        DatabaseManager.h
        Admin.cpp
        Admin.h
        Person.cpp
        Person.h
        Teacher.cpp)
