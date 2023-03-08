cmake_minimum_required(VERSION 3.23)
project(Tanks)

set(CMAKE_CXX_STANDARD 17)

add_executable(Tanks Tanks.cpp)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)


target_link_libraries(Tanks PRIVATE sfml-graphics)
target_compile_features(Tanks PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET Tanks POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:Tanks> $<TARGET_FILE_DIR:Tanks> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS Tanks)