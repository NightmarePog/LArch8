cmake_minimum_required(VERSION 3.15)

project(CustomAssemblerProject VERSION 1.0 LANGUAGES C)

# --- Standard a kompilátor ---
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

# --- Hlavní program ---
add_executable(${PROJECT_NAME}
    src/assembler/main.c
    src/assembler/addr_translation.c
    src/assembler/file_processer.c
    src/assembler/precompiler.c
    src/assembler/checks.c
    src/assembler/translator.c
    src/assembler/assembler_words.c
)

# --- Testy ---
# Najde všechny .c soubory v tests/tests/
file(GLOB TEST_SRC "tests/tests/*.c")

add_executable(run_tests
    ${TEST_SRC}
    src/assembler/addr_translation.c
    src/assembler/file_processer.c
    src/assembler/precompiler.c
    src/assembler/checks.c
    src/assembler/translator.c
    src/assembler/assembler_words.c
    thirdparty/Unity/src/unity.c
)

target_include_directories(run_tests PRIVATE
    include
    thirdparty/Unity/src
)

# --- Povolit testování ---
enable_testing()
add_test(NAME assembler_test COMMAND run_tests)
