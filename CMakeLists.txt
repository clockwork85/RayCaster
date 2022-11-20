cmake_minimum_required(VERSION 3.23)
project(RayCaster)

set(CMAKE_CXX_STANDARD 17)

#add_subdirectory(lib)
# include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0)
FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()

FetchContent_Declare(
        Eigen
        GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
        GIT_TAG master
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
        )
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(BUILD_TESTING OFF)
set(EIGEN_BUILD_PKGCONFIG OFF)
FetchContent_MakeAvailable(Eigen)

add_library(MathUtils STATIC MathUtils.cpp MathUtils.h)
target_link_libraries(MathUtils Eigen3::Eigen)
add_library(Canvas STATIC Canvas.cpp Canvas.h Color.h)
target_link_libraries(Canvas MathUtils)
add_library(Ray STATIC RayCaster.cpp RayCaster.h Sphere.h)
target_link_libraries(Ray MathUtils Eigen3::Eigen)
add_library(Transform STATIC Transform.cpp Transform.h)
target_link_libraries(Transform MathUtils Eigen3::Eigen)
add_library(Color STATIC Color.h Color.cpp)
target_link_libraries(Color MathUtils Eigen3::Eigen)
add_library(Lights STATIC Lights.h Lights.cpp)
target_link_libraries(Lights MathUtils Color Eigen3::Eigen)

add_executable(RayCaster main.cpp)
target_link_libraries(RayCaster MathUtils Canvas Ray Eigen3::Eigen)

add_executable(RayCasterTest test.cpp Material.h)
target_link_libraries(RayCasterTest gtest gtest_main gmock gmock_main MathUtils Canvas Ray Transform Lights Eigen3::Eigen)
