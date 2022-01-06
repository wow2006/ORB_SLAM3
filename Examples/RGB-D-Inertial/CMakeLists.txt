cmake_minimum_required(VERSION 3.18)

project(ORB_SLAM3_RGBD)

find_package(realsense2)

if(realsense2_FOUND)
    add_executable(rgbd_inertial_realsense_D435i rgbd_inertial_realsense_D435i.cc)
    target_link_libraries(rgbd_inertial_realsense_D435i PRIVATE ORB_SLAM3::ORB_SLAM3 ${realsense2_LIBRARY})
    target_include_directories(rgbd_inertial_realsense_D435i PRIVATE ${realsense_INCLUDE_DIR})
endif()