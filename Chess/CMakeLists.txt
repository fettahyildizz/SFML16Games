cmake_minimum_required(VERSION 3.16)
project(Chess LANGUAGES CXX)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

set(CMAKE_DEBUG_POSTFIX d)
set(CMAKE_EXPORT_COMPILE_COMMANDS On)

include_directories(include)

add_library(Utils src/chess/utils.cpp)
target_link_libraries(Utils sfml-graphics sfml-window)

add_library(Pieces src/chess/pieces.cpp)
target_link_libraries(Pieces sfml-graphics sfml-window)

add_executable(Chess src/main.cpp)
set_target_properties(Chess PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
target_link_libraries(Chess Utils Pieces sfml-graphics sfml-window sfml-system)
target_compile_features(Chess PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET CMakeSFMLProject
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:CMakeSFMLProject>
        VERBATIM)
endif()

install(TARGETS Chess)