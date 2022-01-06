cmake_minimum_required(VERSION 3.18)

project(ORB_SLAM3_RGBD)

add_executable(rgbd_tum rgbd_tum.cc)
target_link_libraries(rgbd_tum PRIVATE ORB_SLAM3::ORB_SLAM3)

find_package(realsense2)

if(realsense2_FOUND)
    add_executable(rgbd_realsense_D435i rgbd_realsense_D435i.cc)
    target_link_libraries(rgbd_realsense_D435i PRIVATE ORB_SLAM3::ORB_SLAM3 ${realsense2_LIBRARY})
    target_include_directories(rgbd_realsense_D435i PRIVATE ${realsense_INCLUDE_DIR})
endif()