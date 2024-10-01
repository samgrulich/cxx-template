file(GLOB_RECURSE SOURCES "./*.cpp" "./*.h" "./*.hpp")

add_library(main ${SOURCES})

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE cxx_setup main)


