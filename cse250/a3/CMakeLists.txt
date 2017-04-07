set(CMAKE_CXX_FLAGS "-std=c++11 -O2")

add_library(PairList OBJECT A3.cpp)
add_executable(A3 $<TARGET_OBJECTS:PairList> driver.cpp)