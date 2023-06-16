cmake_minimum_required(VERSION 3.24)
project(Miniature_assembly_machine_simulatior C)

set(CMAKE_C_STANDARD 11)

add_executable(Miniature_assembly_machine_simulatior assemble.c assemble.h run.c run.h)
