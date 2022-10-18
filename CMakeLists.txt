cmake_minimum_required(VERSION 3.23)
project(oom_classroom)

set(CMAKE_CXX_STANDARD 14)

add_executable(oom_classroom_server main.cpp src/system/frontend.cpp src/system/frontend.h src/system/backend.cpp src/system/backend.h src/network/server.cpp src/network/server.h src/entity/classroom.cpp src/entity/classroom.h src/entity/user.cpp src/entity/user.h)

add_executable(oom_classroom_client main.cpp src/network/client.cpp src/network/client.h src/entity/classroom.cpp src/entity/classroom.h src/entity/user.cpp src/entity/user.h)