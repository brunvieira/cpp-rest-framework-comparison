cmake_minimum_required(VERSION 3.7)

project(cpp_comparison_cpprestsdk)

find_library(CPPREST_LIB cpprest)
find_package(Boost REQUIRED COMPONENTS random system thread filesystem chrono atomic date_time regex)
find_package(OpenSSL 1.0.0 REQUIRED)

include_directories("/usr/local/include")
link_directories("/usr/local/lib")

add_executable(cpp_comparison_cpprestsdk src/main.cpp src/handler.cpp src/route.cc)
target_link_libraries(cpp_comparison_cpprestsdk
  ${CPPREST_LIB}
  Boost::boost
  Boost::random
  Boost::system
  Boost::thread
  Boost::filesystem
  Boost::chrono
  Boost::atomic
  Boost::date_time
  Boost::regex
  OpenSSL::SSL
)
target_compile_features(cpp_comparison_cpprestsdk PRIVATE cxx_range_for)