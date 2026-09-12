cmake_minimum_required(VERSION 3.20)

project(ArshuMartBackend)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Drogon CONFIG REQUIRED)

add_executable(ArshuMartBackend
    main.cpp
)

target_link_libraries(ArshuMartBackend PRIVATE Drogon::Drogon)
