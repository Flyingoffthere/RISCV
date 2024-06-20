cmake_minimum_required(VERSION 3.28)
project(RISCV)

set(CMAKE_CXX_STANDARD 20)
find_package(Catch2 3 REQUIRED)
add_executable(
        tests
        tests/test.cpp
        include/signal.hpp
        include/instruction_memory.hpp
        include/datapool.hpp
        src/instruction_memory.cpp
        include/main_memory.hpp
        src/main_memory.cpp
        include/register_file.hpp
        src/register_file.cpp
        include/alu.hpp
        src/alu.cpp
        include/controller.hpp
        src/controller.cpp
)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
add_executable(RISCV main.cpp
        tests/test.cpp
        include/signal.hpp
        include/communication.hpp
        include/instruction_memory.hpp
        include/datapool.hpp
        src/instruction_memory.cpp
        include/main_memory.hpp
        src/main_memory.cpp
        include/register_file.hpp
        src/register_file.cpp
        include/alu.hpp
        src/alu.cpp
        include/controller.hpp
        src/controller.cpp
)
