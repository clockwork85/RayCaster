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

FetchContent_Declare(
        assimp
        GIT_REPOSITORY https://github.com/assimp/assimp.git
        GIT_TAG master)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_INJECT_DEBUG_POSTFIX OFF CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(assimp)

set(CMAKE_CXX_FLAGS "-O3")

add_executable(RayCaster
        main.cpp

        # Headers
        Canvas.h
        Color.h
        Lights.h
        MathUtils.h
        Mesh.h
        Pattern.h
        RayCaster.h
        Sphere.h
        Shape.h

        # Sources
        Canvas.cpp
        Cylinder.cpp
        Cube.cpp
        Mesh.cpp
        Transform.cpp
        Triangle.cpp
        Sphere.cpp
        RayCaster.cpp
        MathUtils.cpp
        World.cpp
        SmoothTriangle.cpp SmoothTriangle.h MeshSmooth.cpp MeshSmooth.h)
target_link_libraries(RayCaster Eigen3::Eigen assimp)

add_executable(RayCasterTest
        test.cpp

        # Headers
        Camera.h
        Canvas.h
        Color.h
        Lights.h
        MathUtils.h
        Material.h
        RayCaster.h
        Sphere.h
        Transform.h
        World.h
        Shape.h
        Intersection.h
        Ray.h
        Computation.h
        Sphere.cpp
        Plane.h
        Pattern.h

        # Sources
        Canvas.cpp
#        Color.cpp
#        Lights.cpp
        MathUtils.cpp
        RayCaster.cpp
        Transform.cpp
        World.cpp
        Patterns.h Cube.cpp Cube.h Cylinder.cpp Cylinder.h Triangle.cpp Triangle.h Mesh.cpp Mesh.h SmoothTriangle.cpp)
target_link_libraries(RayCasterTest gtest gtest_main Eigen3::Eigen assimp)
