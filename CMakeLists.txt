cmake_minimum_required(VERSION 2.8)

project( game )

add_definitions(-std=c++11)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/3rdparts/CMake)


find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

# Pour gérer un bug a la fac, a supprimer sur machine perso:
# set(OPENGL_LIBRARIES /usr/lib/x86_64-linux-gnu/libGL.so.1)


if(APPLE)

	find_package(SDL2 REQUIRED)

	include_directories(${SDL2_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} 3rdparts/glimac/include 3rdparts/glm)

	set(ALL_LIBRARIES glimac ${SDL2_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})

else()

	find_package(SDL REQUIRED)

	include_directories(${SDL_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} 3rdparts/glimac/include 3rdparts/glm)

	set(ALL_LIBRARIES glimac ${SDL_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})

endif()


add_subdirectory(3rdparts/glimac)


file(GLOB SRC_FILES src/*.cpp src/*.hpp shaders/*.glsl)

	
add_executable(game ${SRC_FILES})
target_link_libraries(game ${ALL_LIBRARIES})


file(COPY shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

