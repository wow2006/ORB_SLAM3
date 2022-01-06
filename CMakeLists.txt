# This cmake is a modified version of https://github.com/forexample/package-example/blob/master/Foo/CMakeLists.txt
cmake_minimum_required(VERSION 3.18)
project(ORB_SLAM3 VERSION 1.0.0 LANGUAGES CXX)

#list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
###############################     Project Var   ############################################
set(library_name ${PROJECT_NAME})
set(library_alias_name ${PROJECT_NAME}::${PROJECT_NAME})
set(library_output_dir ${CMAKE_CURRENT_BINARY_DIR}/bin)
###############################     Project Var   ############################################

###############################      Option      #############################################
option(BUILD_EXAMPLES       "Build Examples"          ON)
option(BUILD_TOOLS          "Build Tools"             OFF)
###############################      Option      #############################################

###############################     Packages     #############################################
find_package(OpenCV CONFIG REQUIRED COMPONENTS core imgproc imgcodecs highgui features2d calib3d) # opencv_core opencv_img_codecs
find_package(Eigen3 CONFIG REQUIRED) # Eigen3::Eigen
find_package(Pangolin CONFIG REQUIRED) # pangolin
find_package(Boost REQUIRED COMPONENTS serialization) # serialization
find_package(OpenSSL REQUIRED) # crypto
find_package(project-settings CONFIG REQUIRED)

# Thirdparty packages
add_subdirectory(Thirdparty/g2o)
add_subdirectory(Thirdparty/DBoW2)
add_subdirectory(Thirdparty/Sophus)
###############################     Packages     #############################################

###############################     ORB-SLAM     #############################################
add_library(${library_name} STATIC)

add_library(${library_alias_name} ALIAS ${library_name})

target_sources(${library_name}
               PRIVATE
               src/Atlas.cc
               src/Config.cc
               src/Converter.cc
               src/Frame.cc
               src/FrameDrawer.cc
               src/G2oTypes.cc
               src/GeometricTools.cc
               src/ImuTypes.cc
               src/KeyFrame.cc
               src/KeyFrameDatabase.cc
               src/LocalMapping.cc
               src/LoopClosing.cc
               src/Map.cc
               src/MapDrawer.cc
               src/MapPoint.cc
               src/MLPnPsolver.cpp
               src/OptimizableTypes.cpp
               src/Optimizer.cc
               src/ORBextractor.cc
               src/ORBmatcher.cc
               src/Settings.cc
               src/Sim3Solver.cc
               src/System.cc
               src/Tracking.cc
               src/TwoViewReconstruction.cc
               src/Viewer.cc
               src/CameraModels/Pinhole.cpp
               src/CameraModels/KannalaBrandt8.cpp
)

target_include_directories(${library_name}
                           PUBLIC
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/CameraModels>                           )

target_link_libraries(${library_name}
                      PUBLIC
                      Eigen3::Eigen
                      opencv_core
                      opencv_imgproc
                      opencv_imgcodecs
                      opencv_highgui
                      opencv_features2d
                      opencv_calib3d
                      Boost::serialization
                      OpenSSL::Crypto
                      pangolin
                      # ThirdParty
                      ORB_SLAM::DBoW2
                      ORB_SLAM::g2o
                      ORB_SLAM::sophus
                      $<BUILD_INTERFACE:project_warnings>
                      $<BUILD_INTERFACE:project_options>)

target_compile_options(${library_name}
                       PRIVATE
                       $<$<CXX_COMPILER_ID:MSVC>:/bigobj>)

target_compile_definitions(${library_name} PUBLIC COMPILEDWITHC11)

set_target_properties(${library_name} PROPERTIES POSITION_INDEPENDENT_CODE ON)
###############################     ORB-SLAM     #############################################
if(BUILD_EXAMPLES)
add_subdirectory(Examples)
endif()

if(BUILD_TOOLS)
add_subdirectory(tools)
endif()
###############################      INSTALL      ############################################
set(config_install_dir "${CMAKE_INSTALL_LIBDIR}/cmake/${library_name}")

set(generated_dir "${CMAKE_CURRENT_BINARY_DIR}/generated")

# Configuration
set(version_config "${generated_dir}/${library_name}ConfigVersion.cmake")
set(project_config "${generated_dir}/${library_name}Config.cmake")
set(TARGETS_EXPORT_NAME "${library_name}Targets")
set(namespace "${library_name}::")

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "${version_config}" COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    "${library_name}Config.cmake.in"
    "${project_config}"
    INSTALL_DESTINATION "${config_install_dir}"
)

install(
    TARGETS ${library_name} DBoW2 g2o
    EXPORT "${TARGETS_EXPORT_NAME}"
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

# Headers:
install (DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/" DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

install(
    FILES "${project_config}" "${version_config}"
    DESTINATION "${config_install_dir}"
)

install(
    EXPORT "${TARGETS_EXPORT_NAME}"
    NAMESPACE "${namespace}"
    DESTINATION "${config_install_dir}"
)
###############################      INSTALL      ############################################
include(FeatureSummary)
feature_summary(WHAT ALL)
