cmake_minimum_required(VERSION 2.8)

project(Study)


add_executable(hw hello_world/hw.cpp)

# find_package(CUDA REQUIRED)
# cuda_add_executable(matadd cuda/matadd.cu)

add_executable(perceptron math/perceptron.cpp)

add_executable(kservo serial/kservo.cpp)
target_link_libraries(kservo ics3)