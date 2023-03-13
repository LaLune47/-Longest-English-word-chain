cmake_minimum_required(VERSION 3.0.2)

add_subdirectory(core)
add_executable(Wordlist Wordlist.cpp ArgParser.cpp)

target_link_libraries(Wordlist
        PRIVATE ${LIBRARY_OUTPUT_PATH}/libCore.dll
        )