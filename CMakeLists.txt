cmake_minimum_required(VERSION 3.0)

set(CMAKE_C_COMPILER /usr/bin/clang)
set(CMAKE_CXX_COMPILER /usr/bin/clang++)

project(Lox-CPP VERSION 1.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(src)

add_executable(
    app

    "src/main.cpp"
    "src/scanner.cpp"
    "src/token.cpp"
    "src/error_handling.cpp"
    "src/keywords.cpp"
    "src/ast_printer.cpp"
    "src/expr.cpp"
    #add_file
)

# add_executable(
#     exprtest

#     "src/test/test_expr.cpp"
#     "src/token.cpp"
#     "src/ast_printer.cpp"
#     "src/expr.cpp"
# )


set_property(TARGET app PROPERTY CXX_STANDARD 17)
# set_property(TARGET exprtest PROPERTY CXX_STANDARD 17)

# target_link_libraries(cppopengl glfw)
# target_link_libraries(cppopengl glad)
# target_link_libraries(cppopengl spdlog)

# file(COPY assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
