cmake_minimum_required(VERSION 3.31.5)
project(SDL3Vulkan_Engine_prot)

set(SDL_TEST OFF)

set(GLM_BUILD_LIBRARY OFF CACHE BOOL "" FORCE)
set(GLM_TEST_ENABLE OFF CACHE BOOL "" FORCE)

find_package(Vulkan REQUIRED)

add_library(${PROJECT_NAME} STATIC)
file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS
    src/*.cpp
    src/*.h
)
target_sources(${PROJECT_NAME} PRIVATE ${ENGINE_SOURCES})

add_subdirectory(vendor/SDL)
add_subdirectory(vendor/SDL_image)
add_subdirectory(vendor/SDL_ttf)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    #PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/SDL/include
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/SDL_image/include
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/SDL_ttf/include
)

include(FetchContent)
FetchContent_Declare(
	glm
	GIT_REPOSITORY "https://github.com/g-truc/glm.git"
	GIT_TAG "1.0.1"
	GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(glm)

FetchContent_Declare(
	microsoft-gsl
	GIT_REPOSITORY "https://github.com/microsoft/GSL.git"
	GIT_TAG "v4.2.0"
	GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(microsoft-gsl)

target_link_libraries(${PROJECT_NAME} PRIVATE Vulkan::Vulkan)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3_image::SDL3_image SDL3::SDL3)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3_ttf::SDL3_ttf SDL3::SDL3)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)
target_link_libraries(${PROJECT_NAME} PRIVATE Microsoft.GSL::GSL)