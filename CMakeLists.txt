cmake_minimum_required(VERSION 3.21)

project(MyProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/collection.h
    src/list.h
    src/vector.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics)

if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}> $<TARGET_FILE_DIR:${PROJECT_NAME}> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS ${PROJECT_NAME})
