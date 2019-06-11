cmake_minimum_required(VERSION 3.7)
project(cpp_comparison_simple_web_server)

set(CMAKE_CXX_STANDARD 11)

find_package(Boost REQUIRED COMPONENTS system thread filesystem chrono atomic date_time)
find_package(OpenSSL 1.0.0 REQUIRED)

add_executable(cpp_comparison_simple_web_server src/main.cpp src/cpputils/cpputils.cpp)
target_link_libraries(cpp_comparison_simple_web_server
  Boost::boost
  Boost::system
  Boost::thread
  Boost::filesystem
  Boost::chrono
  Boost::atomic
  Boost::date_time
  OpenSSL::SSL
)

target_include_directories(
    cpp_comparison_simple_web_server
    PRIVATE
    /usr/local/include/simple-web-server
    /usr/local/include/rapidjson
)