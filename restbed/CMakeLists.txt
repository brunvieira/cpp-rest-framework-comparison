cmake_minimum_required(VERSION 3.7)
project(cpp_comparison_restbed)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenSSL 1.0.0 REQUIRED)
find_package(Threads)

add_executable(cpp_comparison_restbed src/cpputils/cpputils.cpp src/main.cpp)
target_link_libraries(cpp_comparison_restbed librestbed.a Threads::Threads OpenSSL::SSL)

target_include_directories(
    cpp_comparison_restbed
    PRIVATE
    /usr/local/include/rapidjson
    /usr/local/include/corvusoft
)