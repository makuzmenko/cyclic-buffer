# CMakeList.txt: проект CMake для danfoss_test; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

if(TARGET !cyclic_buffer) # To avoid diamond dependencies; may not be necessary depending on you project.
    return()
endif()

# Добавьте источник в исполняемый файл этого проекта.
add_executable (cyclic_buffer "tests.cpp" "tests.h" "cyclic_buffer.h")
target_compile_features(cyclic_buffer PRIVATE cxx_std_17)
target_link_libraries(cyclic_buffer gtest gtest_main)
add_dependencies(cyclic_buffer gtest)
add_dependencies(cyclic_buffer gtest_main)
# TODO: Добавьте тесты и целевые объекты, если это необходимо.
