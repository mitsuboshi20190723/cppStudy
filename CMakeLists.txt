cmake_minimum_required(VERSION 2.8)

project(Study)


add_executable(HW hello_world/hw.cpp)

# find_package(CUDA REQUIRED)
# cuda_add_executable(MATADD cuda/matadd.cu)

add_executable(PERCEPTRON math/perceptron.cpp)

add_executable(KSERVO serial/kservo.cpp)
target_link_libraries(KSERVO ics3)