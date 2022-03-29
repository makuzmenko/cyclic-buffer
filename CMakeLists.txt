# CMakeList.txt: файл проекта CMake верхнего уровня; проведите глобальную конфигурацию
# и включите сюда подпроекты.
#
cmake_minimum_required (VERSION 3.8)

project ("cyclic_buffer")

enable_testing()

configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download"
)
execute_process(COMMAND "${CMAKE_COMMAND}" --build .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download"
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory("${CMAKE_BINARY_DIR}/googletest-src"
                 "${CMAKE_BINARY_DIR}/googletest-build"
)

include_directories("${CMAKE_BINARY_DIR}/googletest-src/googletest/include" 
                     ${gtest_SOURCE_DIR}
                     "${gtest_SOURCE_DIR}/include")

set(GTEST_INCLUDE_DIR "${CMAKE_BINARY_DIR}/googletest-src/googletest/include")
set(GTEST_LIBRARY "${CMAKE_BINARY_DIR}/lib")
set(GTEST_MAIN_LIBRARY "${CMAKE_BINARY_DIR}/lib")

find_package(GTest REQUIRED)

# Включите подпроекты.

add_subdirectory ("cyclic_buffer")