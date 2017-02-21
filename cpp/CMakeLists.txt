cmake_minimum_required(VERSION 2.8)
project(s3-sample)

#this will locate the aws sdk for c++ package so that we can use its targets
#set(aws-sdk-cpp_DIR, "/usr/local/lib")

find_package(aws-cpp-sdk-core)

find_package(aws-cpp-sdk-s3)
add_executable(s3-sample src/main.cpp)

#since we called find_package(), this will resolve all dependencies, header files, and cflags necessary
#to build and link your executable. 
target_link_libraries(s3-sample aws-cpp-sdk-s3)
