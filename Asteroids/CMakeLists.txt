cmake_minimum_required(VERSION 3.16)
project(Asteroids LANGUAGES CXX)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS On)

include_directories(include)

add_library(Animation src/asteroids/animation.cpp)
target_link_libraries(Animation sfml-graphics)

add_library(Explosion src/asteroids/explosion.cpp)
target_link_libraries(Explosion Animation sfml-graphics)

add_library(Rock src/asteroids/rock.cpp)
target_link_libraries(Rock Animation sfml-graphics)

add_library(Bullet src/asteroids/bullet.cpp)
target_link_libraries(Bullet Animation sfml-graphics)

add_library(Spaceship src/asteroids/spaceship.cpp)
target_link_libraries(Spaceship Animation sfml-graphics)

add_executable(Asteroids src/main.cpp)
target_link_libraries(Asteroids Explosion Spaceship Rock Bullet sfml-window sfml-system)
target_compile_features(Asteroids PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET CMakeSFMLProject
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:CMakeSFMLProject>
        VERBATIM)
endif()

install(TARGETS Asteroids)