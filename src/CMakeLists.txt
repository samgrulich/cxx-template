file(GLOB_RECURSE SOURCES "./*.cpp" "./*.h" "./*.hpp")
list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
add_library(main ${SOURCES})

add_executable(${PROJECT_NAME} main.cpp "./main.cpp")
target_link_libraries(${PROJECT_NAME} PRIVATE cxx_setup main)


