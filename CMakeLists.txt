cmake_minimum_required(VERSION 2.4)

project(Study)


add_executable(HW hw.cpp)


add_executable(KSERVO kservo.cpp)
target_link_libraries(KSERVO ics3)
