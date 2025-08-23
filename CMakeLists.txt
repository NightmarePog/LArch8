cmake_minimum_required(VERSION 3.15)

project(CustomAssemblerProject VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-Wall -Wextra -pedantic)

add_executable(${PROJECT_NAME}
    src/assembler/main.c
    src/assembler/precompiler.c
    src/assembler/tokenization_and_parser.c
)

target_include_directories(${PROJECT_NAME} PRIVATE include)

# tbh i have no idea how this works...
# i just stole something and hope it works 