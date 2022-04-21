cmake_minimum_required(VERSION 3.18)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include("cmake/HunterGate.cmake")

HunterGate(
        URL "https://github.com/cpp-pm/hunter/archive/v0.23.314.tar.gz"
        SHA1 "95c47c92f68edb091b5d6d18924baabe02a6962a"
)

project(fib)

hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)

set(config_bin "lib/cmake/${PROJECT_NAME}")
set(generated_dir "${CMAKE_CURRENT_BINARY_DIR}/generated")
set(project_config "${generated_dir}/${PROJECT_NAME}Config.cmake")
set(TARGETS_EXPORT_NAME "${PROJECT_NAME}")

add_library(${PROJECT_NAME} STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/fib.cpp
        )

target_include_directories(${PROJECT_NAME} PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:include>"
        )

add_executable(tests ${CMAKE_CURRENT_SOURCE_DIR}/tests/test.cpp)
target_link_libraries(tests ${PROJECT_NAME} GTest::gtest_main)
enable_testing()
add_test(NAME unit_tests COMMAND tests)

include(CMakePackageConfigHelpers)

configure_package_config_file (
        "cmake/Config.cmake.in"
        "${project_config}"
        INSTALL_DESTINATION "${config_bin}"
)

install(TARGETS ${PROJECT_NAME}
        EXPORT ${TARGETS_EXPORT_NAME}
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION "include"
        )

install(
        FILES "include/fib.hpp"
        DESTINATION "include"
)

install(EXPORT "${TARGETS_EXPORT_NAME}"
        FILE "${TARGETS_EXPORT_NAME}.cmake"
        DESTINATION "${config_bin}")

install(FILES "${project_config}"
        DESTINATION "${config_bin}")

install(TARGETS tests
        RUNTIME DESTINATION bin)
