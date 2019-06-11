cmake_minimum_required(VERSION 3.7)
project(cpp_comparison_pistache)

set(CMAKE_CXX_STANDARD 14)
find_package(Pistache REQUIRED)

add_executable(cpp_comparison_pistache src/main.cpp src/cpputils/cpputils.cpp)
target_link_libraries(cpp_comparison_pistache pistache_static)
target_include_directories(
    cpp_comparison_pistache
    PRIVATE
    /usr/local/include/pistache
    /usr/local/include/rapidjson
)

