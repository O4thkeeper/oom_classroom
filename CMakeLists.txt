cmake_minimum_required(VERSION 3.22)
project(oom_classroom)

set(CMAKE_CXX_STANDARD 14)

set(server_file server_main.cpp src/system/frontend.cpp src/system/frontend.h
        src/system/backend.cpp src/system/backend.h
        src/network/server.cpp src/network/server.h
        src/entity/classroom.cpp src/entity/classroom.h
        src/entity/user.cpp src/entity/user.h
        src/data/database.cpp src/data/database.h src/network/data_transfer.cpp src/network/data_transfer.h src/network/data_template.h)

set(client_file client_main.cpp src/network/client.cpp src/network/client.h
        src/entity/classroom.cpp src/entity/classroom.h
        src/entity/user.cpp src/entity/user.h
        src/network/data_transfer.cpp src/network/data_transfer.h src/network/data_template.h )

link_directories(/usr/local/lib)
include_directories(/usr/local/include/mysql++)
include_directories(/usr/include/mysql/)
add_executable(oom_classroom_server ${server_file})
target_link_libraries(oom_classroom_server -lmysqlpp)

add_executable(oom_classroom_client ${client_file})


#enable_testing()
#add_subdirectory(third_party/googletest)
#include_directories(third_party/googletest/googletest/include)
#set(GTEST_LIB gtest gtest_main)
#
#add_executable(test_database test/test_database.cpp src/data/database.cpp src/data/database.h)
#target_link_libraries(test_database ${GTEST_LIB} mysqlpp)
#add_test(NAME test_database COMMAND test_database)
