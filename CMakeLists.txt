cmake_minimum_required(VERSION 2.8)

project(cppStudy)


add_executable(hw hello_world/hw.cpp)

find_package(OpenCV REQUIRED)
#find_package(CUDA REQUIRED)


add_executable(perceptron math/perceptron.cpp)


add_executable(joynics2 serial/joynics2.cpp)


add_executable(kservo serial/kservo.c)
target_link_libraries(kservo ics3)


if(OpenCV_FOUND)
    message("OpenCV version: " ${OpenCV_VERSION})
    include_directories(${OpenCV_INCLUDE_DIRS})
    add_executable(webcam pantilt/webcam.cpp)
    target_link_libraries(webcam ${OpenCV_LIBS})
endif(OpenCV_FOUND)


#if(CUDA_FOUND)
#    message("CUDA version: " ${CUDA_VERSION})
#    cuda_add_executable(matadd cuda/matadd.cu)
#endif(CUDA_FOUND)


add_library(motion pantilt/motion.cpp)
# if SHARED : cmake -DBUILD_SHARED_LIBS=ON ..
add_executable(pantilt pantilt/pantilt.cpp)
target_link_libraries(pantilt motion)
