cmake_minimum_required(VERSION 3.15)

project(Assembler&Interpreter_custom VERSION 1.0 LANGUAGES C)

# --- Standard & compiler ---
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")
add_compile_options(-Wall -Wextra -pedantic)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# --- Include dirs ---
include_directories(
    include
    thirdparty/Unity/src
)

# --- assembler ---
add_executable(Assembler
    # ASSEMBLER
    src/assembler/main.c
    src/assembler/addr_translation.c
    src/assembler/parsing.c
    src/assembler/checks.c
    src/assembler/translator.c
    # GLOBALS
    src/words.c
    src/file_processer.c
    src/parsing.c
    
)

# --- interpreter ---
add_executable(Interpreter
    #INTERPRETER
    src/interpreter/main.c
    src/interpreter/parsing.c
    #GLOBALS
    src/parsing.c
    src/words.c
    src/file_processer.c
    src/print.c
)

target_include_directories(Interpreter PRIVATE
    include
)

# --- tests ---
file(GLOB TEST_SRC "tests/tests/*.c")

add_executable(run_tests
    ${TEST_SRC}
    src/assembler/addr_translation.c
    src/assembler/parsing.c
    src/assembler/checks.c
    src/assembler/translator.c

    src/words.c
    src/file_processer.c

    thirdparty/Unity/src/unity.c
    
)

target_include_directories(run_tests PRIVATE
    include
    thirdparty/Unity/src
)

enable_testing()
add_test(NAME assembler_test COMMAND run_tests)
