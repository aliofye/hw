#Sets compiler flags to treat most compiler warnings as errors.
set(CMAKE_CXX_FLAGS "-g3 -Wall -Wno-sign-compare -Werror -Wno-unused-variable -std=c++11")

#Compiling A5-functions will check if your syntax is correct.
add_library(A5-functions OBJECT Item.cpp A5.cpp)

#A5 is an executable for using your functions.
add_executable(A5 Item.cpp A5.cpp driver.cpp)