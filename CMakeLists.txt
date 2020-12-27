cmake_minimum_required(VERSION 2.8)

project(Study)


add_executable(hw hello_world/hw.cpp)


# find_package(CUDA REQUIRED)
# cuda_add_executable(matadd cuda/matadd.cu)


add_executable(perceptron math/perceptron.cpp)


add_executable(joynics2 serial/joynics2.cpp)


add_executable(kservo serial/kservo.c)
target_link_libraries(kservo ics3)


add_library(motion pantilt/motion.cpp)
# if SHARED : cmake -DBUILD_SHARED_LIBS=ON ..
add_executable(pantilt pantilt/pantilt.cpp)
target_link_libraries(pantilt motion)