#Sets compiler flags to treat most compiler warnings as errors.
set(CMAKE_CXX_FLAGS "-Wall -Wno-sign-compare -Werror -Wno-unused-variable -std=c++11")

#Compiling Stack will check if your class is defined properly.
add_library(Stack OBJECT Stack.cpp)

#A4 is an executable for using your Stack.
add_executable(A4 $<TARGET_OBJECTS:Stack> driver.cpp)