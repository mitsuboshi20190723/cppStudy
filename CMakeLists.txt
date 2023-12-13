cmake_minimum_required(VERSION 2.8)

project(cppStudy)

find_package(OpenCV REQUIRED)
find_package(CUDA REQUIRED)


add_executable(hw hello_world/hw.cpp)


add_executable(perceptron math/perceptron.cpp)


add_executable(ffer math/ffer.cpp)


#add_executable(joynics2 serial/joynics2.cpp)


add_executable(kservo serial/kservo.c)


add_library(motion pantilt/motion.cpp) # if SHARED : cmake -DBUILD_SHARED_LIBS=ON ..
add_executable(pantilt4axis pantilt/pantilt4axis.cpp)
target_link_libraries(pantilt4axis motion)



if(OpenCV_FOUND)
    message("OpenCV version: " ${OpenCV_VERSION})
    include_directories(${OpenCV_INCLUDE_DIRS})


    add_executable(raspicam serial/raspicam.cpp)
    target_link_libraries(raspicam ${OpenCV_LIBS})


#    add_executable(fd math/fd.cpp)
#    target_link_libraries(fd dlib ${OpenCV_LIBS})


#    add_library(motion pantilt/motion.cpp)
#    add_executable(pantilt pantilt/pantilt.cpp)
#    target_link_libraries(pantilt motion ${OpenCV_LIBS})

endif(OpenCV_FOUND)



if(CUDA_FOUND)
    message("CUDA version: " ${CUDA_VERSION})


    cuda_add_executable(matmul cuda/matmul.cu)
 
 
    cuda_add_executable(hfd cuda/hfd.cu)

endif(CUDA_FOUND)



if(OpenCV_FOUND AND CUDA_FOUND)
    message("depend OpenCV and CUDA")


    cuda_add_executable(face_detect cuda/face_detect.cpp)
    target_link_libraries(face_detect dlib ${OpenCV_LIBS})
 
 
    cuda_add_executable(webcamera cuda/webcamera.cpp)
    target_link_libraries(webcamera ${OpenCV_LIBS})

endif(OpenCV_FOUND AND CUDA_FOUND)

