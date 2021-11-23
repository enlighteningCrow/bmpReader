# execute_process(COMMAND echo --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=${PROJECT_SOURCE_DIR}/valgrind-out.txt ${PROJECT_BINARY_DIR}/${PROJECT_NAME})
cmake_minimum_required(VERSION 3.0.0)
project(bmpReader VERSION 0.1.0)

# set_property(TARGET bmpReader PROPERTY C_STANDARD 11)
set(C_STANDARD 17)

include(CTest)
enable_testing()

# add_compile_definitions("-Wall -Wextra -ggdb3")

# SET(GCC_COVERAGE_COMPILE_FALGS )
add_compile_options(-Wall -Wextra -ggdb3)
add_executable(bmpReader main.c pixel.c utils.c utils_pix.c bmp.c parse.c write_bmp.c utils_cptr.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

execute_process(COMMAND echo valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=${PROJECT_SOURCE_DIR}/valgrind-out.txt ${PROJECT_BINARY_DIR}/${PROJECT_NAME})